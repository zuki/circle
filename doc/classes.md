# クラス一覧

## ベースライブラリ

* C2DGraphics: VSyncとハードウェアアクセラレーションによるダブルバッファリングを備えたソフトウェアグラフィックライブラリ。
* CActLED: Act LEDの点灯・消灯をスイッチする。Raspberry Piのモデルをチェックして、正しいLEDピンを使用する。
* CBcm54213Device: Raspberry Pi 4 の BCM54213PE Gigabit Ethernet Transceiver 用のドライバです。
* CBcmFrameBuffer: フレームバッファの初期化、8bit深度のカラーパレット設定。
* CBcmMailBox: シンプルなGPUメールボックスインターフェイス、現在プロパティインターフェイスに使用されています。
* CBcmPCIeHostBridge: Raspberry Pi 4 の PCIe Host Bridge 用のドライバです。
* CBcmPropertyTags: GPU 側からいくつかの情報を取得したり、こちら側で何かを制御します。
* CBcmRandomNumberGenerator: 内蔵のハードウェア乱数発生器のドライバです。
* CBcmWatchdog: CBcmWatchdog: BCM2835 ウォッチドッグデバイスのドライバです。
* CCharGenerator: コンソールフォントのピクセル情報を提供します。コンソールフォントの画素情報を提供します。
* CClassAllocator: オブジェクトのクラス別割り当てのためのサポートクラス
* CCPUThrottle: ユーザー要件と SoC 温度に応じて CPU クロックレートを管理します。
* CDevice: すべてのデバイスのベースクラス
* CDeviceNameService。CDeviceNameService: デバイスを名前で登録し、後でこの名前で検索することができます。
* CDeviceTreeBlob。シンプルな Devicetree blob パーサー
* CDMA4Channel: プラットフォーム DMA4 "ラージアドレス" コントローラのサポート (ヘルパークラス).
* CDMAChannel: プラットフォーム DMA コントローラサポート (I/O read/write、メモリコピー).
* CDMASoundBuffers: CDMASoundBuffers: サウンドデバイスドライバが使用する DMA バッファを連結したもの。
* CExceptionHandler: 中止例外が発生した場合、スタックトレースとパニックメッセージを生成します。
* CGPIOClock: GPIO クロックを使用し、初期化、起動、停止を行う。
* CGPIOManager: CGPIOPin 用の割り込みマルチプレクサ (GPIO 割り込みが使用される場合のみ必要)。
* CGPIOPin：GPIOピンをカプセル化し、読み込み、書き込み、反転が可能。割り込みをサポートします。簡単な初期化。
* CGPIOPinFIQ。GPIO 高速割り込みピン (システムで 1 つだけ許可される)。
* CGenericLock。スケジューラの有無にかかわらず、リソースをロックします。
* CHeapAllocator。CHeapAllocator: フラットメモリ領域からブロックを割り当てる。
* CHDMISoundBaseDevice: HDMI サウンドデバイス。HDMI サウンドデバイスへの低レベルアクセス (VCHIQ なし)。
* CI2CMaster: I2C マスターデバイス用ドライバです。
* CI2CSlave: I2C スレーブデバイス用ドライバです。
* CI2SSoundBaseDevice: I2Sサウンドデバイスへの低レベルアクセス。
* CInterruptSystem: 割り込みに接続し、割り込みハンドラが呼び出される。
* CKernelOptions: カーネルオプション。cmdline.txt (doc/cmdline.txt を参照) からカーネルオプションを提供する。
* CLatencyTester: 実行中のコードのIRQレイテンシを測定します。
* CLogger: ターゲットデバイスへのロギングメッセージの書き込み
* CMACAddress: EthernetのMACアドレスをカプセル化する。
* CMachineInfo: 実行中のコンピュータに関するさまざまな情報を取得するためのヘルパークラスです。
* CMemorySystem: CMemorySystem： 要求があればMMUを有効にし、ページテーブルを切り替えます（ここでは使用しません）。
* CMPHIDevice：MPHIを使用するドライバーです。IRQを生成するためにMPHIデバイスを使用するドライバです。
* CMultiCoreSupport: Raspberry Pi 2 のマルチコアサポートを実装しています。
* CNetDevice: ネットデバイスの基本クラス（インターフェース）です。ネットデバイスの基本クラス（インターフェース）です。
* CNullDevice：ネットデバイスの基本クラス（インターフェース）です。送信データを無視し、読み出し時に0バイトを返すキャラクタデバイス。
* CNumberPool: CNumberPool: (デバイス)番号のアロケーションプール。
* CPageAllocator: (デバイス)番号の割り当てプール。CPageAllocator: フラットメモリ領域からアライメントされたページを割り当てる。
* CPageTable: MMU (AArch32) が使用するページテーブルをカプセル化する．
* CPtrArray: コンテナクラス．コンテナクラス．ポインタの動的配列．
* CPtrList: コンテナクラス．コンテナクラス．ポインタのリスト．
* CPtrListFIQ: コンテナクラス．ポインタのリスト，FIQ_LEVEL から使用可能．
* CPWMOutput: Pulse Width Modulator 出力（2ch）．
* CPWMSoundDevice: PWM デバイスを使用して、さまざまな形式のサウンド サンプルを再生します。
* CPWMSoundBaseDevice：PWMデバイスを使用して、さまざまな形式のサウンドサンプルを再生します。CPWMSoundBaseDevice: PWM デバイスを使用して、3.5mm ヘッドフォンジャックにサウンドを生成するためのローレベルアクセス。
* CScreenDevice: 画面に文字を書き込むデバイスです。画面への文字書き込み、一部エスケープシーケンス（未実装のものもあります）
* CSerialDevice。PL011 UART 用ドライバ、割り込みまたはポーリングモード
* CSMIMaster: セカンドメモリインタフェースのドライバです。
* CSoundBaseDevice: サウンドデバイスの基本クラス。CSoundBaseDevice: サウンドデバイスのベースクラス、複数のサウンドフォーマットを変換する。
* CSpinLock: CSpinLock: 複数のコアからリソースへの同時アクセスを同期させるためのスピンロックをカプセル化する。
* CSPIMaster: CSPIMaster: (非 AUX) SPI マスター・デバイス用ドライバ。同期ポーリング動作。
* CSPIMasterAUX: 補助 SPI マスター(SPI1)用ドライバです。
* CSPIMasterDMA： SPI0マスタデバイス用ドライバ。非同期 DMA 動作。
* CString。Format() メソッドは printf() のように動作する(ただし、書式オプションは少ない)。
* CTime: 時刻を保持、作成、更新します。
* CTimer: システムクロックを管理し、カーネルタイマーと較正済み遅延ループをサポート。
* CTracer。CTracer: トレースイベントをデバッグ用にリングバッファに収集し、後でロガーにダンプします。
* CTranslationTable。MMU (AArch64) で使用する変換テーブルをカプセル化します。
* CUserTimer: 細かい設定が可能なユーザプログラマブルインタラプトタイマ (ARM_IRQ_TIMER1 に基づく).
* CVirtualGPIOPin: VideoCoreによって制御される「仮想」GPIOピンをカプセル化します（出力のみ）．
* CWriteBufferDevice: 書き込みデバイス．CWriteBufferDevice: (スクリーンなどの)デバイスにバッファリングされた書き込みを行うためのフィルタ．

