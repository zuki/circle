# サンプル一覧

| サンプル名  |  説明                                          |
|------------|-------------------------------------------------|
| 01-gpiosimple | シンプルなGPIOの使用例。Act LEDを点滅させる |
| 02-screenpixel | スクリーンにピクセルをセットする |
| [03-screentext](doc/03-screentext.md) | テキストをスクリーンに書き出す。debug_hexdump()とアサートの使用法を示す |
| 04-timer | タイマーによる割り込み。例外ハンドラのデモ |
| 05-usbsimple | ルートハブのUSBデバイスディスクリプタを表示する |
| 06-ethernet | Ehternetからブロードキャストを受信する |
| [07-usbstorage](doc/07-usbstorage.md) | MBR（マスターブートレコード）からパーティションテーブルを表示する |
| 08-usbkeyboard | **[PnP]** タイプした文字スクリーンにエコーする（またはキーボードrawモード） |
| 09-softserial | GPIO割り込みのデモ。非UARTのGPIOピン経由のシリアルインタフェース |
| [10-usbmouse](doc/10-usbmouse) | **[PnP]** USBマウスをサポートした小さなペイントプログラム |
| 11-gpioclock | GPIOクロック0を使って方形波信号を生成し、この信号をサンプリングして表示する |
| 12-pwmsound | PWMデバイスとDMAコントローラを使って短いサウンドサンプルを演奏する |
| 13-pwmoutput | PMWデバイスを使って、接続されたLEDの明るさを連続的に変化させる |
| 14-usbprinter | テキストを何行かUSBプリンタに印刷する（GDIプリンタは動かない） |
| 15-files | 接続されたUSBドライブのルートディレクトリをリストする。ファイル"circle.txt"を書き出して読み込む |
| 16-i2cping | I2C経由で接続された2つのRaspberry Pi間でデータブロックを転送する |
| 17-fractal | マンデルブローセットからフラクタル画像を表示する（シングルコアとマルチコアでビルド可能） |
| [18-ntptime](doc/18-ntptime.md) | **[PnP]** インターネット時刻サーバ（NTP）からシステムタイムを設定する。ブートタイムを削減する |
| 19-tasks | 協調型非プリエンプティブスケジューラのデモ |
| 20-tcpsimple | シンプルなTCPエコーサーバ |
| [21-webserver](doc/21-webserver.md) | Act LEDを制御するシンプルなHTTPWebサーバ |
| 23-spisimple | SPIスレーブデバイスとの間でデータを送受信する。受信したデータをダンプする |
| 24-hwrandom | ハードウェア乱数生成器のデモ |
| 25-spidma | DMPを使ってSPIスレーブデバイスとの間でデータを送受信する |
| 26-cpustress | フラクタル画像を計算してCPUに負荷を与える。SoCの温度図を表示する |
| [27-usbgamepad](doc/27-usbgamepad.md) | **[PnP]** 接続したUSBゲームパッドに関する情報と現在の状態を表示する |
| 28-touchscreen | Raspberry Pi公式タッチスクリーンのタッチイベントを表示する |
| 29-miniorgan | **[PnP]** PWM、HDMI、I2Sサウンド、（USB, シリアル接続の）MIDI、USBキーボードを使ったミニオルガン楽器 |
| 30-gpiofiq | FIQを使った高速GPIOイベントキャプチャとトレーシングクラスのデモ |
| 31-webclient | HTTPWebサーバからRPiハードウェアリビジョンリストを取得してパースする |
| 32-i2cshell | **[PnP]** I2Cデバイスととの対話型通信のためのコマンドラインツール |
| [33-syslog](doc/33-syslog.md) | UDPを使ったsyslogサーバへのログメッセージの送信方法のデモ |
| 34-sounddevices | 複数のサウンドデバイスを1つのアプリケーションに統合する |
| 35-mqttclient | MQTTクライアントのデモ |
| 36-softpwm | CUserTimerクラスを使ったソフトウェアPWMの実装 |
| 37-showgamepad | **[PnP]** 定型化されたゲームパッドと接続されたUSBゲームパッドの状態をスクリーンに示す |
| 38-bootloader | ウェブフロントエンドを持つHTTPとTFTPベースのブートローダ |
| [39-umsdplugging](doc/39-umsdplugging.md) | **[PnP]** USBフラッシュメモリを脱着してディレクトリをリスト |
| 40-irqlatency | **[PnP]** IRQレイテンシーの最大測定値を表示する |
| 41-screenanimations | フリッカーやスクリーンテアリングのない2Dグラフィックのスクリーン表示デモ |
| 42-i2sinput | I2SからPWMサウンドデータコンバータとデジタルサウンドレコーダ |

**注**: [PnP] のマークが付いているさんップルはUSBプラグアンドプレイが有効になっています。
