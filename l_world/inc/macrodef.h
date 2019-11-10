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


#define MAX(a, b)           ( ((a) > (b)) ? (a) : (b) )
#define MIN(a, b)           ( ((a) < (b)) ? (a) : (b) )

// Macro calculate/get the size/lenght of array.
// the parameter/argument must be array name but not pointer.
#define ARRAY_SIZE(arr)      ( sizeof(arr)/sizeof(arr[0]) )

// Bit mask
#define BIT(n)              ( 1U<<(n) )



#ifdef __cplusplus
}
#endif
#endif //MACRODEF_H_
