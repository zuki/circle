# ADDON_04: wlan/hello_waln

このサンプルはRaspberry Pi 3, 4とZero Wに搭載されているオンボードWLANデバイスを使用して
WLANに接続し、NTPサーバからシステム時間を更新します。現在のろこと、デフォルトではWPA[2]
対応のWLANしか接続できません。WLANドライバはPlan 9オペレーティングシステムから移植しました。
さらに、移植した"WPA Supplicant"ツールも使用しています。

ビルドする前に以下のコマンドを実行してサブモジュール addon/wlan/hostap を取得する
必要があります。

	git submodule update --init addon/wlan/hostap

メインのCircleライブラリの他に addon/fatfs/ と addon/SDCard のライブラリも必要であり、
WLANライブラリとサンプルをビルドする前にこれらのライブラリを作成する必要があります。

	cd addon/wlan
	./makeall

Raspberry Piの様々なWLANコントローラに対応するため、以下のファームウェアファイルを提供
する必要があります。

    brcmfmac43430-sdio.txt
    brcmfmac43430-sdio.bin
    brcmfmac43436-sdio.bin
    brcmfmac43436-sdio.txt
    brcmfmac43436-sdio.clm_blob
    brcmfmac43455-sdio.bin
    brcmfmac43455-sdio.clm_blob
    brcmfmac43455-sdio.txt
    brcmfmac43456-sdio.bin
    brcmfmac43456-sdio.txt
    brcmfmac43456-sdio.clm_blob
    brcmfmac43455-sdio.raspberrypi,5-model-b.bin
    brcmfmac43455-sdio.raspberrypi,5-model-b.txt
    brcmfmac43455-sdio.raspberrypi,5-model-b.clm_blob

これらのファイルは以下を実行することによりダウンロードすることができます（ "wget" ツールを使用）。

	cd addon/wlan/firmware
	make

これらのファイルはブート用に使用されるSDカードの /firmware ディレクトリにコピーする
必要があります。これらのダウンロードしたファームウェアファイルはCircleでテスト済みです。

さらに、SDカードのルートディレクトリには "wpa_supplicant.conf" という構成ファイルも
必要です。このサンプルディレクトリにあるテンプレートファイルを編集して、自身のWi-Fi
ネットワークのSSIDとパスワードを設定してください。また、お住まいの国のISO/IECアルファ2
コードも設定する必要があります。
