# Circleディレクトリ構成

## lib

```
lib
├── fs
│   ├── Makefile
│   ├── fat
│   │   ├── Makefile
│   │   ├── fat.cpp
│   │   ├── fatcache.cpp
│   │   ├── fatdir.cpp
│   │   ├── fatfs.cpp
│   │   └── fatinfo.cpp
│   ├── partition.cpp
│   └── partitionmanager.cpp
├── input
│   ├── Makefile
│   ├── console.cpp
│   ├── keyboardbehaviour.cpp
│   ├── keyboardbuffer.cpp
│   ├── keymap.cpp
│   ├── keymap_de.h
│   ├── keymap_es.h
│   ├── keymap_fr.h
│   ├── keymap_it.h
│   ├── keymap_uk.h
│   ├── keymap_us.h
│   ├── linediscipline.cpp
│   ├── mouse.cpp
│   ├── mousebehaviour.cpp
│   ├── rpitouchscreen.cpp
│   └── touchscreen.cpp
├── net
│   ├── Makefile
│   ├── arphandler.cpp
│   ├── checksumcalculator.cpp
│   ├── dhcpclient.cpp
│   ├── dnsclient.cpp
│   ├── httpclient.cpp
│   ├── httpdaemon.cpp
│   ├── icmphandler.cpp
│   ├── ipaddress.cpp
│   ├── linklayer.cpp
│   ├── mqttclient.cpp
│   ├── mqttreceivepacket.cpp
│   ├── mqttsendpacket.cpp
│   ├── netconfig.cpp
│   ├── netconnection.cpp
│   ├── netdevlayer.cpp
│   ├── netqueue.cpp
│   ├── netsocket.cpp
│   ├── netsubsystem.cpp
│   ├── nettask.cpp
│   ├── networklayer.cpp
│   ├── ntpclient.cpp
│   ├── ntpdaemon.cpp
│   ├── phytask.cpp
│   ├── retransmissionqueue.cpp
│   ├── retranstimeoutcalc.cpp
│   ├── routecache.cpp
│   ├── socket.cpp
│   ├── syslogdaemon.cpp
│   ├── tcpconnection.cpp
│   ├── tcprejector.cpp
│   ├── tftpdaemon.cpp
│   ├── transportlayer.cpp
│   └── udpconnection.cpp
├── sched
│   ├── Makefile
│   ├── mutex.cpp
│   ├── scheduler.cpp
│   ├── semaphore.cpp
│   ├── synchronizationevent.cpp
│   ├── task.cpp
│   └── taskswitch.S
├── usb
│   ├── Makefile
│   ├── README
│   ├── dwhcicompletionqueue.cpp
│   ├── dwhcidevice.cpp
│   ├── dwhciframeschednper.cpp
│   ├── dwhciframeschednsplit.cpp
│   ├── dwhciframeschedper.cpp
│   ├── dwhciregister.cpp
│   ├── dwhcirootport.cpp
│   ├── dwhcixactqueue.cpp
│   ├── dwhcixferstagedata.cpp
│   ├── lan7800.cpp
│   ├── smsc951x.cpp
│   ├── usbbluetooth.cpp
│   ├── usbcdcethernet.cpp
│   ├── usbconfigparser.cpp
│   ├── usbdevice.cpp
│   ├── usbdevicefactory.cpp
│   ├── usbendpoint.cpp
│   ├── usbfunction.cpp
│   ├── usbgamepad.cpp
│   ├── usbgamepadps3.cpp
│   ├── usbgamepadps4.cpp
│   ├── usbgamepadstandard.cpp
│   ├── usbgamepadswitchpro.cpp
│   ├── usbgamepadxbox360.cpp
│   ├── usbgamepadxboxone.cpp
│   ├── usbhiddevice.cpp
│   ├── usbhostcontroller.cpp
│   ├── usbkeyboard.cpp
│   ├── usbmassdevice.cpp
│   ├── usbmidi.cpp
│   ├── usbmouse.cpp
│   ├── usbprinter.cpp
│   ├── usbrequest.cpp
│   ├── usbserial.cpp
│   ├── usbserialcdc.cpp
│   ├── usbserialch341.cpp
│   ├── usbserialcp2102.cpp
│   ├── usbserialft231x.cpp
│   ├── usbserialpl2303.cpp
│   ├── usbstandardhub.cpp
│   ├── usbstring.cpp
│   ├── usbtouchscreen.cpp
│   ├── xhcicommandmanager.cpp
│   ├── xhcidevice.cpp
│   ├── xhciendpoint.cpp
│   ├── xhcieventmanager.cpp
│   ├── xhcimmiospace.cpp
│   ├── xhciring.cpp
│   ├── xhciroothub.cpp
│   ├── xhcirootport.cpp
│   ├── xhcisharedmemallocator.cpp
│   ├── xhcislotmanager.cpp
│   └── xhciusbdevice.cpp
├── 2dgraphics.cpp
├── Makefile
├── SpinCore
├── actled.cpp
├── alloc.cpp
├── assert.cpp
├── bcm54213.cpp
├── bcmframebuffer.cpp
├── bcmmailbox.cpp
├── bcmpciehostbridge.cpp
├── bcmpropertytags.cpp
├── bcmrandom.cpp
├── bcmrandom200.cpp
├── bcmwatchdog.cpp
├── cache-v7.S
├── chainboot.cpp
├── chargenerator.cpp
├── classallocator.cpp
├── cputhrottle.cpp
├── cxa_guard.cpp
├── debug.cpp
├── delayloop.S
├── device.cpp
├── devicenameservice.cpp
├── devicetreeblob.cpp
├── dma4channel.cpp
├── dmachannel.cpp
├── dmasoundbuffers.cpp
├── exceptionhandler.cpp
├── exceptionhandler64.cpp
├── exceptionstub.S
├── exceptionstub64.S
├── font.h
├── gpioclock.cpp
├── gpiomanager.cpp
├── gpiopin.cpp
├── gpiopinfiq.cpp
├── hdmisoundbasedevice.cpp
├── heapallocator.cpp
├── i2cmaster.cpp
├── i2cslave.cpp
├── i2ssoundbasedevice.cpp
├── interrupt.cpp
├── interruptgic.cpp
├── koptions.cpp
├── latencytester.cpp
├── libhelper.cpp
├── libstub.S
├── logger.cpp
├── macaddress.cpp
├── machineinfo.cpp
├── memory.cpp
├── memory64.cpp
├── mphi.cpp
├── multicore.cpp
├── netdevice.cpp
├── new.cpp
├── nulldevice.cpp
├── numberpool.cpp
├── pageallocator.cpp
├── pagetable.cpp
├── ptrarray.cpp
├── ptrlist.cpp
├── ptrlistfiq.cpp
├── purecall.cpp
├── pwmoutput.cpp
├── pwmsoundbasedevice.cpp
├── pwmsounddevice.cpp
├── qemu.cpp
├── screen.cpp
├── serial.cpp
├── setjmp.S
├── smimaster.cpp
├── soundbasedevice.cpp
├── spimaster.cpp
├── spimasteraux.cpp
├── spimasterdma.cpp
├── spinlock.cpp
├── startup.S
├── startup64.S
├── string.cpp
├── synchronize.cpp
├── synchronize64.cpp
├── sysinit.cpp
├── time.cpp
├── timer.cpp
├── tracer.cpp
├── translationtable64.cpp
├── usertimer.cpp
├── util.cpp
├── util_fast.S
├── virtualgpiopin.cpp
└── writebuffer.cpp
```

