# サンプル 10: usbmouse

このサンプルプログラムの実行にはUSBマウスを装着する必要があります。
まずLEDを5回点滅してカーネルイメージが正しく読み込まれたことを示します。
初期化が終わっても画面は何も表示されていません。マウスの左ボタンまたは
右ボタンを押してマウスを動かすと画面に何かを書くことができます。マウスに
中ボタンがあれば、それを押すると画面をクリアすることができます。ホイールが
ある場合は、マウスの右ボタンで描画する際のピクセルの色を変えることができます。

本サンプルはUSBプラグアンドプレイに対応しているため、システム稼働中、稼働前の
いつでもUSBマウスを脱着することができます。USBマウスを装着すると自動的に検出され、
使用することができます。Raspberry Pi 1-3とZero ではこのサンプルプログラムを使用
するために`include/circle/sysconfig.h`ファイルでシステムオプション
`USE_USB_SOF_INTR`を定義しておく必要があります。

### 実行結果

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
00:00:03.29 kernel: Compile time: Sep 19 2022 15:53:55
00:00:03.29 kernel: Please attach an USB mouse, if not already done!
00:00:08.58 usbdev2-2: Device ven93a-2510 found
00:00:08.59 usbdev2-2: Product: PIXART USB OPTICAL MOUSE
00:00:08.60 usbdev2-2: Interface int3-1-2 found
00:00:08.60 usbdev2-2: Using device/interface int3-1-2
00:00:08.66 usbhub: Port 2: Device configured
00:00:08.67 kernel: USB mouse has 1431655765 buttons
00:00:08.67 kernel: USB mouse has a wheel
00:00:09.18 umouse: offset=0xd5d5d575, length=0x55455575
00:00:11.63 usbmouse.cpp(173): stack[1] is 0x906E0
00:00:11.63 usbmouse.cpp(173): stack[4] is 0x907B0
00:00:11.63 usbmouse.cpp(173): stack[11] is 0x90804
00:00:11.63 usbmouse.cpp(173): stack[13] is 0x8E2B0
00:00:11.63 usbmouse.cpp(173): stack[16] is 0x907B0
00:00:11.63 usbmouse.cpp(173): stack[20] is 0x80F00
00:00:11.63 usbmouse.cpp(173): stack[23] is 0x84CA0
00:00:11.63 usbmouse.cpp(173): stack[28] is 0xA3A14
00:00:11.63 usbmouse.cpp(173): stack[29] is 0xA6088
00:00:11.63 usbmouse.cpp(173): stack[57] is 0x83A90
00:00:11.63 usbmouse.cpp(173): assertion failed: length <= 32
```
