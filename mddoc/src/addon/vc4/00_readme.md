# vc4: README

このディレクトリにはVCHIQインターフェースデバイス用のドライバと
関連するヘッダーファイル、VCHIQオーディオサービスドライバ、このドライバを
使ってサウンドサンプルを再生するサンプルプログラムが含まれています。
VCHIQはRaspberry PiのVPU（ビデオ処理ユニット）とARM CPUの間のメッセージ
ベースのインタフェースです。これはさまざまな種類のメディアデータの転送に
使用されます。

さらに、サブディレクトリ `addon/vc4/interface/`には、EGLとOpenGL ES、OpenVG、
Dispmanx API を実装した、アクセラレーション対応のグラフィックスユーザランド
コードの部分的な移植版が含まれています。詳細についてはこのサブディレクトリ
にある README ファイルをご確認ください。

VCHIQサウンドサンプルプログラムをビルドするには、まず、Circleのベースライブラリと
ディレクトリ `addon/linux/` のLinuxカーネルドライバエミュレーションライブラリを
ビルドする必要があります。その後、ディレクトリ `addon/vc4/` で次のコマンドを
実行してください。

```bash
	./makeall clean
	./makeall
```

サンプルプログラムはディレクトリ `addon/vc4/sound/sample/` にあります。

VCHIQ インタフェースドライバのソースコードとVCHIQ オーディオサービスドライバの
ソースコードの一部は Linux から流用したものです。

```bash
	Copyright (c) 2010-2014 Broadcom. All rights reserved.
```

また、一部のコードは

```bash
	Copyright (c) 2014 Raspberry Pi (Trading) Ltd. All rights reserved.
```

このソースコードは GPLv2 の下でライセンスされています。詳細については
これらのソースファイルのヘッダーを参照してください。

## 実行結果

###  `Config.mk`を変更

```bash
PREFIX = arm-none-eabi-
AARCH = 32
RASPPI = 3
DEFINE += -DARM_ALLOW_MULTI_CORE
DEFINE += -DDEFAULT_KEYMAP=\"us\"
SERIALPORT = /dev/cu.usbserial-AI057C9L
FLASHBAUD =  921600
USERBAUD = 115200
```

### ビルド

