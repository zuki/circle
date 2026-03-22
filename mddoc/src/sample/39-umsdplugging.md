# サンプル 39: umsdplugging

本サンプルはUSBマスストレージデバイス（"UMSD"、フラッシュドライブなど）のUSB
プラグアンドプレイをデモします。従来のアプリケーション制御によるUMSDのセミ
プラグアンドプレイはもう必要ありません。ただし、Raspberry Pi 1-3とZero で
このサンプルプログラムをビルドする前には、include/circle/sysconfig.h ファイルで
システムオプション` USE_USB_SOF_INTR` を定義しておく必要があります。

サンプルは起動するとUSBメモリを接続するよう促します。FATファイルシステムの
USBメモリを接続してください。安全のため、重要なデータは入れないでください。
プラグインするとUSBメモリは自動的に検出され、マウントされます。ドライブ上に
ファイルがある場合、サンプルプログラムはフラッシュドライブのルートディレクトリの
リストを表示します。

次に、サンプルアプリケーションによってファイルシステムが直ちにアンマウントされ、
USBメモリをUSBコネクタから取り外すよう促されます。この操作を行うと、USBデバイスの
登録が自動的に解除されます。この処理が完了すると再び処理が開始されます。次の実行で
同じUSBメモリや異なるUSBメモリを接続することができます。

Circleには2種類のFATファイルシステムドライバの実装（APIが異なる）が付属しています。
デフォルトではこのサンプルは`lib/fs/fat/`にあるCFATFileSystemクラスを使用します。
`addon/fatfs/`にあるFatFsファイルシステムモジュールを使用したい場合は、サンプルの
Makefileに **USE_FATFS = 1** を定義する必要があります。また、このサンプルの
ディレクトリで "make "を実行する前に、`addon/fatfs/`のライブラリを手動でビルドして
おく必要があります。デフォルトクラスを使用する場合はこの作業は必要ありません。


### 実行結果

cmdline.txtはそのままSDカードにあり

#### 1. `make flash`

```
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
Sending.............................................................................................................................................ok
Finished in 21.3 seconds.
Sending go command...ok
Closing serial port...ok
Done!
```

#### `minicom`

`make flash`がDoneで終了後、LEDが点滅している間にminicomを立ち上げる

