# README

このサンプルは、以下のいずれかのサウンドデバイスを通じて、440Hzの変調トーンを再生します。

* 3.5mmヘッドフォンジャック経由のPWMサウンドデバイス（Raspberry Pi 5ではアダプタが必要）
* 外部ハードウェアを使用したI2Sサウンドデバイス（PCM5102AおよびPCM5122 DACで動作確認済み）
* サウンド対応HDMIモニター経由のHDMIサウンドデバイス（VCHIQ非対応、HDMI0のみ、Raspberry Pi 5では非対応）
* サウンド対応HDMIモニターまたはヘッドフォンジャック経由のVCHIQサウンドデバイス（オプション）
* 外部ハードウェアを使用したUSBサウンドデバイス（USBオーディオクラス仕様に対応、Raspberry Pi 4および5のみ）

デフォルトではVCHIQオプションなしでビルドされます。VCHIQには追加のライブラリが必要であり、
それらを手動でビルドする必要があるためです。VCHIQサウンドサポートを利用したい場合はサンプルの
Makefileの"USE_VCHIQ_SOUND = 1"という行を有効にしてください。その後、プロジェクトの
ルートディレクトリから以下のコマンドを実行してください：

```bash
./makeall --nosample
cd addon/linux
make
cd ../vc4
./makeall
cd ../../sample/34-sounddevices
make
```

これで、ビルド済みのカーネルイメージが現在のディレクトリにあるはずです。

使用するサウンドデバイスを選択するにはSDカード上に"cmdline.txt"というファイルを作成し、
以下のいずれかの行を記述してください.

```bash
	sounddev=sndpwm			または
	sounddev=sndi2s			または
	sounddev=sndhdmi		または
	sounddev=sndvchiq soundopt=0	または
	sounddev=sndusb
```

デフォルトでは音声出力はヘッドフォンジャック経由（VCHIQオプションなし）または
音声出力対応のHDMIモニター経由（VCHIQオプションあり）で行われます。詳細については
ファイル "doc/cmdline.txt" をご確認ください。

PCM5122ベースのサウンドデバイスでI2S動作を行う場合、config.hでDACのI2C
スレーブアドレスを設定する必要がある場合があります。デフォルトではアドレス 0x4C と
0x4D が自動検出されます。WM8960ベースのI2SサウンドカードもデフォルトのI2Cスレーブ
アドレス 0x1A でサポートされています。

USB 動作（Raspberry Pi 4/5 のみ）にはUSBオーディオクラス・ストリーミング
デバイスが必要です。サンプルプログラムの起動前にUSBサウンドカードを接続し、
プログラムの実行中は取り外さないでください。

## ビルド

```bash
$ cp Config.mk.m3 Config.mk
zuki@airm3:~/raspi_os/circle$ ./makeall clean
$ ./makeall
$ cd 34-sounddevices/
$ make clean && make
$ cp kernel8.img /Volume/NO\ NAME/
$ vi /Volume/NO\ NAME/cmdline
    'sounddev=sndhdmi'を既存の行の末尾に追記
$ minicom
```

## 実行

- モニターから440Hzの音が聞こえた
- USB端子にキーボードが接続されている場合は外しておく(`keymap.cpp(144): assertion failed: pDefaultMap != 0`)

