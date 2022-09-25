//
// sysconfig.h
//
// Configurable system options
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2022  R. Stange <rsta2@o2online.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef _circle_sysconfig_h
#define _circle_sysconfig_h

///////////////////////////////////////////////////////////////////////
//
// メモリ
//
///////////////////////////////////////////////////////////////////////

#define MEGABYTE		0x100000	// do not change

// KERNEL_MAX_SIZEはビルドするカーネルイメージの最大許容サイズです。
// 作成するカーネルイメージが大量のデータを含む場合はこの値を増加
// させるひつようがあるかもしれません。値は16KBの倍数である必要があります。

#ifndef KERNEL_MAX_SIZE
#define KERNEL_MAX_SIZE		(2 * MEGABYTE)
#endif

// HEAP_DEFAULT_NEWは、メモリタイプが明示的に指定されない場合に、
// "new"演算子で使用するデフォルトヒープを定義します。指定可能な
// 値は、HEAP_LOW（1GB以下のメモリ）、HEAP_HIGH（1GB以上のメモリ）、
// HEAP_ANY（利用可能であれば1GB以上 、そうでなければ1GB以下のメモリ） 。
// この値にHEAP_ANYを設定すると事実上統一ヒープとなり、利用可能な
// すべてのメモリ空間を使用します。これはDMA用に明示的に低位メモリを
// 必要とする一部のデバイスで問題を引き起こす可能性があるため、この値の
// デフォルトはHEAP_LOWに設定されています。この設定が重要なのはRaspberry
// Pi 4だけです。

#ifndef HEAP_DEFAULT_NEW
#define HEAP_DEFAULT_NEW	HEAP_LOW
#endif

// HEAP_DEFAULT_MALLOCは、malloc()とcalloc()で使用されるヒープを定義します。
// 書斎はHEAP_DEFAULT_NEWの説明を参照してください。おの設定を変更することは
// 推奨しません。malloc()を使ってDMA用に低位メモリの割当を要求する
// デバイスドライバが存在するためです。この設定が重要なのはRaspberry
// Pi 4だけです。

#ifndef HEAP_DEFAULT_MALLOC
#define HEAP_DEFAULT_MALLOC	HEAP_LOW
#endif

// HEAP_BLOCK_BUCKET_SIZESは、動的メモリ管理 ("new" 演算子と malloc()) の
// ベースとなるヒープアロケータを構成します。ヒープアロケータは空きメモリ
// ブロックをいくつかの空きリスト (バケット) に分けて管理します。各フリー
// リストには特定のサイズのブロックが含まれています。ブロックを割り当てる際
// 要求されたブロックサイズは次に利用可能なバケットサイズのサイズに切り上げ
// られます。要求されたサイズが利用可能な最大のバケットサイズより大きい場合、
// そのブロックは割り当てられますが、そのブロックが解放される際にそのメモリ
// 領域は失われます。ブロックバケットは割当と解放のたびに確認しなければなら
// ないのでバケットの数は少ないほうが望ましい。このオプションを使用すると
// アプリケーションのニーズに最適なバケットサイズを設定することができます。
// バケツサイズをカンマ区切りで昇順に指定する必要があります。すべてのサイズは
// 64の倍数である必要があります。最大で20個のサイズを定義することができます。

#ifndef HEAP_BLOCK_BUCKET_SIZES
#define HEAP_BLOCK_BUCKET_SIZES	0x40,0x400,0x1000,0x4000,0x10000,0x40000,0x80000
#endif

///////////////////////////////////////////////////////////////////////
//
// Raspberry Pi 1, Zero (W) and Zero 2 W
//
///////////////////////////////////////////////////////////////////////

#if RASPPI == 1

// ARM_STRICT_ALIGNMENT activates the memory alignment check. If an
// unaligned memory access occurs an exception is raised with this
// option defined. This should normally not be activated, because
// newer Circle images are not tested with it.

//#define ARM_STRICT_ALIGNMENT

// GPU_L2_CACHE_ENABLED has to be defined, if the L2 cache of the GPU
// is enabled, which is normally the case. Only if you have disabled
// the L2 cache of the GPU in config.txt this option must be undefined.

#ifndef NO_GPU_L2_CACHE_ENABLED
#define GPU_L2_CACHE_ENABLED
#endif

#endif

#if RASPPI == 1 || RASPPI == 3

// USE_PWM_AUDIO_ON_ZEROは、RPi Zero（W）とZero 2 WでGPIO12/13
// （または18/19）をPWMオーディオ出力に使用するために定義できます。
// これを使用するには何らかの外部回路が必要です。
// 警告: RPi Zeroでこのオプションを定義した場合は、これらのGPIOピンに
//       電圧を印加しないでください、ピンが破壊される可能性があります。

//#define USE_PWM_AUDIO_ON_ZERO

// The left PWM audio output pin is by default GPIO12. The following
// define moves it to GPIO18.
//#define USE_GPIO18_FOR_LEFT_PWM_ON_ZERO

