# ether4330.cの関数

## (1) EMMC (host) と CYW4335 (client) 間でSDIOで通信する

```c
/*  コマンドcmdを実行して（sdiolockは呼び出し側でロックされている）応答を返す */
static ulong sdiocmd_locked(int cmd, ulong arg);

/*  コマンドcmdを実行して（sdiolockは関数内でロックする）応答を返す */
static ulong sdiocmd(int cmd, ulong arg);

/*  コマンドcmdを実行して（sdiolockは呼び出し先の関数でロックする）応答を返す */
static ulong trysdiocmd(int cmd, ulong arg);

/*  CMD52で機能fnのアドレスaddrのデータ(8bit)を読み取る */
static int sdiord(int fn, int addr);

/*  CMD52で8bitのデータdatを機能fnのアドレスaddrに書き出す */
/*   エラーが発生した場合は最大10回再試行する */
static void sdiowr(int fn, int addr, int data);

/*  CMD53で長さlenのバッファaのデータを機能fnのアドレスaddrに書き出す */
/*  incr=1の場合は1ブロック書き出す毎にaddrを増分する */
static void sdiorwext(int fn, int write, void *a, int len, int addr, int incr);

/*  (*addr | bits) をaddrに書き込む */
static void sdioset(int fn, int addr, int bits);

/*  sdioを初期化する */
static void sdioinit(void);

/*  SDIOカードをリセット : SDIO仕様 4.2.2参照 */
static void sdioreset(void);

/*  FNをアボートさせる : SDIO仕様 CCCR: 06h: ASxを参照 */
static void sdioabort(int fn);
```

## (2) EMMC (host) と CYW4335 の間でSDIOのFn1(チップのレジスタとメモリ)とFn2（Ethernetパケット）経由で通信する

```c
/*  CMD52: Fn1のアドレスオフセットoffにvalを書き込む */
static void cfgw(ulong off, int val);

/*  CMD52: Fn1のアドレスオフセットoffの値を読み込む */
static int cfgr(ulong off);

/*  CMD53: 機能Fnのアドレスオフセットoffから４バイト読み込む */
static ulong cfgreadl(int fn, ulong off);

/*  CMD53: 機能Fnのアドレスオフセットoffに４バイトのデータdataを書き込む */
static void cfgwritel(int fn, ulong off, u32int data);

/*  チップ内部のアドレス用の基底アドレスをsbaddr[2-0]にセット */
static void sbwindow(ulong addr);

/*  Fn1を使った読み書き: アドレスはバイトアクセス */
static void sbrw(int fn, int write, uchar *buf, int len, ulong off);

/*  Fn1を使った読み書き: アドレスはウィンドウアドレス相対の32ビットワードアクセス */
static void sbmem(int write, uchar *buf, int len, ulong off);

/* Fn2を使ったパケットの読み書き */
static void packetrw(int write, uchar *buf, int len);
```

## (3) Silicon Backplane経由のチップコアの構成と制御

```c
/*  バックプレーンを無効にする */
static void sbdisable(ulong regs, int pre, int ioctl);

/*  バックプレーンをリセットする */
static void sbreset(ulong regs, int pre, int ioctl);

/*  チップコアの情報を取得してctlオブジェクトにセット */
static void corescan(Ctlr *ctl, ulong r);

/*  チップメモリの情報を取得してctlオブジェクトの該当フィールドにセット */
static void ramscan(Ctlr *ctl);

/* バックプレーンを初期化する */
static void sbinit(Ctlr *ctl);

/* バックレプレーンをenableにする */
static void sbenable(Ctlr *ctl);
```

## (4) ファームウェアとconfigファイルのアップロード

```c
/* configファイルを'var=value\0'のリストの形に処理 */
static int condense(uchar *buf, int n);

/* /boot または /sys/lib/firmware にファームウェアファイルがないか探す */
static Chan* findfirmware(char *file);

/* ファイル（ファームウェア、config）をアップロードする */
static int upload(Ctlr *ctl, char *file, int isconfig);

/* 規制ファイル (.clm) をファームウェアにアップロード */
static void reguload(Ctlr *ctl, char *file);

/* ファームウェアファイルをアップロード */
static void fwload(Ctlr *ctl);
```

## (5) wlanによるデータパケットと制御パケットの送受信

```c
/* SDIOからの割り込みを処理 */
static void intwait(Ctlr *ctlr, int wait);

/* パケットを読み込む */
static Block* wlreadpkt(Ctlr *ctl);

/* パケットの送信を開始する */
static void txstart(Ether *edev);

/* カーネルプロセスに実行させるパケット受信処理関数 */
static void rproc(void *a);

/* linkdown する */
static void linkdown(Ctlr *ctl);
```

