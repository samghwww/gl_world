/*******************************************************************************
Copyright (C) 2019 Sam He(HeGuanglin)

Discription:
    Definition/declaratino of l system kernel handle event.
History:
    Date        Author          Notes
 2019/10/07     Sam He          The first version
 
*******************************************************************************/

#ifndef EVENT_H_
#define EVENT_H_


#ifdef __cplusplus
extern "C" {
#endif
typedef struct evt {
    struct evt *nxt;

} Event_t;


#ifdef __cplusplus
}
#endif
#endif //EVENT_H_
