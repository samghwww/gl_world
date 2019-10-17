/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Implementation of memory pool or memory heap.

History:
    Date        Author          Notes
 2019/10/06     Sam He          The first version

*******************************************************************************/

#include "mm.h"

#include "../lib/queue.h"
#include "../lib/list.h"

#include <string.h>

// Memory block neighbor,
// The left or right or both block connected/linked with the current block.
// The connection is base on physical memory address.
typedef struct {
    mblk_t *pprv; // Pointer of previous.
    mblk_t *pnxt; // Pointer of next.
} mblk_neighbor_t;

typedef enum {
    MBLK_NEIGHBOR_TYPE_PREV,
    MBLK_NEIGHBOR_TYPE_NEXT,
    MBLK_NEIGHBOR_TYPE_INVALID,
} mblk_neighbor_type_t;



// If allocte a new memory block,
// use this macro to calcaulate how much memory space memory block occupied.
#define BLK_MSZ(bsz) ( (bsz) + sizeof(void*) )

// memory block pointer convert to memory base address
#define BLK2MEM(pb) ( (void*) (((char*)pb) + sizeof(void*)) )

// Memory address convert to memory pointer
#define MEM2BLK(pm) ( (mblk_t*) (((char*)pm) - sizeof(void*)) )

#define IS_ALLOC_ALL_FREE_BLOCK(pfrblk, allocSz)    \
    (allocSz == (pfrblk)->sz ||                     \
     (allocSz+sizeof(*pfrblk)+sizeof(void*)) >= (pfrblk)->sz)


void * const MemoryPool[MM_POOL_SIZE_DEF/sizeof(void*)];
DList_t MemoryFreeBlockList;
mm_t MCB[MM_POOL_NUNBER_DEF];   // Memory control block arry.

static inline err_t mm_checkMemAddrValid(mm_t const * const _pmm,
  void const * const _pmemAddr)
{
    if (_pmm->pbase <= _pmemAddr <= (void*)((char*)_pmm->pbase + _pmm->sz)) {
      return ERR_SUCCESS;
    } else {
      return ERR_INVALID_ADDR;
    }
}

static inline ux_t mm_getBlkSz(mblk_t const * const _pblk)
{
    return _pblk->sz;
}

static inline ux_t mm_getMemSz(void const* const _pmem)
{
    return MEM2BLK(_pmem)->sz;
}

static inline err_t mm_freeBlkListAdd(mm_t * const _pmm,
    mblk_t const * const _pblk)
{
    return Queue_Delete((void*)_pmm->pfrlst, _pblk);
}

static inline mblk_t *mm_getBlkPrevNeighor(mblk_t const * const _pblk)
{
    // I don't know how to calculate it?
}

static inline mblk_t *mm_getBlkNextNeighor(mblk_t const * const _pblk)
{
    return (mblk_t*)((char*)(&_pblk->pnxt) + _pblk->sz);
}

static inline void *mm_getBlkPrevBoundary(mblk_t const * const _pblk)
{
    return (void*)(((char*)_pblk) + sizeof(void*));
}

static inline void *mm_getBlkNextBoundary(mblk_t const * const _pblk)
{
    return (void*)((char*)(&_pblk->pnxt) + _pblk->sz);
}

static inline bool mm_2blkIsNeighbor(mblk_t const * const _pblkPrv,
    mblk_t const * const _pblkNxt)
{
    return (mm_getBlkNextBoundary(_pblkPrv) == _pblkNxt);
}

static mblk_t *mm_findBlkPrevFreeNeighbor(mblk_t const * const _pblkBase,
    mblk_t const * const _pblkFind)
{
    mblk_t const *psrch = (mblk_t const *)_pblkBase;
    while (psrch) {
        if (mm_2blkIsNeighbor(psrch, _pblkFind)) {
            return psrch;
        } else {
            psrch = psrch->pnxt;
        }
    }
    return NULL;
}

static mblk_t *mm_findBlkNextFreeNeighbor(mblk_t const * const _pblkBase,
    mblk_t const * const _pblkFind)
{
    mblk_t const *psrch = (mblk_t const *)_pblkBase;
    while (psrch) {
        if (mm_2blkIsNeighbor(_pblkFind, psrch)) {
            return psrch;
        } else {
            psrch = psrch->pnxt;
        }
    }
    return NULL;
}

static void mm_findBlkFreeNeighbor(mm_t const * const _pmm,
    mblk_t const * const _pblkFind, mblk_neighbor_t * const _pneighbor)
{
    mblk_t const * psrch = _pmm->pfrlst;
    _pneighbor->pprv = NULL;
    _pneighbor->pnxt = NULL;
    while (psrch) {
        if (mm_2blkIsNeighbor(psrch, _pblkFind)) {
            _pneighbor->pprv = psrch;
            _pneighbor->pnxt = mm_findBlkNextFreeNeighbor(psrch->pnxt, _pblkFind);
            break;
        }
        else if (mm_2blkIsNeighbor(_pblkFind, psrch)) {
            _pneighbor->pnxt = psrch;
            _pneighbor->pprv = mm_findBlkPrevFreeNeighbor(psrch->pnxt, _pblkFind);
            break;
        } else {
            psrch = psrch->pnxt;
        }
    }
}

