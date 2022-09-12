Circle
======

> If you read this file in an editor you should switch line wrapping on.

概要
--------

Circleは、Raspberry PiのためのC++ベアメタルプログラミング環境です。すべての既存モデル
（モデルA+、B、B+、Raspberry Pi 2、3、4、400、Raspberry Pi Zeroでテスト済み）で使用
できるはずです。ただし、Raspberry Pi Picoはサポートしていません。Circleは、テスト
可能な[C++クラス](doc/classes.md)と[アドオンライブラリ](addon/README)を提供しており、
Raspberry Piの様々なハードウェア機能の制御に使用できます。また、Circleと共にクラスの
使い方を説明する[サンプルプログラム](sample/README)も配布しています。Circleは
32ビットまたは64ビットのベアメタルアプリケーションの作成に使用することができます。

Circleは特定の目的のために大きな（オプションの）サードパーティCライブラリをaddon/に
収めています。これがGitHubがこのプロジェクトをC言語プロジェクトと評価している理由です。
メインのCircleライブラリはクラスを使ったC++で書かれています。そのためC++プログラミング
環境と呼ばれています。

リリース 44.5
-------------------

この中間リリースは**Raspberry Pi 1-3とZero用のDWHCI USB低レベルドライバの改訂版**を
提供します。システムオプション `USE_USB_FIQ` を使用するとこのドライバでFIQ（Fast
Interrupt Request）を使用できるようになり、USB上でより正確なタイミングが得られる
ようになります。これによりUSBデバイスとの互換性が向上し、特に小さなデータバッファ
しか持たないUSB MIDIコントローラからMIDIデータを受信する際にデータの損失を防ぐことが
できます。このシステムでサポートされるFIQソースは1つだけなので、このシステム
オプションではFIQをUSB以外の用途に使用することはできません。Raspberry Pi 4の
xHCI USBドライバはこのシステムオプションに対応していないため変更はありません。

**Raspberry Pi 1-3とZeroのUSB MIDIコントローラからのデータ損失を防ぐ**ために
ファイル *cmdline.txt* に `usbboost=true` という新しいオプションも用意されました。
これはUSB MIDIの処理を高速化しますが、その反面、システム負荷が増える可能性があります。

システムオプションの `USE_EMBEDDED_MMC_CM4` は `USE_EMBEDDED_MMC_CM` に名前を変え、Compute Module 3+と4の **組み込みMMCメモリ** のサポートがテストされています。

I2Sサウンドデバイスの `CI2SSoundBaseDevice` クラスドライバが **WM8960 DACをサポート**
しました。

**HD44780 LCDディスプレイドライバがI2Cをサポート**しました。

バグフィックス:

* `CHDMISoundBaseDevice`クラスでStereoのチャンネルが入れ替わっていた。
* 想定以上のデータを送信するUSBデバイスがあるようです。この修正により、上位レイヤで
  処理されるべき、フレームオーバーランエラーの偽装によるシステムクラッシュを防ぐことが
  できるようになりました。
* `NDEBUG`オプションでWLANサポートをビルドできなかった。

使用中のファームウェアを[boot/](boot/)でダウンロードできるものに更新するのを
忘れないでください。

The 44th Step
-------------

This release comes with new features, improvements and bug fixes. There is a new HDMI sound driver class `CHDMISoundBaseDevice`, which allows to generate **HDMI sound without VCHIQ** driver, which can be easier to integrate in an application. This is shown by the [sample/29-miniorgan](sample/29-miniorgan) and [sample/34-sounddevices](sample/34-sounddevices). On the Raspberry Pi 4 only the connector HDMI0 is supported. The class `CI2SSoundBaseDevice` now supports the **PCM5122 DAC**.

A new class ``C2DGraphics`` has been added to the base library, which provides **2D drawing routines**, which work without flickering or screen tearing. This is demonstrated in the [sample/41-screenanimations](sample/41-screenanimations).

The **scheduler library** has been improved and provides the new classes `CMutex` and `CSemaphore`. Multiple tasks can wait for a `CSynchronzationEvent` to be set now.

There is a **new serial bootloader and flash tool** (Flashy), which improves the download speed and reliability. Please see the second part of the file [doc/bootloader.txt](doc/bootloader.txt) for more information! You can interrupt the download process with Ctrl-C now and start again, without resetting your Raspberry Pi. You should update your bootloader kernel image(s) on the SD card in any case. The old flash tool is still available.

