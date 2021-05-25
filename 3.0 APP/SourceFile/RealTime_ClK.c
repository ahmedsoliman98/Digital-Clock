/*
 * RealTime_ClK.c
 *
 * The Idea of this application is to make a real time clock system represent the time throw a six 7-segment display 2 for hour, 2 for minute and 2 for second
 * and this clock can be set up it is time by instruction setting appear on the LCD display " Set Time Click 1 "
 * The user can click '1' throw the keypad and it will appear on the LCD the "Hour :  _:_ " to inform that it will set the hour then the minute and second will appear in the same way 
 * the clock will represent time in the 24h form not 12 the minute and the second max value can appear is 59 then it will increase the next dimension and it will return to 0
 *
 * The Implementation 
 * We used the Timer 2 with the external crystal clock with the value 32768 Hz frequency to make it has an overflow exactly after a 1 second 
 * so we makes its ISR to increase a generic volatile second counter and display this value on the 7-segment E5, E6 after the sec counter reach 60 it increase min counter by 1 display on the 7-segment E4, E3 and return to 0
 * same way after min counter reach 60 it will increase the hour counter by 1 display on the 7-segment Enable 2 & 1  
 *
 * We used the Timer0 to setup an counter after a 5msec to used the multiplexing feature to operate the six 7-segment on the same pins 
 *
 * Created: 1/12/2021 6:25:45 PM
 *  Author: ahmedsoliman
 */ 

#include "ATmega32A_Config.h"
#include "ATmega32A_DIO_Config.h"
#include "ATmega32A_Timers_Config.h"
#include "ATmega32A_Interrupt.h"
#include "Keypad_Config_Driver.h"
#include "BCD_7Segment.h"
#include "LCD.h"