static err_t mm_addFreeBlk(void const* const _pfrlst,
    mblk_t * const _pblkFree)
{
    return SingleList_UnRingAdd(_pfrlst, _pblkFree);
}

static err_t mm_removeFreeBlk(void const * const _pfrlst,
    mblk_t const * const _pblkFree)
{
    return SingleList_UnRingDelete(_pfrlst, &_pblkFree->pprv);
}

static inline mblk_t * mm_mergeNeighborBlk(mblk_t * const _pblkPrv,
    mblk_t const * const _pblkNxt)
{
    _pblkPrv->sz += _pblkNxt->sz + sizeof(void*);
    return _pblkPrv;
}

// Memory pool initializatio function.
// _pmm: The pointer of the memory pool or memory base address.
// _mmSz: The size of memory pool.
err_t mm_init(void * const _pmm, ux_t _mmSz)
{
    MCB[0].pbase  = _pmm;
    MCB[0].pfrlst = &MemoryFreeBlockList;
    MCB[0].sz     = _mmSz;

    

    mblk_t *pfrblk = (mblk_t*)_pmm;
    memset(pfrblk, 0x00, sizeof(*pfrblk));
    pfrblk->sz = _mmSz - (sizeof(void*) * 2); // Subtract pprv and pnxt
    MCB[0].pfrlst->pdhead = pfrblk;
    MCB[0] .pfrlst->pdtail = pfrblk;
}

// Allocate a new memory block for user.
// _sz: The size of memory user want.
void* mm_malloc(mm_t *_pmm, ux_t _allocSz)
{
    if (NULL == _pmm || NULL == _pmm->pfrlst || 0x00 == _allocSz) {
        goto MALLOC_FAILD;
    }
    mblk_t *psrch = _pmm->pfrlst;
    while (psrch) {
        if (psrch->sz >= _allocSz) {
            goto MALLOC_SUCCEED;
        } else {
            psrch = psrch->pnxt;
        }
    }
MALLOC_FAILD:
    return NULL;
MALLOC_SUCCEED:
    // If free memory block will be used completely.
    // Just remove this current free node.
    // Otherwise change it point to the new free node,
    // and set the new free node's free space size.
    mm_removeFreeBlk(_pmm->pfrlst, psrch);
    if (IS_ALLOC_ALL_FREE_BLOCK(psrch, _allocSz)) {
        // mm_removeFreeBlk(_pmm->pfrlst, psrch);
    } else {
        //mblk_t *pnewFreeBlk = (mblk_t*)(((char*)BLK2MEM(psrch)) + _allocSz);
        mm_addFreeBlk(_pmm->pfrlst, (mblk_t*)(((char*)BLK2MEM(psrch)) + _allocSz));
    }
    return BLK2MEM(psrch);
}

// Realloc memory for the memory block allocated.
// _pmm: memory pool base address or the pointer point to memory pool.
// _p: the address/pointer of memory block allocated.
// _sz: the size of memory user want to reallocate now.
void* mm_realloc(mm_t* _pmm, void * const _pem, ux_t _sz)
{

}

// Free the memory block allocated but want to free and do not use again.
// The memory address user want to free.
void mm_free(mm_t const * const _pmm, void const * const _pmem)
{
    mblk_t *pfrBlk = MEM2BLK(_pmem);
    mblk_neighbor_t frBlkNeighbor = {NULL, NULL};
    mm_findBlkFreeNeighbor(_pmm, pfrBlk, &frBlkNeighbor);
    if (frBlkNeighbor.pprv && frBlkNeighbor.pnxt) {
        mm_removeFreeBlk(_pmm->pfrlst, frBlkNeighbor.pprv);
        mm_removeFreeBlk(_pmm->pfrlst, frBlkNeighbor.pnxt);
        mm_mergeNeighborBlk(frBlkNeighbor.pprv, pfrBlk);
        mm_mergeNeighborBlk(frBlkNeighbor.pprv, frBlkNeighbor.pnxt);
        mm_addFreeBlk(_pmm->pfrlst, frBlkNeighbor.pprv);
    }
    else if (frBlkNeighbor.pprv) {
        mm_removeFreeBlk(_pmm->pfrlst, frBlkNeighbor.pprv);
        mm_mergeNeighborBlk(frBlkNeighbor.pprv, pfrBlk);
        mm_addFreeBlk(_pmm->pfrlst, frBlkNeighbor.pprv);
    }
    else if (frBlkNeighbor.pnxt) {
        mm_removeFreeBlk(_pmm->pfrlst, frBlkNeighbor.pnxt);
        mm_mergeNeighborBlk(pfrBlk, frBlkNeighbor.pnxt);
        mm_addFreeBlk(_pmm->pfrlst, pfrBlk);
    } else {
        mm_addFreeBlk(_pmm->pfrlst, pfrBlk);
    }
}
