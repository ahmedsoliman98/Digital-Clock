/*
 * ATmega32A_Interrupt.h
 *
 * Created: 10/5/2020 2:22:19 PM
 *  Author: ahmedsoliman
 */ 


#ifndef ATMEGA32A_INTERRUPT_H_
#define ATMEGA32A_INTERRUPT_H_


	#include "StandardDataType.h"
/******************************************************* The External interrupt Defintion ***************************************************************/
/* Vector 0 is the reset vector */
/* External Interrupt Request 0 */
#define INT0_vect            _VECTOR(1)
#define INT0_vect_num        1

/* External Interrupt Request 1 */
#define INT1_vect            _VECTOR(2)
#define INT1_vect_num        2

/* External Interrupt Request 2 */
#define INT2_vect            _VECTOR(3)
#define INT2_vect_num        3
	

/* bits of The MCUCR register to Control INT0, INT1 */
#define ISC00		(0)
#define ISC01		(1)
#define ISC10		(2)
#define ISC11		(3)
#define ISC2      (6)
	
/* bits of The GICR register */
#define INT0     (6)
#define INT1     (7)
#define INT2     (5)
	
/*********************************************************************** The Timer Interrupt Definition ***********************************************/
/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_vect            _VECTOR(4)
#define TIMER2_COMP_vect_num        4

/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vect            _VECTOR(5)
#define TIMER2_OVF_vect_num        5

/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_vect            _VECTOR(6)
#define TIMER1_CAPT_vect_num        6

/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_vect            _VECTOR(7)
#define TIMER1_COMPA_vect_num        7

/* Timer/Counter1 Compare Match B */
#define TIMER1_COMPB_vect            _VECTOR(8)
#define TIMER1_COMPB_vect_num        8

/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect            _VECTOR(9)
#define TIMER1_OVF_vect_num        9

/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_vect            _VECTOR(10)
#define TIMER0_COMP_vect_num        10

/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect            _VECTOR(11)
#define TIMER0_OVF_vect_num        11

/* Serial Transfer Complete */
#define SPI_STC_vect            _VECTOR(12)
#define SPI_STC_vect_num        12

	typedef enum
	{
		EXINT_LowLevel,
		EXINT_Toggle,
		EXINT_FallingEdge,
		EXINT_RisingEdge,
	}ExInterrupt_Modes;


	typedef enum
	{
		EXINT_INT0,
		EXINT_INT1,
		EXINT_INT2,
	}EXInterrupt_Source;


	extern void (* EXTINT0_ISR) (void);
	extern void (* EXTINT1_ISR) (void);
	extern void (* EXTINT2_ISR) (void);
	
	void EXTINT_InterruptInit(EXInterrupt_Source source,ExInterrupt_Modes Mode);


#endif /* ATMEGA32A_INTERRUPT_H_ */