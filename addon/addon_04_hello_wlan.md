# ADDON_04: wlan/hello_waln

このサンプルはRaspberry Pi 3, 4とZero Wに搭載されているオンボードWLANデバイスを使用して
WLANに接続し、NTPサーバからシステム時間を更新します。現在のろこと、デフォルトではWPA[2]
対応のWLANしか接続できません。WLANドライバはPlan 9オペレーティングシステムから移植しました。
さらに、移植した"WPA Supplicant"ツールも使用しています。

ビルドする前に以下のコマンドを実行してサブモジュール addon/wlan/hostap を取得する
必要があります。

	git submodule update --init addon/wlan/hostap

メインのCircleライブラリの他に addon/fatfs/ と addon/SDCard のライブラリも必要であり、
WLANライブラリとサンプルをビルドする前にこれらのライブラリを作成する必要があります。

	cd addon/wlan
	./makeall

Raspberry Piの様々なWLANコントローラに対応するため、以下のファームウェアファイルを提供
する必要があります。

    brcmfmac43430-sdio.txt
    brcmfmac43430-sdio.bin
    brcmfmac43436-sdio.bin
    brcmfmac43436-sdio.txt
    brcmfmac43436-sdio.clm_blob
    brcmfmac43455-sdio.bin
    brcmfmac43455-sdio.clm_blob
    brcmfmac43455-sdio.txt
    brcmfmac43456-sdio.bin
    brcmfmac43456-sdio.txt
    brcmfmac43456-sdio.clm_blob
    brcmfmac43455-sdio.raspberrypi,5-model-b.bin
    brcmfmac43455-sdio.raspberrypi,5-model-b.txt
    brcmfmac43455-sdio.raspberrypi,5-model-b.clm_blob

これらのファイルは以下を実行することによりダウンロードすることができます（ "wget" ツールを使用）。

	cd addon/wlan/firmware
	make

これらのファイルはブート用に使用されるSDカードの /firmware ディレクトリにコピーする
必要があります。これらのダウンロードしたファームウェアファイルはCircleでテスト済みです。

さらに、SDカードのルートディレクトリには "wpa_supplicant.conf" という構成ファイルも
必要です。このサンプルディレクトリにあるテンプレートファイルを編集して、自身のWi-Fi
ネットワークのSSIDとパスワードを設定してください。また、お住まいの国のISO/IECアルファ2
コードも設定する必要があります。

## ビルド・実行ログ

### ビルド

