# サンプル 18: ntptime

このサンプルプログラムはEthernetコントローラ内蔵モデルでしか動作しません。

ビルドする前に`kernel.cpp`のネットワーク設定（デフォルトはDHCP）とタイム
ゾーンをローカルネットワークの設定に合うように更新する必要があります。
Raspberry PiのEthernetコネクタにローカルのEthernetを接続するのを忘れないで
ください。

最初にLEDが5回点滅しカーネルイメージが正しく読み込まれたことを示します。
初期化が終わるとサンプルプログラムはインターネット上のNTP（ネットワーク
タイムプロトコル）サーバから現在時刻を取得し、システム時刻を設定します。
時刻は15分ごとに更新されます。システム時刻が更新されるとログメッセージが
表示されます。

ネットワーク上の他のコンピュータからRaspberry Piにpingを打ってください。
応答があるはずです。

本サンプルはUSBプラグアンドプレイ（USB PnP）を有効にしています。ネット
ワークインターフェイスデバイスはオンボードで固定されており、取り外しが
できないため、この機能は必要ありません。しかし、USB PnPサポートを使用する
ことにより、通常のプログラム実行が実行中になるまで、USBデバイスの初期化を
延期することができます。これにより、アプリケーションの起動時間を短縮する
ことができます。config.txtに以下の設定をすることにより起動時間をさらに
短縮することが可能です。

```
boot_delay=0
disable_splash=1
force_eeprom_read=0
gpu_mem=16
```

最後のオプションはSDカードにカットダウンされたファームウェアを必要とし、
3Dグラフィックでは動作しなくなります（`boot/README`を参照）。
`include/circle/sysconfig.h`でシステムオプション `CALIBRATE_DELAY` を
無効にするとさらに起動時間を短縮することができます。

### 実行結果

```
logger: Circle 44.5 started on Raspberry Pi 3 Model B+ (AArch64)
00:00:00.66 timer: SpeedFactor is 1.51
00:00:01.29 kernel: Compile time: Sep 20 2022 08:38:20
00:00:01.52 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:01.52 usbdev0-1: Interface int9-0-1 found
00:00:01.53 usbdev0-1: Function is not supported
00:00:01.53 usbdev0-1: Interface int9-0-2 found
00:00:01.54 usbdev0-1: Using device/interface int9-0-2
00:00:02.26 usbdev0-1: Device ven424-2514, dev9-0-2 found
00:00:02.26 usbdev0-1: Interface int9-0-1 found
00:00:02.26 usbdev0-1: Function is not supported
00:00:02.27 usbdev0-1: Interface int9-0-2 found
00:00:02.27 usbdev0-1: Using device/interface int9-0-2
00:00:02.99 usbdev0-1: Device ven424-7800 found
00:00:03.00 usbdev0-1: Using device/interface ven424-7800
00:00:03.13 lan7800: MAC address is B8:27:EB:AB:E8:48
00:00:03.28 usbhub: Port 1: Device configured
00:00:03.29 usbhub: Port 1: Device configured
00:00:03.29 dwroot: Device configured
00:00:07.29 dhcp: No response from server. Retrying.
00:00:07.29 dhcp: Time value invalid (43200 75600 30318)
00:00:15.29 dhcp: No response from server. Retrying.
00:00:15.29 dhcp: IP address is 192.168.10.114
00:00:15.29 kernel: Try "ping 192.168.10.114" from another computer!
Sep 20 08:39:26.30 ntpd: System time updated
```

#### ping

```
$ ping 192.168.10.114
PING 192.168.10.114 (192.168.10.114): 56 data bytes
64 bytes from 192.168.10.114: icmp_seq=0 ttl=64 time=0.947 ms
64 bytes from 192.168.10.114: icmp_seq=1 ttl=64 time=0.695 ms
64 bytes from 192.168.10.114: icmp_seq=2 ttl=64 time=0.534 ms
64 bytes from 192.168.10.114: icmp_seq=3 ttl=64 time=0.503 ms
64 bytes from 192.168.10.114: icmp_seq=4 ttl=64 time=0.763 ms
64 bytes from 192.168.10.114: icmp_seq=5 ttl=64 time=0.610 ms
^C
--- 192.168.10.114 ping statistics ---
6 packets transmitted, 6 packets received, 0.0% packet loss
round-trip min/avg/max/stddev = 0.503/0.675/0.947/0.150 ms
```

#### QEMUでの実行

![18-ntptime](doc/qemu/18-ntptime.png)
