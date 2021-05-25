/*
 *
 * @file <ATmega32A_Config.h>
 * @brief <This is a Header File for the ATmega32A Mc configuration>
 *
 *Postbult Driver for digital IO in ATmega32A 
 * @APIS			  
 *					
 * @authors <ahmedsoliman>
 * @date <7/10/2020 4:08:31 PM>
 *
 */


/*      Guard File 
    to make sure that this file is not include more than one time in the same space
*/
#ifndef ATMEGA32A_CONFIG_H_
#define ATMEGA32A_CONFIG_H_

 #include <StandardDataType.h>

   #define printLog (msg)      {}
   #define F_CPU (16000000u)
   #define NULL	((void *) (0x00))
   
 /*
  *
  * @brief <GPIO>
  *		  volatile uint8		PIN < Should assign unsigned integer 8 bit PIN Address to it >
  *        volatile uint8		DDR < Should assign unsigned integer 8 bit data direction register Address to it >
  *        volatile uint8		PORt < Should assign unsigned integer 8 bit PORT Address to it >
  */
   typedef struct
   {
	   volatile uint8 PIN;
	   volatile uint8 DDR;
	   volatile uint8 PORT;
   }GPIO;
  
  
   /* The Value Of the Memory Mapped Is 0x02 This Value Add to the real Address To Mapped it to The RAM */
   #define IO_MAPPED_OFFSET (0x20)
   
   /* Statues Register */
   #define SREG_ADDRESS    (0x3F)
   #define SREG       (*(volatile uint8 *)(SREG_ADDRESS + IO_MAPPED_OFFSET))
   
   /* The Asynchronous Statues Register ASSR */
   #define ASSR_ADRESS (0x22)
   #define ASSR (*(volatile uint8 *)(ASSR_ADRESS + IO_MAPPED_OFFSET))
   
   /* ASSR Bits*/
   #define TCR2UB (0)
   #define OCR2UB (1)
   #define TCN2UB (3)
   #define AS2    (4)
   
  /* check the flash condition */ 
 #define  SPMCR_ADDRESS  (0x37)
 #define  SPMCR    (*(volatile uint8 *) (SPMCR_ADDRESS + IO_MAPPED_OFFSET))
 
 #define SPMIE  (0)
   
   /*********************************************************************************** IO Pins Address ***********************************************************************************************************************************************************************/
   
   
   /* Note In The Data Sheet That The Value Of The PIN , DDR , PORT is in sequential Start From 0x19 For PINA And The Same Idea on The Other B,C,D */
   #define GPIOA_ADDERSS_IO (0x19)
   #define GPIOB_ADDERSS_IO (0x16)
   #define GPIOC_ADDERSS_IO (0x13)
   #define GPIOD_ADDERSS_IO (0x10)
   
   
   /* Define The Value Of Address Of The A,B,C,D In C (The Mapped Address In RAM) */
   
   #define GPIOA    ((GPIO *) (GPIOA_ADDERSS_IO + IO_MAPPED_OFFSET))
   #define GPIOB    ((GPIO *) (GPIOB_ADDERSS_IO + IO_MAPPED_OFFSET))
   #define GPIOC    ((GPIO *) (GPIOC_ADDERSS_IO + IO_MAPPED_OFFSET))
   #define GPIOD    ((GPIO *) (GPIOD_ADDERSS_IO + IO_MAPPED_OFFSET))
   
   
   

/******************************************************************************************* The Interrupt Register and Pins Address *************************************************************************************************************************************************/

/* the MCU control Register */
#define MCUCR_ADDRESS  (0x35)  

/* The MCU control and Statues Register */ 
#define MCUCSR_ADDRESS  (0x34)

/* General Interrupt Control Register */
#define GICR_ADDRESS  (0x3B)

/*General Interrupt flag Register */
#define GIFR_ADDRESS  (0x3A)


 /* Define The Value Of Address Of The MCUCR, NCUCSR, GICR, GIFR In C (The Mapped Address In RAM) */
#define MCUCR      (*(volatile uint8 *)(MCUCR_ADDRESS + IO_MAPPED_OFFSET))
#define MCUCSR     (*(volatile uint8 *)(MCUCSR_ADDRESS + IO_MAPPED_OFFSET))
#define GICR       (*(volatile uint8 *)(GICR_ADDRESS + IO_MAPPED_OFFSET))
#define GIFR       (*(volatile uint8 *)(GIFR_ADDRESS + IO_MAPPED_OFFSET))

