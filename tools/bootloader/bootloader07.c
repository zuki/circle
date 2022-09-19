
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

// 2  outer corner  (5V)
// 4            (5V)
// 6            (GND)
// 8  TX out    (GP14)
// 10 RX in     (GP15)

// in vectors64.s
extern void PUT32 ( unsigned int, unsigned int );
extern void PUT16 ( unsigned int, unsigned int );
extern void PUT8 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern unsigned int GETPC ( void );
extern void BRANCHTO ( unsigned int );
extern void dummy ( unsigned int );

// in periph.c
extern void uart_init ( void );
extern unsigned int uart_lcr ( void );
extern void uart_flush ( void );
extern void uart_send ( unsigned int );
extern unsigned int uart_recv ( void );
extern unsigned int uart_check ( void );
extern void hexstring ( unsigned int );
extern void hexstrings ( unsigned int );
extern void timer_init ( void );
extern unsigned int timer_tick ( void );

// '0-9A-F'を数値に変換
int nibble_from_hex(int ascii)
{
    // 0: '1' = 0x31 &= 0x0F => 0x1
    if (ascii>='0' && ascii<='9')
        return ascii & 0x0F;
    // B: 66 - 7 = 59 = 0x3B &= 0x0f => 0xB
    if (ascii>='A' && ascii<='F')
        return (ascii - 7) & 0x0F;
    return -1;
}

// 数値を'0-9A-F'に変換して送信
void uart_send_hex_nibble(int rc)
{
    if(rc>9) rc+=0x37; else rc+=0x30;
    uart_send(rc);
}

// 数値をHEX文字列で送信
void uart_send_hex_byte(int val)
{
    uart_send_hex_nibble((val >> 4) & 0x0f);
    uart_send_hex_nibble(val & 0x0f);
}

// 文字列を送信
void uart_send_str(const char* psz)
{
    while (*psz)
    {
        uart_send(*psz++);
    }
}

void delay_micros(unsigned int period)
{
    unsigned int start = timer_tick();
    while (timer_tick() - start < period)
    {
    }
}

// 受信モード状態
typedef enum
{
    recv_state_ready,
    recv_state_hex,
    recv_state_binary,
    recv_state_eof,
    recv_state_error,
} recv_state;

// 現在のihexレコードの状態
typedef enum
{
    ihex_state_none,
    ihex_state_start,
    ihex_state_addr_hi,
    ihex_state_addr_lo,
    ihex_state_rectype,
    ihex_state_seg_hi,
    ihex_state_seg_lo,
    ihex_state_write_bytes,
    ihex_state_end,
} ihex_state;

//------------------------------------------------------------------------
/**
 * @brief bootroaderのmain関数
 */
