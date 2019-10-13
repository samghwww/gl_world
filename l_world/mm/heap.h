#ifndef HEAP_H_
#define HEAP_H_


#include "../../inc/err.h"


#ifdef __cplusplus
extern "C" {
#endif
/// @NOTE: YOU'RE WRITING ARTICLE, BUT NOT JUST CODE.
///        THE FIRST RESPONSIBILITY MUST BE YOUR CODE IS READABLE.
///         1. READABLE(可读性)
///         2. VALIDITY(正确性)
///         3. STABLITY(稳定性)
///         4. FLEXIBILITY(灵活性)
///         5. PORTABILITY(移植性)

err_t Heap_Init(void * const _pheapBaseAddr, ux_t _heapSz);
void *Heap_Malloc(void *_pheap, ux_t _allocMemSz);
void *Heap_Realloc(void *_pheap, void *_pmemAlloced, ux_t _reallocMemSz);
void Heap_Free(void *_pmemFree);



#ifdef __cplusplus
}
#endif
#endif //HEAP_H_
