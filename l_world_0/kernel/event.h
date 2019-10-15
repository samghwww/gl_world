/*******************************************************************************
 Copyright (C) 2019 Sam He(HeGuanglin)

 History:
    Date        Author          Notes
 2019/10/07     Sam He          The first version

 Discription:
    Definition/declaratino of l system kernel handle event.
 
*******************************************************************************/

#ifndef EVENT_H_
#define EVENT_H_

typedef struct evt {
    struct evt *nxt;

} Event_t;

#endif //EVENT_H_
