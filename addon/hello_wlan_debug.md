```bash
$ minicom


Welcome to minicom 2.8

OPTIONS: 
Compiled on Jan  4 2021, 00:04:46.
Port /dev/cu.usbserial-AI057C9L, 08:12:02
Using character set conversion

Press Meta-Z for help on special keys

logger: Circle 50 started on Raspberry Pi 3 Model B+ 1GB (AArch64)
logger: Revision code is a020d3, compiler has been GCC 14.3.1
00:00:00.66 timer: SpeedFactor is 1.51
00:00:01.47 usbdev: Dumping 0x12 bytes starting at 0x610F00
00:00:01.47 usbdev: 0F00: 12 01 00 02 09 00 02 40-24 04 14 25 B3 0B 00 00
00:00:01.48 usbdev: 0F10: 00 01 25 B8 D5 F5 D5 55-75 5D 55 D4 D5 75 55 51
00:00:01.53 usbdev: Dumping 0x29 bytes starting at 0x610F80
00:00:01.54 usbdev: 0F80: 09 02 29 00 01 01 00 E0-01 09 04 00 00 01 09 00
00:00:01.54 usbdev: 0F90: 01 00 07 05 81 03 01 00-0C 09 04 00 01 01 09 00
00:00:01.55 usbdev: 0FA0: 02 00 07 05 81 03 01 00-0C B4 37 00 20 37 35 20
00:00:01.56 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:01.61 usbdev0-1: Interface int9-0-1 found
00:00:01.61 usbdev0-1: Function is not supported
00:00:01.62 usbdev0-1: Interface int9-0-2 found
00:00:01.62 usbdev0-1: Using device/interface int9-0-2
00:00:02.24 usbdev: Dumping 0x12 bytes starting at 0x613B40
00:00:02.24 usbdev: 3B40: 12 01 00 02 09 00 02 40-24 04 14 25 B3 0B 00 00
00:00:02.25 usbdev: 3B50: 00 01 25 B8 63 65 20 69-6E 74 39 2D 30 2D 32 00
00:00:02.30 usbdev: Dumping 0x29 bytes starting at 0x614D40
00:00:02.31 usbdev: 4D40: 09 02 29 00 01 01 00 E0-01 09 04 00 00 01 09 00
00:00:02.31 usbdev: 4D50: 01 00 07 05 81 03 01 00-0C 09 04 00 01 01 09 00
00:00:02.32 usbdev: 4D60: 02 00 07 05 81 03 01 00-0C B4 37 00 20 32 44 20
00:00:02.33 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:02.38 usbdev0-1: Interface int9-0-1 found
00:00:02.39 usbdev0-1: Function is not supported
00:00:02.39 usbdev0-1: Interface int9-0-2 found
00:00:02.39 usbdev0-1: Using device/interface int9-0-2
00:00:03.01 usbdev: Dumping 0x12 bytes starting at 0x617A40
00:00:03.01 usbdev: 7A40: 12 01 10 02 FF 00 FF 40-24 04 00 78 00 03 00 00
00:00:03.02 usbdev: 7A50: 00 01 07 A8 31 3A 20 49-6E 74 65 72 66 61 63 65
00:00:03.08 usbdev: Dumping 0x27 bytes starting at 0x617B40
00:00:03.08 usbdev: 7B40: 09 02 27 00 01 01 00 E0-01 09 04 00 00 03 FF 00
00:00:03.09 usbdev: 7B50: FF 00 07 05 81 02 00 02-00 07 05 02 02 00 02 00
00:00:03.09 usbdev: 7B60: 07 05 83 03 10 00 04 E9-32 20 36 36 20 36 31 20
00:00:03.10 usbdev0-1: Device ven424-7800 found
00:00:03.15 usbdev0-1: Using device/interface ven424-7800
00:00:03.23 lan7800: MAC address is B8:27:EB:AB:E8:48
00:00:03.37 usbhub: Port 1: Device configured
00:00:03.37 usbhub: Port 1: Device configured
00:00:03.38 dwroot: Device configured
00:00:03.40 sdhost: emmc1: sdhost-bcm2835 loaded
00:00:03.91 emmc: Capacity is 29512 MBytes
00:00:03.91 emmc: Found a valid version 3.0x SD card
00:00:04.05 wlan: cfgreadl 18000000: 45 43 26 15
00:00:04.05 wlan: ether4330: chip 0x4345 rev 6 type 1
00:00:04.06 wlan: cfgreadl 180000fc:  0 a0 10 18
00:00:04.06 wlan: core 800 mem 0x18000000
00:00:04.06 wlan: core 800 mem 0x1c000000
00:00:04.07 wlan: core 800 ctl 0x18100000
00:00:04.07 wlan: core 812 mem 0x18001000
00:00:04.08 wlan: core 812 ctl 0x18101000
00:00:04.08 wlan: core 83e mem 0x18002000
00:00:04.08 wlan: core 83e mem 0x18005000
00:00:04.09 wlan: core 83e mem 0x0
00:00:04.09 wlan: core 83e mem 0x180000
00:00:04.09 wlan: core 83e mem 0x200000
00:00:04.10 wlan: core 83e ctl 0x18102000
00:00:04.10 wlan: core 83e ctl 0x18105000
00:00:04.10 wlan: core 83c mem 0x18003000
00:00:04.11 wlan: core 83c mem 0x8000000
00:00:04.11 wlan: core 83c ctl 0x18103000
00:00:04.12 wlan: core 83c ctl 0x18106000
00:00:04.12 wlan: core 829 mem 0x18004000
00:00:04.12 wlan: core 829 ctl 0x18104000
00:00:04.13 wlan: core 135 ctl 0x18000000
00:00:04.13 wlan: core 135 ctl 0x18001000
00:00:04.13 wlan: core 135 ctl 0x18002000
00:00:04.14 wlan: core 135 ctl 0x18003000
00:00:04.14 wlan: core 135 ctl 0x18004000
00:00:04.15 wlan: core 135 ctl 0x18005000
00:00:04.15 wlan: core 135 ctl 0x18107000
00:00:04.15 wlan: core 240 ctl 0x19000000
00:00:04.16 wlan: core 240 ctl 0x18108000
00:00:04.16 wlan: core 367 mem 0x18109000
00:00:04.16 wlan: core 366 mem 0x1810a000
00:00:04.17 wlan: core 301 mem 0x18200000
00:00:04.17 wlan: core fff mem 0xa0000
00:00:04.18 wlan: core fff mem 0x240000
00:00:04.18 wlan: core fff mem 0x10000000
00:00:04.18 wlan: core fff mem 0x18008000
00:00:04.19 wlan: core fff mem 0x1810e000
00:00:04.19 wlan: core fff mem 0x18300000
00:00:04.19 wlan: core fff mem 0x1a000000
00:00:04.20 wlan: core fff mem 0x1d000000
00:00:04.20 wlan: cfgreadl 18102800:  0  0  0  0
00:00:04.21 wlan: cfgwritel 18102408: 23  0  0  0
00:00:04.21 wlan: cfgreadl 18102408: 23  0  0  0
00:00:04.21 wlan: cfgwritel 18102800:  1  0  0  0
00:00:04.22 wlan: cfgreadl 18102800:  1  0  0  0
00:00:04.22 wlan: cfgwritel 18102408: 23  0  0  0
00:00:04.23 wlan: cfgreadl 18102408: 23  0  0  0
00:00:04.23 wlan: cfgreadl 18102408: 23  0  0  0
00:00:04.24 wlan: cfgreadl 18102800:  1  0  0  0
00:00:04.24 wlan: sbreset 0x18102000 0x23 0x1 ->
00:00:04.25 wlan: cfgreadl 18102800:  1  0  0  0
00:00:04.25 wlan: cfgwritel 18102800:  0  0  0  0
00:00:04.25 wlan: cfgreadl 18102800:  0  0  0  0
00:00:04.26 wlan: cfgwritel 18102408: 21  0  0  0
00:00:04.26 wlan: cfgreadl 18102408: 21  0  0  0
00:00:04.27 wlan: cfgreadl 18102408: 21  0  0  0
00:00:04.27 wlan: cfgreadl 18102800:  0  0  0  0
00:00:04.28 wlan: 0x21 0x0
00:00:04.28 wlan: cfgreadl 18101800:  1  0  0  0
00:00:04.28 wlan: cfgwritel 18101408:  7  0  0  0
00:00:04.29 wlan: cfgreadl 18101408:  7  0  0  0
00:00:04.29 wlan: cfgreadl 18101408:  7  0  0  0
00:00:04.30 wlan: cfgreadl 18101800:  1  0  0  0
00:00:04.30 wlan: sbreset 0x18101000 0x7 0x1 ->
00:00:04.30 wlan: cfgreadl 18101800:  1  0  0  0
00:00:04.31 wlan: cfgwritel 18101800:  0  0  0  0
00:00:04.31 wlan: cfgreadl 18101800:  0  0  0  0
00:00:04.32 wlan: cfgwritel 18101408:  5  0  0  0
00:00:04.32 wlan: cfgreadl 18101408:  5  0  0  0
00:00:04.33 wlan: cfgreadl 18101408:  5  0  0  0
00:00:04.33 wlan: cfgreadl 18101800:  0  0  0  0
00:00:04.33 wlan: 0x5 0x0
00:00:04.34 wlan: cfgreadl 18002004: 44  b  0  0
00:00:04.34 wlan: cr4 banks b44
00:00:04.34 wlan: cfgwritel 18002040:  0  0  0  0
00:00:04.35 wlan: cfgreadl 18002044:  f 8c 10  0
00:00:04.35 wlan: bank 0 reg 108c0f size 131072
00:00:04.36 wlan: cfgwritel 18002040:  1  0  0  0
00:00:04.36 wlan: cfgreadl 18002044:  f 8c 10  0
00:00:04.37 wlan: bank 1 reg 108c0f size 131072
00:00:04.37 wlan: cfgwritel 18002040:  2  0  0  0
00:00:04.37 wlan: cfgreadl 18002044:  f 8c 10  0
00:00:04.38 wlan: bank 2 reg 108c0f size 131072
00:00:04.38 wlan: cfgwritel 18002040:  3  0  0  0
00:00:04.39 wlan: cfgreadl 18002044:  3 8c 10  0
00:00:04.39 wlan: bank 3 reg 108c03 size 32768
00:00:04.40 wlan: cfgwritel 18002040:  4  0  0  0
00:00:04.40 wlan: cfgreadl 18002044:  f 8c 10  0
00:00:04.40 wlan: bank 4 reg 108c0f size 131072
00:00:04.41 wlan: cfgwritel 18002040:  5  0  0  0
00:00:04.41 wlan: cfgreadl 18002044:  7 8c 10  0
00:00:04.42 wlan: bank 5 reg 108c07 size 65536
00:00:04.42 wlan: cfgwritel 18002040:  6  0  0  0
00:00:04.43 wlan: cfgreadl 18002044:  f 8c 10  0
00:00:04.43 wlan: bank 6 reg 108c0f size 131072
00:00:04.44 wlan: cfgwritel 18002040:  7  0  0  0
00:00:04.44 wlan: cfgreadl 18002044:  7 8c 10  0
00:00:04.44 wlan: bank 7 reg 108c07 size 65536
00:00:04.45 wlan: ARM 0x18102000 D11 0x18101000 SOCRAM 0x0,0x0 819200 bytes @ 0x198000
00:00:04.46 wlan: chipclk: 40
00:00:04.46 wlan: chipclk: 61
00:00:04.46 wlan: cfgwritel 1c000058:  0  0  0  0
00:00:04.47 wlan: cfgwritel 1c00005c:  0  0  0  0
00:00:04.47 wlan: firmware load...
00:00:04.76 wlan: compare...
00:00:05.04 wlan: 
00:00:05.04 wlan: config load...
00:00:05.04 wlan: compare...
00:00:05.05 wlan: 
00:00:05.05 wlan: cfgwritel 18004020: ff ff ff ff
00:00:05.05 wlan: b83ef198
00:00:05.05 wlan: cfgreadl 18102800:  0  0  0  0
00:00:05.06 wlan: cfgwritel 18102408: 23  0  0  0
00:00:05.06 wlan: cfgreadl 18102408: 23  0  0  0
00:00:05.07 wlan: cfgwritel 18102800:  1  0  0  0
00:00:05.07 wlan: cfgreadl 18102800:  1  0  0  0
00:00:05.08 wlan: cfgwritel 18102408:  3  0  0  0
00:00:05.08 wlan: cfgreadl 18102408:  3  0  0  0
00:00:05.09 wlan: cfgreadl 18102408:  3  0  0  0
00:00:05.09 wlan: cfgreadl 18102800:  1  0  0  0
00:00:05.09 wlan: sbreset 0x18102000 0x3 0x1 ->
00:00:05.10 wlan: cfgreadl 18102800:  1  0  0  0
00:00:05.10 wlan: cfgwritel 18102800:  0  0  0  0
00:00:05.11 wlan: cfgreadl 18102800:  0  0  0  0
00:00:05.11 wlan: cfgwritel 18102408:  1  0  0  0
00:00:05.12 wlan: cfgreadl 18102408:  1  0  0  0
00:00:05.12 wlan: cfgreadl 18102408:  1  0  0  0
00:00:05.12 wlan: cfgreadl 18102800:  0  0  0  0
00:00:05.13 wlan: 0x1 0x0
00:00:05.13 wlan: enabling HT clock...
00:00:05.26 wlan: chipclk: d2
00:00:05.26 wlan: cfgwritel 18004048:  0  0  4  0
00:00:05.26 wlan: cfgwritel 18004024: e0  0  0  0
00:00:05.38 wlsetvar clmload:: Dumping 0x584 bytes starting at 0x645440
00:00:05.38 wlsetvar clmload:: 5440: 02 10 02 00 78 05 00 00-00 00 55 5D 42 4C 4F 42
00:00:05.39 wlsetvar clmload:: 5450: 3C 00 00 00 8E 7F B5 22-01 00 00 00 02 00 00 00
00:00:05.40 wlsetvar clmload:: 5460: 00 00 00 00 3C 00 00 00-34 0A 00 00 BB 46 6A 3D
00:00:05.40 wlsetvar clmload:: 5470: 00 00 00 00 00 00 00 00-70 0A 00 00 04 00 00 00
00:00:05.41 wlsetvar clmload:: 5480: 8A 44 52 FF 00 00 00 00-43 4C 4D 20 44 41 54 41
00:00:05.42 wlsetvar clmload:: 5490: 00 00 0C 00 02 00 52 50-69 2E 34 00 00 00 00 00
00:00:05.43 wlsetvar clmload:: 54A0: 00 00 00 00 00 00 00 00-00 00 31 2E 32 39 2E 34
00:00:05.43 wlsetvar clmload:: 54B0: 00 00 00 00 00 00 00 00-08 04 00 00 43 6C 6D 49
00:00:05.44 wlsetvar clmload:: 54C0: 6D 70 6F 72 74 3A 20 31-2E 33 39 2E 31 00 00 00
00:00:05.45 wlsetvar clmload:: 54D0: 00 00 00 00 00 00 00 00-00 00 76 32 20 32 31 2F
00:00:05.46 wlsetvar clmload:: 54E0: 31 31 2F 31 35 00 00 00-00 00 00 00 00 00 00 00
00:00:05.46 wlsetvar clmload:: 54F0: 26 2E 26 3E 26 6E 26 7E-26 86 26 9F 36 3E 86 86
00:00:05.47 wlsetvar clmload:: 5500: 86 8E 86 9F 97 9F 06 02-02 01 01 01 01 00 06 02
00:00:05.48 wlsetvar clmload:: 5510: 05 01 01 01 07 02 04 01-01 01 02 08 04 02 02 01
00:00:05.49 wlsetvar clmload:: 5520: 01 01 09 02 02 01 01 01-01 02 00 FF 01 24 01 00
00:00:05.49 wlsetvar clmload:: 5530: 01 6C 01 01 02 00 FF 01-1B 01 00 01 44 01 01 01
00:00:05.50 wlsetvar clmload:: 5540: 00 FF 01 1E 00 00 01 44-00 01 02 00 FF 01 14 01
00:00:05.51 wlsetvar clmload:: 5550: 00 01 40 01 01 02 00 FF-01 14 01 00 01 40 01 01
00:00:05.52 wlsetvar clmload:: 5560: 02 00 FF 01 14 01 00 01-40 01 01 02 00 FF 01 14
00:00:05.52 wlsetvar clmload:: 5570: 01 00 01 44 01 01 02 00-FF 01 14 01 00 01 40 01
00:00:05.53 wlsetvar clmload:: 5580: 01 02 00 FF 01 14 01 00-01 40 01 01 02 00 FF 01
00:00:05.54 wlsetvar clmload:: 5590: 14 01 00 01 40 01 01 02-00 FF 01 1E 01 00 01 44
00:00:05.55 wlsetvar clmload:: 55A0: 01 01 02 00 FF 01 14 01-00 01 40 01 01 02 00 FF
00:00:05.55 wlsetvar clmload:: 55B0: 01 14 01 00 01 40 01 01-02 00 FF 01 1E 01 00 01
00:00:05.56 wlsetvar clmload:: 55C0: 40 01 01 02 00 FF 01 1B-01 00 01 40 01 01 01 00
00:00:05.57 wlsetvar clmload:: 55D0: FF 01 1E 00 00 01 44 00-01 01 00 FF 01 0A 00 02
00:00:05.58 wlsetvar clmload:: 55E0: 01 28 00 01 01 00 FF 01-0A 00 02 01 28 00 01 02
00:00:05.58 wlsetvar clmload:: 55F0: 00 00 01 0A 01 02 01 28-01 01 00 00 03 00 00 00
00:00:05.59 wlsetvar clmload:: 5600: E0 01 00 00 0A 0C 0D 0E-0F 10 11 12 13 14 15 0C
00:00:05.60 wlsetvar clmload:: 5610: 00 01 02 03 04 05 06 07-08 09 0A 0B 01 0B 01 0D
00:00:05.61 wlsetvar clmload:: 5620: 0C 0D 24 30 24 40 24 74-24 80 24 8C 24 90 24 A5
00:00:05.61 wlsetvar clmload:: 5630: 34 40 34 74 34 8C 34 A5-84 8C 84 90 84 A5 95 A5
00:00:05.62 wlsetvar clmload:: 5640: 00 01 00 01 01 01 03 02-03 11 01 04 03 05 0E 11
00:00:05.63 wlsetvar clmload:: 5650: 02 05 10 02 06 11 01 07-02 07 11 01 09 02 0A 11
00:00:05.64 wlsetvar clmload:: 5660: 00 00 00 00 00 00 00 00-24 40 04 64 90 04 95 A5
00:00:05.64 wlsetvar clmload:: 5670: 04 32 30 32 31 2D 31 31-2D 31 35 20 30 31 3A 33
00:00:05.65 wlsetvar clmload:: 5680: 32 3A 34 30 00 00 00 04-03 40 05 00 40 0E 00 44
00:00:05.66 wlsetvar clmload:: 5690: 11 00 05 03 40 02 00 40-07 00 40 0A 00 08 02 40
00:00:05.67 wlsetvar clmload:: 56A0: 02 00 40 0B 00 04 02 44-0A 00 44 11 00 05 02 44
00:00:05.67 wlsetvar clmload:: 56B0: 06 00 44 0A 00 08 02 44-07 00 44 0B 00 04 02 44
00:00:05.68 wlsetvar clmload:: 56C0: 05 00 44 10 00 05 02 44-02 00 44 09 00 08 02 44
00:00:05.69 wlsetvar clmload:: 56D0: 02 00 44 0A 00 04 02 44-03 00 44 11 00 05 02 44
00:00:05.69 wlsetvar clmload:: 56E0: 00 00 44 0A 00 08 02 44-00 00 44 0B 00 04 02 38
00:00:05.70 wlsetvar clmload:: 56F0: 08 00 44 11 00 05 01 38-05 00 08 02 38 04 00 44
00:00:05.71 wlsetvar clmload:: 5700: 0B 00 04 01 40 07 00 05-01 40 04 00 08 01 40 03
00:00:05.72 wlsetvar clmload:: 5710: 00 00 01 50 03 00 04 01-40 07 00 05 01 40 04 00
00:00:05.72 wlsetvar clmload:: 5720: 08 01 40 03 00 04 01 44-07 00 05 01 40 04 00 08
00:00:05.73 wlsetvar clmload:: 5730: 01 40 03 00 04 01 44 04-00 05 01 40 01 00 08 01
00:00:05.74 wlsetvar clmload:: 5740: 40 01 00 04 01 40 07 00-05 01 40 04 00 08 01 40
00:00:05.75 wlsetvar clmload:: 5750: 03 00 04 01 44 07 00 05-01 44 04 00 08 01 44 03
00:00:05.75 wlsetvar clmload:: 5760: 00 04 02 2C 07 00 44 11-00 05 02 2C 04 00 44 0A
00:00:05.76 wlsetvar clmload:: 5770: 00 08 02 2C 03 00 44 0B-00 04 03 38 05 00 38 0F
00:00:05.77 wlsetvar clmload:: 5780: 00 44 11 00 05 03 38 02-00 38 08 00 44 0A 00 08
00:00:05.78 wlsetvar clmload:: 5790: 02 38 02 00 38 0A 00 04-02 44 06 00 44 11 00 05
00:00:05.78 wlsetvar clmload:: 57A0: 02 44 03 00 44 0A 00 08-02 40 03 00 40 0B 00 04
00:00:05.79 wlsetvar clmload:: 57B0: 01 44 09 00 05 01 44 05-00 08 01 44 05 00 04 02
00:00:05.80 wlsetvar clmload:: 57C0: 2C 03 00 38 11 00 05 02-2C 00 00 38 0A 00 08 02
00:00:05.81 wlsetvar clmload:: 57D0: 2C 00 00 38 0B 00 04 02-2C 03 00 38 11 00 05 02
00:00:05.81 wlsetvar clmload:: 57E0: 2C 00 00 38 0A 00 08 02-2C 00 00 38 0B 00 12 04
00:00:05.82 wlsetvar clmload:: 57F0: 05 06 07 08 09 0A 0B 0C-0D 0E 0F 10 11 12 13 14
00:00:05.83 wlsetvar clmload:: 5800: 15 00 01 44 01 00 00 01-44 01 00 00 01 44 00 00
00:00:05.84 wlsetvar clmload:: 5810: 00 01 44 01 00 00 01 44-01 00 00 01 40 01 00 00
00:00:05.84 wlsetvar clmload:: 5820: 01 40 01 00 00 01 40 01-00 00 01 40 01 00 00 01
00:00:05.85 wlsetvar clmload:: 5830: 40 01 00 00 01 40 01 00-00 01 44 01 00 00 01 44
00:00:05.86 wlsetvar clmload:: 5840: 01 00 00 01 44 01 00 00-01 44 01 00 00 01 44 00
00:00:05.87 wlsetvar clmload:: 5850: 00 02 01 28 00 00 02 01-28 00 00 02 01 28 01 00
00:00:05.87 wlsetvar clmload:: 5860: 02 00 00 00 E0 03 00 00-01 00 00 00 7E 00 00 00
00:00:05.88 wlsetvar clmload:: 5870: 04 00 00 00 85 00 00 00-0A 0C 0D 0E 0F 10 11 12
00:00:05.89 wlsetvar clmload:: 5880: 13 14 15 08 04 05 06 07-08 09 0A 0B 01 0D 01 00
00:00:05.90 wlsetvar clmload:: 5890: C0 04 00 00 74 01 00 00-94 01 00 00 17 0A 00 00
00:00:05.90 wlsetvar clmload:: 58A0: B8 01 00 00 F0 03 00 00-A1 00 00 00 ED 08 00 00
00:00:05.91 wlsetvar clmload:: 58B0: 79 03 00 00 FD 01 00 00-C8 04 00 00 D8 01 00 00
00:00:05.92 wlsetvar clmload:: 58C0: FC 09 00 00 7F B2 00 00-D8 03 00 00 00 00 00 00
00:00:05.93 wlsetvar clmload:: 58D0: 68 00 00 00 1C 0A 00 00-00 00 00 00 04 0A 00 00
00:00:05.93 wlsetvar clmload:: 58E0: 66 03 00 00 00 00 00 00-7C 01 00 00 00 00 00 00
00:00:05.94 wlsetvar clmload:: 58F0: E9 01 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:05.95 wlsetvar clmload:: 5900: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:05.96 wlsetvar clmload:: 5910: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:05.96 wlsetvar clmload:: 5920: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:05.97 wlsetvar clmload:: 5930: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:05.98 wlsetvar clmload:: 5940: 00 00 00 00 00 00 00 00-01 00 00 00 04 04 00 00
00:00:05.99 wlsetvar clmload:: 5950: 75 00 00 00 D0 04 00 00-41 44 00 05 06 05 06 00
00:00:05.99 wlsetvar clmload:: 5960: 29 41 45 00 08 09 08 09-00 09 41 4C 00 05 06 05
00:00:06.00 wlsetvar clmload:: 5970: 06 00 29 41 4F 00 05 06-05 06 00 29 41 52 00 0D
00:00:06.01 wlsetvar clmload:: 5980: 0E 0D 0E 00 0A 41 54 00-05 06 05 06 00 29 41 55
00:00:06.02 wlsetvar clmload:: 5990: 00 00 01 00 01 00 09 41-5A 00 05 06 05 06 00 29
00:00:06.02 wlsetvar clmload:: 59A0: 42 41 00 05 06 05 06 00-29 42 45 00 05 06 05 06
00:00:06.03 wlsetvar clmload:: 59B0: 00 29 42 46 00 05 06 05-06 00 09 42 47 00 05 06
00:00:06.04 wlsetvar clmload:: 59C0: 05 06 00 29 42 15 55 15-55 7D 55 15 5F 5D 55 55
00:00:06.05 wlan: cfgreadl 18004020: c0  0  0 21
00:00:06.05 wlan: cfgwritel 18004020: c0  0  0 21
00:00:06.05 wlan: cfgreadl 1800404c:  8  0  4  0
00:00:06.06 wlan: cfgwritel 18004040:  2  0  0  0
00:00:06.06 wlan: ether4330: firmware ready
00:00:06.07 wlsetvar clmload:: Dumping 0x50C bytes starting at 0x645440
00:00:06.07 wlsetvar clmload:: 5440: 04 10 02 00 00 05 00 00-00 00 55 5D 42 4A 00 05
00:00:06.08 wlsetvar clmload:: 5450: 06 05 06 00 29 42 4C 00-05 06 05 06 00 29 42 4F
00:00:06.09 wlsetvar clmload:: 5460: 00 01 02 01 02 00 09 42-52 00 08 09 08 09 00 09
00:00:06.10 wlsetvar clmload:: 5470: 42 54 00 05 06 05 06 00-09 43 41 00 02 03 02 03
00:00:06.10 wlsetvar clmload:: 5480: 00 0A 43 48 00 05 06 05-06 00 29 43 4C 00 08 09
00:00:06.11 wlsetvar clmload:: 5490: 08 09 00 09 43 4D 00 05-06 05 06 00 29 43 4E 00
00:00:06.12 wlsetvar clmload:: 54A0: 03 04 03 04 00 09 43 4F-00 04 05 04 05 00 0A 43
00:00:06.13 wlsetvar clmload:: 54B0: 52 00 0F 10 0F 10 00 0A-43 56 00 05 06 05 06 00
00:00:06.13 wlsetvar clmload:: 54C0: 29 43 59 00 05 06 05 06-00 29 43 5A 00 05 06 05
00:00:06.14 wlsetvar clmload:: 54D0: 06 00 29 44 45 00 05 06-05 06 00 29 44 4B 00 05
00:00:06.15 wlsetvar clmload:: 54E0: 06 05 06 00 29 44 4F 00-08 09 08 09 00 0A 44 5A
00:00:06.16 wlsetvar clmload:: 54F0: 00 06 07 06 07 00 08 45-43 00 08 09 08 09 00 09
00:00:06.16 wlsetvar clmload:: 5500: 45 45 00 05 06 05 06 00-29 45 53 00 05 06 05 06
00:00:06.17 wlsetvar clmload:: 5510: 00 29 46 49 00 05 06 05-06 00 29 46 4F 00 05 06
00:00:06.18 wlsetvar clmload:: 5520: 05 06 00 29 46 52 00 05-06 05 06 00 29 47 41 00
00:00:06.19 wlsetvar clmload:: 5530: 05 06 05 06 00 29 47 42-00 08 09 08 09 00 09 47
00:00:06.19 wlsetvar clmload:: 5540: 45 00 05 06 05 06 00 29-47 46 00 05 06 05 06 00
00:00:06.20 wlsetvar clmload:: 5550: 29 47 49 00 05 06 05 06-00 29 47 4C 00 05 06 05
00:00:06.21 wlsetvar clmload:: 5560: 06 00 29 47 50 00 05 06-05 06 00 29 47 52 00 05
00:00:06.22 wlsetvar clmload:: 5570: 06 05 06 00 29 47 54 00-07 08 07 08 00 09 48 4B
00:00:06.22 wlsetvar clmload:: 5580: 00 08 09 08 09 00 09 48-52 00 05 06 05 06 00 29
00:00:06.23 wlsetvar clmload:: 5590: 48 55 00 05 06 05 06 00-29 49 45 00 05 06 05 06
00:00:06.24 wlsetvar clmload:: 55A0: 00 29 49 4C 00 09 0A 09-0A 00 09 49 4E 00 0A 0B
00:00:06.25 wlsetvar clmload:: 55B0: 0A 0B 00 09 49 51 00 05-06 05 06 00 29 49 53 00
00:00:06.25 wlsetvar clmload:: 55C0: 05 06 05 06 00 29 49 54-00 05 06 05 06 00 29 4A
00:00:06.26 wlsetvar clmload:: 55D0: 50 00 0B 0C 0B 0C 00 0A-4B 45 00 05 06 05 06 00
00:00:06.27 wlsetvar clmload:: 55E0: 29 4B 52 00 0C 0D 0C 0D-00 09 4C 49 00 05 06 05
00:00:06.28 wlsetvar clmload:: 55F0: 06 00 29 4C 53 00 05 06-05 06 00 09 4C 54 00 05
00:00:06.28 wlsetvar clmload:: 5600: 06 05 06 00 29 4C 55 00-05 06 05 06 00 29 4C 56
00:00:06.29 wlsetvar clmload:: 5610: 00 05 06 05 06 00 29 4C-59 00 05 06 05 06 00 29
00:00:06.30 wlsetvar clmload:: 5620: 4D 43 00 05 06 05 06 00-29 4D 44 00 05 06 05 06
00:00:06.31 wlsetvar clmload:: 5630: 00 29 4D 45 00 05 06 05-06 00 29 4D 46 00 05 06
00:00:06.31 wlsetvar clmload:: 5640: 05 06 00 29 4D 4B 00 05-06 05 06 00 29 4D 4C 00
00:00:06.32 wlsetvar clmload:: 5650: 05 06 05 06 00 29 4D 51-00 05 06 05 06 00 29 4D
00:00:06.33 wlsetvar clmload:: 5660: 54 00 05 06 05 06 00 29-4D 58 00 0D 0E 0D 0E 00
00:00:06.34 wlsetvar clmload:: 5670: 09 4D 59 00 0E 0F 0E 0F-00 09 4D 5A 00 05 06 05
00:00:06.34 wlsetvar clmload:: 5680: 06 00 29 4E 49 00 04 05-04 05 00 09 4E 4C 00 05
00:00:06.35 wlsetvar clmload:: 5690: 06 05 06 00 29 4E 4F 00-05 06 05 06 00 29 4E 5A
00:00:06.36 wlsetvar clmload:: 56A0: 00 08 09 08 09 00 09 4F-4D 00 05 06 05 06 00 09
00:00:06.36 wlsetvar clmload:: 56B0: 50 41 00 08 09 08 09 00-0A 50 45 00 08 09 08 09
00:00:06.37 wlsetvar clmload:: 56C0: 00 09 50 46 00 05 06 05-06 00 29 50 48 00 08 09
00:00:06.38 wlsetvar clmload:: 56D0: 08 09 00 09 50 4C 00 05-06 05 06 00 29 50 4D 00
00:00:06.39 wlsetvar clmload:: 56E0: 05 06 05 06 00 29 50 54-00 05 06 05 06 00 29 52
00:00:06.39 wlsetvar clmload:: 56F0: 45 00 05 06 05 06 00 29-52 4F 00 05 06 05 06 00
00:00:06.40 wlsetvar clmload:: 5700: 29 52 53 00 05 06 05 06-00 29 52 57 00 07 08 07
00:00:06.41 wlsetvar clmload:: 5710: 08 00 09 53 45 00 05 06-05 06 00 29 53 47 00 08
00:00:06.42 wlsetvar clmload:: 5720: 09 08 09 00 09 53 49 00-05 06 05 06 00 29 53 4B
00:00:06.42 wlsetvar clmload:: 5730: 00 05 06 05 06 00 29 53-4D 00 05 06 05 06 00 29
00:00:06.43 wlsetvar clmload:: 5740: 53 52 00 05 06 05 06 00-29 53 5A 00 05 06 05 06
00:00:06.44 wlsetvar clmload:: 5750: 00 29 54 46 00 05 06 05-06 00 29 54 47 00 05 06
00:00:06.45 wlsetvar clmload:: 5760: 05 06 00 29 54 48 00 08-09 08 09 00 09 54 52 00
00:00:06.45 wlsetvar clmload:: 5770: 05 06 05 06 00 29 54 57-00 0F 10 0F 10 00 0A 54
00:00:06.46 wlsetvar clmload:: 5780: 5A 00 05 06 05 06 00 29-55 47 00 05 06 05 06 00
00:00:06.47 wlsetvar clmload:: 5790: 29 55 4D 00 0F 10 0F 10-00 0A 55 53 00 0F 10 0F
00:00:06.48 wlsetvar clmload:: 57A0: 10 00 0A 56 41 00 05 06-05 06 00 29 56 45 00 03
00:00:06.48 wlsetvar clmload:: 57B0: 04 03 04 00 09 56 49 00-0F 10 0F 10 00 0A 57 46
00:00:06.49 wlsetvar clmload:: 57C0: 00 05 06 05 06 00 29 58-4B 00 05 06 05 06 00 29
00:00:06.50 wlsetvar clmload:: 57D0: 58 54 00 10 00 10 00 00-20 58 58 00 11 11 11 11
00:00:06.51 wlsetvar clmload:: 57E0: 00 2A 58 5A 00 12 12 12-12 00 2A 59 54 00 05 06
00:00:06.51 wlsetvar clmload:: 57F0: 05 06 00 29 5A 41 00 08-09 08 09 00 09 00 00 FF
00:00:06.52 wlsetvar clmload:: 5800: 00 00 00 06 01 FF 03 17-05 17 0E 1E 11 00 03 40
00:00:06.53 wlsetvar clmload:: 5810: 05 01 40 0E 01 44 11 01-0C 01 FF 02 1B 0A 1E 11
00:00:06.54 wlsetvar clmload:: 5820: 00 02 3C 0A 01 3C 11 01-07 02 FF 03 17 05 17 0F
00:00:06.54 wlsetvar clmload:: 5830: 1E 11 00 02 3C 05 01 3C-10 01 04 01 FF 02 17 03
00:00:06.55 wlsetvar clmload:: 5840: 14 11 00 02 3C 03 01 3C-11 01 0B 01 FF 02 11 08
00:00:06.56 wlsetvar clmload:: 5850: 14 11 00 02 38 03 01 3C-0D 01 09 01 FF 01 17 07
00:00:06.57 wlsetvar clmload:: 5860: 00 02 40 03 01 3C 0C 01-03 01 FF 01 17 03 00 01
00:00:06.57 wlsetvar clmload:: 5870: 3C 03 01 09 01 FF 01 17-07 00 01 40 07 01 09 01
00:00:06.58 wlsetvar clmload:: 5880: FF 01 17 07 00 01 3C 07-01 05 01 FF 01 14 04 00
00:00:06.59 wlsetvar clmload:: 5890: 01 3C 04 01 09 01 FF 01-18 07 00 01 3C 07 01 09
00:00:06.60 wlsetvar clmload:: 58A0: 02 FF 01 14 07 00 01 44-07 01 0A 01 FF 02 0E 07
00:00:06.60 wlsetvar clmload:: 58B0: 14 11 00 02 2C 07 01 2C-11 01 07 01 FF 03 11 05
00:00:06.61 wlsetvar clmload:: 58C0: 11 0F 1E 11 00 03 38 03-01 2C 0B 01 2C 10 01 08
00:00:06.62 wlsetvar clmload:: 58D0: 01 FF 02 1E 06 1E 11 00-02 3C 06 01 3C 11 01 0B
00:00:06.63 wlsetvar clmload:: 58E0: 02 FF 02 18 08 1E 11 00-01 3C 09 01 04 00 01 02
00:00:06.63 wlsetvar clmload:: 58F0: 0B 03 0E 11 00 02 2C 03-01 38 11 01 04 00 01 02
00:00:06.64 wlsetvar clmload:: 5900: 0B 03 0E 11 00 02 2C 03-01 38 11 01 00 00 00 00
00:00:06.65 wlsetvar clmload:: 5910: 00 00 00 00 12 04 05 06-07 08 09 0A 0B 0C 0D 0E
00:00:06.66 wlsetvar clmload:: 5920: 0F 10 11 12 13 14 15 01-02 02 03 11 2A 2A 2A 3A
00:00:06.66 wlsetvar clmload:: 5930: 2A 6A 2A 7A 2A 8A 2A 9B-2A AB 3A 3A 6A 6A 7A AB
00:00:06.67 wlsetvar clmload:: 5940: 8A 9B 9B 9B 45 43 00 00-00 00 00 00 04 04 00 00
00:00:06.68 wlan: cfgreadl 18004020: 80  0  0  0
00:00:06.68 wlan: cfgwritel 18004020: 80  0  0  0
00:00:06.69 wlan: cfgreadl 1800404c:  2  0  4  0
00:00:06.69 wlan: cfgwritel 18004040:  2  0  0  0
00:00:06.70 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.70 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.71 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.71 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.71 wlan: ether4330: addr B8:27:EB:FE:BD:1D
00:00:06.72 wlsetvar assoc_listen:: Dumping 0x4 bytes starting at 0x29C7F8
00:00:06.72 wlsetvar assoc_listen:: C7F8: 0A 00 00 00 00 00 00 00-00 02 00 00 00 00 00 00
00:00:06.73 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.74 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.74 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.75 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.75 wlsetvar bus:txglom:: Dumping 0x4 bytes starting at 0x29C810
00:00:06.76 wlsetvar bus:txglom:: C810: 00 00 00 00 00 00 00 00-80 DA 13 00 00 00 00 00
00:00:06.76 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.77 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.77 wlsetvar bcn_timeout:: Dumping 0x4 bytes starting at 0x29C818
00:00:06.78 wlsetvar bcn_timeout:: C818: 0A 00 00 00 00 00 00 00-01 08 00 00 00 00 00 00
00:00:06.79 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.79 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.80 wlsetvar assoc_retry_max:: Dumping 0x4 bytes starting at 0x29C820
00:00:06.80 wlsetvar assoc_retry_max:: C820: 03 00 00 00 00 00 00 00-80 DA 13 00 00 00 00 00
00:00:06.81 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.82 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.82 wlsetvar event_msgs:: Dumping 0x10 bytes starting at 0x29C890
00:00:06.83 wlsetvar event_msgs:: C890: FF FF EF FF FF EE BF FF-7F FF FF FF FF FF FF EF
00:00:06.83 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.84 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.84 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.85 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.85 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.86 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.86 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.86 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.89 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.89 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.90 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.90 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.91 wlsetvar roam_off:: Dumping 0x4 bytes starting at 0x29C858
00:00:06.91 wlsetvar roam_off:: C858: 01 00 00 00 00 00 00 00-01 00 00 00 00 00 00 00
00:00:06.92 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.92 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.93 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.93 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.94 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.94 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.95 wlan: cfgreadl 18004020: 40  0 80  0
00:00:06.95 wlan: cfgwritel 18004020: 40  0 80  0
00:00:06.95 kernel: Compile time: Sep  4 2025 14:20:14
00:00:07.08 wpa: Setting country code to 'JP'
00:00:07.08 wlsetvar country:: Dumping 0xC bytes starting at 0x6600E8
00:00:07.09 wlsetvar country:: 00E8: 4A 50 00 E7 FF FF FF FF-4A 50 00 55 F5 55 55 75
00:00:07.10 wlan: cfgreadl 18004020: 40  0 80  0
00:00:07.10 wlan: cfgwritel 18004020: 40  0 80  0
00:00:07.11 wlan: ether4330: [country code changed] status 0 flags 0x18 reason 0
00:00:08.11 wlan: cfgreadl 18004020: 40  0 80  0
00:00:08.11 wlan: cfgwritel 18004020: 40  0 80  0
00:00:08.11 wlsetvar escan:: Dumping 0x88 bytes starting at 0x13C090
00:00:08.12 wlsetvar escan:: C090: 01 00 00 00 01 00 34 12-00 00 00 00 00 00 00 00
00:00:08.13 wlsetvar escan:: C0A0: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:08.13 wlsetvar escan:: C0B0: 00 00 00 00 00 00 00 00-00 00 00 00 FF FF FF FF
00:00:08.14 wlsetvar escan:: C0C0: FF FF 02 00 FF FF FF FF-FF FF FF FF FF FF FF FF
00:00:08.15 wlsetvar escan:: C0D0: FF FF FF FF 0E 00 01 00-01 2B 02 2B 03 2B 04 2B
00:00:08.16 wlsetvar escan:: C0E0: 05 2E 06 2E 07 2E 08 2B-09 2B 0A 2B 0B 2B 0C 2B
00:00:08.16 wlsetvar escan:: C0F0: 0D 2B 0E 2B 00 00 00 00-00 00 00 00 00 00 00 00
00:00:08.17 wlsetvar escan:: C100: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:08.18 wlsetvar escan:: C110: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:08.18 wlan: cfgreadl 18004020: 40  0 80  0
00:00:08.19 wlan: cfgwritel 18004020: 40  0 80  0
00:00:08.19 wlan: ether4330: [escan result] status 8 flags 0x0 reason 0
00:00:08.20 wlan: ether4330: [escan result] status 8 flags 0x0 reason 0
00:00:08.21 wlan: cfgreadl 18004020: 40  0  0  0
00:00:08.21 wlan: cfgwritel 18004020: 40  0  0  0
00:00:08.21 wlan: ether4330: [escan result] status 8 flags 0x0 reason 0
00:00:08.57 wlan: cfgreadl 18004020: 40  0 80  0
00:00:08.57 wlan: cfgwritel 18004020: 40  0 80  0
00:00:08.58 wlan: ether4330: [escan result] status 8 flags 0x0 reason 0
00:00:08.59 wlan: cfgreadl 18004020: 40  0 80  0
00:00:08.59 wlan: cfgwritel 18004020: 40  0 80  0
00:00:08.60 wlan: ether4330: [escan result] status 8 flags 0x0 reason 0
00:00:08.70 wlan: cfgreadl 18004020: 40  0 80  0
00:00:08.71 wlan: cfgwritel 18004020: 40  0 80  0
00:00:08.71 wlan: ether4330: [escan result] status 8 flags 0x0 reason 0
00:00:08.76 wlan: cfgreadl 18004020: 40  0 80  0
00:00:08.76 wlan: cfgwritel 18004020: 40  0 80  0
00:00:08.76 wlan: ether4330: [escan result] status 8 flags 0x0 reason 0
00:00:08.78 wlan: cfgreadl 18004020: 40  0 80  0
00:00:08.78 wlan: cfgwritel 18004020: 40  0 80  0
00:00:08.79 wlan: ether4330: [escan result] status 8 flags 0x0 reason 0
00:00:08.80 wlan: cfgreadl 18004020: 40  0 80  0
00:00:08.80 wlan: cfgwritel 18004020: 40  0 80  0
00:00:08.81 wlan: ether4330: [escan result] status 8 flags 0x0 reason 0
00:00:08.81 wlan: ether4330: [escan result] status 8 flags 0x0 reason 0
00:00:08.82 wlan: cfgreadl 18004020: 40  0  0  0
00:00:08.82 wlan: cfgwritel 18004020: 40  0  0  0
00:00:08.86 wlan: cfgreadl 18004020: 40  0 80  0
00:00:08.86 wlan: cfgwritel 18004020: 40  0 80  0
00:00:08.87 wlan: ether4330: [escan result] status 8 flags 0x0 reason 0
00:00:09.66 wlan: cfgreadl 18004020: 40  0 80  0
00:00:09.66 wlan: cfgwritel 18004020: 40  0 80  0
00:00:09.66 wlan: ether4330: [escan result] status 8 flags 0x0 reason 0
00:00:10.72 wpa: Trying to associate with f8:b7:97:87:2c:de (SSID='MSRS_TDF_A2_S04' freq=2452 MHz)
00:00:10.73 wlsetvar wpaie:: Dumping 0x16 bytes starting at 0x65FA90
00:00:10.73 wlsetvar wpaie:: FA90: 30 14 01 00 00 0F AC 04-01 00 00 0F AC 04 01 00
00:00:10.74 wlsetvar wpaie:: FAA0: 00 0F AC 02 0C 00 00 00-E8 BD 0C 00 00 00 00 00
00:00:10.75 wlan: cfgreadl 18004020: 40  0 80  0
00:00:10.75 wlan: cfgwritel 18004020: 40  0 80  0
00:00:10.76 wlsetvar wpa_auth:: Dumping 0x4 bytes starting at 0x65FA88
00:00:10.76 wlsetvar wpa_auth:: FA88: C0 00 00 00 00 00 00 00-30 14 01 00 00 0F AC 04
00:00:10.77 wlan: cfgreadl 18004020: 40  0 80  0
00:00:10.77 wlan: cfgwritel 18004020: 40  0 80  0
00:00:10.78 wlsetvar auth:: Dumping 0x4 bytes starting at 0x65FA88
00:00:10.78 wlsetvar auth:: FA88: 00 00 00 00 00 00 00 00-30 14 01 00 00 0F AC 04
00:00:10.79 wlan: cfgreadl 18004020: 40  0 80  0
00:00:10.80 wlan: cfgwritel 18004020: 40  0 80  0
00:00:10.80 wlsetvar wsec:: Dumping 0x4 bytes starting at 0x65FA88
00:00:10.81 wlsetvar wsec:: FA88: 04 00 00 00 00 00 00 00-30 14 01 00 00 0F AC 04
00:00:10.81 wlan: cfgreadl 18004020: 40  0 80  0
00:00:10.82 wlan: cfgwritel 18004020: 40  0 80  0
00:00:10.82 wlsetvar wpa_auth:: Dumping 0x4 bytes starting at 0x65FA88
00:00:10.83 wlsetvar wpa_auth:: FA88: 80 00 00 00 00 00 00 00-30 14 01 00 00 0F AC 04
00:00:10.84 wlan: cfgreadl 18004020: 40  0 80  0
00:00:10.84 wlan: cfgwritel 18004020: 40  0 80  0
00:00:10.85 wlsetvar join:: Dumping 0x44 bytes starting at 0x65FA68
00:00:10.85 wlsetvar join:: FA68: 0F 00 00 00 4D 53 52 53-5F 54 44 46 5F 41 32 5F
00:00:10.86 wlsetvar join:: FA78: 53 30 34 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:10.87 wlsetvar join:: FA88: 00 00 00 00 FF 00 00 00-FF FF FF FF FF FF FF FF
00:00:10.87 wlsetvar join:: FA98: FF FF FF FF FF FF FF FF-F8 B7 97 87 2C DE 00 00
00:00:10.88 wlsetvar join:: FAA8: 00 00 00 00 00 00 00 00-30 FD 65 00 00 00 00 00
00:00:10.89 wlan: ether4330: [escan result] status 0 flags 0x0 reason 0
00:00:10.89 wlan: cfgreadl 18004020: 40  0  0  0
00:00:10.90 wlan: cfgwritel 18004020: 40  0  0  0
00:00:13.59 wlan: cfgreadl 18004020: 40  0 80  0
00:00:13.59 wlan: cfgwritel 18004020: 40  0 80  0
00:00:13.60 wlan: ether4330: [assoc req ie] status 0 flags 0x0 reason 0
00:00:13.60 wlan: ether4330: [auth] status 0 flags 0x0 reason 0
00:00:13.61 wlan: ether4330: [assoc resp ie] status 0 flags 0x0 reason 0
00:00:13.62 wlan: ether4330: [assoc] status 0 flags 0x0 reason 0
00:00:13.62 wlan: ether4330: [link] status 0 flags 0x1 reason 0
00:00:13.63 wlan: ether4330: [eapol msg] status 0 flags 0x0 reason 0
00:00:13.67 wlan: cfgreadl 18004020: 40  0 80  0
00:00:13.67 wlan: cfgwritel 18004020: 40  0 80  0
00:00:13.68 wlan: ether4330: [join] status 0 flags 0x0 reason 0
00:00:13.69 wlan: ether4330: [set ssid] status 0 flags 0x0 reason 0
00:00:13.69 wpa: Associated with f8:b7:97:87:2c:de
00:00:14.52 wlan: cfgreadl 18004020: 40  0 80  0
00:00:14.52 wlan: cfgwritel 18004020: 40  0 80  0
00:00:14.52 wlan: ether4330: [eapol msg] status 0 flags 0x0 reason 0
00:00:14.53 wlsetvar wsec_key:: Dumping 0xA4 bytes starting at 0x65F258
00:00:14.54 wlsetvar wsec_key:: F258: 00 00 00 00 10 00 00 00-01 7B 26 EF 76 DB 10 C9
00:00:14.55 wlsetvar wsec_key:: F268: A0 DD 56 EB 07 A3 D0 76-00 00 00 00 00 00 00 00
00:00:14.55 wlsetvar wsec_key:: F278: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.56 wlsetvar wsec_key:: F288: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.57 wlsetvar wsec_key:: F298: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.58 wlsetvar wsec_key:: F2A8: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.58 wlsetvar wsec_key:: F2B8: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.59 wlsetvar wsec_key:: F2C8: 04 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.60 wlsetvar wsec_key:: F2D8: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.61 wlsetvar wsec_key:: F2E8: 00 00 00 00 00 00 00 00-00 00 00 00 F8 B7 97 87
00:00:14.61 wlsetvar wsec_key:: F2F8: 2C DE 00 00 00 00 00 00-30 F4 65 00 00 00 00 00
00:00:14.62 wlan: cfgreadl 18004020: 40  0 80  0
00:00:14.62 wlan: cfgwritel 18004020: 40  0 80  0
00:00:14.63 wlsetvar wsec_key:: Dumping 0xA4 bytes starting at 0x65F278
00:00:14.64 wlsetvar wsec_key:: F278: 01 00 00 00 10 00 00 00-C8 95 3E ED 97 A6 4B A6
00:00:14.64 wlsetvar wsec_key:: F288: 1A 95 D2 5E C1 1A 99 0E-00 00 00 00 00 00 00 00
00:00:14.65 wlsetvar wsec_key:: F298: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.66 wlsetvar wsec_key:: F2A8: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.67 wlsetvar wsec_key:: F2B8: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.67 wlsetvar wsec_key:: F2C8: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.68 wlsetvar wsec_key:: F2D8: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.69 wlsetvar wsec_key:: F2E8: 04 00 00 00 02 00 00 00-00 00 00 00 00 00 00 00
00:00:14.70 wlsetvar wsec_key:: F2F8: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.70 wlsetvar wsec_key:: F308: 97 79 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:14.71 wlsetvar wsec_key:: F318: 00 00 00 00 00 00 00 00-50 F4 65 00 00 00 00 00
00:00:14.72 wlan: cfgreadl 18004020: 40  0 80  0
00:00:14.72 wlan: cfgwritel 18004020: 40  0 80  0
00:00:14.73 wpa: WPA: Key negotiation completed with f8:b7:97:87:2c:de [PTK=CCMP GTK=CCMP]
00:00:14.74 wpa: CTRL-EVENT-CONNECTED - Connection to f8:b7:97:87:2c:de completed [id=0 id_str=]
00:00:14.74 wlsetvar mcast_list:: Dumping 0xA bytes starting at 0x64F740
00:00:14.75 wlsetvar mcast_list:: F740: 01 00 00 00 01 00 5E 00-00 01 55 55 75 55 55 57
00:00:14.76 wlan: cfgreadl 18004020: 40  0 80  0
00:00:14.76 wlan: cfgwritel 18004020: 40  0 80  0
00:00:14.77 wlsetvar allmulti:: Dumping 0x4 bytes starting at 0x64F738
00:00:14.77 wlsetvar allmulti:: F738: 00 00 00 00 00 00 00 00-01 00 00 00 01 00 5E 00
00:00:14.78 wlan: cfgreadl 18004020: 40  0 80  0
00:00:14.79 wlan: cfgwritel 18004020: 40  0 80  0
00:00:15.02 wlan: cfgreadl 18004020: 40  0 80  0                                 
00:00:15.02 wlan: cfgwritel 18004020: 40  0 80  0                                
00:00:15.03 wlan: cfgreadl 18004020: 40  0 80  0                                 
00:00:15.04 wlan: cfgwritel 18004020: 40  0 80  0                                
00:00:15.04 dhcp: IP address is 192.168.10.104
00:00:15.13 wlan: channel: 0
00:00:15.13 wlan: bssid: f8:b7:97:87:2c:de
00:00:15.13 wlan: essid: MSRS_TDF_A2_S04
00:00:15.14 wlan: crypt: wpa2
00:00:15.14 wlan: oq: 0
00:00:15.14 wlan: txwin: 75
00:00:15.14 wlan: txseq: 35
00:00:15.15 wlan: status: associated
00:00:15.15 kernel: Try "ping 192.168.10.104" from another computer!
00:00:15.16 wlan: cfgreadl 18004020: 40  0 80  0
00:00:15.16 wlan: cfgwritel 18004020: 40  0 80  0
00:00:15.19 wlan: cfgreadl 18004020: 40  0 80  0
00:00:15.19 wlan: cfgwritel 18004020: 40  0 80  0
00:00:16.18 wlan: cfgreadl 18004020: 40  0 80  0
00:00:16.18 wlan: cfgwritel 18004020: 40  0 80  0
Sep  4 14:23:12.16 ntpd: System time updated
Sep  4 14:23:14.22 wlan: cfgreadl 18004020: 40  0 80  0
Sep  4 14:23:14.23 wlan: cfgwritel 18004020: 40  0 80  0
Sep  4 14:23:17.18 wlan: cfgreadl 18004020: 40  0 80  0
Sep  4 14:23:17.18 wlan: cfgwritel 18004020: 40  0 80  0
Sep  4 14:23:18.18 wlan: cfgreadl 18004020: 40  0 80  0
Sep  4 14:23:18.19 wlan: cfgwritel 18004020: 40  0 80  0
Sep  4 14:23:19.16 ntpd: System time updated
Sep  4 14:23:24.18 wlan: cfgreadl 18004020: 40  0 80  0
Sep  4 14:23:24.19 wlan: cfgwritel 18004020: 40  0 80  0
Sep  4 14:23:25.18 wlan: cfgreadl 18004020: 40  0 80  0
Sep  4 14:23:25.18 wlan: cfgwritel 18004020: 40  0 80  0
Sep  4 14:23:26.16 ntpd: System time updated
                                         
$ 
```