## USB ライブラリ

* CDWHCICompletionQueue。(USE_USB_FIQ が有効な場合) 完了準備が整った USB リクエストをキューに入れる。
* CDWHCIDevice: Raspberry Pi 1-3 用 USB ホストコントローラインターフェース (HCI) ドライバ。
* CDWHCIFrameScheduler: シンプルなマイクロフレームスケジューラ用ベースクラス
* CDWHCIFrameSchedulerNonPeriodic: 非高速デバイスへの非インタラプトスプリットフレームの送信をスケジューリングします。
* CDWHCIFrameSchedulerNoSplit: 直接接続された非高速デバイスへのフレーム送信をスケジューリングします。
* CDWHCIFrameSchedulerPeriodic: 非高速デバイスへの割り込み分割フレームの送信を予約します。
* CDWHCIRegister: CDWHCIDevice のサポートクラスで、HCI のレジスタをカプセル化します。
* CDWHCIRootPort: CDWHCIDeviceのサポートクラスで、ルートポートを初期化します。
* CDWHCITransactionQueue。(USE_USB_SOF_INTR が有効な場合)来る USB トランザクションをキューに入れます。
* CDWHCITransferStageData: CDWHCITransferStageData。1つのHCIチャネルで転送ステージに必要なすべてのデータを保持します。
* CLAN7800Device: Raspberry Pi 3 B+のオンボードUSBギガビットイーサネットデバイス用ドライバです。
* CSMSC951xDevice: オンボード USB イーサネットデバイス用ドライバです。
* CUSBBluetoothDevice: USB Bluetooth BR/EDR ドングル用の Bluetooth HCI トランスポートドライバです。
* CUSBBulkOnlyMassStorageDevice: USBマスストレージデバイス(バルク)用ドライバです。USB 大容量記憶装置(バルクのみ)用ドライバ
* CUSBCDCEthernetDevice: QEMUに実装されたUSB CDCイーサネットデバイス用ドライバです。
* CUSBConfigurationParser: USBコンフィギュレーションディスクリプタのパースとバリデーションを行います。
* CUSBDevice: 一般的なUSBデバイスをカプセル化します。一般的な USB デバイスのカプセル化(デバイスの機能検出)を行います。
* CUSBDeviceFactory: CUSBDeviceFactoryは、USBデバイスの機能オブジェクトを作成します。CUSBDeviceFactory: USBでサポートされる様々な機能のオブジェクトを作成します。
* CUSBEndpoint: CUSBEndpoint: USBデバイスのエンドポイントをカプセル化します。
* CUSBFunction: USBデバイスのエンドポイントをカプセル化します。CUSBFunction: USBデバイスの機能（インターフェース記述子で表現）をカプセル化します。
* CUSBGamePadDevice：USBゲームパッドドライバの基本クラスです。USB ゲームパッドドライバの基本クラスです。
* CUSBGamePadPS3Device： USBゲームパッドドライバの基本クラスです。PS3 ゲームパッド用ドライバ
* CUSBGamePadPS4Device： PS4 ゲームパッド用ドライバです。PS4ゲームパッド用ドライバ
* CUSBGamePadStandardDevice：PS4ゲームパッド用ドライバ。USB HID クラスレポートインタフェースを持つ USB ゲームパッド用ドライバ (3-0-0)
* CUSBGamePadSwitchProDevice: Nintendo Switch Proゲームパッド用ドライバ
* CUSBGamePadXbox360Device: Xbox 360 有線ゲームパッド用ドライバ
* CUSBGamePadXboxOneDevice: Xbox Oneゲームパッド用ドライバ
* CUSBHCIDevice。Raspberry PiのモデルによってCDWHCIDeviceまたはCXHCIDeviceの別称があります。
* CUSBHCIRootPort: USB HCIルートポートを表す基底クラスです。
* CUSBHIDDevice: 一般的なUSB HIDデバイス。一般的なUSB HIDデバイス(例：キーボード、マウス、ゲームパッド)
* CUSBHostController。CDWHCIDevice のベースクラスで、ホストコントローラの基本機能をいくつか提供します。
* CUSBKeyboardDevice: USBキーボードデバイス。USB キーボード用ドライバ
* CUSBMIDIDevice: USB Audio Class MIDI 1.0 デバイス用ドライバです。
* CUSBMouseDevice: USB マウス用ドライバ USB マウス用ドライバ
* CUSBPrinterDevice：USBプリンタ用ドライバ。USB プリンタ用簡易通信ドライバ（バックチャネルは使用しません） * CUSBRequest： USB プリンタ用ドライバ。
* CUSBRequest: USB デバイス（URB）に対するリクエスト。
* CUSBSerialCDCDevice: USB CDC シリアルデバイス用ドライバ（例：micro:bit）。
* CUSBSerialCH341Device: CH341 ベースの USB シリアルデバイス用ドライバ
* CUSBSerialCP2102Device: CP2102 ベースの USB シリアルデバイス用ドライバ
* CUSBSerialDevice: USBシリアルデバイス用ドライバ USBシリアルデバイスドライバの基本クラスとインタフェース
* CUSBSerialFT231XDevice: FTDI社製USBシリアルデバイス用ドライバ。FTDI ベースの USB シリアルデバイス用ドライバ
* CUSBSerialPL2303Device: PL2303 ベースの USB シリアルデバイス用ドライバ PL2303 ベースの USB シリアルデバイス用ドライバ
* CUSBStandardHub: LAN9512/9514および外部ハブ（最大8ポート）用USBハブドライバ
* CUSBString: CUSBString: USBデバイスで利用可能な文字列記述子をカプセル化します。
* CUSBTouchScreenDevice：タッチスクリーンデバイス。USB HIDクラスタッチスクリーン用ドライバです。
* CXHCICommandManager: xHCIドライバの同期式xHCコマンド実行。
* CXHCIDevice: USBホストコントローラインタフェース(xHCI)ドライバ Raspberry Pi 4用USBホストコントローラインターフェース(xHCI)ドライバ。
* CXHCIEndpoint: xHCIドライバで使用するUSBデバイスのエンドポイントを1つカプセル化します。
* CXHCIEventManager: xHCIドライバのxHCイベント処理。
* CXHCIMMIOSpace: CXHCIMMIOSpace。CXHCIMMIOSpace: xHCIコントローラのメモリマップドI/Oレジスタへのアクセスを提供します。
* CXHCIRing: xHCIコントローラとの通信のための転送、コマンドまたはイベントリングをカプセル化します。
* CXHCIRootHub。xHCIコントローラの利用可能なUSBルートポートを初期化します。
* CXHCIRootPort: xHCIコントローラのUSBルートポートをカプセル化します。
* CXHCISharedMemAllocator: xHCIコントローラの共有メモリ割り当て。xHCIドライバの共有メモリ割り当て。
* CXHCISlotManager: USBデバイススロットの管理。xHCIコントローラのUSBデバイススロットを管理します。
* CXHCIUSBDevice: xHCIコントローラに接続された1つのUSBデバイスをカプセル化。

