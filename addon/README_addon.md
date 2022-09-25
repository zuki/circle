# ADDON_00: Addonについて

このディレクトリ（とそのサブディレクトリ）のライブラリとサンプルは
個別にビルドする必要があります。サンプルをビルドするには、まずライブラリを
先にビルドする必要があります。

選んだディレクトリに移動して以下を実行してください。

```
make clean
make
```

### ディレクトリ一覧

| ディレクトリ | 説明                                        |
|:-------------|:--------------------------------------------|
| dio | spi_dioボードにライブラリ（BitWizard.nl作） |
| display | ディスプレイ（LCDドットマトリクスなど）ドライバを提供するライブラリ |
| fatfs | FatFs - LFNをサポートした汎用FATファイルシステムモジュール（ChaN作） |
| gpio | 外部GPIO拡張ボード（RTK.GPIOなど）にアクセスするためのライブラリ |
| OneWire | 1-wireデバイス（Paul Stoffregen作）とDS18x20センサーのサポートライブラリ |
| Properties | ファイルに保存した構成属性にアクセスするためのライブラリ |
| qemu | CircleをQEMUで使用するためのサポートライブラリとデモ |
| linux | Linuxカーネルデバイスドライバエミュレーション（HDMIサウンドとアクセレイテッドグラフィクスで使用） |
| lvgl | LVGL組み込みGUIライブラリ（LVGL Kft作） |
| microbit | micro:bitコンピュータの機能にアクセスするためのライブラリ |
| pico | Raspberry Pi Picoの機能（RAMローダーなど）にアクセスするためのライブラリ |
| profile | パフォーマンス分析のためのソフトウェアプロファイリングライブラリ |
| rtc | リアルタイムクロック（RTC）のドライバを提供するライブラリ |
| SDCard | 内部EMMCコントローラを使ったSDカードアクセスドライバ（John Cronin作） |
| sensor | I2Cとセンサデバイスのためのドライバ |
| Spectrum | ZXスペクトラムスクリーンエミュレータクラス（Jose Luis Sanchez作） |
| tftpfileserver | カーネルイメージとファームウェアの更新をサポートするTFTPファイルサーバ |
| ugui | uGUIライブラリを使ったデジタルオシロスコープサンプル（Achim Doebler作） |
| vc4 | HDMIサウンドとアクセレイテッドグラフィクス（EGL, OpenGL ES, OpenVG, Dispmanx）のサポート |
| webconsole | webブラウザを使ったシステムログにリモートアクセスするためのライブラリ |
| wlan | WLANサポート（R. Miller作のPlan 9ドライバとJ. Malinen作のWPAサプリカントを使用）|
| WS28XX | WS28XX制御のLEDストライプ/ネオピクセルのドライバ（SPIとSMI接続） |
