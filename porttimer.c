/*
 * FreeModbus Libary: ATMega168 Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

/* ----------------------- AVR includes -------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- Defines ------------------------------------------*/
#define MB_TIMER_PRESCALER      ( 1024UL )
#define MB_TIMER_TICKS          ( F_CPU / MB_TIMER_PRESCALER )
#define MB_50US_TICKS           ( 20000UL )

/* ----------------------- Static variables ---------------------------------*/
static USHORT   usTimerOCRADelta;

/* ----------------------- Start implementation -----------------------------*/
BOOL xMBPortTimersInit( USHORT usTim1Timerout50us )
{
    /* Calculate overflow counter an OCR values for Timer1. */
    usTimerOCRADelta =
        ( MB_TIMER_TICKS * usTim1Timerout50us ) / ( MB_50US_TICKS );

    TCCRnA = 0x00;
    TCCRnB = 0x00;
    
    #if MB_TIMER == 1
    TCCR1C = 0x00;
    #endif
    vMBPortTimersDisable();

    return TRUE;
}


inline void vMBPortTimersEnable()
{
    TCNTn = 0;
    if( usTimerOCRADelta > 0 )
    {
        TIMSKn |= _BV( OCIEnA );
        OCRnA = usTimerOCRADelta;
    }
    TCCRnB |= PRESCALER;
}


inline void vMBPortTimersDisable()
{
    /* Disable the timer. */
    TCCRnB &= ~PRESCALER;
    /* Disable the output compare interrupts for channel A/B. */
    TIMSKn &= ~( _BV( OCIEnA ) );
    /* Clear output compare flags for channel A/B. */
    TIFRn |= _BV( OCFnA ) ;
}


ISR(SIG_OUTPUT_COMPAREnA)
{
    ( void )pxMBPortCBTimerExpired(  );
    
}

