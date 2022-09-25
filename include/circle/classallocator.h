//
// classallocator.h
//
// Class-specific allocator support
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2017-2022  R. Stange <rsta2@o2online.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef _circle_classallocator_h
#define _circle_classallocator_h

#include <circle/spinlock.h>
#include <circle/types.h>
#include <assert.h>

// 以下のマクロはクラスにクラス固有のアロケータを定休する場合に使用する

// クラス定義の最後に指定する
#define DECLARE_CLASS_ALLOCATOR                 \
    public:                                     \
        void *operator new (size_t nSize);      \
        void operator delete (void *pBlock, size_t nSize);      \
        static void InitAllocator (unsigned nReservedObjects);  \
        static void InitProtectedAllocator (unsigned nReservedObjects,  \
                            unsigned nTargetLevel);             \
    private:                                    \
        static CClassAllocator *s_pAllocator;

// クラス実装ファイルの最後に指定する
#define IMPLEMENT_CLASS_ALLOCATOR(class)        \
    CClassAllocator *class::s_pAllocator = 0;   \
    void *class::operator new (size_t nSize)    \
    {                                \
        assert (nSize == sizeof (class));       \
        assert (s_pAllocator != 0);             \
        return s_pAllocator->Allocate ();       \
    }                                \
    void class::operator delete (void *pBlock, size_t nSize)    \
    {                                \
        assert (nSize == sizeof (class));       \
        assert (s_pAllocator != 0);             \
        s_pAllocator->Free (pBlock);            \
    }                                \
    void class::InitAllocator (unsigned nReservedObjects)       \
    {                                \
        assert (s_pAllocator == 0);             \
        s_pAllocator = new CClassAllocator (sizeof (class),     \
                            nReservedObjects,   \
                            #class);            \
        assert (s_pAllocator != 0);             \
    }                                \
    void class::InitProtectedAllocator (unsigned nReservedObjects,  \
                        unsigned nTargetLevel)  \
    {                                \
        if (s_pAllocator == 0)                  \
        {                            \
            s_pAllocator = new CClassAllocator (    \
                        sizeof (class),         \
                        nReservedObjects,       \
                        nTargetLevel,           \
                        #class);                \
            assert (s_pAllocator != 0);         \
        }                            \
        else                         \
            s_pAllocator->Extend (nReservedObjects, \
                          nTargetLevel);        \
    }

// クラスをインスタンス化する前のどこかでこれを呼び出す
#define INIT_CLASS_ALLOCATOR(class, objects) \
    class::InitAllocator (objects)
// スピンロックにより保護されているアロケータを初期化する
#define INIT_PROTECTED_CLASS_ALLOCATOR(class, objects, level) \
    class::InitProtectedAllocator (objects, level)

/**
 * @class CClassAllocator
 * @brief クラス固有アロケータを表すクラス
 */
class CClassAllocator
{
public:
    CClassAllocator (size_t nObjectSize,
             unsigned       nReservedObjects,
             const char    *pClassName);

    CClassAllocator (size_t nObjectSize,
             unsigned       nReservedObjects,
             unsigned       nTargetLevel,
             const char    *pClassName);

    ~CClassAllocator (void);

    void *Allocate (void);

    void Free (void *pBlock);

    void Extend (unsigned nReservedObjects, unsigned nTargetLevel);

private:
    void Init (size_t nObjectSize, unsigned nReservedObjects);

private:
    size_t      m_nObjectSize;          ///< オブジェクトサイズ
    unsigned    m_nReservedObjects;     ///< 予約オブジェクト数
    const char *m_pClassName;           ///< クラス名

    unsigned char *m_pMemory;           ///< メモリへのポインタ
    struct TBlock *m_pFreeList;         ///< 空きリスト

    boolean   m_bProtected;             ///< 保護されているか
    unsigned  m_nTargetLevel;           ///< 対象レベル
    CSpinLock m_SpinLock;               ///< スピンロック
};

#endif
