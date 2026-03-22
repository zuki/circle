# QEMU

Circleアプリケーションは32ビットと64ビットモードのQEMUプロセッサエミュレータで
実行することができます。すべてのRaspberry PiハードウェアデバイスがQEMUでサポート
されているわけではないので制約はあるかもしれませんが、多くのCircleサンプルが動作
します。過去には公式のQEMUではRaspberry PiのUSBとネットワークがサポートされて
いませんでしたが、現在のv6.0.0ではUSBとTCP/IPネットワークがサポートされるように
なりました。QEMUでUSBを使用するCircleアプリケーションを動作させるためには、今の
ところパッチが必要であり、次のリポジトリで提供されています。

* https://github.com/smuehlst/qemu

Circle用のQEMUソースコードの取得とビルドは次の手順で行います。

```
git clone https://github.com/smuehlst/qemu.git
cd qemu
git submodule update --init --recursive

mkdir build
cd build
../configure --target-list=arm-softmmu,aarch64-softmmu
make
```

Circleのconfigureツールには--qemuというオプションがあり、QEMUで動作するように
Circleのプログラムをビルドするには適用する必要があります。

Raspberry Pi 3 (AArch64)用のCircleサンプル（sample/17-fractalなど）をビルドした場合、
次のようにQEMUで実行することができます。

```
./qemu-system-aarch64 -M raspi3b -kernel /path_to_circle/sample/17-fractal/kernel8.img
```

32ビットモードではカーネルイメージを指定するのに`-kernel`ではなく`-bios`オプションを
使用することに注意してください。これはRaspberry Pi Zeroのエミュレーションでのみ動作
確認済みです。

```
./qemu-system-arm -M raspi0 -bios kernel.img
```

次のオプションがQEMUの特定の機能を有効にします。

| オプション | 説明  |
|:-----------|:------|
| -global bcm2835-fb.xres=1024 -global bcm2835-fb.yres=768 | 画面解像度を設定する |
| -serial stdio | シリアル出力をstdoutに書き込む |
| -d guest_errors,unimp | 未実装の機能の呼び出しをstdoutに書き込む |
| -drive file=filename,if=sd,format=raw | ディスクイメージファイルをSDカードとしてアクセス可能にする |
| -device usb-kbd | USBキーボードのサポートを有効にする |
| -device usb-mouse | USBマウスのサポートを有効にする。ただし、マウスカーソルは動作しない |
| -semihosting | semihostingのサポートを有効にする |

最後のオプションは、CircleプログラムからQEMUを自動的に終了させることが
できるようにするためのものです。このためには`include/circle/sysconfig.h`で
システムオプションの`LEAVE_QEMU_ON_HALT`を定義する必要があります。さらに、
このオプションにより、Circleプログラムはホストシステムのファイルシステムに
あるファイルにアクセスできるようになります。これはセキュリティ問題を引き起こす
可能性があるため、注意が必要です。

### ネットワーク

QEMUでネットワークを設定するのはそれほど優しくはないかもしれません。次の構成が
テストされています。

`sample/21-webserver`において

```
qemu-system-aarch64 -M raspi3b -kernel kernel8.img \
    -netdev user,id=net0,hostfwd=tcp::8080-:80 -device usb-net,netdev=net0
```

ホストシステムのウェブブラウザで`http:localhost:8080`を開いてください! ホストの
ポート8080はゲストシステムのポート80に転送されます。

### デバッグ

QEMUで動作するCircleアプリケーションはARMをサポートしているGNUデバッガ（GDB）を
使用してデバッグすることができます。これを行うにはQEMUのコマンドラインに`-s`
（GDBサポートを有効にする）と`-S`（GDB接続を待つ）オプションを追加する必要が
あります。GDB内では次のコマンドを使用します。

```
file kernel8.elf
target remote :1234
cont
```

### 参照リンク

さらなる情報については次のサイトを参照してください。

* https://www.qemu.org/

### 実行結果

#### QEMUビルド

- 指定通りの手順でビルドしたところエラーが発生

    ```
    In file included from ../disas/arm-a64.cc:25:
    In file included from /Users/dspace/raspi_os/qemu/disas/libvixl/vixl/a64/disasm-a64.h:34:
    In file included from /Users/dspace/raspi_os/qemu/disas/libvixl/vixl/a64/assembler-a64.h:32:
    In file included from /Users/dspace/raspi_os/qemu/disas/libvixl/vixl/invalset.h:33:
    In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/c++/v1/vector:285:
    ../version:1:1: error: expected unqualified-id
    6.0.0
    ^
    17 errors generated.
    ninja: build stopped: subcommand failed.
    make: *** [run-ninja] Error 1
    ```

- [QEMU-issue129](https://gitlab.com/qemu-project/qemu/-/issues/129)の[パッチ](https://gitlab.com/qemu-project/qemu/-/commit/75eebe0b1f15464d19a39c4186bfabf328ab601a)を適用

    - 画面表示せず（02-screenpixel, 03-screentext, 17-fractalのいずれも）、真っ黒なGUI画面。
    - 21-webserverは動作
- QEMU masterをビルド（[Fix USB problems with Circle ](https://github.com/smuehlst/qemu/commit/62b39b245b1909c370a365aa2e93fd44830240d2)を適用）
    - 結果は変わらず（画面表示せず、ネットワークは動作）

#### Linuxでの実行

- aptでインストールしたQEMU
  - 画面表示は動作
  - USBデバイスを使用するアプリケーションは動作せず

      ```
      dwhci: Unknown vendor 0x4F54294A
      ```

- [Circle用パッチ](https://gitlab.com/qemu-project/qemu/-/commit/75eebe0b1f15464d19a39c4186bfabf328ab601a)を適用
  - 画面表示OK
  - USBデバイスの使用もOK

##### 画面例

![qemu-03-screentext](doc/qemu/03-screentext.png)

![qemu-08-usbkeyboard](doc/qemu/08-usbkeyboard.png)

![qemu-21-webserver-screen](doc/qemu/21-webserver-screen.png)

![qemu-21-webserver-log](doc/qemu/21-webserver-log.png)