int notmain ( void )
{
    /** 受信状態 */
    recv_state recvstate;
    /** データ送信状態 */
    ihex_state datastate;
    /** バイト数 */
    unsigned int byte_count;
    /** アドレス */
    unsigned int address;
    /** レコード種別 */
    unsigned int record_type;
    /** */
    unsigned int segment;
    /** CRC計算用 */
    unsigned int sum;
    /** 受信コマンド */
    unsigned int ra;
    /** 遅延時間 */
    unsigned int start_delay = 10000;       // 10ms default

    uart_init();
    timer_init();

restart:
    recvstate = recv_state_ready;
    datastate = ihex_state_none;
    byte_count=0;
    address=0;
    record_type=0;
    segment=0;
    sum=0;

    // ready信号を送信 ("-F" はfastモードをサポートしていることを示す）
    uart_send_str("IHEX-F\r\n");

    while(1)
    {
        ra=uart_recv();

        // リスタートコマンドはバイナリ状態以外のすべて状態で受けつける
        if (ra=='R' && recvstate != recv_state_binary)
        {
            goto restart;
        }

        switch (recvstate)
        {
            case recv_state_ready:
                if(ra==':')
                {
                    // hexレコードの開始
                    recvstate = recv_state_hex;
                    datastate = ihex_state_start;
                    sum = 0;
                    continue;
                }
                if (ra=='=')
                {
                    // バイナリレコードの開始
                    recvstate = recv_state_binary;
                    datastate = ihex_state_start;
                    sum = 0;
                    continue;
                }
                if(ra==0x0D || ra==0x0A)
                {
                    // 空白は無視
                    continue;
                }
                if(ra==0x80)
                {
                    // フラッシュバイト0x80は起動時にフラッシャーツールが
                    // 送信するものであり、ブートローダを以前にキャンセル
                    // された未知の状態からフラッシュさせるためのもの。
                    // ここでは安心して無視できる。
                    continue;
                }
                // フォーマットエラー
                uart_send_str("#ERR:format\r\n");
                recvstate = recv_state_error;
                continue;

            case recv_state_hex:
            {
                // hexバイトを読み込む
                int hi = nibble_from_hex(ra);
                int lo = nibble_from_hex(uart_recv());

                // 妥当性チェック
                if (hi < 0 || lo < 0)
                {
                    uart_send_str("#ERR:hex\r\n");
                    recvstate = recv_state_error;
                    continue;
                }

                ra = (hi << 4) | lo;
                break;
            }

            case recv_state_binary:
                // バイナリレコード場合は特別な処理は不要
                break;

            case recv_state_eof:
                if (ra=='s')
                {
                    // 開始遅延をセット（n hex digits, マイクロ秒単位）
                    start_delay = 0;
                    int nibble;
                    while ((nibble = nibble_from_hex(uart_recv())) >= 0)
                    {
                        start_delay = start_delay << 4 | nibble;
                    }
                    continue;
                }

                // レコードの受信が終了したら、goコマンドを待つ
                if (ra=='g' || ra=='G')
                {
                    // ackを送信
                    uart_send(0x0D);
                    uart_send('-');
                    uart_send('-');
                    uart_send(0x0D);
                    uart_send(0x0A);
                    uart_send(0x0A);

                    // 開始前の遅延
                    if (start_delay)
                        delay_micros(start_delay);

                    // ロードされたプログラムにジャンプ
                    #if AARCH == 32
                    BRANCHTO(0x8000);
                    #else
                    BRANCHTO(0x80000);
                    #endif
                }
                continue;

            case recv_state_error:
                // エラー状態の場合はすべてを無視する
                continue;
        }

        // チェックサムを更新する
        sum += ra;

        // データバイトを処理する
        switch (datastate)
        {
            case ihex_state_none:
                uart_send_str("#ERR:internal\r\n");
                recvstate = recv_state_error;
                break;

            case ihex_state_start:
                byte_count=ra;
                datastate = ihex_state_addr_hi;
                break;

            case ihex_state_addr_hi:
                address = ra << 8;
                datastate = ihex_state_addr_lo;
                break;

            case ihex_state_addr_lo:
                address |= ra;
                datastate = ihex_state_rectype;
                break;

            case ihex_state_rectype:
                record_type = ra;
                switch (record_type)
                {
                    case 0x00:
                        datastate = ihex_state_write_bytes;
                        break;

                    case 0x02:
                    case 0x04:
                        datastate = ihex_state_seg_hi;
                        break;

                    default:
                        datastate = ihex_state_end;
                        break;
                }
                break;

            case ihex_state_write_bytes:
                PUT8(segment | address, ra);
                address++;
                byte_count--;
                if (byte_count == 0)
                    datastate = ihex_state_end;
                break;

            case ihex_state_seg_hi:
                segment = ra << 8;
                byte_count--;
                datastate = ihex_state_seg_lo;
                break;

            case ihex_state_seg_lo:
                segment |= ra;
                byte_count--;
                if (record_type == 0x04)
                    segment<<=16;
                else
                    segment<<=4;
                datastate = ihex_state_end;
                break;

            case ihex_state_end:
                if (byte_count == 0)
                {
                    // チェックサムをチェック
                    if ((sum & 0xFF) != 0)
                    {
                        uart_send_str("#ERR:checksum\r\n");
                        recvstate = recv_state_error;
                    }
                    else if (record_type == 0x01)
                    {
                        // EOFレコードを受信。goコマンドを受付可能
                        uart_send_str("#EOF:ok\r\n");
                        recvstate = recv_state_eof;
                    }
                    else
                    {
                        // 次のレコード
                        recvstate = recv_state_ready;
                    }
                }
                else
                {
                    byte_count--;
                }
                break;
        }
    }
    return(0);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//
// Copyright (c) 2014 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------
