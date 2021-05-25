/*
 * ATmega32A_Timers_Config.h
 *
 * Created: 1/1/2021 10:12:21 PM
 *  Author: ahmedsoliman
 *
 ********************* Internal Structure *********************
 *
 * We have at the ATmega32A a 3 Timers 0,1,2 Each one of them has it is feature than the other 
 *
 * TMSK it the general register to all timers it is a mask able register to the interrupt bit of the Timers
 * TIFR it is the Timer interrupt flag register it hold the flags of the interrupts situation of the 3 timers
 *
 * Timer0 (8-Bit timer)
 * It has an TCNT0 the counter register , OCR0 it the Compare match value hold register , TCCR0  it is the control register of the timer 
 * It has a single compare unit OCR0 the TCNT0  clear on the compare match
 * has an 8 selection of the Clock prescaler 
 * has an 4 different work mode (Normal Mode , CTC Mode , phase Correct Mode , Fast PWM )
 * It has 2 Interrupt Source on if the TCNT0 reach to the bottom ( Overflow ) and the other at the Compare match btween the value on the OCR0 and the TCNT0
 *
 * Timer2 (8-bit Timer)
 * it is the same as the timer0 but the biggest different that the timer2 has the ability to get an External Clock source on the Pin TOSC1 PC6 if it from RC circuit or from TOSC1, TOSC2 if it form an Crystal Oscillator 
 * The biggest use of the timer 2 in the application of the real time clock because the ability of adding crystal that equal 32768Hz and the wide scale option of the prescaler value that we use 128 in that appliction
 * Single Compare match from OCR2 
 * It has an TCNT2 the counter register , OCR2 it the Compare match value hold register , TCCR2  it is the control register of the timer
 * It has 2 Interrupt Source on if the TCNT2 reach to the bottom ( Overflow ) and the other at the Compare match between the value on the OCR2 and the TCNT2
 *
 * Timer1 (16-bit Timer)
 * It be a kind different from the 2 other timer because it is a 16 bit timer and because it is the 8-bit microcontroller all the register must be a 8-bit so register of the timer1 is divided into 2 register 
 * it has 2 independent output compare match OCR1A , OCR1B 
 * has a one input capture unit and capture noise 
 * Has 4 external interrupt source 
 * Variable PWM periods 
 * 
 ***************** Operating Mode *****************************
 *
 * Timer 0 
 * It has a 4 operating Mode switch between them by the 2 bit WGM00, WGm01 in the control register TCCR0
 * 1- Normal Mode WGM00 0 WGM01 0
 * it is the default Mode in that mode TCNT0 the counter timer register count from 0 to 255 then it get overflow return to 0 and raise the TOV0 flag bit in the TIFR
 * and if the bit TOIE0 interrupt mask enable in the TMSK register it call interrupt source event 
 *
 * 2- CTC Mode WGM00 0 WGM01 1
 * In that Mode The User store an value in the OCR0 register and the TCNT0 count as normal and when the value of the TCNT0 reach to be equal to the Value in the OCR0 raise the OCF0 flag bit in the TIFR and TCNT0 return to 0
 *  and if the bit OCIE0 interrupt mask enable in the TMSK register it call interrupt source event 
 * The value store in the OCR0 decide by the time the user want to pass to get interrupt that by( T (of the user want to pass)/ T timer time in sec) Note that the Timer time get by 1/(F_Cpu/the value of the prescaler)
 *
 * Note We Can Generat an Signal in The CTC , Normal Mode (Non PWM Mode)
 * That By Used The Pin PB3 and control the output signal by the 2 bit COM01 , COM00 in the control register this bit is also used to control the signal in the PWM mode 
 *     COM01    COM00
 *      0        0      Normal Port Operation the OC0 is Disconnected 
 *      0        1      Toggle OC0 on a Compare match
 *      1        0      Clear OC0 on a Compare match
 *      1        1      Set "    " "  "    "   " 
 * The Frequency of the output signal get by :
 * Time of the output signal = time periode of the one cycle * time of cycle  = 2*(1 + OCR0) * time of timer ->  N(prescaler value)/F_CPU
 * The frequency of The output signal is F_CPu / (2N * (1 + OCR0) )
 * Te max OC0 Freqency it when N = 1 and OCR0 = 0 that mean Fmax = F_CPu / 2
 *
 * 3- Fast PWM Mode WGM00 1 WGM01 1
 *  The generating signal appear on the PB3 the OC0  Pin The shape of the signal decide by the user through the bit COM00 COM01 
 *     COM01    COM00
 *      0        0      Normal Port Operation the OC0 is Disconnected
 *      0        1      Reserved _ _
 *      1        0      Clear OC0 on a Compare match and Set OC0 at TCNT0 Reach the bottom (overflow)  (non inverting mode)
 *      1        1      Set "    " "  "    "   " "    "   Clear   "   "     "   "    "       "          (inverting Mode )
 *
 * time of the OC0 = 256 *(1/F_timer)
 * if the user store in the OCR0 the value 64 that mean in the non inverting mode the off 75% of the signal and the on the 25% and in the inverting mode is vise versa 
 * 
 * 4- phase Correct PWM Mode WGM00 1 WGM01 0
 *  This mode is same as fast PWM mode but the TCNT0 is counting up and down not get overflow  
 *  The generating signal appear on the PB3 the OC0  Pin The shape of the signal decide by the user through the bit COM00 COM01
 *     COM01    COM00
 *      0        0      Normal Port Operation the OC0 is Disconnected
 *      0        1      Reserved _ _
 *      1        0      Clear OC0 on a Compare match in TCNT0 in up counting and Set OC0 at Compare match on TCNT0 in down counting  (non inverting mode)
 *      1        1      Set "    " "  "    "   " "    "   Clear   "   "     "   "    "       "       "      "  "    "   "    "        (inverting Mode )
 * time of the OC0 = 510 *(1/F_timer)     Because ( 2* 256 = 510 )
 * 
 *
 * Timer 2 
 * it has the exact same Mode as the timer0 but the different in the Registers and the bit called 
 *
 *
 * Timer 1
 *
 *  
 ***************** Timers Register ***********************
 * It Have Four Register 2 is general and the other is different for each timer that in timer 0,2  
 *
 * Timer0
 *  1- TCCR0 
 *     Timer Counter Control Register 
 *     bit0 - bit3 CS00 : CS02 : it an the prescaler value for the clock input to the timer selection 
 *     bit3 , bit6 WGM00 WGM01:  it the bits responsible to the Mode selection of the timer 
 *     bit4 , bit5 COM00, COM01 : it is the bit responsible to the decide the shape of the output signal from the PB3 
 *     bit 7 FOC0 : it fake the Compare match Event but not make TCNT0 return to 0 
 *        
 *  2 - TCNT0 
 *      It is the counter 8-bit register 
 *
 *  3- OCR0 
 *     it is the register that Hold the Compare math value 
 *    
 * Timer2
 *  1- TCCR2
 *     Timer Counter Control Register
 *     bit0 - bit3 CS20 : CS22 : it an the prescaler value for the clock input to the timer selection
 *     bit3 , bit6 WGM20 WGM21:  it the bits responsible to the Mode selection of the timer
 *     bit4 , bit5 COM20, COM21 : it is the bit responsible to the decide the shape of the output signal from the PD7
 *     bit 7 FOC1 : it fake the Compare match Event but not make TCNT2 return to 0
 *
 *  2 - TCNT2
 *      It is the counter 8-bit register
 *
 *  3- OCR2
 *     it is the register that Hold the Compare math value
 *
 * 
 *
 * 
 */ 
  


