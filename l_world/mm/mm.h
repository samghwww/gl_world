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

#include "../inc/typedef.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL 0
#endif

#define MM_POOL_DEF_BASE			
#define MM_POOL_DEF_SIZE			


typedef unsigned long long ux_t;
typedef struct mblk {
    ux_t         sz;  // Block size
    struct mblk* nxt; // If the block is free block this point to the next free block
} mblk_t;

typedef struct{
	void    *pbase;  // memory base address
	mblk_t  *frlst; // Free list
	ux_t     sz;    // memory pool size
} mm_t;


static inline void* malloc(ux_t _mallocSz)
{

}

static inline void *realloc(void const *const _pmalloced, ux_t reallocSz)
{

}

static inline void free(void const* const _pfree)
{
	
}

#ifdef __cplusplus
}
#endif
#endif //MM_H_
