# サンプル 04: Timer

最初にLEDを5回点滅してカーネルイメージが正しく読み込まれたことを
示します。ほとんどのものを初期化した後、タイマーの割り込みがオンになり、
遅延ループが較正されます。15秒後に発火するカーネルタイマーが起動します。
1秒ごとにログメッセージが生成されます。

カーネルタイマーが発火するとTimerHandler()が呼ばれ、無効なアドレスにジャンプ
することにより "Prefetch Abort"が生成されます（そのためにページテーブルに
実行不可ビットが設定されています）。これとは別に「未定義命令」例外を発生させる
こともできます。これは、例外ハンドラのデモのためです。

### 実行結果

#### 1. 無効なアドレスへのジャンプ

```
logger: Circle 44.5 started on Raspberry Pi 3 Model B+ (AArch64)
00:00:00.66 timer: SpeedFactor is 1.51
00:00:00.66 kernel: Compile time: Oct  8 2022 16:56:59
00:00:00.67 kernel: An exception will occur after 15 seconds from now
00:00:01.00 kernel: Time is 1
00:00:02.00 kernel: Time is 2
00:00:03.00 kernel: Time is 3
00:00:04.00 kernel: Time is 4
00:00:05.00 kernel: Time is 5
00:00:06.00 kernel: Time is 6
00:00:07.00 kernel: Time is 7
00:00:08.00 kernel: Time is 8
00:00:09.00 kernel: Time is 9
00:00:10.00 kernel: Time is 10
00:00:11.00 kernel: Time is 11
00:00:12.00 kernel: Time is 12
00:00:13.00 kernel: Time is 13
00:00:14.00 kernel: Time is 14
00:00:15.00 kernel: Time is 15
00:00:15.67 except: stack[1] is 0x877E0
00:00:15.67 except: stack[8] is 0x80A78
00:00:15.67 except: stack[9] is 0x8C088
00:00:15.67 except: stack[41] is 0x80000
00:00:15.67 except: stack[44] is 0x80A78
00:00:15.67 except: stack[47] is 0x80A80
00:00:15.67 except: Synchronous exception (PC 0x500000, EC 0x21, ISS 0xF, FAR 0)
```

#### 2. 未定義命令の実行

```
logger: Circle 44.5 started on Raspberry Pi 3 Model B+ (AArch64)
00:00:00.66 timer: SpeedFactor is 1.51
00:00:00.66 kernel: Compile time: Oct  8 2022 16:58:42
00:00:00.67 kernel: An exception will occur after 15 seconds from now
00:00:01.00 kernel: Time is 1
00:00:02.00 kernel: Time is 2
00:00:03.00 kernel: Time is 3
00:00:04.00 kernel: Time is 4
00:00:05.00 kernel: Time is 5
00:00:06.00 kernel: Time is 6
00:00:07.00 kernel: Time is 7
00:00:08.00 kernel: Time is 8
00:00:09.00 kernel: Time is 9
00:00:10.00 kernel: Time is 10
00:00:11.00 kernel: Time is 11
00:00:12.00 kernel: Time is 12
00:00:13.00 kernel: Time is 13
00:00:14.00 kernel: Time is 14
00:00:15.00 kernel: Time is 15
00:00:15.67 except: stack[1] is 0x877E0
00:00:15.67 except: stack[8] is 0x80A80
00:00:15.67 except: stack[9] is 0x8C088
00:00:15.67 except: stack[41] is 0x80000
00:00:15.67 except: stack[44] is 0x80A80
00:00:15.67 except: stack[47] is 0x80A80
00:00:15.67 except: Synchronous exception (PC 0x80840, EC 0x0, ISS 0x0, FAR 0x0)
```

### Timer発火までの処理手順

1. 割り込み機構を初期化: CInterruptSystem::Initialize()
    1- すべての割り込み要因による割り込みを無効
    1. システム全体の割り込みを有効に: asm volatile ("msr DAIFClr, #2")
2. タイマー初期化: CTimer::Initialize()
    1. 物理カウンタ割り込みのハンドラを登録: m_pInterruptSystem->ConnectIRQ (ARM_IRQLOCAL0_CNTPNS, InterruptHandler, this);
    2. 現在のカウンタを取得: asm volatile ("mrs %0, CNTPCT_EL0" : "=r" (nCNTPCT));
    3. 割り込み時間（1/HZ）を登録: asm volatile ("msr CNTP_CVAL_EL0, %0" :: "r" (nCNTPCT + m_nClockTicksPerHZTick));
    4. 割り込みを有効に: asm volatile ("msr CNTP_CTL_EL0, %0" :: "r" (1));
3. アプリケーション実行: CKernel::Run()
    1. タイマーを登録（15病後にTimerHandlerを実行）: m_Timer.StartKernelTimer (15 * HZ, TimerHandler);
4. 割り込み発生: exceptionstub64.S
   1. IRQStub: bl InterruptHandler
5. 1/HZ割り込みの実行:
    1. 割り込みハンドラ実行: InterruptHandler()
       - CInterruptSystem::InterruptHandler()
          - s_pThis->CallIRQHandler(ARM_IRQLOCAL0_CNTPNS)
              - TIRQHandler *pHandler = m_apIRQHandler[nIRQ];
              - (*pHandler) (m_pParam[nIRQ])
    2. 登録ハンドラ(2.a)を実行: CTimer::InterruptHandler(void *pParam)
       - CTimer::InterruptHandler()
          - 各種時刻更新: if (++m_nTicks % HZ == 0) { m_nUptime++; m_nTime++; }
          - タイマー発火: CTimer::PollKernelTimers(void)
             - ハンドラ（3.a)を実行: (*pHandler) ((TKernelTimerHandle) pTimer, pTimer->m_pParam, pTimer->m_pContext)