## (6) ホストとファームウェア間のコマンドインタフェース

```c
/* イベント番号を文字列に変更する */
static char* evstring(uint event);

/* 受信したイベント要求を処理 */
static void bcmevent(Ctlr *ctl, uchar *p, int len);

/* 接続状態を返す */
static int joindone(void *a);

/* 接続されるまで待機 */
static int waitjoin(Ctlr *ctl);

/* コマンドが終了した際に実行するハンドラ関数 */
static int cmddone(void *a);

/* ファームウェアにコマンドopを実行させる */
static void wlcmd(Ctlr *ctl, int write, int op, void *data, int dlen, void *res, int rlen);

/* valを引数にコマンドopの処理する */
static void wlcmdint(Ctlr *ctl, int op, int val);

/* 変数nameの値を取得する */
static void wlgetvar(Ctlr *ctl, char *name, void *val, int len);

/* 変数nameに長さlenの値をセットする */
static void wlsetvar(Ctlr *ctl, char *name, void *val, int len);

/* 変数nameに4バイトの値をセットする */
static void wlsetint(Ctlr *ctl, char *name, int val);

/* WEPキーワードctl->keys[i]を変数wsec_keyにセットする */
static void wlwepkey(Ctlr *ctl, int i);

/* WPAキーワードを変数wsec_keyにセットする */
static void wlwpakey(Ctlr *ctl, int id, uvlong iv, uchar *ea);

/* 名前がssidのAPに接続する */
static void wljoin(Ctlr *ctl, char *ssid, int chan, uchar *bssid);

/* APを作成する */
static void wlcreateAP(Ctlr *ctl, char *ssid, int channel, int hidden);

/* APスキャンを開始する */
static void wlscanstart(Ctlr *ctl);

/* APスキャン結果をセットする */
static void wlscanresult(Ether *edev, uchar *p, int len);

/* 国コードをセットする */
static void wlsetcountry(Ctlr *ctlr, const char *ccode);

/* カーネルプロセスに実行させるAPスキャン処理関数 */
static void lproc(void *a);

/* wlanを初期化する */
static void wlinit(Ether *edev, Ctlr *ctlr);
```

## (7) Plan 9 ドライバインタフェース

```c
/* ifstatをaにコピー */
static long etherbcmifstat(Ether* edev, void* a, long n, ulong offset);

/* Ethernet送信を開始 */
static void etherbcmtransmit(Ether *edev);

/* aをhexとしてパースしてbufにセット */
static int parsehex(char *buf, int buflen, char *a);

/* WEPキーワードをパースしてkey->datにセットする */
static int wepparsekey(WKey* key, char* a);

/* WPAキーワードをパースしてkey->datにセットする */
static int wpaparsekey(WKey *key, uvlong *ivp, char *a);

/* aをwapieとしてパースしてauth関連の変数にセットする */
static void setauth(Ctlr *ctlr, Cmdbuf *cb, char *a);

/* WEPの暗号化方式をチェックしてctlr->cryptotype, auth変数にセットする */
static int setcrypt(Ctlr *ctlr, Cmdbuf*cb, char *a);

/* ファームウェアコマンドを実行する */
static long etherbcmctl(Ether* edev, const void* buf, long n);

/* bssdiをbssidにコピーする */
static void etherbcmgetbssid (struct Ether *edev, void *bssid);

/* secsをscansecsにセットする */
static void etherbcmscan(void *a, uint secs);

/* 登録されているイベントハンドラをtype, paramsを引数に実行する */
static void callevhndlr(Ctlr* ctlr, ether_event_type_t type, const ether_event_params_t *params);

/* イベントハンドラhndlr、イベントコンテキストcontextを登録する */
static void etherbcmsetevhndlr(struct Ether *edev, ether_event_handler_t *hndlr, void *context);

/* イーサネットデバイスをattachする */
static void etherbcmattach(Ether* edev);

/* bufの内容に基づいてマルチキャストをセットする */
static void ethersetmulticast(Ether *edev, void *buf, long n);

/* wlanを停止する */
static void etherbcmshutdown(Ether*edev);

/* イーサネットドライバとして登録するpnpハンドラ関数 */
static int etherbcmpnp(Ether* edev);

/* WiFiデバイス(CYW43XX)を"4330"の名前で登録する*/
void ether4330link(void);
```