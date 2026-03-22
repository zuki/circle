# サンプル 21: webserver

このサンプルプログラムはEthernetコントローラを搭載したRaspberry Piでしか動作しません。

ビルドする前に`kernel.cpp`のネットワーク設定（デフォルトではDHCPを使用）をローカルの
ネットワーク設定に合わせて更新する必要があります。このサンプルをビルドするには
converttoolをコンパイルするためにビルドシステムのプラットフォームをターゲットとする
GCCコンパイラが必要です。Raspberry PiのEthernetコネクタにローカルのEthernetを接続する
のを忘れないでください。

最初にカーネルイメージが正しく読み込まれたことを示すためにLEDが5回点滅します。初期化が済むと
サンプルプログラムは80番ポート(http)でTCPコネクションの着信を待機します。画面上に表示されている
URLを、ネットワーク上の他のコンピュータのウェブブラウザで開いてください。Raspberry PiのAct LEDを
切り替えるための簡単なフォームが表示されるはずです。

### 実行

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
00:00:05.57 netdev: Link is 1000BASE-T Full-duplex
00:00:09.57 dhcp: No response from server. Retrying.
00:00:11.58 dhcp: IP address is 192.168.10.114
00:00:11.59 kernel: Compile time: Sep 19 2022 16:42:15
00:00:11.59 kernel: Open "http://192.168.10.114/" in your web browser!
00:00:32.59 httpd: 192.168.10.103 "GET /" 200 912
00:00:32.67 httpd: 192.168.10.103 "GET /style.css" 200 372
00:00:32.69 httpd: 192.168.10.103 "GET /ledoff.png" 200 573
00:00:32.74 httpd: 192.168.10.103 "GET /favicon.ico" 200 1150
00:00:36.99 httpd: 192.168.10.103 "POST /index.html" 200 911
00:00:37.06 httpd: 192.168.10.103 "GET /ledon.png" 200 538
00:00:37.06 httpd: 192.168.10.103 "GET /style.css" 200 372
00:00:40.39 httpd: 192.168.10.103 "POST /index.html" 200 912
00:00:40.45 httpd: 192.168.10.103 "GET /style.css" 200 372
00:00:40.46 httpd: 192.168.10.103 "GET /ledoff.png" 200 573
00:00:44.54 httpd: 192.168.10.103 "POST /index.html" 200 911
00:00:44.61 httpd: 192.168.10.103 "GET /style.css" 200 372
00:00:44.61 httpd: 192.168.10.103 "GET /ledon.png" 200 538
```

##### 画面

下の画面で`On`, `Off`を指定して`OK`ボタンを押すとRaspi上のLEDがOn/Offする。

![21-webserver](doc/sample/21-webserver.png)
