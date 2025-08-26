# Circle

> If you read this file in an editor you should switch line wrapping on.

## 概要

Circleは、Raspberry PiのためのC++ベアメタルプログラミング環境です。ほとんどの既存モデル
（モデルA+, B, B+, Raspberry Pi 2, 3, 4, 5, 400, 5, Raspberry Pi Zero (2)でテスト済み）
で使用できるはずです。ただし、Raspberry Pi Picoはサポートしていません。Raspberry Pi 
500とCompute Module 5で動作するかはわかりません。Circleは、テスト可能な
[C++クラス](doc/classes.md)と[アドオンライブラリ](addon/README)を提供しており、
Raspberry Piの様々なハードウェア機能の制御に使用できます。また、Circleにはクラスの
使い方を説明する[サンプルプログラム](sample/README)も同梱されています。Circleは
32ビットまたは64ビットのベアメタルアプリケーションの作成に使用することができます。

Circleは特定の目的のために大きな（オプションの）サードパーティのCライブラリをaddon/に
収めています。これがGitHubがこのプロジェクトをC言語プロジェクトと評価している理由です。
メインのCircleライブラリはクラスを使用するC++で書かれています。そのためC++プログラミング
環境と呼ばれています。

## リリース 50
 
このリリースには送受信に対応した完全なネットワークマルチキャスト機能（IGMPv2対応を
含む）が含まれています。ローカルネットワーク上でmDNSホスト名を決定し維持するクラス
`CmDNSDaemon` が追加されました。他のホストと名前が衝突した場合はホスト名に数値の
接尾辞を付加することで解決します。このデーモンは誰かが自身へのポインタを要求した
際に自動的に起動されます。これは現在 `CmDNSDaemon` と連動して動作する `CmDNSPublisher`
クラスに追加されました。 *test/mdns-publisher* は数値の接尾辞を使用して一意の
サービス名を生成します。

### さらなるニュース

* `CTerminalDevice` シーケンスの ESC "[0m" と ESC "[27m" の機能が変更されました。
  前者では色設定もリセットされますが、後者では逆転モードのみがリセットされます。
* `CLogger::Read()` メソッドはログバッファが空の場合に 0 を返すようになりました。
  以前は -1 を返していました。