/* Global interrupt bit Control Define */
#define GLOBAL_INT_ENABLE()	(SET_Bit(SREG,7))
#define GLOBAL_INT_DISABLE()	(RESET_Bit(SREG,7))


/* Interrupt Service Routine Definitions */

/* signal : is the initial condition of the interrupt to be disable nested feature
 * __INTR_ATTRS : this like volatile act to note the optimization do not remove this function if we not call
 * __VA_ARGS__ it is replace by any thing will write instead of the ... 
 */
#define ISR(vector, ...)        \
void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
void vector (void)


#define ISR_NESTED_ENABLE     __attribute__((signal))
#define ISR_NESTED_DISABLE    __attribute__((interrupt))
/* use when the interrupt function was write with assembly */
#define ISR_NAKED            __attribute__((naked))

/* use to make an interrupt do the same function as the other interrupt */
#define ISR_ALIASOF(v) __attribute__((alias(__STRINGIFY(v))))


#define _VECTOR(N)    __vector_ ## N



/******************************************************************************************************************* USART In THe AVR ******************************************************************************************************************************/


#define UCSRA_ADDRESS   (0x0B)
#define UCSRB_ADDRESS   (0x0A)
#define UCSRC_ADDRESS   (0x20)
#define UBRRH_ADDRESS   (0x20)
#define UBRRL_ADDRESS   (0x09)
#define UDR_ADDRESS     (0x0C)


/* Define The Value Of Address Of The UCSRA, UCSRB, UCSRC, UBRRH, UBRRL, UDR In C (The Mapped Address In RAM) */

#define UCSRA    (*(volatile uint8 *)(UCSRA_ADDRESS + IO_MAPPED_OFFSET))
#define UCSRB    (*(volatile uint8 *)(UCSRB_ADDRESS + IO_MAPPED_OFFSET))
#define UCSRC    (*(volatile uint8 *)(UCSRC_ADDRESS + IO_MAPPED_OFFSET))
#define UBRRH    (*(volatile uint8 *)(UBRRH_ADDRESS + IO_MAPPED_OFFSET))
#define UBRRL    (*(volatile uint8 *)(UBRRL_ADDRESS + IO_MAPPED_OFFSET))
#define UDR      (*(volatile uint8 *)(UDR_ADDRESS + IO_MAPPED_OFFSET))

/******************************************* define the bit on the register USRAT control and statues register ************************************/
#define RXC    (7)
#define TXC    (6)
/* indicate if the transmitter buffer is ready to receive */ 
#define UDRE   (5)
/* Errors Flag FE for indicate the stop bit error
 * DOR data over right 
 * PE parity check detection 
 */ 
#define FE     (4)
#define DOR    (3)
#define PE     (2)
/* to double USART transmission speed */
#define U2X    (1)
/* Enable the multi processor communication */
#define MPCM   (0)

/*********************************************** define the bit on the register UCSRB **************************************************/
#define RXCIE  (7)
/* Enable interrupt  */
#define TXCIE  (6)
#define UDRIE  (5)
#define RXEN   (4)
#define TXEN   (3)
/* combined with UCSZ 1:0 to set the number of the data bit */
#define UCSZ2  (2)
/* ninth bit place at transmission or receiver */
#define RXB8   (1)
#define TXB8   (0)

/*********************************************** define the bit on the register UCSRC ********************************************************/
/* this bit select between access UCSRC and UBRRH register if it set reading UCSRC */
#define URSEL  (7)
/* UART mode select between synch or Asynch */
#define UMSEL  (6)
/* this bit Withe UPM0 select the parity mode */
#define UPM1   (5)
#define UPM0   (4)
/* select the number of the stop bit 1 or 2 */
#define USBS   (3)
#define UCSZ1  (2)
#define UCSZ0  (1)
/* define clock Polarity */
#define UCPOL  (0)

/****************************************************************************************************************** ADC in The ATmega32 ***********************************************************************************************************************/

/* The address of the ADC 4 register */
#define ADCMUX_ADDRESS   (0x07)
#define ADCSRA_ADDRESS   (0x06)
#define ADCL_ADDRESS     (0x04)
#define ADCH_ADDRESS     (0x05)

/* the mapping address of the 4 register */
/* Is The Register Of The Bit Selection From The PORT A pin It for Multiplexer 32 so It Have 5 Bit Control */
#define ADCMUX     (*(volatile uint8 *)(ADCMUX_ADDRESS + IO_MAPPED_OFFSET))

