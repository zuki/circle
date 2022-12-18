# サンプル 08: ethernet

このサンプルプログラムはボード上にEthernetコントローラを搭載しているモデルの
Raspberry Piでのみ動作します。

最初にLEDが5回点滅しカーネルイメージが正しく読み込まれたことを示します。
USBホストコントローラを初期化した後、USBハブドライバが接続されているすべての
USBデバイスを検出し、その識別子（ベンダー、デバイス、インターフェース）を表示します。

ボードにあるイーサネットコントローラを初期化した後、2秒（イーサネットPHYが立ち
上がる時間）待って、受信フレームをダンプします。今のところ、ブロードキャスト
フレームにしかありません。別のコンピュータから`ping address`を使うとローカル
ネットワークにブロードキャストを強制的に送ることができます。ここでアドレスには
ローカルネットワークに存在しないIPアドレスを指定する必要があります（これにより
ARPリクエストが生成されるからです）。このテストではローカルのイーサネットを
Raspberry Piに接続する必要があるだけです。外部USBデバイスは必要ありません。

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
00:00:03.28 usbhub: Port 1: Device ven424-7800 configured
00:00:03.28 usbhub: Port 1: Device ven424-2514, dev9-0-2 configured
00:00:03.29 dwroot: Device configured
00:00:03.29 kernel: Compile time: Oct 24 2022 14:52:23
00:00:05.30 kernel: Dumping received broadcasts
                                                                                // ping 192.168.10.123
00:00:29.08 kernel: 60 bytes received from AC:87:A3:19:BC:D8 (protocol ARP)     //  AC:87:A3:19:BC:D8はmacのen0
00:00:29.08 kernel: Dumping 0x3C bytes starting at 0x29D440                     //  192.168.10.103
00:00:29.09 kernel: D440: FF FF FF FF FF FF AC 87-A3 19 BC D8 08 06 00 01       // FF:FF:FF:FF:FF:FF, AC:87:A3:19:BC:D8, 0x0806, 0x0001
00:00:29.09 kernel: D450: 08 00 06 04 00 01 AC 87-A3 19 BC D8 C0 A8 0A 67       // 0x080, 0x06, 0x04, 0x0001, AC:87:A3:19:BC:D8, C0.A8.0A.67
00:00:29.10 kernel: D460: 00 00 00 00 00 00 C0 A8-0A 7B 00 00 00 00 00 00       // 00:00:00:00:00:00, C0.A8.0A.7B (192.168.10.123)
00:00:29.11 kernel: D470: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:30.08 kernel: 60 bytes received from AC:87:A3:19:BC:D8 (protocol ARP)
00:00:30.08 kernel: Dumping 0x3C bytes starting at 0x29D440
00:00:30.09 kernel: D440: FF FF FF FF FF FF AC 87-A3 19 BC D8 08 06 00 01
00:00:30.10 kernel: D450: 08 00 06 04 00 01 AC 87-A3 19 BC D8 C0 A8 0A 67
00:00:30.10 kernel: D460: 00 00 00 00 00 00 C0 A8-0A 7B 00 00 00 00 00 00
00:00:30.11 kernel: D470: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:31.08 kernel: 60 bytes received from AC:87:A3:19:BC:D8 (protocol ARP)
00:00:31.08 kernel: Dumping 0x3C bytes starting at 0x29D440
00:00:31.09 kernel: D440: FF FF FF FF FF FF AC 87-A3 19 BC D8 08 06 00 01
00:00:31.10 kernel: D450: 08 00 06 04 00 01 AC 87-A3 19 BC D8 C0 A8 0A 67
00:00:31.10 kernel: D460: 00 00 00 00 00 00 C0 A8-0A 7B 00 00 00 00 00 00
00:00:31.11 kernel: D470: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:32.08 kernel: 60 bytes received from AC:87:A3:19:BC:D8 (protocol ARP)
00:00:32.09 kernel: Dumping 0x3C bytes starting at 0x29D440
00:00:32.09 kernel: D440: FF FF FF FF FF FF AC 87-A3 19 BC D8 08 06 00 01
00:00:32.10 kernel: D450: 08 00 06 04 00 01 AC 87-A3 19 BC D8 C0 A8 0A 67
00:00:32.10 kernel: D460: 00 00 00 00 00 00 C0 A8-0A 7B 00 00 00 00 00 00
00:00:32.11 kernel: D470: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
00:00:33.08 kernel: 60 bytes received from AC:87:A3:19:BC:D8 (protocol ARP)
00:00:33.09 kernel: Dumping 0x3C bytes starting at 0x29D440
00:00:33.09 kernel: D440: FF FF FF FF FF FF AC 87-A3 19 BC D8 08 06 00 01
00:00:33.10 kernel: D450: 08 00 06 04 00 01 AC 87-A3 19 BC D8 C0 A8 0A 67
00:00:33.10 kernel: D460: 00 00 00 00 00 00 C0 A8-0A 7B 00 00 00 00 00 00
00:00:33.11 kernel: D470: 00 00 00 00 00 00 00 00-00 00 00 00 00 00 00 00
```

#### ping

```
$ ping 192.168.10.123
PING 192.168.10.123 (192.168.10.123): 56 data bytes
Request timeout for icmp_seq 0
Request timeout for icmp_seq 1
Request timeout for icmp_seq 2
Request timeout for icmp_seq 3
ping: sendto: No route to host
Request timeout for icmp_seq 4
ping: sendto: Host is down
Request timeout for icmp_seq 5
^C
--- 192.168.10.123 ping statistics ---
7 packets transmitted, 0 packets received, 100.0% packet loss
```
