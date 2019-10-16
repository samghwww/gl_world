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
// use this macro to calcaulate how much memory space will be used.
#define BLK_USZ(sz) ( (sz)+sizeof(mblk_t) )

// memory block pointer convert to memory base address
#define BLK2MEM(pb) ( (void*)(&((pb)->nxt)) )

// Memory address convert to memory pointer
#define MEM2BLK(pm) ( (mblk_t*)(((char*)pm)-sizeof(void*)) )

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
    return Queue_Delete((void*)_pmm->frlst, _pblk);
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
    return (void*)(((char*)_pblk) + sizeof(vodi*));
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
    mblk_t const * psrchBlk = _pmm->frlst;
    _pneighbor->pprv = NULL;
    _pneighbor->pnxt = NULL;
    while (psrchBlk) {
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

// Memory pool initializatio function.
// _pmm: The pointer of the memory pool or memory base address.
// _mmSz: The size of memory pool.
err_t mm_init(void const * const _pmm, ux_t _mmSz)
{

}

// Allocate a new memory block for user.
// _sz: The size of memory user want.
void* mm_malloc(mm_t *_pmm, ux_t _sz)
{
    if (NULL == _pmm || NULL == _pmm->frlst || 0x00 == _sz) {
        goto MALLOC_FAILD;
    }
    mblk_t* tmp = _pmm->frlst;
    while (tmp) {
        if (tmp >= _sz) {
            goto MALLOC_SUCCEED;
        } else {
            tmp = tmp->nxt;
        }
    }
MALLOC_FAILD:
    return NULL;
MALLOC_SUCCEED:
    // If free memory block will be used completely.
    // Just remove this current free node.
    // Otherwise change it point to the new free node,
    // and set the new free node's free space size.
    if (BLK_USZ(_sz) >= mm_getBlkSz(tmp)) {
        // If system got here, that means that this current tmp node will used
        // completely. So just delete/remove this "tmp" node here right now.

        // If the "tmp" node is the first free node
        // REMOVE THE HEADER OF FREE LIST HEAD HERE.

        // If it's not the first free list node
        // done such as the following/below code.
    } else {

    }
    return BLK2MEM(tmp);
}

// Realloc memory for the memory block allocated.
// _pmm: memory pool base address or the pointer point to memory pool.
// _p: the address/pointer of memory block allocated.
// _sz: the size of memory user want to reallocate now.
void* mm_realloc(mm_t* _pmm, void *const _pem, ux_t _sz)
{

}

// Free the memory block allocated but want to free and do not use again.
// The memory address user want to free.
void mm_free(mm_t const * const _pmm, void const * const _pmem)
{
    mblk_t *pfrBlk = MEM2BLK(_pmem);
    mblk_neighbor_t frBlkNeighbor = {NULL, NULL};
    mm_findBlkFreeNeighbor(_pmm, pfrBlk, &frBlkNeighbor);

    if (frBlkNeighbor.pprv) {
        frBlkNeighbor.pprv->sz; += pfrBlk->sz - sizeof(void*);
        pfrBlk->pnxt = frBlkNeighbor.pprv->pnxt;
        frBlkNeighbor.pprv->pnxt = pfrBlk->pnxt;
    }
    if (frBlkNeighbor.pnxt) {
        pfrBlk->sz += frBlkNeighbor.pprv->sz - sizeof(void*);
    }

}