/* Define The Pins On=f The Enable For Each on Of The 7-Segment */
 #define En1_7SegHr   (PIN0)
 #define En2_7SegHr   (PIN1)
 #define En3_7SegMin  (PIN2)
 #define En4_7SegMin  (PIN3)
 #define En5_7Segsec  (PIN4)
 #define En6_7Segsec  (PIN5)
 
 /* This value make the timer 0 get an interrupt request each 3msec */
 #define CTC_TOP_VALUE (47)
  
  /* work as flag that a five mSec are passed to make a multiplexing between the six 7-segment */
  volatile unsigned char Five_msec;
  /* Define The Counter Of The second as a Volatile beacuce it increment each time timer2 response to the interrupt request in the ISR */
  volatile unsigned char oneSec_Counter;
  /* Define The Counter Of The Minute and The Hour */
  unsigned char oneMin_Counter;
  unsigned char oneHr_Counter ;
  unsigned char temp_var ;
  
  /* Set The Pins and Port Of The keypad */
  KEYPAD_PIN key = {GPIOB, PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7};
 /* Set The Key Data */
 unsigned char KeyData [][COL] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
  };
  
  /* Define The Timer number , Mode , source of interrupt and the prescaler for each one clock */  
  TIMER_DATATYPE timer0 = {Timer0, Timer_CTC_Mode, Timer_Fcpu_Div1024, Timer_TopCTC_Interrupt};
  TIMER_DATATYPE timer2 = {Timer2, Timer_Overflow_Mode, Timer2_OneSec_CLK, Timer_Overflow_Interrupt};
  
  /* Define The pins And The port for each one of the 7-segments we connect the six of Then On The Same Pins And Port */  
  SevenSegment pins_7Segment=  {GPIOD, PIN0, PIN1, PIN2, PIN3};

		  
 
  void RealTime_ClK_INTIA(void)
  {
	  /* setup the pins and initiate the function for the LCD */
	  LCD_init();
	  
	  /* setup the pins for the Keypad */
	  keypad_Intiat(key);
	  
	  /* setup the pins for the 7-Segment */
	  sevenSegment_setup(pins_7Segment);

	  
	  /* set up the enable pin for the each one of the 7-segment we make it Output pin the default value out is 0 if we change to 1 that enable the 7-segment */
	  DIO_pinConfiguration(GPIOC,En1_7SegHr, Output);
	  DIO_pinConfiguration(GPIOC,En2_7SegHr, Output);
	  DIO_pinConfiguration(GPIOC,En3_7SegMin, Output);
	  DIO_pinConfiguration(GPIOC,En4_7SegMin, Output);
	  DIO_pinConfiguration(GPIOC,En5_7Segsec, Output);
	  DIO_pinConfiguration(GPIOC,En6_7Segsec, Output);
	  
	  /* Timer 0 and 2 set up */
	  TIMER_INTIATE(timer0);
	  TIMER_DELAY(timer0,CTC_TOP_VALUE);
	  TIMER_INTIATE(timer2);
	  LCD_DisplayString("to setup Clock");
	  LCD_Select_RowCol(1,3);
	  LCD_DisplayString("press '1'");
  }
  
  
  
  
  
  void RealTime_ClK_OPERATE(void)
  {
	  while (keypad_Read(key) != '1')
	  {
			DIO_pinWrite(GPIOC,En1_7SegHr,LOW);
			DIO_pinWrite(GPIOC,En2_7SegHr,LOW);
			DIO_pinWrite(GPIOC,En3_7SegMin,LOW);
			DIO_pinWrite(GPIOC,En4_7SegMin,LOW);
			DIO_pinWrite(GPIOC,En5_7Segsec,LOW);
			DIO_pinWrite(GPIOC,En6_7Segsec,HIGH);
			sevenSegment_write(pins_7Segment, (oneSec_Counter%10));
			Five_msec = 0;
			while(Five_msec == 0);
			DIO_pinWrite(GPIOC,En1_7SegHr,LOW);
			DIO_pinWrite(GPIOC,En2_7SegHr,LOW);
			DIO_pinWrite(GPIOC,En3_7SegMin,LOW);
			DIO_pinWrite(GPIOC,En4_7SegMin,LOW);
			DIO_pinWrite(GPIOC,En5_7Segsec,HIGH);
			DIO_pinWrite(GPIOC,En6_7Segsec,LOW);
			sevenSegment_write(pins_7Segment, (oneSec_Counter/10));
			Five_msec = 0;
			while(Five_msec == 0);
			
		
		  	
        DIO_pinWrite(GPIOC,En1_7SegHr,LOW);
		DIO_pinWrite(GPIOC,En2_7SegHr,LOW);
		DIO_pinWrite(GPIOC,En3_7SegMin,LOW);
		DIO_pinWrite(GPIOC,En4_7SegMin,HIGH);
		DIO_pinWrite(GPIOC,En5_7Segsec,LOW);
		DIO_pinWrite(GPIOC,En6_7Segsec,LOW);
		sevenSegment_write(pins_7Segment, (oneMin_Counter%10));
		Five_msec = 0;
		while(Five_msec == 0);
		DIO_pinWrite(GPIOC,En1_7SegHr,LOW);
		DIO_pinWrite(GPIOC,En2_7SegHr,LOW);
		DIO_pinWrite(GPIOC,En3_7SegMin,HIGH);
		DIO_pinWrite(GPIOC,En4_7SegMin,LOW);
		DIO_pinWrite(GPIOC,En5_7Segsec,LOW);
		DIO_pinWrite(GPIOC,En6_7Segsec,LOW);
		sevenSegment_write(pins_7Segment, (oneMin_Counter/10));
		Five_msec = 0;
		while(Five_msec == 0);
		
	
		DIO_pinWrite(GPIOC,En1_7SegHr,LOW);
		DIO_pinWrite(GPIOC,En2_7SegHr,HIGH);
		DIO_pinWrite(GPIOC,En3_7SegMin,LOW);
		DIO_pinWrite(GPIOC,En4_7SegMin,LOW);
		DIO_pinWrite(GPIOC,En5_7Segsec,LOW);
		DIO_pinWrite(GPIOC,En6_7Segsec,LOW);
		sevenSegment_write(pins_7Segment, (oneHr_Counter%10));
		Five_msec = 0;
		while(Five_msec == 0);
		DIO_pinWrite(GPIOC,En1_7SegHr,HIGH);
		DIO_pinWrite(GPIOC,En2_7SegHr,LOW);
		DIO_pinWrite(GPIOC,En3_7SegMin,LOW);
		DIO_pinWrite(GPIOC,En4_7SegMin,LOW);
		DIO_pinWrite(GPIOC,En5_7Segsec,LOW);
		DIO_pinWrite(GPIOC,En6_7Segsec,LOW);
		sevenSegment_write(pins_7Segment, (oneHr_Counter/10));
		Five_msec = 0;
		while(Five_msec == 0);		  
		  if (oneSec_Counter >= 60)
		  {
			  oneSec_Counter = 0;
			  oneMin_Counter++;
		  }
		  if (oneMin_Counter >= 60)
		  {
			  oneMin_Counter = 0;
			  oneHr_Counter++;
		  }
		  if (oneHr_Counter >= 25)
		  {
			  oneHr_Counter =0;
		  }
		  		  
		  		  
	  }
	  LCD_Clear();
	  LCD_DisplayString("Set Hour : _ _");
	  LCD_Select_RowCol(0,11);
	  while(temp_var == 0)
	  {
	     temp_var = keypad_Read(key) ;
	  }	  
	  oneHr_Counter = ((temp_var - 48) * 10);
	  LCD_DisplayChar(temp_var);
	  LCD_Select_RowCol(0,13);
	  temp_var = 0 ;
	  while(temp_var == 0)
	  {
		  temp_var = keypad_Read(key);
	  }
	  oneHr_Counter =oneHr_Counter + (temp_var - 48);
	  LCD_DisplayChar(temp_var);
	  LCD_Select_RowCol(1,0);
	   temp_var = 0 ;
	  LCD_DisplayString("Next press '*'");
	  while(keypad_Read(key) != '*');
	  
	  /* Set Up the Minute */
	  LCD_Clear();
	  LCD_DisplayString("Set Minute : _ _");
	  LCD_Select_RowCol(0,13);
	  while(temp_var == 0)
	  {
		  temp_var = keypad_Read(key) ;
	  }
	  oneMin_Counter = ((temp_var - 48) * 10);
	  LCD_DisplayChar(temp_var);
	  LCD_Select_RowCol(0,15);
	  temp_var = 0 ;
	  while(temp_var == 0)
	  {
		  temp_var = keypad_Read(key);
	  }
	  oneMin_Counter =oneMin_Counter + (temp_var - 48);
	  LCD_DisplayChar(temp_var);
	  LCD_Select_RowCol(1,0);
	   temp_var = 0 ;
	  LCD_DisplayString("Next press '*'");
	  while(keypad_Read(key) != '*');
	  
	  /* Set Up the Second */
	  LCD_Clear();
	  LCD_DisplayString("Set Second : _ _");
	  LCD_Select_RowCol(0,13);
	  while(temp_var == 0)
	  {
		  temp_var = keypad_Read(key) ;
	  }
	  oneSec_Counter = ((temp_var - 48) * 10);
	  LCD_DisplayChar(temp_var);
	  LCD_Select_RowCol(0,15);
	  temp_var = 0 ;
	  while(temp_var == 0)
	  {
		  temp_var = keypad_Read(key);
	  }
	  oneSec_Counter =oneSec_Counter + (temp_var - 48);
	  LCD_DisplayChar(temp_var);
	  LCD_Select_RowCol(1,0);
	   temp_var = 0 ;
	  LCD_DisplayString("Next press '*'");
	  while(keypad_Read(key) != '*');
	  LCD_Clear();
	  LCD_DisplayString("to setup Clock");
	  LCD_Select_RowCol(1,3);
	  LCD_DisplayString("press '1'");
  }
  
  
  ISR(TIMER0_COMP_vect)
  {
	  Five_msec = 1;
  }
  
  ISR(TIMER2_OVF_vect)
  {
	  oneSec_Counter++;
  }