/* ADCMUX bit */
#define MUX0   (0)
#define MUX1   (1)
#define MUX2   (2)
#define MUX3   (3)
#define MUX4   (4)
#define ADLAR  (5)
#define REF0   (6)
#define REF1   (7)
/* It is ADS Control And Statues Register */
#define ADCSRA     (*(volatile uint8 *)(ADCSRA_ADDRESS + IO_MAPPED_OFFSET))

/* ADCSRA bit */
#define ADPS0   (0)
#define ADPS1   (1)
#define ADPS2   (2)
#define ADIE    (3)
#define ADIF    (4)
#define ADATE   (5)
#define ADSC    (6)
#define ADEN    (7)
/* it the 8 bit data register that hold from ADC0 - ADC7 */ 
#define ADCL       (*(volatile uint8 *)(ADCL_ADDRESS + IO_MAPPED_OFFSET))
/* it storing 2 bit ADC8, ADC9 */
#define ADCH     (*(volatile uint8 *)(ADCH_ADDRESS + IO_MAPPED_OFFSET))  


/************************************************************************************************ Timers Registers ***************************************************************************************************/

/* The Address of The Timer 0 Register */
#define TCCR0_ADDRESS (0x33)
#define TCNT0_ADDRESS (0x32)
#define OCR0_ADDRESS  (0x3C)
/* The Address of The Timer 2 Register */
#define TCCR2_ADDRESS (0x25)
#define TCNT2_ADDRESS (0x24)
#define OCR2_ADDRESS  (0x23)
/* The Address of the Timer 1 Register */
#define TCCR1A_ADDRESS (0x2F)
#define TCCR1B_ADDRESS (0x2E)
#define TCNT1H_ADDRESS (0x2D)
#define TCNT1L_ADDRESS (0x2C)
#define OCR1AH_ADDRESS (0x2B)
#define OCR1AL_ADDRESS (0x2A)
#define OCR1BH_ADDRESS (0x29)
#define OCR1BL_ADDRESS (0x28)
#define ICR1H_ADDRESS  (0x27)
#define ICR1L_ADDRESS  (0x26)
/* general Registers Use With The Timers 0,1,2 */
#define TIFR_ADDRESS (0x38)
#define TIMASK_ADDRESS (0x39)

/* Timer Counter Control Register in Timer 0 */
#define TCCR0 (*(volatile uint8 *) (TCCR0_ADDRESS + IO_MAPPED_OFFSET))

/* TCCR0 Bit */
#define CS00    (0)
#define CS01    (1)
#define CS02    (2)
#define WGM01   (3)
#define COM00   (4)
#define COM01   (5)
#define WGM00   (6)
#define FOC0    (7)

/* Timer Counter Control Register in Timer 0 */
#define TCCR2 (*(volatile uint8 *) (TCCR2_ADDRESS + IO_MAPPED_OFFSET))

/* TCCR0 Bit */
#define CS20    (0)
#define CS21    (1)
#define CS22    (2)
#define WGM21   (3)
#define COM20   (4)
#define COM21   (5)
#define WGM20   (6)
#define FOC2    (7)

/* Timer Counter Control Register in Timer 1 */
#define TCCR1A (*(volatile uint8 *) (TCCR1A_ADDRESS + IO_MAPPED_OFFSET))

/* TCCR1A Bit */
#define WGM10    (0)
#define WGM11    (1)
#define FOC1B    (2)
#define FOC1A    (3)
#define COM1B0   (4)
#define COM1B1   (5)
#define COM1A0   (6)
#define COM1A1   (7)

#define TCCR1B (*(volatile uint8 *) (TCCR1B_ADDRESS + IO_MAPPED_OFFSET))

/* TCCR1B Bit */
#define CS10     (0)
#define CS11     (1)
#define CS12     (2)
#define WGM12    (3)
#define WGM13    (4)
/* Bit 5 is Reserved */
#define ICES1    (6)
#define ICNC1    (7)

/* Timer Interrupt Mask Register control the interrupt enable */
#define TIMSK     (*(volatile uint8 *)(TIMASK_ADDRESS + IO_MAPPED_OFFSET))

/* TIMASK Bit */
#define TOIE0   (0)
#define OCIE0   (1)
#define TOIE1   (2)
#define OCIE1B  (3)
#define OCIE1A  (4)
#define TICIE1  (5)
#define TOIE2   (6)
#define OCIE2   (7)