```
$ minicom

logger: Circle 44.5 started on Raspberry Pi 3 Model B+ (AArch64)
00:00:00.66 timer: SpeedFactor is 1.51
00:00:01.52 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:01.52 usbdev0-1: Interface int9-0-1 found
00:00:01.53 usbdev0-1: Function is not supported
00:00:01.53 usbdev0-1: Interface int9-0-2 found
00:00:01.53 usbdev0-1: Using device/interface int9-0-2
00:00:02.25 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:02.26 usbdev0-1: Interface int9-0-1 found
00:00:02.26 usbdev0-1: Function is not supported
00:00:02.27 usbdev0-1: Interface int9-0-2 found
00:00:02.27 usbdev0-1: Using device/interface int9-0-2
00:00:02.99 usbdev0-1: Device ven424-7800 found
00:00:02.99 usbdev0-1: Using device/interface ven424-7800
00:00:03.13 lan7800: MAC address is B8:27:EB:AB:E8:48
00:00:03.28 usbhub: Port 1: Device configured
00:00:03.28 usbhub: Port 1: Device configured
00:00:03.29 dwroot: Device configured
00:00:03.29 kernel: Compile time: Sep 17 2022 10:58:01
00:00:03.29 kernel: Plug in an USB flash drive!
00:00:10.12 usbdev1-3: Device ven93a-2510 found
00:00:10.13 usbdev1-3: Product: PIXART USB OPTICAL MOUSE
00:00:10.13 usbdev1-3: Interface int3-1-2 found
00:00:10.14 usbdev1-3: Using device/interface int3-1-2
00:00:10.20 usbhub: Port 3: Device configured
00:00:14.94 usbmouse.cpp(173): stack[1] is 0x93740
00:00:14.94 usbmouse.cpp(173): stack[4] is 0x93810
00:00:14.94 usbmouse.cpp(173): stack[11] is 0x93864
00:00:14.94 usbmouse.cpp(173): stack[13] is 0x91310
00:00:14.94 usbmouse.cpp(173): stack[16] is 0x93810
00:00:14.94 usbmouse.cpp(173): stack[23] is 0x87D00
00:00:14.94 usbmouse.cpp(173): stack[28] is 0x843F4
00:00:14.94 usbmouse.cpp(173): stack[29] is 0xA9088
00:00:14.94 usbmouse.cpp(173): stack[57] is 0x86AF0
00:00:14.94 usbmouse.cpp(173):(assertion failed:`nength <= 32       # プログラム自体がassertionエラー
```

#### 3. USBメモリを接続

2のassertionエラーはUSBメモリではなくマウスをつなげていたためだった。

```
logger: Circle 44.5 started on Raspberry Pi 3 Model B+ (AArch64)
00:00:00.66 timer: SpeedFactor is 1.51
00:00:01.52 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:01.52 usbdev0-1: Interface int9-0-1 found
00:00:01.53 usbdev0-1: Function is not supported
00:00:01.53 usbdev0-1: Interface int9-0-2 found
00:00:01.53 usbdev0-1: Using device/interface int9-0-2
00:00:02.25 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:02.26 usbdev0-1: Interface int9-0-1 found
00:00:02.26 usbdev0-1: Function is not supported
00:00:02.27 usbdev0-1: Interface int9-0-2 found
00:00:02.27 usbdev0-1: Using device/interface int9-0-2
00:00:02.99 usbdev0-1: Device ven424-7800 found
00:00:02.99 usbdev0-1: Using device/interface ven424-7800
00:00:03.13 lan7800: MAC address is B8:27:EB:AB:E8:48
00:00:03.28 usbhub: Port 1: Device configured
00:00:03.28 usbhub: Port 1: Device configured
00:00:03.29 dwroot: Device configured
00:00:03.29 kernel: Compile time: Sep 17 2022 10:58:01
00:00:03.29 kernel: Plug in an USB flash drive!
00:00:13.95 usbdev0-1: Device ven411-110 found
00:00:13.96 usbdev0-1: Product: BUFFALO USB Flash Disk
00:00:13.96 usbdev0-1: Interface int8-6-50 found
00:00:13.96 usbdev0-1: Using device/interface int8-6-50
00:00:14.22 umsd: Capacity is 3824 MByte
00:00:14.22 usbhub: Port 2: Device configured
00:00:14.30 fatinfo: FAT32: 977025 clusters of 4.0K
00:00:14.31 dwhci: Transaction failed (status 0x202)        // transactionエラー
00:00:14.31 kernel: Remove USB flash drive!
00:00:29.93 usbdev0-1: Device ven411-110 removed
00:00:29.94 kernel: Plug in an USB flash drive!
00:00:37.29 usbdev0-1: Device ven411-110 found
00:00:37.30 usbdev0-1: Product: BUFFALO USB Flash Disk
00:00:37.30 usbdev0-1: Interface int8-6-50 found
00:00:37.31 usbdev0-1: Using device/interface int8-6-50
00:00:37.57 umsd: Capacity is 3824 MByte
00:00:37.57 usbhub> Port 2: Device configu?ed
00:00:37.61 dwhci: Transaction failed (status 0x202)        // transactionエラー
00:00:37.64 fatinfo: FAT32: 977025 clusters of 4.0K
00:00:37.65 kernel: Remove USB flash drive!
Illegal instruction: 4
```

#### 4. `addon/fatfs`を使用

```
$ cd addon/fatfs
$ make
  CC    ff.o
  CPP   diskio.o
  CPP   ffsystem.o
  CC    ffunicode.o
  AR    libfatfs.a
$ cd sample/390umsdplugging
$ make clean
$ make
$ make flash
$ minicom