* DHCP プロセスが改善され、一部の状況下でより高速になりました。
* クラス `CTimer` にメソッド `GetUptime(sec, usec)` が追加されました。
* *addon/fatfs/* にある FatFs ライブラリが Unicode パッチを含む R0.16 に更新されました。
* 表示用フォント `Font12x22` が追加されました。クラス `CCharGenerator` は幅が最大 
  32 ピクセルのフォントを処理できます。

### バグフィックス

* クラス `CHDMISoundBaseDevice` のHDMI音声サポートがステップ49以降動作していません
  でした。
* これまでのバージョンのWLANサポートは、オープンなセキュリティアドバイザリが存在する
  wpa_supplicant v0.7.0のポートを基に実装されていました。これらはwpa_supplicant v2.11を
  Circleにポートすることで修正されました。
* USBガジェットドライバにおける Enumeration done の処理に問題があり、USBマスストレージ
  デバイス (MSD) ガジェットからのブートができなくなっていました。

Circleのビルドに推奨されるツールチェーンは現在GCC 14.3.1をベースにしています（ビルド
セクションを参照）。

*boot/* にダウンロード可能な推奨ファームウェアが更新されました。Raspberry Pi 5では
このCircleバージョンで一部の機能が動作しないため、新しいDTBファイルを使用する必要が
あります。

*addon/wlan/firmware/* にダウンロード可能なWLANファームウェアが更新されました。
古いバージョンにはセキュリティ脆弱性が存在する可能性があるため、新しいファームウェアの
使用を強く推奨します。

## 機能

> 現在、Raspberry Pi 5で"x"またはその他の情報が表示されている機能のみサポートされています。

Circleは次の機能をサポートしています。

| グループ              | 機能                                                         | RPi 5       |
|:----------------------|:-------------------------------------------------------------|:-----------:|
| C++ビルド環境         | AArch32とAArch64のサポート                                   | AArch64のみ |
|                       | 基本的なライブラリ関数（new, deleteなど）                    |      x      |
|                       | MMUを使用するすべてのCPUキャッシュを有効化                   |      x      |
|                       | 割り込みのサポート (IRQとFIQ)                                | IRQのみ     |
|                       | マルチコアのサポート (Raspberry Pi 2, 3, 4)                  |      x      |
|                       | 協調型非プリエンプティブスケジューラ                         |      x      |
|                       | CPUクロックレート管理                                        |      x      |
|                       | Clang/LLVMのサポート（実験的）                               |      x      |
|                       |                                                              |             |
| デバッグサポート      | 画面、UART,シスログサーバへのカーネルログ出力                |      x      |
|                       | スタックトレース付きのC-assertions                           |      x      |
|                       | スタックトレース付きのハードウェア例外ハンドラ               |      x      |
|                       | rpi_stubを使ったGDBのサポート (Raspberry Pi 2, 3)            |             |
|                       | シリアルブートローダを同梱 (David Welch作)                   |      x      |
|                       | ソフトウェアポロファイリングのサポート (シングルコア)        |      x      |
|                       | QEMUのサポート                                               |             |
|                       |                                                              |             |
| SoCデバイス           | GPIOピン（割り込みあり, Act LED）とクロック                  |      x      |
|                       | フレームバッファ（エスケープシーケンス付きスクリーンドライバ | 制限あり    |
|                       | UART（ポーリング／割り込みドライバ）                         |      x      |
|                       | システムタイマー（カーネルタイマー付き）                     |      x      |
|                       | プラットフォームDMAコントローラ                              | DMA40のみ   |
|                       | RP1 プラットフォームDMAコントローラ (Raspberry Pi 5のみ)     |      x      |
|                       | EMMC SDカードインタフェースドライバ                          |      x      |
|                       | SDHOST SDカードインタフェースドライバ (Raspberry Pi 1-3)     |             |
|                       | PWM出力（2チャンネル）                                       | 4チャンネル |
|                       | PWMサウンド出力（ヘッドフォンジャック）                      | アダプタ    |
|                       | I2Cマスターとスレーブ                                        | マスタのみ  |
|                       | SPI0マスターaster（ポーリング／DMAドライバ）                 |      x      |
|                       | SPI1補助マスター（ポーリング）                               |             |
|                       | SPI3-6マスター（Raspberry Pi 4）（ポーリング）               | SPI1-3, 5   |
|                       | SMIマスター                                                  |             |
|                       | I2Sサウンド入出力                                            |      x      |
|                       | HDMIサウンド出力（VCHIQなし）                                |      x      |
|                       | ハードウェア乱数ジェネレータ                                 |      x      |
|                       | ウォッチドッグデバイス                                       |      x      |
|                       | Raspberry Pi公式タッチスクリーン（v1のみ）                   |             |
|                       | VCHIQインタフェースとオーディオサービスドライバ              |             |
|                       | Raspberry Pi 4のBCM54213PE Gigabit Ethernet NIC              |             |
|                       | Raspberry Pi 5のMAcb/GEM Gigabit Ethernet NIC                |      x      |
|                       | ワイアレスLANアクセス                                        |      x      |
|                       | XPT2046ベースのタッチスクリーンドライバ                      |      x      |
|                       |                                                              |             |
| USB                   | ホストコントローラインタフェース (HCI) ドライバ              |      x      |
|                       | 標準ハブドライバ (USB 2.0 のみ)                              |      x      |
|                       | HIDクラスデバイスドライバ (keyboard, mouse, gamepad)         |      x      |
|                       | オンボードEthernetデバイスドライバ (SMSC951x)                |             |
|                       | オンボードEthernetデバイスドライバ (LAN7800)                 |             |
|                       | CDC Ethernetデバイスドライバdevices (RTL815x, QEMU)          |             |
|                       | USBマスストレージデバイスドライバ (バルクのみ)               |      x      |
|                       | USBフロッピーディスクデバイスドライバ (実験的)               |      x      |
|                       | USBオーディストリーミングデバイスドライバ (RPi4のみ)         |      x      |
|                       | 様々なUSBシリアルデバイスドライバ                            |      x      |
|                       | オーディクラスMIDI入力のサポート                             |      x      |
|                       | タッチスクリーンドライバ (デジタイザモード)                  |      x      |
|                       | プリンタドライバ                                             |      x      |
|                       | MIDI ガジェットドドライバ                                    |             |
|                       | シリアルCDCガジェットドドライバ                              |             |
|                       | マスストレージデバイスガジェットドライバ                     |             |
|                       |                                                              |             |
| ファイルシステム      | 内部FATドライバ (限定された機能)                             |      x      |
|                       | FatFsドライバ（ (全機能, by ChaN)                            |      x      |
|                       |                                                              |             |
| TCP/IPネットワーク    | プロトコル: ARP, IP, ICMP, UDP, TCP                          |      x      |
|                       | クライアント: DHCP, DNS, NTP, HTTP, Syslog, MQTT, mDNS       |      x      |
|                       | サーバ: HTTP, TFTP                                           |      x      |
|                       | BSDライクのC++ソケットAPI                                    |      x      |
|                       |                                                              |             |
| グラフィックス        | OpenGL ES 1.1 and 2.0, OpenVG 1.1, EGL 1.4                   |             |
|                       | (not on Raspberry Pi 4)                                      |             |
|                       | uGUI (by Achim Doebler)                                      |             |
|                       | LVGL (by LVGL Kft)                                           |      x      |
|                       | 2D graphics class in base library                            |      x      |
|                       |                                                              |             |
| 未サポート            | Bluetooth                                                    |             |

## ビルド

> 64ビットアプリケーションのビルドは次節を参照

> Raspberry Pi 5では32ビットアプリケーションをサポートしていない

ここではPC Linuxでのビルドについて説明します。Windowsでのビルドについては
[doc/windows-build.txt](doc/windows-build.txt) を参照してください。Raspberry Pi 1
用にビルドする場合は、ARM1176JZFコア（EABI対応）用の[ツールチェイン](http://elinux.org/Rpi_Software#ARM)が
必要です。Raspberry Pi 2/3/4の場合は、Cortex-A7/-A53/-A72をサポートするツール
チェインが必要です。これら全てに対応するツールチェーンは[ここ](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads)から
ダウンロードできます。Circleは、このサイトにあるバージョン *10.3-2021.07* (gcc-arm-10.3-2021.07-x86_64-arm-none-eabi.tar.xz) でテストされています。

まず、 *Rules.mk* ファイルを編集し、Raspberry Piのバージョン（ *RASPPI* 、1、2、3、4）と
ツールチェーンコマンドの *PREFIX* を設定します。または、 *Config.mk* ファイルを作成し
（gitでは無視されます）、以下のように、Raspberry Piのバージョンとコンパイラの
プリフィックスを *PREFIX* 変数に設定します（最後のダッシュを忘れないでください）。

```
RASPPI = 1
PREFIX = arm-none-eabi-
```

次の表は適切な *RASPPI* 値の選択に役立てることができます。

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

## AArch64

Circleは64ビットアプリケーションの構築をサポートしており、Raspberry Pi 3, 4, 5で
動作させることができます。また、BCM2837 SoCをベースとするRaspberry Pi 2バージョンと
Raspberry Pi Zero 2もありますが、これらのRaspberry Piバージョンも使用できます
（RASPPI = 3とする）。

Circleで64ビットアプリケーションをビルドするための推奨ツールチェーンは
[ここ](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)からダウンロードできます。
Circleはこのウェブサイトのバージョン*14.3.Rel1* (arm-gnu-toolchain-14.3.rel1-x86_64-aarch64-none-elf.tar.xz) でテストされています。これがAArch64をビルドするための
推奨ツールチェインです。

一部のLinuxプラットフォームではディストロが提供するツールチェイン（例: Ubuntuの
*g++-aarch64-linux-gnu* やFedoraの *gcc-c++-aarch64-linux-gnu* ）があり、これらを
使ってCircleを手早く動作させる可能性がありますが、これはご自分でテストする必要が
あります。ディストロが提供するツールチェインで問題（全く反応しない、外部ライブラリ
とのリンクに失敗するなど）が発生した場合は、問題を報告する前にまず推奨の
ツールチェイン（上記参照）で試してみてください。

まず、 *Rules.mk* を編集し、Raspberry Piのアーキテクチャ( *AARCH* 、32または64)と
ツールチェーンコマンドの *PREFIX64* を設定します。 `AARCH = 64` の場合は *RASPPI*
変数に3, 4, 5のいずれかを設定する必要があります。または、 *Config.mk* ファイルを作成して
（gitでは無視されます）、以下のように、Raspberry Piのアーキテクチャとコンパイラの
プリフィックスを *PREFIX64* 変数に設定します（最後のダッシュを忘れないでください）。

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

デフォルトではCircleライブラリだけがビルドされます。サンプルプログラムをビルドするには
`makeall` した後に対象のサブディレクトリに移動して `make` を実行してください。

## インストール

Raspberry Piのファームウェア（boot/ディレクトリに移動して `make` を実行すると
取得できます）と *kernel\*.img* （sample/のサブディレクトリ）をSD(HC)カードの
FATファイルシステムにコピーします。

常に、boot/ディレクトリにある *config32.txt* （32ビットモード）または *config64.txt* 
（64ビットモード）をSD(HC)カードコピーして *config.txt* とリネームすることを勧めます。
これらのファイルは特にRaspberry Pi 4でFIQを使うために必要だからです。さらに、SDカードには
*armstub7-rpi4.bin* （32ビットモード）または *armstub8-rpi4.bin* （64ビットモード）
ファイルも必要です。このファイルのビルド方法については [boot/README](boot/README)を
参照してください。

最後にSD(HC)カードをRaspberry Piにセットします。

## ディレクトリ構成

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
 *make* を実行してください。
* doc: その他の文書ファイルがあります。
* test: Circleの様々な機能をテストするテストプログラムがあります。
* tools: CircleのビルドやCircleをより快適に使用するためのツール（シリアル
ブートローダなど）があります。

## クラス

次のC++クラスがCircleに追加されました。

### Netライブラリ

* CIGMPHandler: IGMP version 2 プロトコルハンドラ
* CmDNSDaemon: mDNS レスポンダタスク

Circleで利用可能なクラスのリストは[doc/classes.txt](doc/classes.md)ファイルにあります。
手元のコンピュータにDoxygenheがインストールされていたら以下を実行することでdoc/htmlに
[classドキュメント](doc/html/index.html)が作成されます。

`./makedoc`

現時点ではDoxygenで詳細な説明が得られるのは少数のクラスだけです。

## その他のトピックス

* [標準ライブラリのサポート](doc/stdlib-support.txt)
* [動的メモリ管理と"new"オペレータ](doc/new-operator.txt)
* [DMAバッファの要件](doc/dma-buffer-requirements.txt)
* [シリアルブートローダのサポート](doc/bootloader.md)
* [マルチコアのサポート](doc/multicore.txt)
* [USBプラグアンドプレイ](doc/usb-plug-and-play.md)
* [デバッグのサポート](doc/debug.md)
* [JTAGデバッグ](doc/debug-jtag.txt)
* [SWDデバッグ (Raspberry Pi 5)](doc/debug-swd.txt)
* [QEMUのサポート](doc/qemu.md)
* [Eclipse IDEのサポート](doc/eclipse-support.txt)
* [リアルタイムアプリケーションについて](doc/realtime.txt)
* [cmdline.txtのオプション](doc/cmdline.md)
* [スクリーンエスケープシーケンス](doc/screen.txt)
* [キーボードエスケープシーケンス](doc/keyboard.txt)
* [Clangのサポート](doc/clang-support.txt)
* [メモリレイアウト](doc/memorymap.md)
* [命名規則](doc/naming-conventions.txt)
* [既知の問題](doc/issues.md)

## Trademarks

Raspberry Pi is a trademark of Raspberry Pi Ltd.

Linux is a trademark of Linus Torvalds.

PS3 and PS4 are registered trademarks of Sony Computer Entertainment Inc.

Windows, Xbox 360 and Xbox One are trademarks of the Microsoft group of companies.

Nintendo Switch is a trademark of Nintendo.

Khronos and OpenVG are trademarks of The Khronos Group Inc.

OpenGL ES is a trademark of Silicon Graphics Inc.

The micro:bit brand belongs to the Micro:bit Educational Foundation.

HDMI is a registered trademark of HDMI Licensing Administrator, Inc.