// The right PWM audio output pin is by default GPIO13. The following
// define moves it to GPIO19.
//#define USE_GPIO19_FOR_RIGHT_PWM_ON_ZERO

#endif

///////////////////////////////////////////////////////////////////////
//
// Raspberry Pi 2, 3 and 4
//
///////////////////////////////////////////////////////////////////////

#if RASPPI >= 2

// USE_RPI_STUB_AT enables the debugging support for rpi_stub and
// defines the address where rpi_stub is loaded. See doc/debug.txt
// for details! Kernel images built with this option defined do
// normally not run without rpi_stub loaded.

//#define USE_RPI_STUB_AT 	0x1F000000

#ifndef USE_RPI_STUB_AT

// ARM_ALLOW_MULTI_COREは、CMultiCoreSupportクラスによるマルチコア
// サポートを使用するには、定義しなければなりません。シングルコア
// アプリケーションの場合は定義するべきではありません。マルチコアは
// 使用しなくてもバス時間を計算するのでシステムがスローダウンする
// 可能性があるためです。

//#define ARM_ALLOW_MULTI_CORE

#endif

// USE_PHYSICAL_COUNTER enables the use of the CPU internal physical
// counter, which is only available on the Raspberry Pi 2, 3 and 4. Reading
// this counter is much faster than reading the BCM2835 system timer
// counter (which is used without this option). It reduces the I/O load
// too. For some QEMU versions this is the only supported timer option,
// for other older QEMU versions it does not work. On the Raspberry Pi 4
// setting this option is required.

#ifndef NO_PHYSICAL_COUNTER
#define USE_PHYSICAL_COUNTER
#endif

#endif

#if RASPPI >= 4

// USE_XHCI_INTERNAL enables the xHCI controller, which is integrated
// into the BCM2711 SoC. The Raspberry Pi 4 provides two independent
// xHCI USB host controllers, an external controller, which is connected
// to the four USB-A sockets (USB 3.0 and 2.0) and an internal controller,
// which is connected to the USB-C power socket (USB 2.0 only). By default
// Circle uses the external xHCI controller. If you want to use the
// internal controller instead, this option has to be defined. Enabling
// this option is the only possibility to use USB on the Compute Module 4
// with Circle. This setting requires the option "otg_mode=1" set in the
// config.txt file too!

//#define USE_XHCI_INTERNAL

#endif

///////////////////////////////////////////////////////////////////////
//
// Timing
//
///////////////////////////////////////////////////////////////////////

// REALTIME optimizes the IRQ latency of the system, which could be
// useful for time-critical applications. This will be accomplished
// by disabling some features (e.g. USB low-/full-speed device support).
// See doc/realtime.txt for details!

//#define REALTIME

// USE_USB_SOF_INTRは、LS/FS USBデバイスとの互換性を向上させます。
// このようなデバイスを使用するアプリケーションでは通常、この
// オプションを設定するべきです。残念ながら、このオプションはシステムの
// タイミングを大きく変化させる原因となります。1秒間に最大8000回、IRQを
// トリガーするためです。USBのプラグアンドプレイを動作させるためには
// このオプションはいかなる場合でも設定しなければなりません。この
// オプションはRaspberry Pi 4には影響ありません。

#ifndef NO_USB_SOF_INTR
#define USE_USB_SOF_INTR
#endif

// USE_USB_FIQは、USBコントローラからのタイムクリティカルな割り込み
// （毎秒8000回発生）をFIQで処理することでUSBのタイミングをより正確に
// するものです。デフォルトのIRQを使用すると、他のIRQが処理されている
// ときにUSB割り込みが遅れたり、マイクロフレーム全体がスキップされる
// ことがあり、一部のUSBデバイスとの通信に問題が発生する場合があります。
// このオプションを有効にする場合はUSE_USB_SOF_INTRも有効にします。FIQを
// 他の用途に使用することができなくなります。このオプションはRaspberry
// Pi 4には影響ありません。

//#define USE_USB_FIQ

#ifdef USE_USB_FIQ
#define USE_USB_SOF_INTR
#endif

// SCREEN_DMA_BURST_LENGTH enables using DMA for scrolling the screen
// contents and set the burst length parameter for the DMA controller.
// Using DMA speeds up the scrolling, especially with a burst length
// greater than 0. The parameter can be 0-15 theoretically, but values
// over 2 are normally not useful, because the system bus gets congested
// with it.

#ifndef SCREEN_DMA_BURST_LENGTH
#define SCREEN_DMA_BURST_LENGTH	2
#endif

// CALIBRATE_DELAY activates the calibration of the delay loop. Because
// this loop is normally not used any more in Circle, the only use of
// this option is that the "SpeedFactor" of your system is displayed.
// You can reduce the time needed for booting, if you disable this.

#ifndef NO_CALIBRATE_DELAY
#define CALIBRATE_DELAY
#endif

///////////////////////////////////////////////////////////////////////
//
// Scheduler
//
///////////////////////////////////////////////////////////////////////

// MAX_TASKS is the maximum number of tasks in the system.

#ifndef MAX_TASKS
#define MAX_TASKS		20
#endif

