# サンプル 27: usbgamepad

このサンプルは接続されたUSBゲームパッドのコントロール情報を表示します。
起動すると使用可能なコントロール（ボタン、軸、ハット）の情報が表示されます。
その後、ボタンを押したり、軸やハットを動かしたりすると、すべての
コントロールの現在の状態が表示されます。

このサンプルはUSBプラグアンドプレイに対応しているためシステム稼働中、稼働前の
いつでもUSBゲームパッドの着脱が可能です。装着すると自動的に検出され、使用する
ことができます。Raspberry Pi 1-3とZeroでこのサンプルプログラムを使用するには
`include/circle/sysconfig.h`ファイルでシステムオプション`USE_USB_SOF_INTR`を
定義する必要があります。

CircleはUSB HIDクラスの標準レポートインターフェース(3-0-0)のゲームパッドと
一部のよく知られたブランドの独自USBインターフェースのゲームパッドに対応しています。
このシンプルなサンプルはこれらのサポート済みのゲームパッドのすべてで動作します。
`sample/37-showgamepad`はゲームパッドの制御をより簡単に調査することができますが、
既知のゲームパッドでしか動作しません。

USB HIDクラスの標準レポートインターフェイスをサポートしているが完全修飾された
レポートディスクリプタを持たないUSBゲームパッドもあります。このようなゲーム
パッドのサポートは一部のゲームパッドコントロールに限られると思われます。

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
00:00:03.29 kernel: Compile time: Sep 19 2022 16:07:44
00:00:03.29 kernel: Please attach an USB gamepad, if not already done!
00:00:03.49 usbdev1-3: Device ven54c-268 found
00:00:03.52 usbdev1-3: Product: Sony_ PLAYSTATION(R)3 Controller
00:00:03.53 usbdev1-3: Using device/interface ven54c-268
00:00:03.62 usbhub: Port 3: Device configured
00:00:03.63 kernel: Gamepad 1: 19 Button(s) 0 Hat(s)
00:00:03.63 kernel: Gamepad 1: Axis 1: Minimum 0 Maximum 255
00:00:03.63 kernel: Gamepad 1: Axis 2: Minimum 0 Maximum 255
00:00:03.64 kernel: Gamepad 1: Axis 3: Minimum 0 Maximum 255
00:00:03.64 kernel: Gamepad 1: Axis 4: Minimum 0 Maximum 255
00:00:03.65 kernel: Gamepad 1: Axis 5: Minimum 0 Maximum 255
00:00:03.66 kernel: Gamepad 1: Axis 6: Minimum 0 Maximum 255
00:00:03.66 kernel: Gamepad 1: Axis 7: Minimum 0 Maximum 255
00:00:03.67 kernel: Gamepad 1: Axis 8: Minimum 0 Maximum 255
00:00:03.67 kernel: Gamepad 1: Axis 9: Minimum 0 Maximum 255
00:00:03.68 kernel: Gamepad 1: Axis 10: Minimum 0 Maximum 255
00:00:03.68 kernel: Gamepad 1: Axis 11: Minimum 0 Maximum 255
00:00:03.69 kernel: Gamepad 1: Axis 12: Minimum 0 Maximum 255
00:00:03.69 kernel: Gamepad 1: Axis 13: Minimum 0 Maximum 255
00:00:03.70 kernel: Gamepad 1: Axis 14: Minimum 0 Maximum 255
00:00:03.70 kernel: Gamepad 1: Axis 15: Minimum 0 Maximum 255
00:00:03.71 kernel: Gamepad 1: Axis 16: Minimum 0 Maximum 255
00:00:03.72 kernel: Use your gamepad controls!
00:00:03.72 kernel: Gamepad 1: Buttons 0x0 Axes 130 110 117 122 0 0 0 0 0 0 0 00
00:00:03.73 kernel: Gamepad 1: Buttons 0x0 Axes 134 113 121 126 0 0 0 0 0 0 0 00
...
00:00:10.14 kernel: Gamepad 1: Buttons 0x1000 Axes 128 142 127 129 0 0 0 0 0 0 0
00:00:10.15 kernel: Gamepad 1: Buttons 0x0 Axes 123 146 127 129 0 0 0 0 0 0 0 00
00:00:10.16 kernel: Gamepad 1: Buttons 0x1000 Axes 117 149 127 129 0 0 0 0 0 0 0
00:00:10.17 kernel: Gamepad 1: Buttons 0x1000 Axes 112 155 127 129 0 0 0 0 0 0 0
...
00:00:10.65 kernel: Gamepad 1: Buttons 0x0 Axes 140 119 122 151 0 0 0 0 0 0 0 00
00:00:10.66 kernel: Gamepad 1: Buttons 0x2000 Axes 140 119 111 148 0 0 0 0 0 0 0
00:00:10.67 kernel: Gamepad 1: Buttons 0x2000 Axes 140 119 100 147 0 0 0 0 0 0 0
...
00:00:13.69 kernel: Gamepad 1: Buttons 0x0 Axes 135 121 126 129 0 0 0 0 0 0 0 00
00:00:13.70 kernel: Gamepad 1: Buttons 0x100 Axes 135 121 127 129 0 0 0 0 0 0 00
00:00:13.71 kernel: Gamepad 1: Buttons 0x100 Axes 135 121 127 129 0 0 0 0 0 0 00
...
00:00:14.73 kernel: Gamepad 1: Buttons 0x0 Axes 135 121 127 129 0 0 0 0 0 0 0 00
00:00:14.74 kernel: Gamepad 1: Buttons 0x200 Axes 135 121 127 129 0 0 0 0 0 0 00
...
00:00:15.11 kernel: Gamepad 1: Buttons 0x0 Axes 135 121 126 129 0 0 0 0 0 0 0 00
00:00:15.12 kernel: Gamepad 1: Buttons 0x80 Axes 135 121 127 129 0 0 0 0 0 0 0 0
00:00:15.13 kernel: Gamepad 1: Buttons 0x80 Axes 135 121 127 129 0 0 0 0 0 0 0 0
```