## Input library

* CConsole。スクリーン/USB キーボードまたは代替デバイス (例: CSerialDevice) を使用するコンソールデバイス。
* CKeyboardBehaviour。一般的なキーボード機能
* CKeyboardBuffer: USB キーボードで入力された文字のバッファ。USB キーボードで入力された文字をバッファリングする
* CKeyMap: CKeyMap: キーボード変換マップ (現時点では 6 つのデフォルトマップを選択可能)
* CLineDiscipline: ラインエディタ機能を実装しています。
* CMouseBehaviour。一般的なマウス機能、マウスカーソルを扱う
* CMouseDevice：マウスデバイス。汎用マウスインターフェースデバイス
* CRPiTouchScreen: Raspberry Pi 公式タッチスクリーン用ドライバ
* CTouchScreenDevice：タッチスクリーン用ドライバ。一般的なタッチスクリーンインターフェースデバイス

## FS library

* CPartition。CDevice から派生したもので、ストレージパーティションへのアクセスをその境界内に制限する。
* CPartitionManager: パーティションマネージャ。プライマリ（非EFI）パーティションごとにCPartitionオブジェクトを作成します。

## FAT FS ライブラリ

* CFAT: FAT storage partition の File Allocation Table 構造をカプセル化します。
* CFATInfo: CFATInfo: (BPB と FS Info から) FAT storage partition を記述する構成情報をカプセル化する。
* CFATDirectory: FAT ストレージパーティション上のディレクトリをカプセル化する。CFATDirectory: FAT パーティション上のディレクトリをカプセル化 (現在はルートディレクトリの 8.3-names のみ)。
* CFATFileSystem。CFATFileSystem: FAT16 および FAT32 ストレージパーティション用のファイルシステムドライバ。
* CFATCache: CFATCache: FAT ストレージパーティション用のセクタキャッシュ。

