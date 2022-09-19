let fs = require('fs');
let os = require('os');
let util = require('util');
let stdout = process.stdout;

// コマンドラインオプション
let hexFile = null;
let serialPortName = null;
let serialPortOptions = {
    dataBits: 8,
    stopBits: 1,
    parity: 'none',
};
let flashBaud = 115200;
let userBaud = 115200;
let waitForAck = true;
let goSwitch = false;
let nogoSwitch = false;
let rebootMagic = null;
let rebootDelay = null;
let monitor = false;
let noFast = false;
let goDelay = 0;

// 現在オープンしているシリアルポート
let port;

// シリアルポートモジュール（遅延ロード）
let SerialPort;

// 設定済みの実行時オプション
let fastMode = false;
let willSendGoCommand;

// 指定されたボーレートでシリアルポートを開く。
// 現在違うボーレートでオープンしている場合は、閉じて、再度開く。
async function openSerialPortAsync(baudRate)
{
    // オープン済みか?
    if (port != null)
    {
        // ボーレートは指定されたものと同じか
        if (serialPortOptions.baudRate == baudRate)
            return;

        // 違う場合はポートを閉じる
        await closeSerialPortAsync();
    }

    // シリアルポートモジュールをロードする。ロードできなかった場合は
    // 簡単なメッセージを表示する
    if (!SerialPort)
    {
        try
        {
            SerialPort = require('serialport');
        }
        catch (err)
        {
            console.log(`\nCan't find module 'serialport'.`);
            console.log(`Please run 'npm install' in the flashy script folder:\n`);
            console.log(`   ` + __dirname + `$ npm install`);
            process.exit(7);
        }
    }

    // Windowsの場合は必要に応じてWSLシリアルポート名を同等のポート名に再マップする
    if (os.platform() == 'win32' && serialPortName.startsWith(`/dev/ttyS`))
    {
        let remapped = `COM` + serialPortName.substr(9);
        stdout.write(`Using '${remapped}' instead of WSL port '${serialPortName}'.\n`)
        serialPortName = remapped;
    }

    // オプションを設定する
    serialPortOptions.baudRate = baudRate;

    // ポートを開く
    stdout.write(`Opening ${serialPortName} at ${baudRate}...`)
    port = new SerialPort(serialPortName, serialPortOptions, function(err) {
        if (err)
        {
            fail(`Failed to open serial port: ${err.message}`);
        }
    });
    stdout.write(`ok\n`);
}

// 古い行を捨てる
function discardOldLines(str)
{
    let nlpos = str.lastIndexOf('\n');
    if (str >= 0)
        return str.substr(nlpos)
    else
        return str;
}

// シリアルポートをdrainする
async function drainSerialPortAsync()
{
    // ポートをDrain
    await new Promise((resolve, reject) => {
        port.drain((function(err) {
            if (err)
                reject(err);
            else
                resolve();
        }));
    });
}

// シリアルポートを閉じる（開いていた場合）
async function closeSerialPortAsync()
{
    if (port)
    {
        stdout.write(`Closing serial port...`)

        // Drain
        await drainSerialPortAsync();

        // Close the port
        await new Promise((resolve, reject) => {
            port.close(function(err) {
                if (err)
                    reject(err);
                else
                {
                    resolve();
                }
            });
        });

        stdout.write(`ok\n`);
    }
}

// 書き込み操作の非同期ラッパー。これによりコールバックを扱う必要がなくなる
async function writeSerialPortAsync(data)
{
    return new Promise((resolve,reject) =>
    {
        port.write(data, function(err)
        {
            if (err)
                reject(err);
            else
                resolve();
        });
    });
};

