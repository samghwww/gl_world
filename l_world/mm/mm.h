/*******************************************************************************
Copyright (C) Sam He(HeGuanglin) 2019

Brief/Descirption:
    Definition of memory pool implement.
History:
// The newest/lasted version should be list above here.
    Date        Author    Note
 2019/10/09     Sam He    The first version
*******************************************************************************/
#pragma once
#ifndef MM_H_
#define MM_H_

#include "../lib/list.h"
#include "../inc/typedef.h"
#include "../inc/err.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL 0
#endif

// Macro set memory pool size in byte.
// must be the value of four time
#define MM_POOL_SIZE_DEF(sz)            ( (sz)/sizeof(void*) )

// Deault number of memory pool.
#define MM_POOL_NUNBER_DEFAULT          ( 1U )
// Default size of memory pool.
#define MM_POOL_SIZE_DEFAULT            MM_POOL_SIZE_DEF(1024*2)
// Default length of memory pool in bytes
#define MM_POOL_LENGTH_DEFAULT          (MM_POOL_SIZE_DEFAULT * sizeof(void*))
// Default memory pool.
#define MM_POOL_DEFAULT                 ( &MemoryPool[0] )
// Default memory control block, used for control memory pool.
#define MM_MCB_DEFAULT                  ( &MemoryCtrlBlock[0] )

// Macro use to initialize memory pool.
#define MM_INIT_DEF(...)                mm_init(MM_POOL_DEFAULT, MM_POOL_LENGTH_DEFAULT)

// Memory block base data type.
typedef struct mblk {
    union {
        ux_t memSz;         // Record the allocted memory size here.
        struct mblk* pprv;  // Point to the previous block.
    };
    struct mblk* pnxt;  // If the block is free block this point to
                        // the next free block.
    ux_t         sz;    // Block size
} mblk_t;

// Memory free list data type.
typedef struct {
    mblk_t *phead;
    mblk_t *ptail;
} mfrlst_t;

// Memory pool control block.
typedef struct{
    void    *pbase;     // memory base address.
    mfrlst_t frlst;     // memory free block list.
    ux_t     sz;        // memory pool size.
} mm_t;

extern void const * MemoryPool[MM_POOL_SIZE_DEFAULT];
extern mm_t MemoryCtrlBlock[MM_POOL_NUNBER_DEFAULT];

err_t mm_init(void * const _pmm, ux_t _mmSz);
void* mm_malloc(mm_t * const _pmm, ux_t _allocSz);
void* mm_realloc(mm_t * const _pmm, void const * const _prealloc, ux_t _reallocSz);
void mm_free(mm_t * const _pmm, void const * const _pfree);



static inline void *malloc(ux_t _mallocSz)
{
    return mm_malloc(MM_MCB_DEFAULT, _mallocSz);
}

static inline void *realloc(void const *const _prealloc, ux_t _reallocSz)
{
    return mm_realloc(MM_MCB_DEFAULT, _prealloc, _reallocSz);
}

static inline void free(void const* const _pfree)
{
    mm_free(MM_MCB_DEFAULT, _pfree);
}

#ifdef __cplusplus
}
#endif
#endif //MM_H_
