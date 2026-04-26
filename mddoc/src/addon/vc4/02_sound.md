# soundサンプル

このサンプルプログラムはVCHIQオーディオサービスを使用して短いサウンドサンプルを再生します。
音声出力に対応したHDMIモニタ、または3.5mmヘッドフォンジャック（Raspberry Pi Zeroを除く）
で再生音を聴くことができます。再生が終了すると、2秒後に再び再生が開始されます。

提供しているsound.h.gzにある（圧縮済みの）サウンドサンプルはファイルサイズを小さくするために
サンプリングレート44100 Hz、8ビットモノラルで録音されています。自分で16ビットステレオ音源を
用意することも可能です（たとえば、Audacityからヘッダーなしの16ビット符号付き生データとして
エクスポートし、小さなプログラムを使ってASCIIに変換する）。その場合、sound.hファイルは次の
ようにする必要があります。

```c
#define SOUND_CHANNELS  2
#define SOUND_BITS		16

signed short Sound[] =
{
1,0,-2,0,2,0,-2,0,2,1,-1,-1,0,1,0,-2,0,3,0,-3,1,3,-2,-2,
...
};
```

ビルド後に kernel.img のサイズが約2MB以上になる場合はファイル `include/circle/sysconfig.h`
の KERNEL_MAX_SIZE を増やす必要がある場合がありますので注意してください。そうしないと動作しません。

VCHIQ オーディオサービスは Circle では常に 16 ビットステレオ音声を再生しますが、その他の
8/16 ビットのモノラル/ステレオ形式は、再生時に変換されます。

## ビルド

- addon/linux (liblinuxemu.a)が32ビットモードしか対応していないため、
  このサンプルも32ビットでビルドする必要がある

```bash
$ cp Config.mk.m3.32 Config.mk
$ ./makeall clean && ./makeall
$ cd addon/linux
$ make
$ cd ../vc4
$ ./makeall clean && ./makeall
$ cd sound/sample
$ make clean && make
$ cp kernel8-32.img /Volumes/NO\ NAME/
$ cp /Volumes/NO\ NAME/config32.txt /Volumes/NO\ NAME/config.txt
```

## 実行

- HDMI接続したモニターから再生された

```bash
logger: Circle 50 started on Raspberry Pi 3 Model B+ 1GB
logger: Revision code is a020d3, compiler has been GCC 14.3.1
00:00:00.66 timer: SpeedFactor is 1.51
00:00:00.66 printk: vchiq: vchiq_init_state: slot_zero = 0x00480000, is_master = 0
00:00:00.67 kernel: Compile time: Apr 25 2026 14:59:36
00:00:00.68 kernel: Playback started
00:00:05.46 kernel: Playback completed
00:00:07.46 kernel: Playback started
```