logger: Circle 44.5 started on Raspberry Pi 3 Model B+ (AArch64)
00:00:00.66 timer: SpeedFactor is 1.51
00:00:01.52 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:01.52 usbdev0-1: Interface int9-0-1 found
00:00:01.53 usbdev0-1: Function is not supported
00:00:01.53 usbdev0-1: Interface int9-0-2 found
00:00:01.53 usbdev0-1: Using device/interface int9-0-2
00:00:02.25 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:02.26 usbdev0-1: Interface int9-0-1 found
00:00:02.26 usbdev0-1: Function is not supported
00:00:02.27 usbdev0-1: Interface int9-0-2 found
00:00:02.27 usbdev0-1: Using device/interface int9-0-2
00:00:02.99 usbdev0-1: Device ven424-7800 found
00:00:02.99 usbdev0-1: Using device/interface ven424-7800
00:00:03.13 lan7800: MAC address is B8:27:EB:AB:E8:48
00:00:03.28 usbhub: Port 1: Device configured
00:00:03.28 usbhub: Port 1: Device configured
00:00:03.29 dwroot: Device configured
00:00:03.29 kernel: Compile time: Sep 17 2022 11:29:16
00:00:03.29 kernel: Plug in an USB flash drive!
00:00:11.65 usbdev0-1: Device ven411-110 found
00:00:11.65 usbdev0-1: Product: BUFFALO USB Flash Disk
00:00:11.66 usbdev0-1: Interface int8-6-50 found
00:00:11.66 usbdev0-1: Using device/interface int8-6-50
00:00:11.92 umsd: Capacity is 3824 MByte
00:00:11.92 usbhub: Port 2: Device configured               // transactionエラーは発生しないがdir listはない
00:00:11.93 kernel: Remove USB flash drive!
00:00:29.09 usbdev0-1: Device ven411-110 removed
00:00:29.09 kernel: Plug in an USB flash drive!
00:00:37.21 usbdev0-1: Device ven411-110 found
00:00:37.22 usbdev0-1: Product: BUFFALO USB Flash Disk
00:00:37.22 usbdev0-1: Interface int8-6-50 found
00:00:37.23 usbdev0-1: Using device/interface int8-6-50
00:00:37.49 umsd: Capacity is 3824 MByte
00:00:37.49 usbhub: Port 2: Device configured
00:00:37.50 kernel: Remove USB flash drive!
00:00:47.49 usbdev0-1: Device ven411-110 removed
00:00:47.49 kernel: Plug in an USB flash drive!
```

#### 5. デフォルトクラスを使用

ファイル表示はスクリーンにされていた。ログ出力もするようにコードを変更。

```
logger: Circle 44.5 started on Raspberry Pi 3 Model B+ (AArch64)
00:00:00.66 timer: SpeedFactor is 1.51
00:00:01.52 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:01.52 usbdev0-1: Interface int9-0-1 found
00:00:01.53 usbdev0-1: Function is not supported
00:00:01.53 usbdev0-1: Interface int9-0-2 found
00:00:01.53 usbdev0-1: Using device/interface int9-0-2
00:00:02.25 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:02.26 usbdev0-1: Interface int9-0-1 found
00:00:02.26 usbdev0-1: Function is not supported
00:00:02.27 usbdev0-1: Interface int9-0-2 found
00:00:02.27 usbdev0-1: Using device/interface int9-0-2
00:00:02.99 usbdev0-1: Device ven424-7800 found
00:00:02.99 usbdev0-1: Using device/interface ven424-7800
00:00:03.13 lan7800: MAC address is B8:27:EB:AB:E8:48
00:00:03.28 usbhub: Port 1: Device configured
00:00:03.28 usbhub: Port 1: Device configured
00:00:03.29 dwroot: Device configured
00:00:03.29 kernel: Compile time: Sep 17 2022 12:28:03
00:00:03.29 kernel: Plug in an USB flash drive!
00:00:10.88 usbdev0-1: Device ven8564-1000 found
00:00:10.88 usbdev0-1: Product: JetFlash Mass Storage Device
00:00:10.89 usbdev0-1: Interface int8-6-50 found
00:00:10.89 usbdev0-1: Using device/interface int8-6-50
00:00:10.98 dwhci: Transaction failed (status 0x202)
00:00:11.32 umsd: Capacity is 7722 MByte
00:00:11.32 usbhub: Port 2: Device configured
00:00:11.33 fatinfo: FAT32: 1972225 clusters of 4.0K
00:00:11.33 kernel: entry: 1
00:00:11.33 kernel: file: test.txt                          // ファイル名が表示されている
00:00:11.34 kernel: next_entry: 1
00:00:11.34 kernel: file: test2.txt                         // ファイル名が表示されている
00:00:11.34 kernel: next_entry: 0
00:00:11.35 kernel: Remove USB flash drive!
00:00:19.80 usbdev0-1: Device ven8564-1000 removed
00:00:19.80 kernel: Plug in an USB flash drive!
```
