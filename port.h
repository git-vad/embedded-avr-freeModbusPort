/*
 * FreeModbus Libary: AVR Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *   - Initial version + ATmega168 support
 * Modfications Copyright (C) 2006 Tran Minh Hoang:
 *   - ATmega8, ATmega16, ATmega32 support
 *   - RS485 support for DS75176
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

#ifndef _PORT_H
#define _PORT_H

/* ----------------------- Platform includes --------------------------------*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "mbconfig.h"

/* ----------------------- Defines ------------------------------------------*/
#define	INLINE                      inline
#define PR_BEGIN_EXTERN_C           extern "C" {
#define	PR_END_EXTERN_C             }

#define ENTER_CRITICAL_SECTION( )   cli()
#define EXIT_CRITICAL_SECTION( )    sei()

#define assert( x )

typedef char    BOOL;

typedef unsigned char UCHAR;
typedef char    CHAR;

typedef unsigned short USHORT;
typedef short   SHORT;

typedef unsigned long ULONG;
typedef long    LONG;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

/* ----------------------- AVR platform specifics ---------------------------*/

#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328P__)
#define UCSRB           UCSR0B
#define TXEN            TXEN0
#define RXEN            RXEN0
#define RXCIE           RXCIE0
#define TXCIE           TXCIE0
#define UDRE            UDRE0
#define UBRR            UBRR0
#define UCSRC           UCSR0C
#define UPM1            UPM01
#define UPM0            UPM00
#define UCSZ0           UCSZ00
#define UCSZ1           UCSZ01
#define UDR             UDR0
#define MB_SIG_USART_DATA USART_UDRE_vect
#define MB_SIG_USART_RECV USART_RX_vect 
#define MB_SIG_UART_TRANS USART_TX_vect


#elif defined (__AVR_ATmega8__)
#warning "Attention, correction of definitions required."

#elif defined (__AVR_ATmega16__)
#warning "Attention, correction of definitions required."

#elif defined (__AVR_ATmega32__)
#warning "Attention, correction of definitions required."

#elif defined (__AVR_ATmega128__)
#warning "Attention, correction of definitions required."

#endif

/* ----------------------- Timer specifics  ---------------------------------*/
/* Select Timer */
#if   MB_TIMER == 0
    #define TCNTn  TCNT0
    #define TCCRnA TCCR0A
    #define TCCRnB TCCR0B
    #define TIMSKn TIMSK0
    #define TIFRn  TIFR0
    #define OCIEnA OCIE0A
    #define OCRnA  OCR0A
    #define OCFnA  OCF0A
    #define PRESCALER (_BV(CS02) | _BV(CS00)) /*1024*/
    #define SIG_OUTPUT_COMPAREnA TIMER0_COMPA_vect

#elif MB_TIMER == 1
    #define TCNTn TCNT1
    #define TCCRnA TCCR1A
    #define TCCRnB TCCR1B
    #define TIMSKn TIMSK1
    #define TIFRn  TIFR1
    #define OCIEnA OCIE1A
    #define OCRnA  OCR1A
    #define OCFnA  OCF1A
    #define PRESCALER (_BV(CS12) | _BV(CS10)) /*1024*/
    #define SIG_OUTPUT_COMPAREnA TIMER1_COMPA_vect

#elif MB_TIMER == 2
    #define TCNTn TCNT2
    #define TCCRnA TCCR2A
    #define TCCRnB TCCR2B
    #define TIMSKn TIMSK2
    #define TIFRn  TIFR2
    #define OCIEnA OCIE2A
    #define OCRnA  OCR2A
    #define OCFnA  OCF2A
    #define PRESCALER (_BV(CS22) | _BV(CS21)) | _BV(CS20)) /*1024*/
    #define SIG_OUTPUT_COMPAREnA TIMER2_COMPA_vect

#endif


#endif
