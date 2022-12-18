# サンプル 05: usbsimple

このサンプルプログラムはボードにUSBハブを搭載したRaspberry Pi、
または外付けのUSBハブを装着したモデルでのみ動作します。

最初にLEDを5回点滅してカーネルイメージが正しく読み込まれたことを
示します。USBホストコントローラを初期化した後、USBハブのUSBデバイス
ディスクリプタを読み込んでログ出力します。とりあえずこれで終了です。
Raspberry PiにオンボードのUSBハブがあれば、このテストではUSBデバイスを
装着する必要はありません。

### 実行結果

```
logger: Circle 44.5 started on Raspberry Pi 3 Model B+ (AArch64)

00:00:00.66 timer: SpeedFactor is 1.51
                                                                # ルートハブ
00:00:01.52 usbdev0-1: Device ven424-2514, dev9-0-2 found       # CUSBDevice オブジェクト
00:00:01.52 usbdev0-1: Interface int9-0-1 found                 # vendor = Microchip‐SMSC
00:00:01.53 usbdev0-1: Function is not supported
00:00:01.53 usbdev0-1: Interface int9-0-2 found                 # function = 9: hub
00:00:01.53 usbdev0-1: Using device/interface int9-0-2          # protocol = 2: multiple TT

00:00:02.25 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:02.26 usbdev0-1: Interface int9-0-1 found
00:00:02.26 usbdev0-1: Function is not supported
00:00:02.27 usbdev0-1: Interface int9-0-2 found
00:00:02.27 usbdev0-1: Using device/interface int9-0-2
                                                                # マウス
00:00:02.43 usbdev1-3: Device ven93a-2510 found                 # vendor = 0x9aa: Pixart Imaging
00:00:02.45 usbdev1-3: Product: PIXART USB OPTICAL MOUSE
00:00:02.45 usbdev1-3: Interface int3-1-2 found                 # subclass = 1: keyboard or mouse
00:00:02.45 usbdev1-3: Using device/interface int3-1-2          # protocol = 2: mouse
                                                                # LAN7800 Ethernetコントローラ
00:00:03.17 usbdev0-1: Device ven424-7800 found                 # vendor = 0x424: Microchip‐SMSC
00:00:03.18 usbdev0-1: Using device/interface ven424-7800       # product = 780: LAN7800
                                                                # USBメモリ
00:00:03.33 usbdev0-1: Device ven8564-1000 found                # vendor = 8654: Transcend Information
00:00:03.34 usbdev0-1: Product: JetFlash Mass Storage Device
00:00:03.34 usbdev0-1: Interface int8-6-50 found                # type = 8: MSC, subtype = 6: SCSI Trasparent
00:00:03.35 usbdev0-1: Using device/interface int8-6-50         #  command set, protocol = 50: Bulk only

00:00:03.49 lan7800: MAC address is B8:27:EB:AB:E8:48           # CLAN7800 オブジェクト

00:00:03.63 usbhub: Port 1: Device ven424-7800 configured       # CUSBStandardHub オブジェクト

00:00:04.03 umsd: Capacity is 7722 MByte                        # CUSBBulkOnlyMassStorageDevice オブジェクト

00:00:04.03 usbhub: Port 2: Device ven8564-1000 configured
00:00:04.04 usbhub: Port 1: Device ven424-2514, dev9-0-2 configured
00:00:04.09 usbhub: Port 3: Device ven93a-2510 configured

00:00:04.10 dwroot: Device configured                           # CDWHCIRootPort オブジェクト

00:00:04.10 kernel: Compile time: Sep 23 2022 12:15:01
00:00:04.11 kernel: USB hub: Vendor 0x0424, Product 0x2514
00:00:04.11 kernel: Dumping device descriptor
00:00:04.11 kernel: Dumping 0x12 bytes starting at 0x29DA40
00:00:04.12 kernel: DA40: 12 01 00 02 09 00 02 40-24 04 14 25 B3 0B 00 00
00:00:04.13 kernel: DA50: 00 01 25 B8 40 00 98 3F-0A 28 54 4F 00 00 00 00
```