```bash
zuki@airm3:~$ cd /Volumes/wdb/raspi_os/circle
zuki@airm3:/Volumes/wdb/raspi_os/circle$ git status
On branch master
Your branch is up to date with 'upstream/master'.

nothing to commit, working tree clean
zuki@airm3:/Volumes/wdb/raspi_os/circle$ ls
addon		Config.mk	Doxyfile	makedoc		tools
app		configure	include		README.md
boot		CONTRIBUTING.md	lib		Rules.mk
CHANGELOG.md	CREDITS		LICENSE		sample
circle.ld	doc		makeall		test
zuki@airm3:/Volumes/wdb/raspi_os/circle$ aarch64-none-elf-gcc -v
Using built-in specs.
COLLECT_GCC=aarch64-none-elf-gcc
COLLECT_LTO_WRAPPER=/Applications/ArmGNUToolchain/14.3.rel1/aarch64-none-elf/bin/../libexec/gcc/aarch64-none-elf/14.3.1/lto-wrapper
Target: aarch64-none-elf
Configured with: /Volumes/data/jenkins/workspace/GNU-toolchain/arm-14/src/gcc/configure --target=aarch64-none-elf --prefix=/Volumes/data/jenkins/workspace/GNU-toolchain/arm-14/build-aarch64-none-elf/install --with-gmp=/Volumes/data/jenkins/workspace/GNU-toolchain/arm-14/build-aarch64-none-elf/host-tools --with-mpfr=/Volumes/data/jenkins/workspace/GNU-toolchain/arm-14/build-aarch64-none-elf/host-tools --with-mpc=/Volumes/data/jenkins/workspace/GNU-toolchain/arm-14/build-aarch64-none-elf/host-tools --with-isl=/Volumes/data/jenkins/workspace/GNU-toolchain/arm-14/build-aarch64-none-elf/host-tools --disable-shared --disable-nls --disable-threads --disable-tls --enable-checking=release --enable-languages=c,c++,fortran --with-newlib --with-gnu-as --with-headers=yes --with-gnu-ld --with-native-system-header-dir=/include --with-sysroot=/Volumes/data/jenkins/workspace/GNU-toolchain/arm-14/build-aarch64-none-elf/install/aarch64-none-elf --with-bugurl=https://bugs.linaro.org/ --with-pkgversion='Arm GNU Toolchain 14.3.Rel1 (Build arm-14.174)'
Thread model: single
Supported LTO compression algorithms: zlib
gcc version 14.3.1 20250623 (Arm GNU Toolchain 14.3.Rel1 (Build arm-14.174)) 
zuki@airm3:/Volumes/wdb/raspi_os/circle$ code .
zuki@airm3:/Volumes/wdb/raspi_os/circle$ touch Config.mk
zuki@airm3:/Volumes/wdb/raspi_os/circle$ ls
addon		Config.mk	Doxyfile	makedoc		tools
app		configure	include		README.md
boot		CONTRIBUTING.md	lib		Rules.mk
CHANGELOG.md	CREDITS		LICENSE		sample
circle.ld	doc		makeall		test
zuki@airm3:/Volumes/wdb/raspi_os/circle$ grep -r SDHOST include/
include/circle/sysconfig.h:// NO_BUSY_WAIT deactivates busy waiting in the EMMC, SDHOST and USB
include/circle/sysconfig.h:// USE_SDHOST selects the SDHOST device as interface for SD card
include/circle/sysconfig.h:// SDHOST device is supported by Raspberry Pi 1-3 and Zero, but
include/circle/sysconfig.h:// not by QEMU. If you rely on a small IRQ latency, USE_SDHOST should
include/circle/sysconfig.h:#ifndef NO_SDHOST
include/circle/sysconfig.h:#define USE_SDHOST
include/circle/bcm2835.h:// SDHOST Controller (SD Card)
include/circle/bcm2835.h:#define ARM_SDHOST_BASE		(ARM_IO_BASE + 0x202000)
include/circle/bcmpropertytags.h:#define PROPTAG_SET_SDHOST_CLOCK	0x00038042

zuki@airm3:/Volumes/wdb/raspi_os/circle$ ./makeall clean
  CLEAN  /Volumes/wdb/raspi_os/circle/tools
  CLEAN  /Volumes/wdb/raspi_os/circle/lib
  CLEAN  /Volumes/wdb/raspi_os/circle/lib/usb
  CLEAN  /Volumes/wdb/raspi_os/circle/lib/usb/gadget
  CLEAN  /Volumes/wdb/raspi_os/circle/lib/input
  CLEAN  /Volumes/wdb/raspi_os/circle/lib/fs
  CLEAN  /Volumes/wdb/raspi_os/circle/lib/fs/fat
  CLEAN  /Volumes/wdb/raspi_os/circle/lib/sched
  CLEAN  /Volumes/wdb/raspi_os/circle/lib/net
  CLEAN  /Volumes/wdb/raspi_os/circle/lib/sound

zuki@airm3:/Volumes/wdb/raspi_os/circle$ ./makeall
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
  CPP   exceptionhandler64.o
  AS    exceptionstub64.o
  CPP   memory64.o
  AS    startup64.o
  CPP   synchronize64.o
  CPP   translationtable64.o
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

zuki@airm3:/Volumes/wdb/raspi_os/circle$ ls
addon		Config.mk	Doxyfile	makedoc		tools
app		configure	include		README.md
boot		CONTRIBUTING.md	lib		Rules.mk
CHANGELOG.md	CREDITS		LICENSE		sample
circle.ld	doc		makeall		test

zuki@airm3:/Volumes/wdb/raspi_os/circle$ git remote -v
origin	git@github.com:zuki/circle.git (fetch)
origin	git@github.com:zuki/circle.git (push)
upstream	https://github.com/rsta2/circle.git (fetch)
upstream	https://github.com/rsta2/circle.git (push)
zuki@airm3:/Volumes/wdb/raspi_os/circle$ ls addon/wlan/
bcm4343.cpp	hostap		p9chan.h	p9ether.cpp	p9util.h
bcm4343.h	makeall		p9cmd.cpp	p9ether.h	Plan9License
emmc.c		Makefile	p9cmd.h		p9proc.cpp	sample
ether4330.c	p9arch.cpp	p9compat.h	p9proc.h
etherevent.h	p9arch.h	p9error.cpp	p9sd.h
firmware	p9chan.cpp	p9error.h	p9util.cpp
zuki@airm3:/Volumes/wdb/raspi_os/circle$ git submodule update --init addon/wlan/hostap
Submodule 'addon/wlan/hostap' (https://github.com/rsta2/hostap.git) registered for path 'addon/wlan/hostap'
Cloning into '/Volumes/wdb/raspi_os/circle/addon/wlan/hostap'...
Submodule path 'addon/wlan/hostap': checked out '237e65ecf72e531c7744cacbc444bd289c316712'

zuki@airm3:/Volumes/wdb/raspi_os/circle$ ls addon/wlan/hostap/
Android.mk	doc		radius_example	wlantest
build_release	eap_example	README		wpa_supplicant
CONTRIBUTIONS	hostapd		src		wpadebug
COPYING		hs20		tests		wpaspy

zuki@airm3:/Volumes/wdb/raspi_os/circle$ cd addon/
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon$ cd fatfs
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/fatfs$ make clean
  CLEAN  /Volumes/wdb/raspi_os/circle/addon/fatfs
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/fatfs$ make
  CC    ff.o
  CPP   diskio.o
  CPP   ffsystem.o
  CC    ffunicode.o
  AR    libfatfs.a
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/fatfs$ ls
diskio.cpp	ff.c		ffconf.h	ffunicode.c	LICENSE.txt
diskio.d	ff.d		ffsystem.cpp	ffunicode.d	Makefile
diskio.h	ff.h		ffsystem.d	ffunicode.o	sample
diskio.o	ff.o		ffsystem.o	libfatfs.a

zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/fatfs$ cd ../SDCard/
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/SDCard$ ls
emmc.cpp	Makefile	mmcerror.h	mmchost.h	sdhost.cpp
emmc.h		mmc.h		mmchost.cpp	sample		sdhost.h
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/SDCard$ make
  CPP   emmc.o
  CPP   mmchost.o
  CPP   sdhost.o
  AR    libsdcard.a
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/SDCard$ ls
emmc.cpp	libsdcard.a	mmchost.cpp	sample		sdhost.o
emmc.d		Makefile	mmchost.d	sdhost.cpp
emmc.h		mmc.h		mmchost.h	sdhost.d
emmc.o		mmcerror.h	mmchost.o	sdhost.h

zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/SDCard$ cd ../wlan
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan$ ls
bcm4343.cpp	hostap		p9chan.h	p9ether.cpp	p9util.h
bcm4343.h	makeall		p9cmd.cpp	p9ether.h	Plan9License
emmc.c		Makefile	p9cmd.h		p9proc.cpp	sample
ether4330.c	p9arch.cpp	p9compat.h	p9proc.h
etherevent.h	p9arch.h	p9error.cpp	p9sd.h
firmware	p9chan.cpp	p9error.h	p9util.cpp
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan$ ./makeall
  CPP   bcm4343.o
  CC    ether4330.o
  CC    emmc.o
  CPP   p9arch.o
  CPP   p9chan.o
  CPP   p9cmd.o
  CPP   p9error.o
  CPP   p9ether.o
  CPP   p9proc.o
  CPP   p9util.o
  AR    libwlan.a
  CC    bss.o
  CC    bssid_ignore.o
  CC    config.o
  CC    config_file.o
  CC    eap_register.o
  CC    events.o
  CPP   main_circle.o
  CC    notify.o
  CC    op_classes.o
  CC    rrm.o
  CC    scan.o
  CC    twt.o
  CC    wpa_supplicant.o
  CC    wpas_glue.o
  CPP   wpasupplicant.o
  CC    ../src/common/hw_features_common.o
  CC    ../src/common/ieee802_11_common.o
  CC    ../src/common/ptksa_cache.o
  CC    ../src/common/wpa_common.o
  CC    ../src/crypto/aes-internal.o
  CC    ../src/crypto/aes-internal-dec.o
  CC    ../src/crypto/aes-internal-enc.o
  CC    ../src/crypto/aes-unwrap.o
  CC    ../src/crypto/aes-omac1.o
  CC    ../src/crypto/md5-internal.o
  CC    ../src/crypto/md5.o
  CC    ../src/crypto/rc4.o
  CC    ../src/crypto/sha1-internal.o
  CC    ../src/crypto/sha1-pbkdf2.o
  CC    ../src/crypto/sha1-prf.o
  CC    ../src/crypto/sha1.o
  CC    ../src/crypto/sha256-internal.o
  CC    ../src/crypto/sha256-prf.o
  CC    ../src/crypto/sha256-tlsprf.o
  CC    ../src/crypto/sha256.o
  CC    ../src/crypto/tls_none.o
  CPP   ../src/drivers/driver_circle.o
  CC    ../src/drivers/driver_common.o
  CC    ../src/drivers/drivers.o
  CC    ../src/eap_common/eap_common.o
  CC    ../src/eap_peer/eap.o
  CC    ../src/eap_peer/eap_methods.o
  CC    ../src/eapol_supp/eapol_supp_sm.o
  CPP   ../src/l2_packet/l2_packet_circle.o
  CC    ../src/rsn_supp/pmksa_cache.o
  CC    ../src/rsn_supp/preauth.o
  CC    ../src/rsn_supp/wpa.o
  CC    ../src/rsn_supp/wpa_ie.o
  CC    ../src/utils/base64.o
  CC    ../src/utils/bitfield.o
  CC    ../src/utils/common.o
  CC    ../src/utils/config.o
  CC    ../src/utils/crc32.o
  CC    ../src/utils/eloop_circle.o
  CPP   ../src/utils/os_circle.o
  CC    ../src/utils/wpa_debug_circle.o
  CC    ../src/utils/wpabuf.o
  AR    libwpa_supplicant.a
  CPP   main.o
  CPP   kernel.o
  LD    kernel8.elf
  DUMP  kernel8.lst
  COPY  kernel8.img
-n   WC    kernel8.img => 
  788328

zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan$ cd firmware/
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan/firmware$ ls
Makefile
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan/firmware$ make
rm -f *.bin *.txt *.clm_blob
wget -q -O brcmfmac43430-sdio.bin https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/cypress/cyfmac43430-sdio.bin
wget -q -O brcmfmac43430-sdio.txt https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/brcm/brcmfmac43430-sdio.txt
wget -q -O brcmfmac43430-sdio.clm_blob https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/cypress/cyfmac43430-sdio.clm_blob
wget -q -O brcmfmac43436-sdio.bin https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/brcm/brcmfmac43436-sdio.bin
wget -q -O brcmfmac43436-sdio.txt https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/brcm/brcmfmac43436-sdio.txt
wget -q -O brcmfmac43436-sdio.clm_blob https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/brcm/brcmfmac43436-sdio.clm_blob
wget -q -O brcmfmac43436s-sdio.bin https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/brcm/brcmfmac43436s-sdio.bin
wget -q -O brcmfmac43436s-sdio.txt https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/brcm/brcmfmac43436s-sdio.txt
wget -q -O brcmfmac43455-sdio.bin https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/cypress/cyfmac43455-sdio-minimal.bin
wget -q -O brcmfmac43455-sdio.txt https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/brcm/brcmfmac43455-sdio.txt
wget -q -O brcmfmac43455-sdio.clm_blob https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/cypress/cyfmac43455-sdio.clm_blob
wget -q -O brcmfmac43456-sdio.bin https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/brcm/brcmfmac43456-sdio.bin
wget -q -O brcmfmac43456-sdio.txt https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/brcm/brcmfmac43456-sdio.txt
wget -q -O brcmfmac43456-sdio.clm_blob https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/brcm/brcmfmac43456-sdio.clm_blob
wget -q -O brcmfmac43455-sdio.raspberrypi,5-model-b.bin https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/cypress/cyfmac43455-sdio-minimal.bin
wget -q -O brcmfmac43455-sdio.raspberrypi,5-model-b.txt https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/brcm/brcmfmac43455-sdio.txt
wget -q -O brcmfmac43455-sdio.raspberrypi,5-model-b.clm_blob https://github.com/RPi-Distro/firmware-nonfree/raw/c9d3ae6584ab79d19a4f94ccf701e888f9f87a53/debian/config/brcm80211/cypress/cyfmac43455-sdio.clm_blob
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan/firmware$ ls
brcmfmac43430-sdio.bin
brcmfmac43430-sdio.clm_blob
brcmfmac43430-sdio.txt
brcmfmac43436-sdio.bin
brcmfmac43436-sdio.clm_blob
brcmfmac43436-sdio.txt
brcmfmac43436s-sdio.bin
brcmfmac43436s-sdio.txt
brcmfmac43455-sdio.bin
brcmfmac43455-sdio.clm_blob
brcmfmac43455-sdio.raspberrypi,5-model-b.bin
brcmfmac43455-sdio.raspberrypi,5-model-b.clm_blob
brcmfmac43455-sdio.raspberrypi,5-model-b.txt
brcmfmac43455-sdio.txt
brcmfmac43456-sdio.bin
brcmfmac43456-sdio.clm_blob
brcmfmac43456-sdio.txt
Makefile

zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan/firmware$ cd ../../..
zuki@airm3:/Volumes/wdb/raspi_os/circle$ cd boot/
zuki@airm3:/Volumes/wdb/raspi_os/circle/boot$ ls
armstub			fixup_cd.dat		kernel8.img
bcm2711-rpi-4-b.dtb	fixup.dat		LICENCE.broadcom
bcm2711-rpi-400.dtb	fixup4.dat		Makefile
bcm2711-rpi-cm4.dtb	fixup4cd.dat		README
bootcode.bin		kernel.img		start_cd.elf
config32.txt		kernel7.img		start.elf
config64.txt		kernel7l.img		start4.elf
COPYING.linux		kernel8-rpi4.img	start4cd.elf
zuki@airm3:/Volumes/wdb/raspi_os/circle/boot$ cp fixup.dat bootcode.bin start.elf /Volumes/boot

zuki@airm3:/Volumes/wdb/raspi_os/circle/boot$ cd ../addon/wlan
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan$ cd sample/
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan/sample$ ls
hello_ap	hello_wlan
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan/sample$ cd hello_wlan/
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan/sample/hello_wlan$ ls
kernel.cpp		kernel8.img		main.o
kernel.d		kernel8.lst		Makefile
kernel.h		kernel8.map		README
kernel.o		main.cpp		wpa_supplicant.conf
kernel8.elf		main.d
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan/sample/hello_wlan$ make clean
  CLEAN  /Volumes/wdb/raspi_os/circle/addon/wlan/sample/hello_wlan
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan/sample/hello_wlan$ make
  CPP   main.o
  CPP   kernel.o
  LD    kernel8.elf
  DUMP  kernel8.lst
  COPY  kernel8.img
-n   WC    kernel8.img => 
  788328
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan/sample/hello_wlan$ ls
kernel.cpp		kernel8.img		main.o
kernel.d		kernel8.lst		Makefile
kernel.h		kernel8.map		README
kernel.o		main.cpp		wpa_supplicant.conf
kernel8.elf		main.d
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan/sample/hello_wlan$ vi wpa_supplicant.conf 
zuki@airm3:/Volumes/wdb/raspi_os/circle/addon/wlan/sample/hello_wlan$ cp kernel8.img wpa_supplicant.conf /Volumes/boot
```

### 実行

```bash
$ minicom


Welcome to minicom 2.8

OPTIONS: 
Compiled on Jan  4 2021, 00:04:46.
Port /dev/cu.usbserial-AI057C9L, 09:22:32
Using character set conversion
                                                                               
Press Meta-Z for help on special keys                                          
                                                                     
// LEDが5回点滅し、しばらくたってさらに2回点滅。何も表示されない

```bash