// エラーが無かったかチェック。エラーがあったらプロセスを終了させる
function bootloaderErrorWatcher(data)
{
    let str = data.toString(`utf8`);

    let err = (/#ERR:(.*)\r/gm).exec(str);
    if (err)
    {
        console.error(`\n\nAn error occurred during the transfer: ${err[1]}`);
        process.exit(9);
    }
}

function watchForBootloaderErrors(enable)
{
    // 冗長?
    if (port.listenerEnabled == enable)
        return;
    port.listenerEnabled = enable;

    // リスナーのインストール/削除
    if (enable)
    {
        port.on('data', bootloaderErrorWatcher);
    }
    else
    {
        port.removeListener('data', bootloaderErrorWatcher);
    }
}



// IHEX形式のアスキーテキストをブートローダが理解できるバイナリストリームに変換する
function binary_encoder()
{
    let state = 0;
    let buffer = Buffer.alloc(65536);
    let buffer_used = 0;
    let unsent_nibble = -1;
    let record_bytes_left = -1;

    // 高速flashバッファをFlush
    async function flush()
    {
        if (buffer_used)
        {
            await writeSerialPortAsync(buffer.subarray(0, buffer_used));
            buffer_used = 0;
        }
    }

    // バイトを書き込む
    async function write(inbyte)
    {
        if (state == 0)
        {
            if (inbyte == 0x3a)     // ":"  HEXモードの書き込み開始コマンド
            {
                // バッファをフラッシュするか?
                if (buffer_used > buffer.length - 1024)
                    await flush();

                // 新レコードを開始する
                buffer[buffer_used++] = 0x3d;     // "="   バイナリモードの書き込み開始コマンドに変換
                fast_record_length = -1;
                state = 1;
                record_bytes_left = -1;
                return;
            }
            else
            {
                // 開始コマンド以外は空白のはず
                if (inbyte != 0x20 && inbyte != 0x0A && inbyte != 0x0D)
                {
                    fail("Invalid .hex file, unexpected character outside record");
                }
                return;
            }
        }

        // 入力文字をhexニブルに変換
        let nibble;
        if (inbyte >= 0x30 && inbyte <= 0x39)       // '0' - '9'
            nibble = inbyte - 0x30;
        else if (inbyte >= 0x41 && inbyte <= 0x46)  // 'A' - 'F'
            nibble = inbyte - 0x41 + 0xA;
        else if (inbyte >= 0x61 && inbyte <= 0x66)  // 'a' - 'f'
            nibble = inbyte - 0x61 + 0xA;
        else
            fail("Invalid .hex file, expected hex digit");

        if (state == 1)
        {
            // 第1 hexニブルなので保存
            state = 2;
            unsent_nibble = nibble;
            return;
        }

        if (state == 2)
        {
            // 第2 hexニブルなのでバイトに変換
            let byte = ((unsent_nibble << 4) | nibble);

            // 1バイト書き込む
            buffer[buffer_used++] = byte;

            // レコード長を初期化する
            if (record_bytes_left == -1)        // レコード先頭のbyteはレコード数
                record_bytes_left = byte + 5;   // +5 は ':'+lengh+address(2)+type

            // レコード長を更新してレコードの終わりかチェックする
            record_bytes_left--;
            if (record_bytes_left == 0)
                state = 0;
            else
                state = 1;
        }
    }

    return { flush, write };
}

// リブートマジック文字列を送信する
async function sendRebootMagic()
{
    // シリアルポートを開く
    await openSerialPortAsync(userBaud);

    // 送信する
    stdout.write(`Sending reboot magic '${rebootMagic}'...`)
    await writeSerialPortAsync(rebootMagic);
    stdout.write(`ok\n`);

    // 遅延
    if (rebootDelay)
    {
        stdout.write(`Delaying for ${rebootDelay}ms while rebooting...`);
        await delay(rebootDelay);
        stdout.write(`ok\n`);
    }
}

// hexファイルをデバイスにFlash
async function flashDevice()
{
    // シリアルポートをOpen
    await openSerialPortAsync(flashBaud);

    // リセット信号は256個の0x80文字で構成され、その後にリセット
    // コマンド'R'コマンドが続きます。ここでのアイデアは0x80は
    // 以前にキャンセルされたフラッシュをバイナリレコードの状態から
    // フラッシュすることです。0x80はブートローダがバイナリレコードの
    // 先頭でキャンセルされる場合に使用されます。ブートローダ自体を
    // 台無しにするようなローメモリアドレスを書かないようにするためです。
    let resetBuf = Buffer.alloc(257, 0x80);
    resetBuf[256] = 'R'.charCodeAt(0);

    // デバイスから準備完了のackである`IHEX`が来るのを待つ
    if (waitForAck)
    {
        // リセットコマンドを送信
        // (bootloaderカーネルの最新版が必要）
        stdout.write(`Sending reset command...`);

        // 受信用のリスナーを設定
        let resolveDeviceReady;
        let buf = "";
        port.on('data', function(data) {

            buf += data.toString(`utf8`);
            if (buf.includes(`IHEX`))
            {
                stdout.write(`ok\n`);

                if (!noFast)
                {
                    // デバイスがIHEX-Fと応答したら高速ブートローダ
                    // なのでコマンドラインスイッチで無効になって
                    // いない限り高速モードに切り替える
                    if (buf.includes(`IHEX-F`))
                    {
                        stdout.write("Fast mode enabled\n");
                        fastMode = true;
                    }
                }

                if (resolveDeviceReady)
                    resolveDeviceReady();
            }
            buf = discardOldLines(buf);

        });

        // リセットコマンドを送信
        await writeSerialPortAsync(resetBuf);

        // リセットをセット
        stdout.write(`ok\n`);
        stdout.write(`Waiting for device...`);

        // 受信を待つ
        await new Promise((resolve, reject) => {
            resolveDeviceReady = resolve;
        });
        port.removeAllListeners('data');

        // デバイスが正しい状態になったのでエラーがないか調べる
        watchForBootloaderErrors(true);
    }
    else
    {
        // リセットコマンドを送信
        await writeSerialPortAsync(resetBuf);
    }

    // 高速書き込み用のバイナリエンコーダを作成
    let binenc = fastMode ? binary_encoder() : null;

    // デバイスにコピー
    let startTime = new Date().getTime();
    stdout.write(`Sending`);
    let fd = fs.openSync(hexFile, `r`);
    let buf = Buffer.alloc(4096);
    while (true)
    {
        // hexファイルから読み込む
        let bytesRead = fs.readSync(fd, buf, 0, buf.length);
        if (bytesRead == 0)
            break;

        if (fastMode)
        {
            // 高速モードの場合、各バイトをバイナリエンコーダに書き込む
            for (let i=0; i<bytesRead; i++)
            {
                await binenc.write(buf[i]);
            }
        }
        else
        {
            // 高速モードでない場合は、シリアルポートに直接書き込む
            await writeSerialPortAsync(buf.subarray(0, bytesRead));
        }
        stdout.write(`.`);
    }
    fs.closeSync(fd);

    // 高速flashバッファをFlush
    if (fastMode)
    {
        binenc.flush();
    }

    // 保留中のエラーを待つ
    // （これからgoコマンドを送信する場合はackedされる前に
    //   エラーが検出されるのでここで待つ必要はない）
    if (waitForAck && !willSendGoCommand)
    {
        // すべてが送信されるのを待つ
        await drainSerialPortAsync();

        // ブートローダから保留中エラーがある場合に備えて少し遅延させる
        await delay(10);
        port.removeAllListeners('data');
    }

    // 完了
    stdout.write(`ok\n`);

    // 実行時間をログ出力
    let elapsedTime = new Date().getTime() - startTime;
    stdout.write(`Finished in ${((elapsedTime / 1000).toFixed(1))} seconds.\n`);
}


// goコマンドを送信してackを待つ
async function sendGoCommand()
{
    // シリアルポートを開く
    await openSerialPortAsync(flashBaud);

    // 送信する
    stdout.write(`Sending go command...`)

    // 開始遅延をセット
    if (goDelay)
    {
        await writeSerialPortAsync(`s${(goDelay*1000).toString(16).toUpperCase()}\n`);
    }

    // デバイスがgoコマンドを受信したことを示す`--`を受信するまで待つ
    if (waitForAck)
    {
        // 受信リスナーをセットアップ
        let resolveAck;
        let buf = "";
        port.on('data', function(data) {

            buf += data.toString(`utf8`);
            if (buf.includes(`\r--\r\n\n`))
            {
                stdout.write(`ok\n`);
                resolveAck();
            }
            buf = discardOldLines(buf);


        });

        // エラーウォッチを有効化
        watchForBootloaderErrors(true);

        // コマンドを送信する
        await writeSerialPortAsync('g');

        // ackを待つ
        await new Promise((resolve, reject) => {
            resolveAck = resolve;
        });
        port.removeAllListeners('data');
    }
    else
    {
        await writeSerialPortAsync('g');
        stdout.write(`ok\n`);
    }
}

// シリアルモニタを開始する
async function startMonitor()
{
    // シリアルポートを開く
    await openSerialPortAsync(userBaud);

    // ブートローダは実行していないはずなのでエラーウォッチャを削除する
    watchForBootloaderErrors(false);

    stdout.write("Monitoring....\n");

    // 受信リスナーをセットアップ
    let resolveDeviceReady;
    port.removeAllListeners('data');
    port.on('data', function(data) {

        var str = data.toString(`utf8`);
        stdout.write(str);
    });

    // 生き続けるために配送されないprmiseを待ち続ける
    await new Promise((resolve) => { });
}

// 非同期遅延ヘルパー
async function delay(period)
{
    return new Promise((resolve) => {
        setTimeout(resolve, period);
    })
}

// ヘルプを表示する
function showHelp()
{
    console.log(`Usage: node flashy <serialport> [<hexfile>] [options]`);
    console.log(`All-In-One Reboot, Flash and Monitor Tool`);
    console.log(``);
    console.log(`<serialport>       Serial port to write to`);
    console.log(`<hexfile>          The .hex file to write (optional)`);
    console.log(`--flashbaud:<N>    Baud rate for flashing (default=115200)`);
    console.log(`--userbaud:<N>     Baud rate for monitor and reboot magic (default=115200)`);
    console.log(`--noack            Send without checking if device is ready`);
    console.log(`--fast             Force fast mode flash`);
    console.log(`--nofast           Disable fast mode`);
    console.log(`--nogo             Don't send the go command after flashing`);
    console.log(`--go               Send the go command, even if not flashing`);
    console.log(`--godelay:<ms>     Sets a delay period for the go command`);
    console.log(`--reboot:<magic>   Sends a magic reboot string at user baud before flashing`);
    console.log(`--rebootdelay:<ms> Delay after sending reboot magic`);
    console.log(`--monitor          Monitor serial port`);
    console.log(`--help             Show this help`);
}

// メッセージを表示してアボート
function fail(msg)
{
    console.error(msg);
    console.error(`Run with --help for instructions`);
    process.exit(7);
}

// コマンドライン引数をパース
function parseCommandLine()
{
    for (let i=2; i<process.argv.length; i++)
    {
        let arg = process.argv[i];
        if (arg.startsWith(`--`))
        {
            let parts = arg.substr(2).split(':');
            let sw = parts[0];
            let value = parts[1];
            switch (sw.toLowerCase())
            {
                case `flashbaud`:
                    flashBaud = Number(value);
                    break;

                case `noack`:
                    waitForAck = false;
                    break;

                case `help`:
                    showHelp();
                    process.exit(0);

                case `nogo`:
                    nogoSwitch = true;
                    break;

                case `go`:
                    goSwitch = true;
                    break;

                case `godelay`:
                    goDelay = Number(value);
                    break;

                case `reboot`:
                    rebootMagic = value;
                    break;

                case `rebootdelay`:
                    rebootDelay = Number(value);
                    break;

                case `monitor`:
                    monitor = true;
                    break;

                case `userbaud`:
                    userBaud = Number(value);
                    break;

                case `fast`:
                    fastMode = true;
                    break;

                case `nofast`:
                    noFast = true;
                    break;

                default:
                    fail(`Unknown switch --${sw}`);
            }
        }
        else
        {
            // 第1引数はシリアルポート名
            if (serialPortName == null)
            {
                serialPortName = arg;
                continue;
            }
            else if (hexFile == null)
            {
                // 第2引数は .hex ファイル
                hexFile = arg;

                // サニティチェック
                if (!arg.toLowerCase().endsWith('.hex'))
                {
                    console.error(`Warning: hex file '${arg}' doesn't have .hex extension.`);
                }
            }
            else
            {
                fail(`Too many command line args: '${arg}'`);
            }
        }
    }

    // シリアルポートなしでは何もできない
    if (!serialPortName)
        fail(`No serial port specified`);
}


// 非同期に実行
(async function()
{
    // コマンドラインのパース
    parseCommandLine();

    willSendGoCommand = (hexFile && !nogoSwitch) || (!hexFile && goSwitch);

    // リブート
    if (rebootMagic)
        await sendRebootMagic();

    // フラッシュ
    if (hexFile)
        await flashDevice();

    // Go
    if (willSendGoCommand)
        await sendGoCommand();

    // モニター
    if (monitor)
        await startMonitor();

    // 終了
    await closeSerialPortAsync();
    stdout.write(`Done!\n`);
})();