#ifndef ATMEGA32A_TIMERS_CONFIG_H_
#define ATMEGA32A_TIMERS_CONFIG_H_

  
   typedef enum
   {
	   Timer0,
	   Timer2,
   }Timer_Selection; 
   
   typedef enum
   {
	   Timer_Overflow_Mode,
	   Timer_CTC_Mode,
	   Timer_CTC_WAVE_OP,
	   Timer_Fast_PWM_Mode,
	   Timer_PhaceCorrect_PWM_Mode,
   }Timer_Mode;
   
   typedef enum
   {
	   Timer_NoCLK_Source,
	   Timer_Fcpu,
	   Timer2_OneSec_CLK,
	   Timer_Fcpu_Div8,
	   Timer_Fcpu_Div64,
	   Timer_Fcpu_Div32,
	   Timer_Fcpu_Div128,
	   Timer_Fcpu_Div256,
	   Timer_Fcpu_Div1024,
	   Timer_FallingEdge,
	   Timer_RisingEdge,
   }Timer_Prescaler_CLK;
   
   
   typedef enum
   {
	   Timer_No_Interrupt,
	   Timer_Overflow_Interrupt,
	   Timer_TopCTC_Interrupt,
   }Timer_Interrupt_Source;
   
   typedef enum
   {
	   NON,
	   Toggle_PB_InCM,
	   Clear_PB_InCM,
	   Set_PB_InCM,
	   Inverting_FPWM,
	   NonInverting_FPWM,
	   ClearUp_SetDowen_PCPWM,
	   SetUp_ClearDowen_PCPWM,
   }Wave_Gen_OP;
   
   typedef struct
   {
	   Timer_Selection timer_Number;
	   Timer_Mode timer_mode;
	   Timer_Prescaler_CLK timer_CLK;
	   Timer_Interrupt_Source TimerINT_Source; 
   }TIMER_DATATYPE;
   
   
   
   void TIMER_INTIATE(TIMER_DATATYPE T);
   void TIMER_DELAY(TIMER_DATATYPE t,unsigned char Top_Value);
   void TIMER_WAVEGEN_NPWM(TIMER_DATATYPE t,Wave_Gen_OP wave, unsigned char Top_Value);
   void TIMER_WAVEGEN_FASTPWM(TIMER_DATATYPE t, Wave_Gen_OP wave, unsigned char Top_Value);
   void TIMER_WAVEGEN_PHACECORRECTPWM(TIMER_DATATYPE t, Wave_Gen_OP wave, unsigned char Top_Value);

#endif /* ATMEGA32A_TIMERS_CONFIG_H_ */