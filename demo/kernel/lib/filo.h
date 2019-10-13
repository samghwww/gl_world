#ifndef __FILO_H__
#define __FILO_H__


#ifdef __cplusplus
extern "C" {
#endif

typedef struct Filo
{
    void *pCntxt;
    long sz;
    long opPos;
} SFlo_t;

#ifdef __cplusplus
}
#endif
#endif //__FILO_H__