```bash
logger: Circle 50 started on Raspberry Pi 3 Model B+ 1GB (AArch64)
logger: Revision code is a020d3, compiler has been GCC 14.3.1
00:00:00.66 timer: SpeedFactor is 1.51
00:00:01.47 usbdev: Dumping 0x12 bytes starting at 0x610480
00:00:01.47 usbdev: 0480: 12 01 00 02 09 00 02 40-24 04 14 25 B3 0B 00 00
00:00:01.48 usbdev: 0490: 00 01 25 B8 55 55 55 55-55 55 55 55 55 55 55 55
00:00:01.53 usbdev: Dumping 0x29 bytes starting at 0x610500
00:00:01.54 usbdev: 0500: 09 02 29 00 01 01 00 E0-01 09 04 00 00 01 09 00
00:00:01.54 usbdev: 0510: 01 00 07 05 81 03 01 00-0C 09 04 00 01 01 09 00
00:00:01.55 usbdev: 0520: 02 00 07 05 81 03 01 00-0C B4 37 00 20 35 35 20
00:00:01.56 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:01.61 usbdev0-1: Interface int9-0-1 found
00:00:01.61 usbdev0-1: Function is not supported
00:00:01.62 usbdev0-1: Interface int9-0-2 found
00:00:01.62 usbdev0-1: Using device/interface int9-0-2
00:00:02.24 usbdev: Dumping 0x12 bytes starting at 0x6130C0
00:00:02.24 usbdev: 30C0: 12 01 00 02 09 00 02 40-24 04 14 25 B3 0B 00 00
00:00:02.25 usbdev: 30D0: 00 01 25 B8 63 65 20 69-6E 74 39 2D 30 2D 32 00
00:00:02.31 usbdev: Dumping 0x29 bytes starting at 0x6142C0
00:00:02.31 usbdev: 42C0: 09 02 29 00 01 01 00 E0-01 09 04 00 00 01 09 00
00:00:02.32 usbdev: 42D0: 01 00 07 05 81 03 01 00-0C 09 04 00 01 01 09 00
00:00:02.32 usbdev: 42E0: 02 00 07 05 81 03 01 00-0C B4 37 00 20 32 44 20
00:00:02.33 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:02.38 usbdev0-1: Interface int9-0-1 found
00:00:02.39 usbdev0-1: Function is not supported
00:00:02.39 usbdev0-1: Interface int9-0-2 found
00:00:02.40 usbdev0-1: Using device/interface int9-0-2
00:00:03.01 usbdev: Dumping 0x12 bytes starting at 0x616FC0
00:00:03.01 usbdev: 6FC0: 12 01 10 02 FF 00 FF 40-24 04 00 78 00 03 00 00
00:00:03.02 usbdev: 6FD0: 00 01 07 A8 31 3A 20 49-6E 74 65 72 66 61 63 65
00:00:03.08 usbdev: Dumping 0x27 bytes starting at 0x6170C0
00:00:03.08 usbdev: 70C0: 09 02 27 00 01 01 00 E0-01 09 04 00 00 03 FF 00
00:00:03.09 usbdev: 70D0: FF 00 07 05 81 02 00 02-00 07 05 02 02 00 02 00
00:00:03.09 usbdev: 70E0: 07 05 83 03 10 00 04 E9-32 20 36 36 20 36 31 20
00:00:03.10 usbdev0-1: Device ven424-7800 found
00:00:03.15 usbdev0-1: Using device/interface ven424-7800
00:00:03.24 lan7800: MAC address is B8:27:EB:AB:E8:48
00:00:03.37 usbhub: Port 1: Device configured
00:00:03.37 usbhub: Port 1: Device configured
00:00:03.38 dwroot: Device configured
00:00:03.38 kernel: Compile time: Apr 26 2026 08:32:59
00:00:03.39 kernel: Playing modulated 440 Hz tone
```

- キーボードを接続するとエラーになる件を修正した（KeyMapが存在しない"us"になっていた。
    cdmline.txtで正しいKeyMapを設定した）

