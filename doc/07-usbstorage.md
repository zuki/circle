# サンプル 07: usbstorage

カーネルイメージが読み込まれたことを示すためにまずLEDを5回点滅します。
USBホストコントローラの初期化が終わるとUSBハブドライバは接続されている
すべてのUSBデバイスを検出し、その識別子（ベンダー、デバイス、インタ
フェース）を表示します。

このステップの新機能は、USBマスストレージデバイスのサポートです（USBメモリや
USBハードディスクも動作するはずです）。サンプルプログラムを実行するには
USBポートにそのようなデバイス（**重要なデータが入っていてはいけません**）を
接続する必要があります。サンプルプログラムはデバイスの最初のセクタ(マスター
ブートレコード)を読み込んでパーティションテーブルをダンプするだけです。
ドライバはデバイスに書き込むこともできますがここでは使用しません。

現時点ではドライバは複数の論理ユニット(カードリーダなどのLUN)を持つデバイスは
サポートしていません。アクセスされる論理ユニットは常にLUN0です。

### 実行結果

```
logger: Circle 44.5 started on Raspberry Pi 3 Model B+ (AArch64)
00:00:00.66 timer: SpeedFactor is 1.51
00:00:01.52 usbdev0-1: Device ven424-2514, dev9-0-2 found   // usbdev0-1: 0=HUBアドレス、1=port番号
00:00:01.52 usbdev0-1: Interface int9-0-1 found             // ven424-2514:
00:00:01.53 usbdev0-1: Function is not supported            //      424=vendor id (Microchip‐SMSC )
00:00:01.53 usbdev0-1: Interface int9-0-2 found             //      2514=product id
00:00:01.53 usbdev0-1: Using device/interface int9-0-2      // dev9-0-2: 9=hub class, 0=sub class,
00:00:02.25 usbdev0-1: Device ven424-2514, dev9-0-2 found   //           2=Hi-speed hub with multiple TTs
00:00:02.26 usbdev0-1: Interface int9-0-1 found
00:00:02.26 usbdev0-1: Function is not supported
00:00:02.27 usbdev0-1: Interface int9-0-2 found
00:00:02.27 usbdev0-1: Using device/interface int9-0-2
00:00:02.43 usbdev1-3: Device ven93a-2510 found             // マウス: 0x93a=Pixart Imaging
00:00:02.45 usbdev1-3: Product: PIXART USB OPTICAL MOUSE
00:00:02.45 usbdev1-3: Interface int3-1-2 found             // int3-1-2: 3=HID class
00:00:02.45 usbdev1-3: Using device/interface int3-1-2
00:00:03.17 usbdev0-1: Device ven424-7800 found             // Ethernet: 0x424=Microchip‐SMSC
00:00:03.18 usbdev0-1: Using device/interface ven424-7800   //           7800=lan7800
00:00:03.33 usbdev0-1: Device ven8564-1000 found            // USBメモリ: 8564=Transcend Information
00:00:03.34 usbdev0-1: Product: JetFlash Mass Storage Device
00:00:03.34 usbdev0-1: Interface int8-6-50 found            // int8-6-50: 8=Mass Storage class
00:00:03.35 usbdev0-1: Using device/interface int8-6-50
00:00:03.49 lan7800: MAC address is B8:27:EB:AB:E8:48
00:00:03.63 usbhub: Port 1: Device configured
00:00:04.03 umsd: Capacity is 7722 MByte
00:00:04.03 usbhub: Port 2: Device configured
00:00:04.04 usbhub: Port 1: Device configured
00:00:04.09 usbhub: Port 3: Device configured
00:00:04.10 dwroot: Device configured
00:00:04.10 kernel: Compile time: Sep 20 2022 11:59:45
00:00:04.11 kernel: Dumping the partition table
00:00:04.11 kernel: # Status Type  1stSector    Sectors
00:00:04.12 kernel: 1 80     0B         6000   15808656
00:00:04.12 kernel: 2 00     00            0          0
00:00:04.12 kernel: 3 00     00            0          0
00:00:04.13 kernel: 4 00     00            0          0
```
