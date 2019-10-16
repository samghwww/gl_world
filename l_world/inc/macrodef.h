/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Definition/declaratino of l system kernel handle task.

History:
    Date        Author          Notes
 2019/10/07     Sam He          The first version

*******************************************************************************/

#ifndef MACRODEF_H_
#define MACRODEF_H_



#ifdef __cplusplus
extern "C" {
#endif


#define ARRY_SIZE(arr)      ( sizeof(arr)/sizeof(arr[0]) )

#define BIT(n)              ( 1U<<(n) )



#ifdef __cplusplus
}
#endif
#endif //MACRODEF_H_
