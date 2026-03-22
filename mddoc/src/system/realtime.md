# REALTIME

CircleはリアルタイムOSではありません。そのため、様々な同時に行われる操作が
タイミング動作に関して干渉する可能性があります。

そうではありますが、割り込み（IRQ）レイテンシに関する特定の要件を持つアプリ
ケーションの実装にCircleを使用することができます。DMX512を使用した照明機器の
制御ソリューションの実装にCircleが使用されていることが知られています。この
アプリケーションでは数マイクロ秒の割り込みレイテンシが必要ですがCircleはこの
条件を満たしてます。

Circleを使ってリアルタイムアプリケーションを実装したい場合は以下の点に注意する
必要があります。

* LSまたはFSのUSBデバイス（USBキーボードやマウスなど）は使用しないこと。それらをサポート
する方法により、そのようなデバイスを使用すると割り込みレイテンシが非常に高くなるためです。
そのようなデバイスがたまたま装着されても無視するようにするために`include/circle/sysconfig.h`
で`#define REALTIME`を有効にすべきです。Raspberry Pi 1-3のアプリケーションでLS/FS USBデバイス
を使用する必要がある場合は、`REALTIME`と共に`#define USE_USB_SOF_INTR`も有効にする必要が
あります。

* スクリーンやシリアルデバイスへの書き込みも割り込みレイテンシを著しく増加させる可能性が
あります。`REALTIME`が定義されている場合この影響は比較的小さいのですが、IRQ_LEVELからの
書き込みは無視されます。`smaple/08-usbkeyboard`と`27-usbgamepad`が`REALTIME`オプションを
指定すると動作しないのはこのためです。

* 小さなIRQレイテンシが必要な場合は、`include/circle/sysconfig.h`で`USE_SDHOST`を無効に
する必要があります。Raspberry Pi 3とZero Wでは、WLANアクセスはSDカードアクセスと並行に
行うことはできないためです。

* Raspberry PiのGPIOブロックは、最大約60MHz（32ビットワード）のデータ出力、最大約15MHzの
データ入力が可能です。正確な値はRaspberry Piのモデルやシステムクロックによって異なります。

* Raspberry Piのベアメタル環境におけるARM CPUのシステムクロックは、通常、公称最大システム
クロックより低くなります。Raspberry Pi 1とZeroでは700MHz、Raspberry Pi 2と3では600MHzです。
Raspberry PiのFSが必要な場合は`CCPUThrottle`クラスを使ってシステムクロックを上げることが
できます。これは`sample/26-cpustress`で実演されています。