```bash
logger: Circle 50 started on Raspberry Pi 3 Model B+ 1GB (AArch64)
logger: Revision code is a020d3, compiler has been GCC 14.3.1
00:00:00.66 timer: SpeedFactor is 1.51
00:00:01.47 usbdev: Dumping 0x12 bytes starting at 0x610480
00:00:01.47 usbdev: 0480: 12 01 00 02 09 00 02 40-24 04 14 25 B3 0B 00 00
00:00:01.48 usbdev: 0490: 00 01 25 B8 55 55 55 55-55 55 55 55 55 55 55 55
00:00:01.53 usbdev: Dumping 0x29 bytes starting at 0x610500
00:00:01.54 usbdev: 0500: 09 02 29 00 01 01 00 E0-01 09 04 00 00 01 09 00
00:00:01.54 usbdev: 0510: 01 00 07 05 81 03 01 00-0C 09 04 00 01 01 09 00
00:00:01.55 usbdev: 0520: 02 00 07 05 81 03 01 00-0C B4 37 00 20 35 35 20
00:00:01.56 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:01.61 usbdev0-1: Interface int9-0-1 found
00:00:01.61 usbdev0-1: Function is not supported
00:00:01.62 usbdev0-1: Interface int9-0-2 found
00:00:01.62 usbdev0-1: Using device/interface int9-0-2
00:00:02.24 usbdev: Dumping 0x12 bytes starting at 0x6130C0
00:00:02.24 usbdev: 30C0: 12 01 00 02 09 00 02 40-24 04 14 25 B3 0B 00 00
00:00:02.25 usbdev: 30D0: 00 01 25 B8 63 65 20 69-6E 74 39 2D 30 2D 32 00
00:00:02.30 usbdev: Dumping 0x29 bytes starting at 0x6142C0
00:00:02.31 usbdev: 42C0: 09 02 29 00 01 01 00 E0-01 09 04 00 00 01 09 00
00:00:02.31 usbdev: 42D0: 01 00 07 05 81 03 01 00-0C 09 04 00 01 01 09 00
00:00:02.32 usbdev: 42E0: 02 00 07 05 81 03 01 00-0C B4 37 00 20 32 44 20
00:00:02.33 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:02.38 usbdev0-1: Interface int9-0-1 found
00:00:02.39 usbdev0-1: Function is not supported
00:00:02.39 usbdev0-1: Interface int9-0-2 found
00:00:02.39 usbdev0-1: Using device/interface int9-0-2
00:00:03.01 usbdev: Dumping 0x12 bytes starting at 0x616FC0
00:00:03.01 usbdev: 6FC0: 12 01 10 02 FF 00 FF 40-24 04 00 78 00 03 00 00
00:00:03.02 usbdev: 6FD0: 00 01 07 A8 31 3A 20 49-6E 74 65 72 66 61 63 65
00:00:03.08 usbdev: Dumping 0x27 bytes starting at 0x6170C0
00:00:03.08 usbdev: 70C0: 09 02 27 00 01 01 00 E0-01 09 04 00 00 03 FF 00
00:00:03.09 usbdev: 70D0: FF 00 07 05 81 02 00 02-00 07 05 02 02 00 02 00
00:00:03.09 usbdev: 70E0: 07 05 83 03 10 00 04 E9-32 20 36 36 20 36 31 20
00:00:03.10 usbdev0-1: Device ven424-7800 found
00:00:03.15 usbdev0-1: Using device/interface ven424-7800
00:00:03.26 usbdev: Dumping 0x12 bytes starting at 0x618C40
00:00:03.27 usbdev: 8C40: 12 01 10 01 00 00 00 08-3C 41 03 20 06 03 01 02
00:00:03.27 usbdev: 8C50: 00 01 3F 8F 6F 75 6E 64-4B B2 61 00 00 00 00 00
00:00:03.34 usbdev: Dumping 0x22 bytes starting at 0x61B240
00:00:03.34 usbdev: B240: 09 02 22 00 01 01 00 A0-23 09 04 00 00 01 03 01
00:00:03.35 usbdev: B250: 01 00 09 21 10 01 00 01-22 41 00 07 05 81 03 08
00:00:03.36 usbdev: B260: 00 18 FE 45 36 31 20 30-30 20 30 30 20 30 30 20
00:00:03.36 usbdev2-3: Device ven413c-2003 found
00:00:03.38 usbdev2-3: Product: Dell Dell USB Keyboard
00:00:03.44 usbdev2-3: Interface int3-1-1 found
00:00:03.44 keymap: pLocale: JP
00:00:03.44 usbdev2-3: Using device/interface int3-1-1
00:00:03.45 lan7800: MAC address is B8:27:EB:AB:E8:48
00:00:03.58 usbhub: Port 1: Device configured
00:00:03.59 usbhub: Port 3: Device configured
00:00:03.59 usbhub: Port 1: Device configured
00:00:03.60 dwroot: Device configured
00:00:03.60 kernel: Compile time: Apr 26 2026 11:41:27
00:00:03.61 kernel: Playing modulated 440 Hz tone
```