// TASK_STACK_SIZE is the stack size for each task.

#ifndef TASK_STACK_SIZE
#define TASK_STACK_SIZE		0x8000
#endif

// NO_BUSY_WAITは、EMMC、SDHOST、USBドライバで同期転送の完了を待つ
// ビジーウェイトを無効にします。このオプションを有効にするには
// システムにスケジューラが必要となり、セカンダリCPUコアから転送を
// 開始することはできません。

//#define NO_BUSY_WAIT

///////////////////////////////////////////////////////////////////////
//
// USB keyboard
//
///////////////////////////////////////////////////////////////////////

// DEFAULT_KEYMAP selects the default keyboard map (enable only one).
// The default keyboard map can be overwritten in with the keymap=
// option in cmdline.txt.

#ifndef DEFAULT_KEYMAP

#define DEFAULT_KEYMAP		"DE"
//#define DEFAULT_KEYMAP		"ES"
//#define DEFAULT_KEYMAP		"FR"
//#define DEFAULT_KEYMAP		"IT"
//#define DEFAULT_KEYMAP		"UK"
//#define DEFAULT_KEYMAP		"US"

#endif

///////////////////////////////////////////////////////////////////////
//
// Other
//
///////////////////////////////////////////////////////////////////////

// SCREEN_HEADLESSは、Raspberry Piがディスプレイを接続せずに動作する場合に
// 定義することができます。Circleのサンプルプログラムの多くは、通常、
// ディスプレイが接続されていることを前提に動作しますが、中にはディスプレイが
// なくても使用できるものもあります。以前はディスプレイが接続されていなくても
// 画面の初期化はエラーを返さずに動作していましたが、特にRaspberry Pi 4では
// そのようなことはありません。このオプションを定義しておかないと、プログラムの
// 初期化に失敗します。ヘッドレスアプリケーションでは、CScreenDeviceクラスを
// 使用せず直接、CSerialDeviceまたはCNullDeviceにロガー出力指定する必要が
// あります。

#define SCREEN_HEADLESS

// SERIAL_GPIO_SELECT selects the TXD GPIO pin used for the serial
// device (UART0). The RXD pin is (SERIAL_GPIO_SELECT+1). Modifying
// this setting can be useful for Compute Modules. Select only one
// definition.

#ifndef SERIAL_GPIO_SELECT

#define SERIAL_GPIO_SELECT	14	// and 15
//#define SERIAL_GPIO_SELECT	32	// and 33
//#define SERIAL_GPIO_SELECT	36	// and 37

#endif

// USE_EMBEDDED_MMC_CM enables access to the on-board embedded MMC
// memory on Compute Modules 3+ and 4. Does not work with SD card on
// CM3+ Lite and CM4 Lite.

//#define USE_EMBEDDED_MMC_CM

// USE_SDHOST selects the SDHOST device as interface for SD card
// access. Otherwise the EMMC device is used for this purpose. The
// SDHOST device is supported by Raspberry Pi 1-3 and Zero, but
// not by QEMU. If you rely on a small IRQ latency, USE_SDHOST should
// be disabled.

#if RASPPI <= 3 && !defined (REALTIME) && !defined (USE_EMBEDDED_MMC_CM)

#ifndef NO_SDHOST
#define USE_SDHOST
#endif

#endif

// SD_HIGH_SPEED enables the high-speed extensions of the SD card
// driver, which should result in a better performance with modern SD
// cards. This is not tested that widely like the standard driver, why
// it is presented as an option here, but is enabled by default.

#ifndef NO_SD_HIGH_SPEED
#define SD_HIGH_SPEED
#endif

// SAVE_VFP_REGS_ON_IRQ enables saving the floating point registers
// on entry when an IRQ occurs and will restore these registers on exit
// from the IRQ handler. This has to be defined, if an IRQ handler
// modifies floating point registers. IRQ handling will be a little
// slower then.

//#define SAVE_VFP_REGS_ON_IRQ

// SAVE_VFP_REGS_ON_FIQ enables saving the floating point registers
// on entry when an FIQ occurs and will restore these registers on exit
// from the FIQ handler. This has to be defined, if the FIQ handler
// modifies floating point registers. FIQ handling will be a little
// slower then.

//#define SAVE_VFP_REGS_ON_FIQ

// LEAVE_QEMU_ON_HALT can be defined to exit QEMU when halt() is
// called or main() returns EXIT_HALT. QEMU has to be started with the
// -semihosting option, so that this works. This option must not be
// defined for Circle images which will run on real Raspberry Pi boards.

//#define LEAVE_QEMU_ON_HALT

// USE_QEMU_USB_FIXは、QEMUでCircleイメージを使用する際の問題を修正
// します。QEMUでUSBを使用する際にCircleがフリーズした場合、この
// オプションを有効にする必要があります。実際のRaspberry Piボードで
// 動作させるCircleイメージでは定義してはいけません。

//#define USE_QEMU_USB_FIX

///////////////////////////////////////////////////////////////////////

#include <circle/memorymap.h>

#endif
