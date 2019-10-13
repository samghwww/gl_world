#ifndef __LIST_DOUBLE_LINK_H__
#define __LIST_DOUBLE_LINK_H__

#include "../inc/typedef.h"
#include "../exception/exception.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct DLinkNode
{
    void             *pCntxt;
    struct DLinkNode *prev;
    struct DLinkNode *next;
} SDLinkNode_t;

#ifdef __cplusplus
}
#endif
#endif //__LIST_DOUBLE_LINK_H__
