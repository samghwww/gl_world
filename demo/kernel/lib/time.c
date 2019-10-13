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

#include <string.h>

#include "./kernel/inc/debug.h"
#include "../exception/exception.h"

#include "time.h"

static SDateTime_t gDateTime;


/// @Brief
///  Set time with the specified time data.
/// @Param
///  _pTm: The pointer point to time data.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t SetTime( const STime_t *const _pTm )
{
    memcpy( &gDateTime.time, _pTm, sizeof( *_pTm ) );
    return ERR_SUCCESS;
}


/// @Brief
///  Get time.
/// @Param
///  None
/// @Return
///  The pointer of time data buffer.
STime_t *GetTime( void )
{
    return &gDateTime.time;
}


/// @Brief
///  Set date with the specified date data.
/// @Param
///  _pDt: The pointer point to date data.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t SetDate( const SDate_t *const _pDt )
{
    memcpy( &gDateTime.date, _pDt, sizeof( *_pDt ) );
    return ERR_SUCCESS;
}


/// @Brief
///  Get date.
/// @Param
///  None
/// @Return
///  The pointer of date data buffer.
SDate_t *GetDate( void )
{
    return &gDateTime.date;
}


/// @Brief
///  Set date and time with the specified data and time data.
/// @Param
///  _pDtTm: The pointer point to date and time data.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t SetDateTime( const SDateTime_t *const _pDtTm )
{
    memcpy( &gDateTime, _pDtTm, sizeof( *_pDtTm ) );
    return ERR_SUCCESS;
}


/// @Brief
///  Get date and time.
/// @Param
///  None
/// @Return
///  The pointer of date and time data buffer.
SDateTime_t *GetDateTime( void )
{
    return &gDateTime;
}


/// @Brief
///  Get The type of year.
/// @Param
///  The value of year.
/// @Return
///  The type of year.
///  @Ref EYearType_t
EYearType_t GetYearType( unsigned long const _year )
{
    return ( ( 0 == ( _year & 3 )  && _year % 100 ) || ( 0 == _year % 400 ) ) ?
        YEAR_TYPE_LEAP : YEAR_TYPE_COMM;
}


/// @Brief
///  Get The day number of month.
/// @Param
///  The value of month.
/// @Return
///  The day number of month.
unsigned char GetDayNumOfMonth( SDateTime_t const *const _pDt )
{
    unsigned char ret;

    if ( _pDt->date.month <= 7 )
    {
        ret = ( _pDt->date.month & 1 ) ? DAY_OF_BIG_MONTH : DAY_OF_LIT_MONTH;
    }
    else
    {
        ret = ( _pDt->date.month & 1 ) ? DAY_OF_LIT_MONTH : DAY_OF_BIG_MONTH;
    }

    return ( 2 != _pDt->date.month ) ? ret :
        ( YEAR_TYPE_COMM == GetYearType( _pDt->date.year ) ) ?
        DAY_OF_COMM_MONTH2 : DAY_OF_LEAP_MONTH2;
}


/// @Brief
///  Callback function to update date and time.
/// @Param
///  _n: The gone past second number.
///  @NOTE: the parameter/argumet _n must less a month second amount.
///         it mean that must less than 28 day's second number.
/// @Return
///  Exception code, contain Error code and warn code.
///  @Ref eExcpt_t
eExcpt_t RunDateTimeCb( unsigned long _n )
{
    // Function inner scope variable.
    //unsigned long tmp;
    // Smaller inner scope variable.
    //unsigned long tp;
#define tmp _n
    // Proccess second and set second value now.
    tmp = gDateTime.time.second + _n;
    gDateTime.time.second = tmp % SECOND_OF_MINUTE;

    // Proccess minute and set minute value now.
    tmp = ( tmp / SECOND_OF_MINUTE ) + gDateTime.time.minute;
    gDateTime.time.minute = tmp % SECOND_OF_MINUTE;

    // Proccess hour and set hour value now.
    tmp = ( tmp / MINUTE_OF_HOUR ) + gDateTime.time.hour;
    gDateTime.time.hour   = tmp % HOUR_OF_DAY;

    // Calculate the rest second parameter/argument value in day.
    tmp = ( tmp / HOUR_OF_DAY ) + gDateTime.date.day;

    gDateTime.date.day = tmp;
    tmp = GetDayNumOfMonth( &gDateTime );

    if ( gDateTime.date.day > tmp )
    {
        gDateTime.date.day -= tmp;
        ++gDateTime.date.month;
        if ( gDateTime.date.month > MONTH_OF_YEAR )
        {
            gDateTime.date.month = gDateTime.date.month - MONTH_OF_YEAR;
            ++gDateTime.date.year;
        }
        else
        {}
    }
    else
    {}

#undef tmp
#if 0
    // If the second parameter value is too large,
    // and it greater than the second number of a year,
    // it need to be proccessed here.
    // Way: add and set the now year value.
    if ( tmp >= DAY_OF_LEAP_YEAR )
    {
        tp = tmp;
        gDateTime.date.year += tp / DAY_OF_LEAP_YEAR;
        // Every four year will meet a leap year,
        // Becuase we calculate the day number of a year use
        // a leap year day number, So that past four year, the day
        // sum number we calculate will more than the infact day number
        // three day. But we need to get these day number and can't ignore
        // it. The following code means that add these more day number to
        // tmp day number variable.
        tmp = ( tp % DAY_OF_LEAP_YEAR ) + ( ( tp / DAY_OF_LEAP_YEAR ) / 4 * 3 );

        for ( tp = tp % DAY_OF_LEAP_YEAR; tp; tp-- )
        {
            if ( YEAR_TYPE_LEAP == GetYearType( gDateTime.date.year ) )
            {
                --tmp;
            }
            else
            {
                // go on
            }
        }
    }
    else
    {
        // TO DO
        // Must to proccess the day number here
    }

    if ( tmp >= DAY_OF_MAX_MONTH )
    {
        tp = tmp;
        gDateTime.date.month += tp / DAY_OF_MAX_MONTH;
        gDateTime.date.year  += gDateTime.date.month > MONTH_OF_YEAR ? 1 : 0;

        // Get the day number from the parameter/argument.
        tmp = ( tp % DAY_OF_MAX_MONTH ) + ( tp / DAY_OF_MAX_MONTH / 2 ) -
            YEAR_TYPE_LEAP == GetYearType( gDateTime.date.year ) ?
            2 : 1;
    }
    else
    {
        // TO DO
        // Must proccess the rest day number here.

    }

    tmp += gDateTime.date.day;

    if ( tmp >= GetDayNumOfMonth( gDateTime.date.month ) )
    {
        ++gDateTime.date.month;
        gDateTime.date.year  += gDateTime.date.month > MONTH_OF_YEAR ? 1 : 0;
    }

    gDateTime.date.day = tmp - GetDayNumOfMonth( gDateTime.date.month );

    //gDateTime.date.month = ?

    //gDateTime.date.year  = ?
#endif

    return ERR_SUCCESS;
} // End @Fun RunDateTimeCb
