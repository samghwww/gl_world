/******************************************************************************
 * Copyright (C) 2019 Tapplock Corp.
 * All rights reserved.
 *
 * File: time.c
 *
 * Brief:
 *  Implement some function about real time counter.
 *
 * Author: Sam He(HeGuanglin)
 * Date:   2019/03/20
 *
 * Mender:
 * Date:
 * Revision:
 *
 ******************************************************************************/

#ifndef __TIME_H__
#define __TIME_H__

#include "../exception/exception.h"


#ifdef __cplusplus
extern "C" {
#endif

#define SECOND_OF_MINUTE        (60)
#define MINUTE_OF_HOUR          (60)
#define HOUR_OF_DAY             (24)

#define SECOND_OF_HOUR          (MINUTE_OF_HOUR * SECOND_OF_MINUTE)
#define SECOND_OF_DAY           (HOUR_OF_DAY    * SECOND_OF_HOUR)
#define MINUTE_OF_DAY           (HOUR_OF_DAY    * MINUTE_OF_HOUR)

#define DAY_OF_BIG_MONTH        (31)
#define DAY_OF_LIT_MONTH        (30)
#define DAY_OF_COMM_MONTH2      (28)
#define DAY_OF_LEAP_MONTH2      (29)
#define DAY_OF_MAX_MONTH        (DAY_OF_BIG_MONTH)
#define DAY_OF_MIN_MONTH        (DAY_OF_COMM_MONTH2)

#define DAY_OF_COMM_YEAR        (365)
#define DAY_OF_LEAP_YEAR        (366)
#define DAY_OF_MAX_YEAR         (DAY_OF_LEAP_YEAR)
#define DAY_OF_MIN_YEAR         (DAY_OF_COMM_YEAR)

#define MONTH_OF_YEAR           (12)

typedef struct
{
    unsigned long year;
    unsigned char month;
    unsigned char day;
} SDate_t;

typedef struct
{
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
} STime_t;

typedef struct
{
    SDate_t date;
    STime_t time;
} SDateTime_t;

typedef enum
{
    YEAR_TYPE_LEAP,
    YEAR_TYPE_COMM,
    YEAR_TYPE_INVALID,
} EYearType_t;


eExcpt_t SetTime( const STime_t *const _pTm );
STime_t *GetTime( void );

eExcpt_t SetDate( const SDate_t *const _pDt );
SDate_t *GetDate( void );

eExcpt_t SetDateTime( const SDateTime_t *const _pDtTm );
SDateTime_t *GetDateTime( void );

EYearType_t GetYearType( unsigned long const _year );
unsigned char GetDayNumOfMonth( SDateTime_t const *const _pDt );

eExcpt_t RunDateTimeCb( unsigned long _n );

#ifdef __cplusplus
}
#endif
#endif //__TIME_H__