```bash
$ cd $(CIRCLE)
$ ./makeall
  TOOL  cflashy
  TOOL  converttool
  CPP   actled.o
  CPP   alloc.o
  CPP   assert.o
  CPP   display.o
  CPP   windowdisplay.o
  CPP   bcmframebuffer.o
  CPP   bcmmailbox.o
  CPP   bcmpropertytags.o
  CPP   bcmwatchdog.o
  CPP   chargenerator.o
  CPP   classallocator.o
  CPP   cputhrottle.o
  CPP   debug.o
  AS    delayloop.o
  CPP   device.o
  CPP   devicenameservice.o
  CPP   dmachannel.o
  CPP   koptions.o
  CPP   logger.o
  CPP   machineinfo.o
  CPP   multicore.o
  CPP   nulldevice.o
  CPP   ptrarray.o
  CPP   ptrlist.o
  CPP   qemu.o
  CPP   terminal.o
  CPP   screen.o
  CPP   serial.o
  CPP   spinlock.o
  CPP   string.o
  CPP   sysinit.o
  CPP   time.o
  CPP   timer.o
  CPP   tracer.o
  CPP   util.o
  AS    util_fast.o
  CPP   virtualgpiopin.o
  CPP   chainboot.o
  CPP   macaddress.o
  CPP   netdevice.o
  CPP   new.o
  CPP   heapallocator.o
  CPP   pageallocator.o
  AS    setjmp.o
  CPP   numberpool.o
  CPP   writebuffer.o
  CPP   2dgraphics.o
  CPP   ptrlistfiq.o
  CPP   font6x7.o
  CPP   font8x8.o
  CPP   font8x10.o
  CPP   font8x12.o
  CPP   font8x14.o
  CPP   font8x16.o
  CPP   font12x22.o
  AS    cache-v7.o
  CPP   exceptionhandler.o
  AS    exceptionstub.o
  CPP   memory.o
  CPP   pagetable.o
  AS    startup.o
  CPP   synchronize.o
  CPP   bcmrandom.o
  CPP   interrupt.o
  CPP   mphi.o
  CPP   gpioclock.o
  CPP   gpiomanager.o
  CPP   gpiopin.o
  CPP   gpiopinfiq.o
  CPP   i2cmaster.o
  CPP   i2cmasterirq.o
  CPP   i2cslave.o
  CPP   pwmoutput.o
  CPP   smimaster.o
  CPP   spimaster.o
  CPP   spimasteraux.o
  CPP   spimasterdma.o
  CPP   usertimer.o
  CPP   latencytester.o
  CPP   purecall.o
  CPP   cxa_guard.o
  AR    libcircle.a
  CPP   lan7800.o
  CPP   smsc951x.o
  CPP   usbbluetooth.o
  CPP   usbcdcethernet.o
  CPP   usbfloppydevice.o
  CPP   usbconfigparser.o
  CPP   usbdevice.o
  CPP   usbdevicefactory.o
  CPP   usbendpoint.o
  CPP   usbfunction.o
  CPP   usbgamepad.o
  CPP   usbgamepadps3.o
  CPP   usbgamepadps4.o
  CPP   usbgamepadstandard.o
  CPP   usbgamepadswitchpro.o
  CPP   usbgamepadxbox360.o
  CPP   usbgamepadxboxone.o
  CPP   usbhiddevice.o
  CPP   usbhostcontroller.o
  CPP   usbkeyboard.o
  CPP   usbmassdevice.o
  CPP   usbmidi.o
  CPP   usbmidihost.o
  CPP   usbmouse.o
  CPP   usbprinter.o
  CPP   usbrequest.o
  CPP   usbstandardhub.o
  CPP   usbstring.o
  CPP   usbserial.o
  CPP   usbserialhost.o
  CPP   usbserialch341.o
  CPP   usbserialcp210x.o
  CPP   usbserialpl2303.o
  CPP   usbserialft231x.o
  CPP   usbserialcdc.o
  CPP   usbtouchscreen.o
  CPP   dwhciregister.o
  CPP   dwhcidevice.o
  CPP   dwhciframeschednper.o
  CPP   dwhciframeschednsplit.o
  CPP   dwhciframeschedper.o
  CPP   dwhcirootport.o
  CPP   dwhcixactqueue.o
  CPP   dwhcicompletionqueue.o
  CPP   dwhcixferstagedata.o
  CPP   dwhciframeschediso.o
  AR    libusb.a
  CPP   dwusbgadget.o
  CPP   dwusbgadgetendpoint.o
  CPP   dwusbgadgetendpoint0.o
  CPP   usbmidigadget.o
  CPP   usbmidigadgetendpoint.o
  CPP   usbcdcgadget.o
  CPP   usbcdcgadgetendpoint.o
  CPP   usbmsdgadget.o
  CPP   usbmsdgadgetendpoint.o
  AR    libusbgadget.a
  CPP   keyboardbehaviour.o
  CPP   keymap.o
  CPP   mousebehaviour.o
  CPP   mouse.o
  CPP   touchscreen.o
  CPP   rpitouchscreen.o
  CPP   xpt2046touchscreen.o
  CPP   console.o
  CPP   keyboardbuffer.o
  CPP   linediscipline.o
  AR    libinput.a
  CPP   partition.o
  CPP   partitionmanager.o
  AR    libfs.a
  CPP   fatfs.o
  CPP   fatcache.o
  CPP   fatinfo.o
  CPP   fat.o
  CPP   fatdir.o
  AR    libfatfs.a
  CPP   task.o
  CPP   scheduler.o
  AS    taskswitch.o
  CPP   synchronizationevent.o
  CPP   mutex.o
  CPP   semaphore.o
  AR    libsched.a
  CPP   netsubsystem.o
  CPP   nettask.o
  CPP   netsocket.o
  CPP   socket.o
  CPP   transportlayer.o
  CPP   networklayer.o
  CPP   linklayer.o
  CPP   netdevlayer.o
  CPP   phytask.o
  CPP   arphandler.o
  CPP   icmphandler.o
  CPP   igmphandler.o
  CPP   routecache.o
  CPP   netconnection.o
  CPP   udpconnection.o
  CPP   tcpconnection.o
  CPP   retransmissionqueue.o
  CPP   retranstimeoutcalc.o
  CPP   tcprejector.o
  CPP   netconfig.o
  CPP   ipaddress.o
  CPP   netqueue.o
  CPP   checksumcalculator.o
  CPP   dnsclient.o
  CPP   ntpclient.o
  CPP   mqttclient.o
  CPP   mqttsendpacket.o
  CPP   mqttreceivepacket.o
  CPP   dhcpclient.o
  CPP   ntpdaemon.o
  CPP   httpdaemon.o
  CPP   httpclient.o
  CPP   tftpdaemon.o
  CPP   syslogdaemon.o
  CPP   mdnsdaemon.o
  CPP   mdnspublisher.o
  AR    libnet.a
  CPP   soundbasedevice.o
  CPP   pwmsounddevice.o
  CPP   hdmisoundbasedevice.o
  CPP   pcm512xsoundcontroller.o
  CPP   wm8960soundcontroller.o
  CPP   dmasoundbuffers.o
  CPP   i2ssoundbasedevice.o
  CPP   pwmsoundbasedevice.o
  AR    libsound.a
$ cd addon/linux
$ make
  CPP   linuxdevice.o
  CPP   linuxemu.o
  CPP   bug.o
  CPP   completion.o
  CPP   delay.o
  CPP   device.o
  CPP   dma-mapping.o
  CPP   interrupt.o
  CPP   kthread.o
  CPP   mutex.o
  CPP   platform_device.o
  CPP   printk.o
  CPP   pthread.o
  CPP   raspberrypi-firmware.o
  CPP   rwlock.o
  CPP   semaphore.o
  CPP   spinlock.o
  CPP   sprintf.o
  CPP   timer.o
  AR    liblinuxemu.a
$ ../vc4
$ ./makeall
  CPP   vchiqdevice.o
  CC    vchiq_arm.o
  CC    vchiq_2835_arm.o
  CC    vchiq_core.o
  CC    vchiq_kern_lib.o
  CC    vchiq_connected.o
  CC    vchiq_shim.o
  CC    vchiq_util.o
  AR    libvchiq.a
  CPP   vchiqsoundbasedevice.o
  CPP   vchiqsounddevice.o
  CPP   vchiqsoundcontroller.o
  AR    libvchiqsound.a
  UNZIP sound.h
  CPP   main.o
  CPP   kernel.o
  LD    kernel8-32.elf
  DUMP  kernel8-32.lst
  COPY  kernel8-32.img
-n   WC    kernel8-32.img =>
342788
$ cd sound/sample
$ ls
kernel.cpp  kernel.o        kernel8-32.lst  main.d    README
kernel.d    kernel8-32.elf  kernel8-32.map  main.o    sound.h
kernel.h    kernel8-32.img  main.cpp        Makefile  sound.h.gz
$ cp kernel8-32.img /Volume/NO\ NAME
$ vi /Volume/NO\ NAME/config.txt
#arm_64bit=1
enable_uart=1
kernel=kernel8-32.img
$ vi /Volume/NO\ NAME/cmdline.txt
width=640 height=480 logdev=ttyS1 loglevel=4
$ minicom
logger: Circle 50 started on Raspberry Pi 3 Model B+ 1GB
logger: Revision code is a020d3, compiler has been GCC 14.3.1
00:00:00.66 timer: SpeedFactor is 1.51
00:00:00.66 printk: vchiq: vchiq_init_state: slot_zero = 0x00480000, is_master = 0
00:00:00.67 kernel: Compile time: Mar 25 2026 15:18:24
00:00:00.68 kernel: Playback started
00:00:05.46 kernel: Playback completed
```

- イヤフォンジャックにイヤフォンをつけると音楽が聞こえた