Circle comes with a **configure script** now, which can be used to create the configuration file `Config.mk` easier. Please enter `configure -h` for a description of its options.

The C++ support has been improved. Now **placement new operators** and **static objects inside of a function** can be used. Furthermore the **C++17 standard** is optionally supported and can be enabled with the option `--c++17` of `configure`, if you have a toolchain version, which supports it.

Further improvements:

* There is a new system option `NO_BUSY_WAIT`. With this option enabled, the EMMC, SDHOST and USB drivers will **not busy wait for the completion of synchronous transfers** any more. This should improve system throughput and network latency, but requires the scheduler in the system.
* The **embedded MMC memory of the Compute Module 4** can be accessed, when the system option `USE_EMBEDDED_MMC_CM4` has been defined.
* The class `CTFTPFatFsFileServer` was added to [addon/tftpfileserver](addon/tftpfileserver) to support **TFTP access with the FatFs filesystem module**.
* The class `CDS18x20` in [addon/OneWire](addon/OneWire) has been improved and is now part of the library, not of the sample as before. It determines the used power mode of the sensor automatically.
* Functions for **atomic memory access** have been added to `<circle/atomic.h>`.

Bug fixes:

* System timer IRQ handling may have stopped working after a while on the Raspberry Pi 1 and Zero before.
* xHCI USB controller did not work on some Raspberry Pi 4 models.
* Starting secondary cores 1-3 was not reliable.
* Access to USB mass-storage devices was not reliable on Raspberry Pi Model A+, 3A+ and Zero before.
* Add workaround for non-compliant low-speed USB devices with bulk endpoints.
* Suppress concurrent split IN/OUT requests on Raspberry Pi 1-3 and Zero in USB serial drivers.
* Enable serial FIFO in polling mode too.
* The screen size select-able in *cmdline.txt* was limited to 1920x1080 before.
* Semaphore implementation in *addon/linux* was not IRQ safe, but used from IRQ handler in VCHIQ driver.
* Allow received text segment in TCP state SYN-RECEIVED.

Don't forget to update the used firmware to the one downloadable in [boot/](boot/)!

機能
--------

Circleは次の機能をサポートしています。

| グループ              | 機能                                                |
|-----------------------|-----------------------------------------------------|
| C++ビルド環境         | AArch32とAArch64のサポート                          |
|                       | 基本的なライブラリ関数（new, deleteなど）           |
|                       | MMUを使用するすべてのCPUキャッシュを有効化          |
|                       | 割り込みのサポート (IRQとFIQ)                         |
|                       | マルチコアのサポート (Raspberry Pi 2, 3, 4)           |
|                       | 協調型非プリエンプティブスケジューラ                |
|                       | CPUクロックレート管理                               |
|                       |                                                     |
| デバッグサポート      | 画面、UART,シスログサーバへのカーネルログ出力       |
|                       | スタックトレース付きのC-assertions                  |
|                       | スタックトレース付きのハードウェア例外ハンドラ      |
|                       | rpi_stubを使ったGDBのサポート (Raspberry Pi 2, 3)     |
|                       | シリアルブートローダを同梱 (David Welch作)          |
|                       | ソフトウェアポロファイリングのサポート (シングルコア) |
|                       | QEMUのサポート                                        |
|                       |                                                     |
| SoCデバイス           | GPIO pins (with interrupt, Act LED) and clocks      |
|                       | Frame buffer (screen driver with escape sequences)  |
|                       | UART(s) (Polling and interrupt driver)              |
|                       | System timer (with kernel timers)                   |
|                       | Platform DMA controller                             |
|                       | EMMC SD card interface driver                       |
|                       | SDHOST SD card interface driver (Raspberry Pi 1-3)  |
|                       | PWM output (2 channels)                             |
|                       | PWM sound output (on headphone jack)                |
|                       | I2C master(s) and slave                             |
|                       | SPI0 master (Polling and DMA driver)                |
|                       | SPI1 auxiliary master (Polling)                     |
|                       | SPI3-6 masters of Raspberry Pi 4 (Polling)          |
|                       | SMI master (experimental)                           |
|                       | I2S sound output and input                          |
|                       | HDMI sound output (without VCHIQ)                   |
|                       | Hardware random number generator                    |
|                       | Watchdog device                                     |
|                       | Official Raspberry Pi touch screen                  |
|                       | VCHIQ interface and audio service drivers           |
|                       | BCM54213PE Gigabit Ethernet NIC of Raspberry Pi 4   |
|                       | Wireless LAN access                                 |
|                       |                                                     |
| USB                   | ホストコントローラインタフェース (HCI) ドライバ     |
|                       | 標準ハブドライバ (USB 2.0 のみ)                     |
|                       | HIDクラスデバイスドライバ (keyboard, mouse, gamepad) |
|                       | オンボードEthernetデバイスドライバ (SMSC951x)       |
|                       | オンボードEthernetデバイスドライバ (LAN7800)        |
|                       | USBマスストレージデバイスドライバ (バルクのみ)      |
|                       | 様々なUSBシリアルデバイスドライバ                   |
|                       | オーディクラスMIDI入力のサポート                    |
|                       | タッチスクリーンドライバ (デジタイザモード)         |
|                       | プリンタドライバ                                    |
|                       |                                                     |
| ファイルシステム      | 内部FATドライバ (限定された機能)                    |
|                       | FatFsドライバ（ (全機能, by ChaN)                   |
|                       |                                                     |
| TCP/IPネットワーク    | プロトコル: ARP, IP, ICMP, UDP, TCP                 |
|                       | クライアント: DHCP, DNS, NTP, HTTP, Syslog, MQTT    |
|                       | サーバ: HTTP, TFTP                                  |
|                       | BSDライクのC++ソケットAPI                           |
|                       |                                                     |
| グラフィックス        | OpenGL ES 1.1 and 2.0, OpenVG 1.1, EGL 1.4          |
|                       | (not on Raspberry Pi 4)                             |
|                       | uGUI (by Achim Doebler)                             |
|                       | LVGL (by LVGL Kft)                                  |
|                       | 2D graphics class in base library                   |
|                       |                                                     |
| 未サポート            | Bluetooth                                           |
|                       | Camera                                              |
|                       | USBデバイス (gadget) モード                         |
|                       | USBアイソクロナス転送とオーディオ                   |

