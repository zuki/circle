# デバッグについて

シングルコアのCircleアプリケーションはGNUデバッガ（GDB）と次のGDBスタブのいずれかを
使用してソースレベルのデバッグが可能です。

* Alpha GDBサーバ（Farjumpによる、Circleのための特別バージョン)

  	https:github.com/farjump/Alpha_Raspberry_Pi_Circle
* rpi_stub（turboscrew@GitHubによる、(Raspberry Pi 2, 3 用のスタンドアロンGDBスタブ)

  	https:github.com/turboscrew/rpi_stub

この文書はrpi_stubの使い方を説明したものです。Alpha GDBサーバーの使い方は上記URLで
確認できます。

### RPI-STUB

Raspberry Pi 2と3におけるシングルコアのCircleアプリケーションはGNUデバッガ（GDB）と
rpi_stubを使ってソースレベルのデバッグが可能です。これを行うには、以下が必要です。

* Raspberry Pi 2/3のUARTに接続されたUSB-シリアル変換器 (3.3V を使用)
* ARMをターゲットとしてビルドされたGNUデバッガ
* [rpi_stub](https:github.com/turboscrew/rpi_stub)

  `Debug/`サブディレクトリにすでに準備されたkernel7.imgがあります。Raspberry Pi 3の場合は最新バージョンが必要です。

kernel7.imgはCircleの起動に必要なファームウェアファイルとともにマイクロSDカードに
インストールする必要があります（これについては`boot/README`ファイルを参照してください）。
（まだない場合は）マイクロSDカードに`cmdline.txt`ファイルを作成し、次のオプションを
書き込みます。

> rpi_stub_baud=115200 rpi_stub_mmu rpi_stub_interrupt=fiq rpi_stub_enable_neon

これはシリアルのボーレートを設定し、rpi_stubのMMUとキャッシュとFIQ割り込みモードを
有効にします。CircleはほとんどFIQを使用しないので、この目的でCircleでこのモードを
使用することが推奨されます。さらにrpi_stubはNEONを有効にし、NEONレジスタのXML記述の
サポートをします。

rpi_stubでデバッグするCircleアプリケーションをビルドする前に次の定義を
`include/circle/sysconfig.h`で有効にする必要があります。

> #define USE_RPI_STUB_AT 0x1F000000

この定義により、Circleは自分でMMUを有効にすることができなくなり（すでに有効になっています）、
Circle は独自の例外ハンドラ（rpi_stub が行います）をインストールしなくなり、rpi_stubが使用
するのでUARTにアクセスしなくなります。この場合、ログメッセージは画面に出力されます（例外は後述
します）。U`SE_RPI_STUB_AT`を定義してビルドしたアプリケーションは、通常、rpi_stubがロードされて
いない状態では実行されません。

rpi_stubはGDBクライアントにログメッセージを送信することができます。これを使うには`cmdline.txt` に"logdev=ttyS1"を設定する必要があります。

GDBを使用するには以下のようにします。

* USB-シリアル変換器をホストコンピュータに接続します。
* 参っ黒SDカードをRaspberry Pi 2/3に挿入して、電源を入れます。
* GDBを起動し、以下のコマンドを実行します。

| コマンド | 説明 |
|:---------|:-----|
| file kernel.elf | デバッグする実行ファイル(カレントディレクトリにあります) |
| set serial baud 115200 | シリアルインタフェースのボーレートを設定します |
| target remote /dev/ttyUSB0 | シリアルインターフェイス (自分の環境に合わせる) |
| load | 実行ファイルを転送する (数秒かかります) |
| break CKernel::Run | CKernel::Run()の入り口にブレークポイントを設定します |
| cont | プログラムを続行します |

ブレークポイントに到達するとプログラムはGDBに戻ります。その後、さらにプログラムを続行し
Ctrl-Cで中断したり、"step"コマンドや"next"コマンドでシングルステップ実行したり、さらに
ブレークポイントを設定したりすることができます。

すべてのGDBコマンドはここで説明されています。

> https://sourceware.org/gdb/current/onlinedocs/gdb/

turboscrew@GitHubにはrpi_stubを提供していただきありがとうございます。