## include

```
include
├── assert.h
└── circle
    ├── fs
    │   ├── fat
    │   │   ├── fat.h
    │   │   ├── fatcache.h
    │   │   ├── fatdir.h
    │   │   ├── fatfs.h
    │   │   ├── fatfsdef.h
    │   │   └── fatinfo.h
    │   ├── fsdef.h
    │   ├── partition.h
    │   └── partitionmanager.h
    ├── input
    │   ├── console.h
    │   ├── keyboardbehaviour.h
    │   ├── keyboardbuffer.h
    │   ├── keymap.h
    │   ├── linediscipline.h
    │   ├── mouse.h
    │   ├── mousebehaviour.h
    │   ├── rpitouchscreen.h
    │   └── touchscreen.h
    ├── net
    │   ├── arphandler.h
    │   ├── checksumcalculator.h
    │   ├── dhcpclient.h
    │   ├── dnsclient.h
    │   ├── http.h
    │   ├── httpclient.h
    │   ├── httpdaemon.h
    │   ├── icmphandler.h
    │   ├── in.h
    │   ├── ipaddress.h
    │   ├── linklayer.h
    │   ├── mqtt.h
    │   ├── mqttclient.h
    │   ├── mqttreceivepacket.h
    │   ├── mqttsendpacket.h
    │   ├── netconfig.h
    │   ├── netconnection.h
    │   ├── netdevlayer.h
    │   ├── netqueue.h
    │   ├── netsocket.h
    │   ├── netsubsystem.h
    │   ├── nettask.h
    │   ├── networklayer.h
    │   ├── ntpclient.h
    │   ├── ntpdaemon.h
    │   ├── phytask.h
    │   ├── retransmissionqueue.h
    │   ├── retranstimeoutcalc.h
    │   ├── routecache.h
    │   ├── socket.h
    │   ├── syslogdaemon.h
    │   ├── tcpconnection.h
    │   ├── tcprejector.h
    │   ├── tftpdaemon.h
    │   ├── transportlayer.h
    │   └── udpconnection.h
    ├── sched
    │   ├── mutex.h
    │   ├── scheduler.h
    │   ├── semaphore.h
    │   ├── synchronizationevent.h
    │   ├── task.h
    │   └── taskswitch.h
    ├── usb
    │   ├── dwhci.h
    │   ├── dwhcicompletionqueue.h
    │   ├── dwhcidevice.h
    │   ├── dwhciframeschednper.h
    │   ├── dwhciframeschednsplit.h
    │   ├── dwhciframeschedper.h
    │   ├── dwhciframescheduler.h
    │   ├── dwhciregister.h
    │   ├── dwhcirootport.h
    │   ├── dwhcixactqueue.h
    │   ├── dwhcixferstagedata.h
    │   ├── lan7800.h
    │   ├── smsc951x.h
    │   ├── usb.h
    │   ├── usbaudio.h
    │   ├── usbbluetooth.h
    │   ├── usbcdcethernet.h
    │   ├── usbconfigparser.h
    │   ├── usbdevice.h
    │   ├── usbdevicefactory.h
    │   ├── usbendpoint.h
    │   ├── usbfunction.h
    │   ├── usbgamepad.h
    │   ├── usbgamepadps3.h
    │   ├── usbgamepadps4.h
    │   ├── usbgamepadstandard.h
    │   ├── usbgamepadswitchpro.h
    │   ├── usbgamepadxbox360.h
    │   ├── usbgamepadxboxone.h
    │   ├── usbhcidevice.h
    │   ├── usbhcirootport.h
    │   ├── usbhid.h
    │   ├── usbhiddevice.h
    │   ├── usbhostcontroller.h
    │   ├── usbhub.h
    │   ├── usbkeyboard.h
    │   ├── usbmassdevice.h
    │   ├── usbmidi.h
    │   ├── usbmouse.h
    │   ├── usbprinter.h
    │   ├── usbrequest.h
    │   ├── usbserial.h
    │   ├── usbserialcdc.h
    │   ├── usbserialch341.h
    │   ├── usbserialcp2102.h
    │   ├── usbserialft231x.h
    │   ├── usbserialpl2303.h
    │   ├── usbstandardhub.h
    │   ├── usbstring.h
    │   ├── usbtouchscreen.h
    │   ├── xhci.h
    │   ├── xhcicommandmanager.h
    │   ├── xhciconfig.h
    │   ├── xhcidevice.h
    │   ├── xhciendpoint.h
    │   ├── xhcieventmanager.h
    │   ├── xhcimmiospace.h
    │   ├── xhciring.h
    │   ├── xhciroothub.h
    │   ├── xhcirootport.h
    │   ├── xhcisharedmemallocator.h
    │   ├── xhcislotmanager.h
    │   └── xhciusbdevice.h
    ├── 2dgraphics.h
    ├── actled.h
    ├── alloc.h
    ├── armv6mmu.h
    ├── armv7lpae.h
    ├── armv8mmu.h
    ├── atomic.h
    ├── bcm2711.h
    ├── bcm2711int.h
    ├── bcm2835.h
    ├── bcm2835int.h
    ├── bcm2836.h
    ├── bcm54213.h
    ├── bcmframebuffer.h
    ├── bcmmailbox.h
    ├── bcmpciehostbridge.h
    ├── bcmpropertytags.h
    ├── bcmrandom.h
    ├── bcmwatchdog.h
    ├── chainboot.h
    ├── chargenerator.h
    ├── classallocator.h
    ├── cputhrottle.h
    ├── debug.h
    ├── device.h
    ├── devicenameservice.h
    ├── devicetreeblob.h
    ├── dma4channel.h
    ├── dmachannel.h
    ├── dmacommon.h
    ├── dmasoundbuffers.h
    ├── exception.h
    ├── exceptionhandler.h
    ├── exceptionstub.h
    ├── genericlock.h
    ├── gpioclock.h
    ├── gpiomanager.h
    ├── gpiopin.h
    ├── gpiopinfiq.h
    ├── hdmisoundbasedevice.h
    ├── heapallocator.h
    ├── i2cmaster.h
    ├── i2cslave.h
    ├── i2ssoundbasedevice.h
    ├── interrupt.h
    ├── koptions.h
    ├── latencytester.h
    ├── logger.h
    ├── macaddress.h
    ├── machineinfo.h
    ├── macros.h
    ├── memio.h
    ├── memory.h
    ├── memorymap.h
    ├── memorymap64.h
    ├── mphi.h
    ├── multicore.h
    ├── netdevice.h
    ├── new.h
    ├── nulldevice.h
    ├── numberpool.h
    ├── pageallocator.h
    ├── pagetable.h
    ├── pci_regs.h
    ├── ptrarray.h
    ├── ptrlist.h
    ├── ptrlistfiq.h
    ├── pwmoutput.h
    ├── pwmsoundbasedevice.h
    ├── pwmsounddevice.h
    ├── qemu.h
    ├── screen.h
    ├── serial.h
    ├── setjmp.h
    ├── smimaster.h
    ├── soundbasedevice.h
    ├── spimaster.h
    ├── spimasteraux.h
    ├── spimasterdma.h
    ├── spinlock.h
    ├── startup.h
    ├── stdarg.h
    ├── string.h
    ├── synchronize.h
    ├── synchronize64.h
    ├── sysconfig.h
    ├── sysconfig.h.nopap
    ├── time.h
    ├── timer.h
    ├── tracer.h
    ├── translationtable64.h
    ├── types.h
    ├── usertimer.h
    ├── util.h
    ├── version.h
    ├── virtualgpiopin.h
    └── writebuffer.h
```