ビルド
--------

> 64ビットアプリケーションのビルドは次節を参照

ここではPC Linuxでのビルドについて説明します。Windowsでのビルドについては
[doc/windows-build.txt](doc/windows-build.txt) を参照してください。Raspberry Pi 1
用にビルドする場合は、ARM1176JZFコア（EABI対応）用の[ツールチェイン](http://elinux.org/Rpi_Software#ARM)が
必要です。Raspberry Pi 2/3/4の場合は、Cortex-A7/-A53/-A72をサポートするツール
チェインが必要です。これら全てに対応するツールチェーンは[ここ](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads)から
ダウンロードできます。Circleは、このサイトにあるバージョン*10.3-2021.07* (gcc-arm-10.3-2021.07-x86_64-arm-none-eabi.tar.xz) でテストされています。

まず、*Rules.mk* ファイルを編集し、Raspberry Piのバージョン（*RASPPI*、1、2、3、4）と
ツールチェーンコマンドの*PREFIX*を設定します。または、*Config.mk*ファイルを作成し
（gitでは無視されます）、以下のように、Raspberry Piのバージョンとコンパイラの
プレフィックスを *PREFIX* 変数に設定します（最後のダッシュを忘れないでください）。

```
RASPPI = 1
PREFIX = arm-none-eabi-
```

次の表はは適切な*RASPPI*値の選択に役立てることができます。

| RASPPI | ターゲット     | モデル                   | 最適化の対象  |
| ------ | -------------- | ------------------------ | ------------- |
|      1 | kernel.img     | A, B, A+, B+, Zero, (CM) | ARM1176JZF-S  |
|      2 | kernel7.img    | 2, 3, Zero 2, (CM3)      | Cortex-A7     |
|      3 | kernel8-32.img | 3, Zero 2, (CM3)         | Cortex-A53    |
|      4 | kernel7l.img   | 4B, 400, CM4             | Cortex-A72    |

バイナリ配布する場合じゃ、*RASPPI = 1*で1回、*RASPPI = 2*で1回、*RASPPI = 4*で1回の
ビルドを行い、作成された*kernel.img*, *kernel7.img*, *kernel7l.img*を含めます。
オプションとして、*RASPPI = 3*でビルドし、作成されたファイル *kernel8-32.img* を
追加することでRaspberry Pi 3に最適化されたバージョンを提供することができます。

構成ファイル*Config.mk*は`configure`ツールで作成することもできます。使い方は
`./configure -h`と入力すると表示されます。

> [include/circle/sysconfig.h](include/circle/sysconfig.h) ファイルには設定可能な
> システムオプションが多数あります。このファイルを見て、あなたの目的に合わせて
> サークルを設定する方法を学んでください。ハードウェア構成によってはこれらの
> オプションを変更する必要があります（たとえば、CM4でUSBを使用する場合など）。

次いでCircleのビルドルートに移動し、以下を実行します。

```
./makeall clean
./makeall
```

デフォルトでは最新のサンプル(番号が最大のもの)だけがビルドされます。ビルドが完了した
kernel.img*はsample/のサブディレクトリにあるはずです。makeallの後に別のサンプルを
ビルドしたい場合はそのサブディレクトリに移動して`make`を実行してください。

RaspbianではRaspberry Pi本体でCircleをビルドすることもできます（`PREFIX =` (空)と
設定）が、*kernel.img*ファイルをSD（HC）カードに格納する何らかの方法が必要です。
外付けのUSBカードリーダーを持つモデルB+や（4つのUSBポートを持つ）Raspberry Pi 2/3/4
モデルBであれば問題ないでしょう。

AArch64
-------

Circleは64ビットアプリケーションの構築をサポートしており、Raspberry Pi 3と4で
動作させることができます。また、BCM2837 SoCをベースとするRaspberry Pi 2バージョンと
Raspberry Pi Zero 2もありますが、これらのRaspberry Piバージョンも使用できます
（RASPPI = 3とする）。

Circleで64ビットアプリケーションをビルドするための推奨ツールチェーンは
[ここ](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads)からダウンロードできます。Circleは
このウェブサイトのバージョン *10.3-2021.07* (gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf.tar.xz) でテストされています。

一部のLinuxプラットフォームではディストロが提供するツールチェイン(例: Ubuntuの
*g++-aarch64-linux-gnu* やFedoraの*gcc-c++-aarch64-linux-gnu*があり、これらを
使ってCircleを手早く動作させる可能性がありますが、これは自分でテストする必要が
あります。ディストロが提供するツールチェインで問題（全く反応しない、外部ライブラリ
とのリンクに失敗するなど）が発生した場合は、問題を報告する前にまず推奨の
ツールチェイン（上記参照）で試してみてください。

まず、*Rules.mk* を編集し、Raspberry Piのアーキテクチャ(*AARCH*、32または64)と
ツールチェーンコマンドの *PREFIX64* を設定します。`AARCH = 64` の場合は *RASPPI*
変数を3または4に設定する必要があります。または、*Config.mk* ファイルを作成して
（gitでは無視されます）、以下のように、Raspberry Piのアーキテクチャとコンパイラの
プレフィックスを *PREFIX64* 変数に設定します（最後のダッシュを忘れないでください）。

```
AARCH = 64
RASPPI = 3
PREFIX64 = aarch64-none-elf-
```

構成ファイル *Config.mk* は `configure` ツールを使っても作成できます。使用法については
`./configure -h` と入力してください。

次いで、Circleのbuildディレクトリに移動して以下のコマンドを実行します。

```
./makeall clean
./makeall
```

デフォルトでは最新のサンプル(番号が最大のもの)だけがビルドされます。ビルドが完了した
*kernel8.img*や*kernel8-rpi4.img*はsample/のサブディレクトリにあるはずです。makeallの
後に別のサンプルをビルドしたい場合はそのサブディレクトリに移動して`make`を実行してください。

インストール
-----------------

Raspberry Piのファームウェア（boot/ディレクトリに移動して*make`を実行すると
取得できます）と*kernel.img*（sample/のサブディレクトリ）をSD(HC)カードの
FATファイルシステムにコピーします。SD(HC)カードをRaspberry Piにセットします。

boot/ディレクトリにある*config32.txt*は、Raspberry Pi 4で32bitモードのFIQを
使うために必要なので、該当する場合はSDカードにコピーして（config.txtにリネームして）
ください。さらに、SDカードには*armstub7-rpi4.bin*ファイルも必要です。このファイルの
ビルド方法については [boot/README](boot/README)を参照してください。

boot/ディレクトリにある*config64.txt*ファイルは64 ビットモードを有効にする
ために必要なので該当する場合はSDカードにコピーする必要があります（config.txtに
リネームしてください）。Raspberry Pi 4でAArch64のFIQサポートにはSDカードにファイル*armstub8-rpi4.bin*を追加する必要があります。このファイルのビルド方法については
[boot/README](boot/README)を参照してください。

ディレクトリ構成
----------------------

* include: 共通のヘッダファイル。ほとんどのクラスヘッダはinclude/circle/
サブディレクトリにあります。
* lib: Circleのクラス実装とサポートファイル（その他のライブラリはlib/のサブ
ディレクトリにあります）。
* sample: サブディレクトリにCircleを使ったサンプルアプリケーションがあります。
main関数はCkernelクラスに実装されています。
* addon: 提供されたライブラリとサンプルがあります（個別にビルドする必要があります）。
* app: 作成するアプリケーションはここに置いてください。独自のライブラリがある場合は
app/libに置いてください）。
* boot: ブートに必要なRaspberry Piのファームウェアを取得するためにこのディレクトリで
*make*を実行してください。
* doc: その他の文書ファイルがあります。
* test: Circleの様々な機能をテストするテストプログラムがあります。
* tools: CircleのビルドやCircleをより快適に使用するためのツール（シリアル
ブートローダなど）があります。

Classes
-------

次のC++クラスがCircleに追加されました。

基本ライブラリ

* C2DGraphics: VSyncとハードウェアアクセレートのダブルバッファリングを持つソフトウェアグラフィックスライブラリ
* CBcmWatchdog: BCM2835ウォッチドッグデバイスドライバ
* CDMASoundBuffers: サウンドデバイスドライバで使用される連結DMAバッファ
* CGenericLock: スケジューラを持つ/持たないリソースをロックする
* CHDMISoundBaseDevice: （VCHIQを持たない）HDMIサウンドデバイスへの低レベルアクセス
* CMPHIDevice: MPHIデバイスがIRQを生成するために使用するドライバ
* CPtrListFIQ: FIQレベルで使用可能なコンテナクラスとポインタリスト
* CSMIMaster: 二次メモリインタフェースドライバ

USBライブラリ

* CDWHCICompletionQueue: 準備完了USBリクエストをキューイングする（USE_USB_FIQで有効になる）
* CUSBTouchScreenDevice: USB HIDクラスタッチスクリーンドライバ

入力ライブラリ

* CRPiTouchScreen: Raspberry Pi公式タッチスクリーンドライバ
* CTouchScreenDevice: 汎用タッチスクリーンインタフェースデバイス

スケジューラライブラリ

* CMutex: タスク間の（クリティカルセクションの）排他制御メソッドを提供
* CSemaphore: セマフォ同期クラスを実装

Circleで利用可能なクラスのリストは[doc/classes.txt](doc/classes.txt)ファイルにあります。
手元のコンピュータにDoxygenheがインストールされていたら以下を実行することでdoc/htmlに
[classドキュメント](doc/html/index.html)が作成されます。

`./makedoc`

現時点ではDoxygennde詳細な説明が得られるのは少数のクラスだけです。

その他のトピックス
--------------------------

* [標準ライブラリのサポート](doc/stdlib-support.txt)
* [動的メモリ管理と"new"オペレータ](doc/new-operator.txt)
* [DMAバッファの要件](doc/dma-buffer-requirements.txt)
* [シリアルブートローダのサポート](doc/bootloader.txt)
* [マルチコアのサポート](doc/multicore.txt)
* [USBプラグアンドプレイ](doc/usb-plug-and-play.txt)
* [デバッグのサポート](doc/debug.txt)
* [JTAGデバッグ](doc/debug-jtag.txt)
* [QEMUのサポート](doc/qemu.txt)
* [Eclipse IDEのサポート](doc/eclipse-support.txt)
* [リアルタイムアプリケーションについて](doc/realtime.txt)
* [cmdline.txtのオプション](doc/cmdline.txt)
* [スクリーンエスケープシーケンス](doc/screen.txt)
* [キーボードエスケープシーケンス](doc/keyboard.txt)
* [メモリレイアウト](doc/memorymap.txt)
* [命名規則](doc/naming-conventions.txt)
* [既知の問題](doc/issues.txt)

Trademarks
----------

Raspberry Pi is a trademark of Raspberry Pi Trading.

Linux is a trademark of Linus Torvalds.

PS3 and PS4 are registered trademarks of Sony Computer Entertainment Inc.

Windows, Xbox 360 and Xbox One are trademarks of the Microsoft group of companies.

Nintendo Switch is a trademark of Nintendo.

Khronos and OpenVG are trademarks of The Khronos Group Inc.

OpenGL ES is a trademark of Silicon Graphics Inc.

The micro:bit brand belongs to the Micro:bit Educational Foundation.

HDMI is a registered trademark of HDMI Licensing Administrator, Inc.
