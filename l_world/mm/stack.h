/*******************************************************************************
Copyright (C) Sam He(HeGuanglin) 2019

Brief/Descirption:

History:
// The newest/lasted version should be list above here.
  Date        Author    Note 
2019/10/09    Sam He    The first version
*******************************************************************************/
#pragma once
#ifndef STACK_H_
#define STACK_H_



#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL 0
#endif

typedef unsigned long long ux_t;
typedef struct mblk {
    ux_t         sz;  // Block size
    struct mblk* nxt; // If the block is free block this point to the next free block
} mblk_t;

typedef struct{
    void    *base;  // memory base address
    mblk_t  *frlst; // Free list
    ux_t     sz;    // memory pool size
} mm_t;

typedef struct {
    void *sp;
    void *top;
    ux_t  sz;
};



#ifdef __cplusplus
}
#endif
#endif //STACK_H_