### もう一つUSBメモリを付けた場合

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
00:00:02.43 usbdev0-1: Device ven781-5170 found
00:00:02.45 usbdev0-1: Product: SanDisk Cruzer Colors+
00:00:02.45 usbdev0-1: Interface int8-6-50 found
00:00:02.45 usbdev0-1: Using device/interface int8-6-50
00:00:02.62 usbdev1-3: Device ven93a-2510 found
00:00:02.63 usbdev1-3: Product: PIXART USB OPTICAL MOUSE
00:00:02.63 usbdev1-3: Interface int3-1-2 found
00:00:02.64 usbdev1-3: Using device/interface int3-1-2
00:00:03.35 usbdev0-1: Device ven424-7800 found
00:00:03.36 usbdev0-1: Using device/interface ven424-7800
00:00:03.52 usbdev0-1: Device ven8564-1000 found
00:00:03.52 usbdev0-1: Product: JetFlash Mass Storage Device
00:00:03.53 usbdev0-1: Interface int8-6-50 found
00:00:03.53 usbdev0-1: Using device/interface int8-6-50
00:00:03.67 lan7800: MAC address is B8:27:EB:AB:E8:48
00:00:03.82 usbhub: Port 1: Device ven424-7800 configured
00:00:04.21 umsd: Capacity is 7722 MByte
00:00:04.21 usbhub: Port 2: Device ven8564-1000 configured
00:00:04.22 usbhub: Port 1: Device ven424-2514, dev9-0-2 configured
00:00:04.75 umsd: Capacity is 3824 MByte
00:00:04.80 usbhub: Port 2: Device ven781-5170 configured       # ポートの再利用をしている
00:00:04.86 usbhub: Port 3: Device ven93a-2510 configured
00:00:04.86 dwroot: Device configured
00:00:04.87 kernel: Compile time: Sep 24 2022 10:53:56
00:00:04.87 kernel: USB hub: Vendor 0x0424, Product 0x2514
00:00:04.88 kernel: Dumping device descriptor
00:00:04.88 kernel: Dumping 0x12 bytes starting at 0x29DA40
00:00:04.88 kernel: DA40: 12 01 00 02 09 00 02 40-24 04 14 25 B3 0B 00 00
00:00:04.89 kernel: DA50: 00 01 25 B8 40 00 98 3F-0A 28 54 4F 00 00 00 00
```

### ハブを接続し、そのハブにマウスを接続

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
00:00:02.43 usbdev0-1: Device ven5e3-608, dev9-0-1 found
00:00:02.43 usbdev0-1: Product: USB2.0 Hub
00:00:02.44 usbdev0-1: Interface int9-0-0 found
00:00:02.44 usbdev0-1: Using device/interface int9-0-0
00:00:03.16 usbdev0-1: Device ven424-7800 found
00:00:03.16 usbdev0-1: Using device/interface ven424-7800
00:00:03.32 usbdev0-1: Device ven8564-1000 found
00:00:03.33 usbdev0-1: Product: JetFlash Mass Storage Device
00:00:03.33 usbdev0-1: Interface int8-6-50 found
00:00:03.34 usbdev0-1: Using device/interface int8-6-50
00:00:03.47 lan7800: MAC address is B8:27:EB:AB:E8:48
00:00:03.62 usbhub: Port 1: Device ven424-7800 configured
00:00:04.02 umsd: Capacity is 7722 MByte
00:00:04.02 usbhub: Port 2: Device ven8564-1000 configured
00:00:04.03 usbhub: Port 1: Device ven424-2514, dev9-0-2 configured
00:00:04.75 usbdev3-3: Device ven93a-2510 found
00:00:04.76 usbdev3-3: Product: PIXART USB OPTICAL MOUSE
00:00:04.77 usbdev3-3: Interface int3-1-2 found
00:00:04.77 usbdev3-3: Using device/interface int3-1-2
00:00:04.83 usbhub: Port 3: Device ven93a-2510 configured
00:00:04.84 usbhub: Port 3: Device ven5e3-608, dev9-0-1 configured
00:00:04.85 dwroot: Device configured
00:00:04.85 kernel: Compile time: Sep 25 2022 11:24:58
00:00:04.85 kernel: USB hub: Vendor 0x0424, Product 0x2514
00:00:04.86 kernel: Dumping device descriptor
00:00:04.86 kernel: Dumping 0x12 bytes starting at 0x29DA40
00:00:04.87 kernel: DA40: 12 01 00 02 09 00 02 40-24 04 14 25 B3 0B 00 00
00:00:04.87 kernel: DA50: 00 01 25 B8 40 00 98 3F-0A 28 54 4F 00 00 00 00
```

