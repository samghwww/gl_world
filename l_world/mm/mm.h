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

#define MM_POOL_SIZE_DEF(sz)            ( (sz)/sizeof(void*) )    //in byte. must be the value of four time

#define MM_POOL_NUNBER_DEFAULT          ( 1U )
#define MM_POOL_BASE_DEFAULT            ( &MCB[0] )
#define MM_POOL_SIZE_DEFAULT            MM_POOL_SIZE_DEF(1024*2)

#define MM_INIT_DEF(...)                mm_init(MM_POOL_BASE_DEFAULT, MM_POOL_SIZE_DEFAULT)

typedef struct mblk {
    union {
        void    *preserved;
        ux_t     sz;  // Block size
    };
    union {
        void        *pmem;
        struct mblk *pprv; // Point to the previous block.
    };
    struct mblk* pnxt; // If the block is free block this point to
                       // the next free block.
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


extern mm_t MCB[MM_POOL_NUNBER_DEFAULT];

err_t mm_init(void * const _pmm, ux_t _mmSz);
void* mm_malloc(mm_t * const _pmm, ux_t _sz);
void* mm_realloc(mm_t * const _pmm, void *const _p, ux_t _sz);
void mm_free(mm_t * const _pmm, void const* const _pmblk);



static inline void *malloc(ux_t _mallocSz)
{
    return mm_malloc(MM_POOL_BASE_DEFAULT, _mallocSz);
}

static inline void *realloc(void const *const _pmalloced, ux_t _reallocSz)
{
    return mm_realloc(MM_POOL_BASE_DEFAULT, _pmalloced, _reallocSz);
}

static inline void free(void const* const _pfree)
{
    mm_free(MM_POOL_BASE_DEFAULT, _pfree);
}

#ifdef __cplusplus
}
#endif
#endif //MM_H_
