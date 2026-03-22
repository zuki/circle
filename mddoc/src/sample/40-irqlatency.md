# サンプル 40: IRQ lantency

このサンプルはプログラムとユーザにより異なるアクションが実行された場合に
測定される最大のIRQレイテンシを表示します。測定にはシステムタイマーを使用し、
デフォルトでは1秒間に25000回のIRQを発生させます。IRQごとに、IRQがトリガーされた
瞬間からIRQハンドラが実行を開始するまでの遅延が計算されます。そして、この遅延の
最小値、最大値、平均値が決定されます。これは、CLatencyTesterクラスで実装されて
います。サンプルプログラムでは変更されていない画面でしか動作しません。

プログラムをビルドする前に以下のオプションを設定することができます。


* `include/circle/sysconfig.h`にあるシステムオプション`REALTIME`

  `CScreenDevice::Write()`と`CSerialDevice::Write()`におけるスピンロック
  処理を変更する。これによりIRQレイテンシが劇的に減少するはずです。
  USE_USB_SOF_INTRが有効になっていないLSとFSのUSBデバイスの検知を無効に
  します。検知はIRQレイテンシを大幅に増大させるためです。

* `include/circle/sysconfig.h`にあるシステムオプション`USE_USB_SOF_INTR`

  Raspberry Pi 1-3とZeroではUSB PnPを動作させるためにいかなる場合でも有効に
  する必要があり、プログラムで有効にされます。このオプションを指定しないと
  REALTIMEが有効な場合、LSとFSのUSBデバイスを使うことができません。Raspberry
  Pi 4には影響ありません。

* サンプルプログラムの`kernel.h`ファイルにあるオプション`USE_BUFFERED_SCREEN`

  このオプションを指定するとメッセージは画面に直接表示されず、リングバッファに
  書き込まれ、後でTASK_LEVELで`CWriteBufferDevice::Update()`が呼ばれた時に表示
  されます。これにより、REALTIMEが定義されていてもIRQ_LEVELからのメッセージを
  表示することができます。それ以外の場合、これらのメッセージは静かに無視されます。

サンプルの実行中に表示されるロガーメッセージを見てください。"Timer elapsed"
メッセージがIRQ_LEVELで1秒ごとに生成され、REALTIMEの指定なし、またはREALTIMEと
USE_BUFFERED_SCREENの両者を指定した場合のみ表示されます。

システムの動作に影響を与えるためにUSBデバイスをいつでも脱着することができます。