## ディスクリプタをダンプ出力

```
logger: Circle 44.5 started on Raspberry Pi 3 Model B+ (AArch64)
00:00:00.66 timer: SpeedFactor is 1.51
00:00:01.47 usbdev: Dumping 0x12 bytes starting at 0x60BE40
00:00:01.47 usbdev: 1.48 usbdev: BE50: 00 01 25 B8 F5 75 55 55-35 56 55 55 D4 5D
00:00:01.53 usbdev: Dumping 0x29 bytes starting at 0x60BEC0
00:00:01.54 usbdev: BEC0: 09 02 29 00 01 01 00 E0-01 09 04 00 00 01 09 00
00:00:01.54 usbdev: BED0: 01 00 07 05 81 03 01 00-0C 09 04 00 01 01 09 00
00:00:01.55 usbdev: BEE0: 02 00 07 05 81 03 01 00-0C B4 37 00 20 35 35 20
00:00:01.56 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:01.56 usbdev0-1: Interface int9-0-1 found
00:00:01.57 usbdev0-1: Function is not supported
00:00:01.57 usbdev0-1: Interface int9-0-2 found
00:00:01.58 usbdev0-1: Using device/interface int9-0-2
00:00:02.24 usbdev: Dumping 0x12 bytes starting at 0x60EA80
00:00:02.25 usbdev: EA80: 12 01 00 02 09 00 02 40-24 04 14 25 B3 0B 00 00
00:00:02.25 usbdev: EA90: 00 01 25 B8 63 65 20 69-6E 74 39 2D 30 2D 32 00
00:00:02.31 usbdev: Dumping 0x29 bytes starting at 0x60FC80
00:00:02.32 usbdev: FC80: 09 02 29 00 01 01 00 E0-01 09 04 00 00 01 09 00
00:00:02.32 usbdev: FC90: 01 00 07 05 81 03 01 00-0C 09 04 00 01 01 09 00
00:00:02.33 usbdev: FCA0: 02 00 07 05 81 03 01 00-0C B4 37 00 20 32 44 20
00:00:02.33 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:02.34 usbdev0-1: Interface int9-0-1 found
00:00:02.34 usbdev0-1: Function is not supported
00:00:02.35 usbdev0-1: Interface int9-0-2 found
00:00:02.35 usbdev0-1: Using device/interface int9-0-2
00:00:03.02 usbdev: Dumping 0x12 bytes starting at 0x612980
00:00:03.03 usbdev: 2980: 12 01 10 02 FF 00 FF 40-24 04 00 78 00 03 00 00
00:00:03.03 usbdev: 2990: 00 01 07 A8 31 3A 20 49-6E 74 65 72 66 61 63 65
00:00:03.09 usbdev: Dumping 0x27 bytes starting at 0x612A80
00:00:03.09 usbdev: 2A80: 09 02 27 00 01 01 00 E0-01 09 04 00 00 03 FF 00
00:00:03.10 usbdev: 2A90: FF 00 07 05 81 02 00 02-00 07 05 02 02 00 02 00
00:00:03.11 usbdev: 2AA0: 07 05 83 03 10 00 04 E9-32 20 36 36 20 36 31 20
00:00:03.11 usbdev0-1: Device ven424-7800 found
00:00:03.12 usbdev0-1: Using device/interface ven424-7800
00:00:03.26 lan7800: MAC address is B8:27:EB:AB:E8:48
00:00:03.40 usbhub: Port 1: Device ven424-7800 configured
00:00:03.41 usbhub: Port 1: Device ven424-2514, dev9-0-2 configured
00:00:03.42 dwroot: Device configured
00:00:03.42 kernel: Compile time: Nov 27 2022 16:43:57
00:00:03.42 kernel: USB hub: Vendor 0x0424, Product 0x2514
00:00:03.43 kernel: Dumping device descriptor
00:00:03.43 kernel: Dumping 0x12 bytes starting at 0x29DA40
00:00:03.44 kernel: DA40: 12 01 00 02 09 00 02 40-24 04 14 25 B3 0B 00 00
00:00:03.44 kernel: DA50: 00 01 25 B8 00 00 00 00-0D 00 00 00 00 00 00 00
```

