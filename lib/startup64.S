/*
 * startup64.S
 *
 * Circle - A C++ bare metal environment for Raspberry Pi
 * Copyright (C) 2014-2019  R. Stange <rsta2@o2online.de>
 *
 * This file contains (sligthly modified) code taken from U-Boot:
 *    armv8_switch_to_el1_m macro
 *    defined in arch/arm/include/asm/macro.h
 *    Copyright (C) 2009 Jean-Christophe PLAGNIOL-VILLARD <plagnioj@jcrosoft.com>
 *    Licensed under GPL-2.0+
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <circle/sysconfig.h>
    /* EL2からEl1へ移行するためのマクロ */
    .macro armv8_switch_to_el1_m, xreg1, xreg2

    /* 汎用タイマーを初期化する */
    mrs    \xreg1, cnthctl_el2
    orr    \xreg1, \xreg1, #0x3    /* EL1がタイマーにアクセスできるようにする */
    msr    cnthctl_el2, \xreg1
    msr    cntvoff_el2, xzr

    /* MPID/MPIDRレジスタを初期化する */
    mrs    \xreg1, midr_el1
    mrs    \xreg2, mpidr_el1
    msr    vpidr_el2, \xreg1
    msr    vmpidr_el2, \xreg2

    /* コプロセッサトラップを無効にする */
    mov    \xreg1, #0x33ff
    msr    cptr_el2, \xreg1     /* EL2へのコプロセッサトラップを無効にする */
    msr    hstr_el2, xzr        /* EL2へのコプロセッサトラップを無効にする */
    mov    \xreg1, #3 << 20
    msr    cpacr_el1, \xreg1    /* EL1でのFP/SIMDを有効にする */

    /* HCR_EL2を初期化する */
    mov    \xreg1, #(1 << 31)   /* 64bit EL1 */
    msr    hcr_el2, \xreg1

    /* SCTLR_EL1の初期化
     *
     * RES1ビットである(29,28,23,22,20,11) を 1 にセットし、
     * RES0ビットである(31,30,27,21,17,13,10,6) と
     * UCI,EE,EOE,WXN,nTWE,nTWI,UCT,DZE,I,UMA,SED,ITD,
     * CP15BEN,SA0,SA,C,A,M を 0 にセットする
     */
    mov    \xreg1, #0x0800
    movk    \xreg1, #0x30d0, lsl #16
    msr    sctlr_el1, \xreg1

    /* EL2からEL1_SP1モードにリターンする */
    mov    \xreg1, #0x3c4
    msr    spsr_el2, \xreg1     /* EL1_SP0 | D | A | I | F */
    adr    \xreg1, 1f
    msr    elr_el2, \xreg1
    eret
1:

    .endm

    .sect    .init

    .globl    _start
_start:                         /* 通常、ブート後はarmstub8からEL2で入る */

    mrs    x0, CurrentEL        /* すでにEL1tモードであるかチェックする */
    cmp    x0, #4               /*   El1tなら1fへ飛ぶ */
    beq    1f

    ldr    x0, =MEM_EXCEPTION_STACK /* IRQ, FIQ と例外ハンドラはEL1hで実行する */
    msr    sp_el1, x0           /* スタックを初期化する */

    ldr    x0, =VectorTable     /* EL2のための例外ベクタテーブルを初期化する */
    msr    vbar_el2, x0
                                /* EL1に移行する */
    armv8_switch_to_el1_m x0, x1

    /* 以下EL1 */
1:    ldr    x0, =MEM_KERNEL_STACK    /* メインスレッドはEL1tで実行し、sp_el0を使用 */
    mov    sp, x0               /* そのスタックを初期化する */

    ldr    x0, =VectorTable     /* 例外ベクタテーブルを初期化する */
    msr    vbar_el1, x0
                                /* sysinitへ分岐 */
    b    sysinit

    /* マルチコアを使用する場合 */
#ifdef ARM_ALLOW_MULTI_CORE

    .globl    _start_secondary
_start_secondary:               /* 通常、ブート後はarmstub8からEL2で入る */

    mrs    x2, mpidr_el1        /* CPU IDを取得する */
    and    x2, x2, #CORES-1

    mrs    x0, CurrentEL        /* すでにEl1tモードであるかチェック */
    cmp    x0, #4               /*     El1tモードなら1fへ飛ぶ */
    beq    1f

    mov    x1, #EXCEPTION_STACK_SIZE    /* 例外スタックのオフセットを計算 */
    mul    x1, x1, x2
    ldr    x0, =MEM_EXCEPTION_STACK     /* IRQ, FIQ と例外ハンドラはEl1hで実行 */
    add    x0, x0, x1
    msr    sp_el1, x0           /* init their stack */
                                /* EL1に移行する */
    armv8_switch_to_el1_m x0, x1

    /* 以下EL1 */
1:    mov    x1, #KERNEL_STACK_SIZE     /* カーネルスタックのオフセットを計算 e */
    mul    x1, x1, x2
    ldr    x0, =MEM_KERNEL_STACK    /* メインスレッドはEl1tで実行し、sp_el0を使用 */
    add    x0, x0, x1
    mov    sp, x0               /* スタックを初期化する */

    ldr    x0, =VectorTable     /* 例外ベクタテーブルを初期化する */
    msr    vbar_el1, x0
                                /* sysinit_secondaryに分岐する */
    b    sysinit_secondary

#endif

/* End */