/* Timer Interrupt Flag Register */
#define TIFR     (*(volatile uint8 *)(TIFR_ADDRESS + IO_MAPPED_OFFSET))

 /* TIFR Bit */
 #define TOV0  (0)
 #define OCF0  (1)
 #define TOV1  (2)
 #define OCF1B (3)
 #define OCF1A (4)
 #define ICF1  (5)
 #define TOV2  (6)
 #define OCF2  (7)

/* Counter Register For The Timer 0 */
#define TCNT0   (*(volatile uint8 *)(TCNT0_ADDRESS + IO_MAPPED_OFFSET))
/* Output Compare Register */
#define OCR0    (*(volatile uint8 *)(OCR0_ADDRESS +IO_MAPPED_OFFSET))

/* Counter Register For The Timer 2 */
#define TCNT2   (*(volatile uint8 *)(TCNT2_ADDRESS + IO_MAPPED_OFFSET))
/* Output Compare Register */
#define OCR2    (*(volatile uint8 *)(OCR2_ADDRESS +IO_MAPPED_OFFSET))

/*Counter Register For The Timer 1 */
#define TCNT1H  (*(volatile uint8 *)(TCNT1H_ADDRESS + IO_MAPPED_OFFSET))
#define TCNT1L  (*(volatile uint8 *)(TCNT1L_ADDRESS + IO_MAPPED_OFFSET))
#define TCNT1  (*(volatile uint8 *)(TCNT1L_ADDRESS + IO_MAPPED_OFFSET))
/* Output Compare Register A */
#define OCR1AH    (*(volatile uint8 *)(OCR1AH_ADDRESS +IO_MAPPED_OFFSET))
#define OCR1AL    (*(volatile uint8 *)(OCR1AL_ADDRESS +IO_MAPPED_OFFSET))
#define OCR1A     (*(volatile uint16 *)(OCR1AL_ADDRESS +IO_MAPPED_OFFSET))
#define OCR1BH    (*(volatile uint8 *)(OCR1BH_ADDRESS +IO_MAPPED_OFFSET))
#define OCR1BL    (*(volatile uint8 *)(OCR1BL_ADDRESS +IO_MAPPED_OFFSET))
#define OCR1B    (*(volatile uint16 *)(OCR1BL_ADDRESS +IO_MAPPED_OFFSET))
/* Input Capture Register */
#define ICR1H     (*(volatile uint8 *)(ICR1H_ADDRESS +IO_MAPPED_OFFSET))
#define ICR1L     (*(volatile uint8 *)(ICR1L_ADDRESS +IO_MAPPED_OFFSET))
#define ICR1      (*(volatile uint16 *)(ICR1L_ADDRESS +IO_MAPPED_OFFSET))

/******************************************************************************** Internal EEPROM Register *****************************************************************************************************/

#define EEARH_ADDRESS         (0x1F)
#define EEARL_ADDRESS         (0x1E)
#define EEDR_ADDRESS          (0x1D)
#define EECR_ADDRESS          (0x1C)

/* The address of the EEPROM address register High bit it contain only bit 9/10 */
#define EEARH        (*(volatile uint8 *) (EEARH_ADDRESS + IO_MAPPED_OFFSET))
/* The address of the EEPROM address register Low bit it contain bits from 0-7 */
#define EEARL        (*(volatile uint8 *) (EEARL_ADDRESS + IO_MAPPED_OFFSET))
/* hold the 10 bits of the address */
#define EEAR        (*(volatile uint16 *) (EEARL_ADDRESS + IO_MAPPED_OFFSET))
/* The address of the EEPROM Control register */
#define EECR         (*(volatile uint8 *) (EECR_ADDRESS + IO_MAPPED_OFFSET))

/* the Control Register Bits */
#define EERE   (0) /* EEPROM Read Enable Bit */ 
#define EEWE   (1) /* EEPROM Write Enable Bit */
#define EEMWE  (2) /* EEPROM Master Write Enable bit */
#define EERIE  (3) /*Ready Interrupt Enable */
/* the Other Bit is Reserved */

/*The address of the EEPROM Data register */
#define EEDR         (*(volatile uint8 *) (EEDR_ADDRESS + IO_MAPPED_OFFSET))


#endif /* ATMEGA32A_CONFIG_H_ */