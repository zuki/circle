# サンプル 03: screentext

最初にLEDを5回点滅させ、イメージが正しく読み込まれたことを示します。
次に、画面に文字セットを書き込みます。さらに、画面またはUARTにログ
メッセージを書き込みます。0x100にあるATAG構造体の開始バイトを
debug_hexdump()します。assert()とスタックトレースの使用法を示します。

SD(HC)カードに次のようなcmdline.txtを作成し、フレームバッファのサイズを
変更することができます。

```
width=640 height=480
```

同じファイルに以下のオプションを追加することでロギング機能を制御できます
（同じ行に追加してください）。

```
logdev=ttyS1 loglevel=4
```

(これによりログメッセージはUARTに書き込まれるようになります。デフォルトは
画面("tty1")、loglevelは生成するメッセージの量を制御します（0: パニックのみ、
1: +エラー、2: +警告、3: +通知、4: *デバッグ出力も(デフォルト))

### 実行結果

#### 1. bootloaderを使わない

```
$ make
$ vi cmdline.txt
$ cp kernel8.img cmdline.txt /Volume/boot
$ minicom

## ここでRaspiの電源オン

logger: Circle 44.5 started on Raspberry Pi 3 Model B+ (AArch64)
kernel: Compile time: Sep 17 2022 10:33:30
kernel: Dumping the start of the ATAGS
kernel: Dumping 0x80 bytes starting at 0x100
kernel: 0100: 05 00 00 00 01 00 41 54-00 00 00 00 00 00 00 00
kernel: 0110: 00 00 00 00 04 00 00 00-02 00 41 54 00 00 40 3B
kernel: 0120: 00 00 00 00 5C 00 00 00-09 00 41 54 62 63 6D 32
kernel: 0130: 37 30 38 5F 66 62 2E 66-62 77 69 64 74 68 3D 36
kernel: 0140: 35 36 20 62 63 6D 32 37-30 38 5F 66 62 2E 66 62
kernel: 0150: 68 65 69 67 68 74 3D 34-31 36 20 62 63 6D 32 37
kernel: 0160: 30 38 5F 66 62 2E 66 62-73 77 61 70 3D 31 20 64
kernel: 0170: 6D 61 2E 64 6D 61 63 68-61 6E 73 3D 30 78 37 66
kernel: The following assertion will fail
kernel.cpp(91): stack[1] is 0x80AEC
kernel.cpp(91): stack[11] is 0x80830
kernel.cpp(91): stack[25] is 0x86F38
kernel.cpp(91): assertion failed: 1 == 2
```

#### 2. bootloaderを使う

```
$ cp tools/bootlader/kernel8.img /Volume/boot
$ cp cmdline.txt /Volume/boot
$ make flash

node ../../tools/flashy/flashy.js \
		/dev/cu.usbserial-AI057C9L \
		--flashBaud:115200 \
		--userBaud:115200 \
		--reboot:reboot_rpi \
		 \
		kernel8.hex
Opening /dev/cu.usbserial-AI057C9L at 115200...ok
Sending reboot magic 'reboot_rpi'...ok
Sending reset command...ok
Waiting for device...ok
Fast mode enabled
Sending.........................................ok
Finished in 4.3 seconds.
Sending go command...ok
Closing serial port...ok
Done!
$ minicom       # すぐに（LEDが店頭している間に）minicomを立ち上げる

logger: Circle 44.5 started on Raspberry Pi 3 Model B+ (AArch64)
kernel: Compile time: Sep 17 2022 10:33:30
kernel: Dumping the start of the ATAGS
kernel: Dumping 0x80 bytes starting at 0x100
kernel: 0100: 05 00 00 00 01 00 41 54-00 00 00 00 00 00 00 00
kernel: 0110: 00 00 00 00 04 00 00 00-02 00 41 54 00 00 40 3B
kernel: 0120: 00 00 00 00 5C 00 00 00-09 00 41 54 62 63 6D 32
kernel: 0130: 37 30 38 5F 66 62 2E 66-62 77 69 64 74 68 3D 36
kernel: 0140: 35 36 20 62 63 6D 32 37-30 38 5F 66 62 2E 66 62
kernel: 0150: 68 65 69 67 68 74 3D 34-31 36 20 62 63 6D 32 37
kernel: 0160: 30 38 5F 66 62 2E 66 62-73 77 61 70 3D 31 20 64
kernel: 0170: 6D 61 2E 64 6D 61 63 68-61 6E 73 3D 30 78 37 66
kernel: The following assertion will fail
kernel.cpp(91): stack[1] is 0x80AEC
kernel.cpp(91): stack[11] is 0x80830
kernel.cpp(91): stack[25] is 0x86F38
kernel.cpp(91): assertion failed: 1 == 2
```