## Scheduler library

* CMutex: タスク間の相互排他（クリティカルセクション）を実現する方法を提供する。
* CTask: このクラスをオーバーロードし、Run()メソッドを定義して独自のタスクを実装し、そのタスクをnewして起動する。
* CScheduler: CScheduler: 一度に実行するタスクを制御する協調的な非実行型スケジューラ。
* CSemaphore: セマフォ同期クラスを実装する。
* CSynchronizationEvent: CSynchronizationEvent: タスクの実行をイベントに同期させるためのメソッドを提供する。

## Net library

* CARPHANDLER。IP アドレスをイーサネット MAC アドレスに解決し、ARP 要求に応答します。
* CChecksumCalculator。いくつかのTCP/IPパケットのチェックサムを計算します。
* CDHCPClient: DHCPクライアントタスク。ネットワークデバイスのIPアドレスリースを取得し、維持します。
* CDNSClient: CDNSClient: ホスト名をIPアドレスに解決します。
* CHTTPClient：HTTPウェブサーバーにドキュメントを要求します。CHTTPClient: HTTPウェブサーバーからドキュメントを要求します。
* CHTTPDaemon：HTTPサーバークラス。シンプルなHTTPサーバークラス
* CICMPHandler。ICMPエラーメッセージのハンドラおよびエコー（Ping）レスポンダ。
* CIPAddress：IPアドレスのカプセル化。IP アドレスのカプセル化。
* CLinkLayer: Ethernet MACレイヤーをカプセル化する。
* CMQTTClient: MQTT IoT プロトコルのクライアント。
* CMQTTReceivePacket。MQTT ヘルパークラス。
* CMQTTSendPacket。MQTT ヘルパークラス。
* CNetConfig: ネットワークコンフィギュレーションをカプセル化する。
* CNetConnection: トランスポート層の仮想接続。仮想トランスポート層接続（UDPまたはTCP（まだ利用できない））。
* CNetDeviceLayer: ネットワークデバイスのサポート層をカプセル化する。送信前／送信後の TX／RX フレームをキューに入れる。
* CNetQueue: ネットワークパケットキューをカプセル化する。
* CNetSocket：ネットワークソケットの基本クラス。ネットワークソケットの基本クラス。
* CNetSubSystem。メインのネットワーク・サブシステム・クラス。CKernelクラスでインスタンスを生成する。
* CNetTask：メインのネットワークタスク。バックグラウンドで動作するメインのネットワーキング・タスク。異なるネットワーク層を処理する。
* CNetworkLayer。IPネットワークレイヤーをカプセル化。パケットフラグメンテーションをサポートしない。
* CNTPClient: インターネットタイムサーバから現在時刻を取得するNTPクライアント。
* CNTPDaemon: CNTPClientを使用するバックグラウンドタスク。CNTPDaemon: CNTPClientを使用して、15分毎にシステム時刻を更新するバックグラウンドタスク。
* CPHYTask: 使用するネットデバイスのPHYを継続的に更新するバックグランドタスク。
* CRetransmissionQueue。TCP再送信キュー。
* CRetransmissionTimeoutCalculator。RFC 6298 に従った TCP 再送タイムアウトを計算する。
* CRouteCache。ICMPリダイレクト要求で受け取った特殊経路をキャッシュする。
* CSocket。ネットワーク・アプリケーション・インターフェース（ソケット）クラス。
* CSysLogDaemon。RFC5424 および RFC5426 (UDP トランスポートのみ) に従った Syslog 送信者タスク。
* CTCPConnection。TCP 接続をカプセル化する。CNetConnectionから派生。
* CTCPRejector： CTCPRejector。CTCPRejector: 開いているコネクションに対応していないTCPセグメントを拒否する。CNetConnection から派生したものです。
* CTFTPDaemon。TFTP サーバータスク。
* CTransportLayer。TCP/UDPトランスポートレイヤーをカプセル化する。
* CUDPConnection: (仮想)UDP接続をカプセル化する。CNetConnectionから派生した。
