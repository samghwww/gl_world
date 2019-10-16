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
    if (_pmm->pbase <= _pmemAddr <= ((char*)_pmm->pbase + _pmm->sz)) {
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

// Memory pool initializatio function.
// _pmm: The pointer of the memory pool or memory base address.
// _mmSz: The size of memory pool.
void* mm_init(void const * const _pmm, ux_t _mmSz)
{

}

// Allocate a new memory block for user.
// _sz: The size of memory user want.
void* mm_malloc(mm_t *_pmm, ux_t _sz)
{
    if (NULL == _pmm || 0x00 == _sz) {
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
MALLOC_SUCCEED:
    // If free memory block will be used completely.
    // Just remove this current free node.
    // Otherwise change it point to the new free node,
    // and set the new free node's free space size.
    if (BLK_USZ(_sz) >= getBlkSz(tmp)) {
        // If system got here, that means that this current tmp node will used
        // completely. So just delete/remove this "tmp" node here right now.

        // If the "tmp" node is the first free node
        // REMOVE THE HEADER OF FREE LIST HEAD HERE.

        // If it's not the first free list node
        // done such as the following/below code.
    } else {

    }
    return BLK2MEM(tmp);
MALLOC_FAILD:
    return NULL; //
}

//
void* mm_realloc(mm_t* _pmm, void *const _p, ux_t _sz)
{

}

// Free the memory block allocated but want to free and do not use again.
// The memory address user want to free.
void mm_free(mm_t *_pmm, void const* const _pmblk)
{

}
