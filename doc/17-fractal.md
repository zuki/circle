# サンプル 17: fractal

このサンプルはマンデルブロー集合のフラクタル画像を表示します。
シングルコアとマルチコアでビルドできます。ビルドする前に
`include/circle/screen.h`で定義されている`DEPTH`に16を設定して
利用可能な色数を増やしてください。また、SDカードにある
cmdline.txtファイルに`loglevel=1`を設定する必要があります。そうしないと
画像を上書きするようなロギングメッセージが生成されます。

このサンプルはマルチコアアーキテクチャの性能向上を実証するのに
適しているために選ばれました。シングルコアのCPUでは画像全体が利用
可能なただ一つのコアで計算されます。マルチコアCPU（Raspberry Pi 2/3のみ）
では、4つのコアの各々がフラクタル画像の1/4を計算するのでより高速に
処理されます。

Raspberry Pi 2/3でこのサンプルをマルチコアで実行したい場合は
`include/circle/sysconfig.h`で`ARM_ALLOW_MULTI_CORE`を定義する必要が
あります。

マンデルブロ集合の計算は他のパラメータ（MAX_ITERATIONなど）を選択したり、
NEON FPU命令を使ってアセンブリ言語で実装したりすることで、はるかに改善
できることに留意してください。これは、krom氏によって行われました。彼の
非常に印象的なサンプルは以下でご覧ください。

https://github.com/PeterLemon/RaspberryPi  (NEON/FractalとSMP/NEON/Fractal)

### 実行結果

![17-fracktal](doc/sample/17-fractal.png)
