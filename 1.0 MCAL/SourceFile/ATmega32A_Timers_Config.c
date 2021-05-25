/*
 * ATmega32A_Timers_Config.c
 *
 * Created: 1/1/2021 10:12:47 PM
 *  Author: ahmedsoliman
 */ 


 /* IMP NOTE !! IT MUST IF WE USE THE DELAY BY THE CTC MODE WRITE THE FUNCTION OF TIMER_DELAY DIRECT AFTER TIMER_ITIATE */
 
 #include "ATmega32A_Config.h"
 #include "ATmega32A_DIO_Config.h"
 #include "ATmega32A_Timers_Config.h"
 
 
    void TIMER_INTIATE(TIMER_DATATYPE T)
	{
		/* make temporary Register To Hold The Initiate Value */
		unsigned char TCCR_Temp = 0x00;
		unsigned char TIMASK_Temp = 0x00;
		
		/* Set up the Timer The User Select */
		switch(T.timer_Number)
		{
			case Timer0:
				/* Set Up The Timer Mode By bit WGM01 WGM00 In The TCCR */
				switch (T.timer_mode)
				{
					case Timer_Overflow_Mode :
						 /* It Is The Normal Mode So No Change Will happened On The Bit */
				 
					break;
					case Timer_CTC_Mode:
						 SET_Bit(TCCR_Temp,WGM01);
						 RESET_Bit(TCCR_Temp, WGM00);
					break;
					case Timer_Fast_PWM_Mode:
						 SET_Bit(TCCR_Temp,WGM00);
						 SET_Bit(TCCR_Temp,WGM01);
					break;
					case Timer_PhaceCorrect_PWM_Mode:
						 SET_Bit(TCCR_Temp,WGM00);
						 RESET_Bit(TCCR_Temp, WGM01);
					break;
					default:
					break;
				}
		
				/* Set Up The Timer Clock Frequency By The Bit CS00, CS01 , CS02 In The TCCR */
				switch(T.timer_CLK)
				{
					case Timer_NoCLK_Source:
						/* It SI The Default State At All Bit Equal 0 */
						/* In This Case The Timer Gets Its Clock From External Device */
					break;
					case Timer_Fcpu:
						 SET_Bit(TCCR_Temp,CS00);
						 RESET_Bit(TCCR_Temp,CS01);
						 RESET_Bit(TCCR_Temp,CS02);
					break;
					case Timer_Fcpu_Div8:
						 RESET_Bit(TCCR_Temp,CS00);
						 SET_Bit(TCCR_Temp,CS01);
						 RESET_Bit(TCCR_Temp,CS02);
					break;
					case Timer_Fcpu_Div64:
						 SET_Bit(TCCR_Temp,CS00);
						 SET_Bit(TCCR_Temp,CS01);
						 RESET_Bit(TCCR_Temp,CS02);
					break;
					case Timer_Fcpu_Div256:
						 RESET_Bit(TCCR_Temp,CS00);
						 RESET_Bit(TCCR_Temp,CS01);
						 SET_Bit(TCCR_Temp,CS02);
					break;
					case Timer_Fcpu_Div1024:
						 SET_Bit(TCCR_Temp,CS00);
						 RESET_Bit(TCCR_Temp,CS01);
						 SET_Bit(TCCR_Temp,CS02);
					break;
					case Timer_FallingEdge:
						 RESET_Bit(TCCR_Temp,CS00);
						 SET_Bit(TCCR_Temp,CS01);
						 SET_Bit(TCCR_Temp,CS02);
					break;
					case Timer_RisingEdge:
						 SET_Bit(TCCR_Temp,CS00);
						 SET_Bit(TCCR_Temp,CS01);
						 SET_Bit(TCCR_Temp,CS02);
				   break;
				   default:
				   break;
				}
		
				/* Set Up The Interrupt Source By Set The Bit referee To The That Source InThe TIMASK */
				switch(T.TimerINT_Source)
				{
					case Timer_Overflow_Interrupt:
						 /* This Interrupt happened when the TCNT reach its Max then return to zero again */ 
						 SET_Bit(TIMSK,TOIE0);
					break;
					case Timer_TopCTC_Interrupt:
						 /* This Interrupt happened When The TCNT Reach The Value Equal The Value OnThe OCR and Return To Zero */
						 SET_Bit(TIMSK,OCIE0);
					break;
					default:
					break;
			
				}
				TCCR0 = TCCR_Temp;
		break;
		case Timer2:
		     /* Set Up The Timer Mode By bit WGM21 WGM20 In The TCCR */
		     switch (T.timer_mode)
		     {
			     case Timer_Overflow_Mode :
			     /* It Is The Normal Mode So No Change Will happened On The Bit */
			     
			     break;
			     case Timer_CTC_Mode:
			     SET_Bit(TCCR_Temp,WGM21);
			     RESET_Bit(TCCR_Temp, WGM20);
			     break;
			     case Timer_Fast_PWM_Mode:
			     SET_Bit(TCCR_Temp,WGM20);
			     SET_Bit(TCCR_Temp,WGM21);
			     break;
			     case Timer_PhaceCorrect_PWM_Mode:
			     SET_Bit(TCCR_Temp,WGM20);
			     RESET_Bit(TCCR_Temp, WGM21);
			     break;
			     default:
			     break;
		     }
		     
		     /* Set Up The Timer Clock Frequency By The Bit CS20, CS21 , CS22 In The TCCR2 */
		     switch(T.timer_CLK)
		     {
			     case Timer_NoCLK_Source:
			     /* It SI The Default State At All Bit Equal 0 */
			     break;
			     case Timer_Fcpu:
			     SET_Bit(TCCR_Temp,CS20);
			     RESET_Bit(TCCR_Temp,CS21);
			     RESET_Bit(TCCR_Temp,CS22);
			     break;
				 case Timer2_OneSec_CLK:
				      /* In This Case To Get The Clock Exactly At One Sec We Used An External Clock With Value 32768Hz At Timer 2 Only Connect To the Pin 6 & 7 at Port C 
					   * Set the Pin AS2 At The Register ASSR To Make The Clock Source From The External Crystal 
					   *  Prescaler Value Will Used is 128 So 
					   */
					  ASSR = 0x08;
					  SET_Bit(TCCR_Temp,CS20);
					  RESET_Bit(TCCR_Temp,CS21);
					  SET_Bit(TCCR_Temp,CS22);
				 break;
			     case Timer_Fcpu_Div8:
			     RESET_Bit(TCCR_Temp,CS20);
			     SET_Bit(TCCR_Temp,CS21);
			     RESET_Bit(TCCR_Temp,CS22);
			     break;
			     case Timer_Fcpu_Div32:
			     SET_Bit(TCCR_Temp,CS20);
			     SET_Bit(TCCR_Temp,CS21);
			     RESET_Bit(TCCR_Temp,CS22);
			     break;
			     case Timer_Fcpu_Div64:
			     RESET_Bit(TCCR_Temp,CS20);
			     RESET_Bit(TCCR_Temp,CS21);
			     SET_Bit(TCCR_Temp,CS22);
			     break;
			     case Timer_Fcpu_Div128:
			     SET_Bit(TCCR_Temp,CS20);
			     RESET_Bit(TCCR_Temp,CS21);
			     SET_Bit(TCCR_Temp,CS22);
			     break;
			     case Timer_Fcpu_Div256:
			     RESET_Bit(TCCR_Temp,CS20);
			     SET_Bit(TCCR_Temp,CS21);
			     SET_Bit(TCCR_Temp,CS22);
			     break;
			     case Timer_Fcpu_Div1024:
			     SET_Bit(TCCR_Temp,CS20);
			     SET_Bit(TCCR_Temp,CS21);
			     SET_Bit(TCCR_Temp,CS22);
			     break;
			     default:
				 /* If The User Select Else This Cases Handle An Error Massage */
			     break;
		     }
		     
		     /* Set Up The Interrupt Source By Set The Bit referee To The That Source InThe TIMASK */
		     switch(T.TimerINT_Source)
		     {
			     case Timer_Overflow_Interrupt:
			     /* This Interrupt happened when the TCNT reach its Max then return to zero again */
			     SET_Bit(TIMSK,TOIE2);
			     break;
			     case Timer_TopCTC_Interrupt:
			     /* This Interrupt happened When The TCNT Reach The Value Equal The Value OnThe OCR and Return To Zero */
			     SET_Bit(TIMSK,OCIE2);
			     break;
			     default:
			     break;
			     
		     }
			 TCCR2 = TCCR_Temp;
			 
		     break; /* The End Of The case Timer2 In the Big Switch */
			 default:
			 break;
		}
			
		
		/* Set The I Bit In The Statues Register To Enable The General Interrupt */
		SET_Bit(SREG, 7);
	}					 
		
		

		

	
		
    void TIMER_DELAY(TIMER_DATATYPE t, unsigned char Top_Value)
	{
		switch(t.timer_Number)
		{
			case Timer0: 
			     OCR0 = Top_Value;
			break;
			case Timer2:
			     OCR2 = Top_Value;
			break;
			default:
			break;
		}
	}
	
	
	void TIMER_WAVEGEN_NPWM(TIMER_DATATYPE t, Wave_Gen_OP wave, unsigned char Top_Value)
	{
		switch (t.timer_Number)
		{
			case Timer0 :
				/* Set The Value Of OCR0 That will Wave Change after it */
				OCR0 = Top_Value;
				/* at the first we set up the pin of the wave output in the Mc as output state */
				DIO_pinConfiguration(GPIOB,PIN3, Output);
				/* Switch on the form we want the signal get out after each compare match */
				switch(wave)
				{
					case NON:
					/* This is The Normal State when the COM00 and COM01 is cleared */
					break;
					case Toggle_PB_InCM:
						 RESET_Bit(TCCR0, COM01);
						 SET_Bit(TCCR0, COM00);
					break;
					case Clear_PB_InCM:
						 SET_Bit(TCCR0, COM01);
						 RESET_Bit(TCCR0, COM00);
					break;
					case Set_PB_InCM:
						SET_Bit(TCCR0, COM01);
						SET_Bit(TCCR0, COM00);
						break;
					break;
					default:
					/* Handling an error massage if the user send an incorrect wave acting state for that mode */
					break;
				}
			break;
			case Timer2: 
				    /* Set The Value Of OCR2 That will Wave Change after it */
					OCR2 = Top_Value;
					/* at the first we set up the pin of the wave output in the Mc as output state OC2 pin */
					DIO_pinConfiguration(GPIOD,PIN7, Output);
					/* Switch on the form we want the signal get out after each compare match */
					switch(wave)
					{
						case NON:
						/* This is The Normal State when the COM00 and COM01 is cleared */
						break;
						case Toggle_PB_InCM:
							 RESET_Bit(TCCR2, COM21);
							 SET_Bit(TCCR2, COM20);
						break;
						case Clear_PB_InCM:
							 SET_Bit(TCCR2, COM21);
							 RESET_Bit(TCCR2, COM20);
						break;
						case Set_PB_InCM:
							SET_Bit(TCCR2, COM21);
							SET_Bit(TCCR2, COM20);
							break;
						break;
						default:
						/* Handling an error massage if the user send an incorrect wave acting state for that mode */
						break;
					}
			break;
			default:
			break;
		}
	
	}	
	void TIMER_WAVEGEN_FASTPWM(TIMER_DATATYPE t, Wave_Gen_OP wave, unsigned char Top_Value)
	{
		switch(t.timer_Number)
		{
			case Timer0:
			     /* Set The Value Of OCR0 That will Define the top of the TCCR0 to change wave state when it reach
				  *
				  * Note: That this value decide the value of the duty cycle (the ratio of ON time ) by Top_Value/ 256 
				  * if the user choose the inverting mode this result become the OFF time ratio 
				  * and if decide non inverting mode this ratio become the ON time ratio 
				  */
				OCR0 = Top_Value;
		
				/* at the first we set up the pin of the wave output in the Mc as output state */
				DIO_pinConfiguration(GPIOB,PIN3, Output);
		
				/* Note 
					* the case of COM00 , COM01 is decimal 1 is reserved ( Not use ) 
					*/
				switch(wave)
				{
					case NON:
							/* This IS the normal mode OC0 IS disconnected when the COM00 and COM01 is cleared  */
				 
					case NonInverting_FPWM:
							/* This mode when the signal on the OC0 is cleared when happen Compare match with the value on OCR0 and Set when TCCR0  reach bottom (Overflow) */
							RESET_Bit(TCCR0, COM00);
							SET_Bit(TCCR0, COM01);
					break;
					case Inverting_FPWM:
							/* This mode when the signal on the OC0 is set when happen Compare match with the value on OCR0 and Cleared when TCCR0  reach bottom (Overflow) */
							SET_Bit(TCCR0, COM00);
							SET_Bit(TCCR0, COM01);
					break;
					default:
							/* Handling an error massage if the user send an incorrect wave acting state for that mode */
					break;
				}
			break;
			case Timer2:
			     /* Set The Value Of OCR2 That will Define the top of the TCCR2 to change wave state when it reach
				  *
				  * Note: That this value decide the value of the duty cycle (the ratio of ON time ) by Top_Value/ 256 
				  * if the user choose the inverting mode this result become the OFF time ratio 
				  * and if decide non inverting mode this ratio become the ON time ratio 
				  */
				OCR2 = Top_Value;
		
				/* at the first we set up the pin of the wave output in the Mc as output state */
				DIO_pinConfiguration(GPIOD,PIN7, Output);
		
				/* Note 
					* the case of COM20 , COM21 is decimal 1 is reserved ( Not use ) 
					*/
				switch(wave)
				{
					case NON:
							/* This IS the normal mode OC0 IS disconnected when the COM00 and COM01 is cleared  */
				 
					case NonInverting_FPWM:
							/* This mode when the signal on the OC0 is cleared when happen Compare match with the value on OCR0 and Set when TCCR0  reach bottom (Overflow) */
							RESET_Bit(TCCR2, COM20);
							SET_Bit(TCCR2, COM21);
					break;
					case Inverting_FPWM:
							/* This mode when the signal on the OC0 is set when happen Compare match with the value on OCR0 and Cleared when TCCR0  reach bottom (Overflow) */
							SET_Bit(TCCR2, COM20);
							SET_Bit(TCCR2, COM21);
					break;
					default:
							/* Handling an error massage if the user send an incorrect wave acting state for that mode */
					break;
				}
			break;
			default :
			break;
		}
		
		
	}	
	
	
	void TIMER_WAVEGEN_PHACECORRECTPWM(TIMER_DATATYPE t, Wave_Gen_OP wave, unsigned char Top_Value)
	{
		switch(t.timer_Number)
		{
			case Timer0:
				/* Set The Value Of OCR0 That will Define the top of the TCCR0 to change wave state when it reach
				 *
				 * Note: That this value decide the value of the duty cycle (the ratio of ON time ) by Top_Value/ 256 
				 * if the user choose Set OC0 at up counting and Clear at down counting  mode this result become the OFF time ratio 
				 * and if decide Clear OC0 at up counting and Set at down counting  mode this ratio become the ON time ratio 
				 */
				OCR0 = Top_Value;
		
				/* at the first we set up the pin of the wave output in the Mc as output state */
				DIO_pinConfiguration(GPIOB,PIN3, Output);
		
				/* Note 
				 * the case of COM00 , COM01 is decimal 1 is reserved ( Not use ) 
				 */
				switch(wave)
				{
					case NON:
					/* This IS the normal mode OC0 IS disconnected when the COM00 and COM01 is cleared  */
			
					case ClearUp_SetDowen_PCPWM:
					/* This mode operation is the signal on the OC0 is clear when happen Compare match with the value on OCR0 at the up counting of the TCNT0 and Set when happen compare match at the down counting of the TCNT0 */
					RESET_Bit(TCCR0, COM00);
					SET_Bit(TCCR0, COM01);
					break;
					case SetUp_ClearDowen_PCPWM:
					/* This mode operation is the signal on the OC0 is set when happen Compare match with the value on OCR0 at the up counting of the TCNT0 and clear when happen compare match at the down counting of the TCNT0 */
					SET_Bit(TCCR0, COM00);
					SET_Bit(TCCR0, COM01);
					break;
					default:
					/* Handling an error massage if the user send an incorrect wave acting state for that mode */
					break;
				}
			break;
			case Timer2:
			    /* Set The Value Of OCR0 That will Define the top of the TCCR2 to change wave state when it reach
				 *
				 * Note: That this value decide the value of the duty cycle (the ratio of ON time ) by Top_Value/ 256 
				 * if the user choose Set OC2 at up counting and Clear at down counting  mode this result become the OFF time ratio 
				 * and if decide Clear OC2 at up counting and Set at down counting  mode this ratio become the ON time ratio 
				 */
				OCR2 = Top_Value;
		
				/* at the first we set up the pin of the wave output in the Mc as output state */
				DIO_pinConfiguration(GPIOD,PIN7, Output);
		
				/* Note 
				 * the case of COM20 , COM21 is decimal 1 is reserved ( Not use ) 
				 */
				switch(wave)
				{
					case NON:
					/* This IS the normal mode OC2 IS disconnected when the COM20 and COM21 is cleared  */
			
					case ClearUp_SetDowen_PCPWM:
					/* This mode operation is the signal on the OC2 is clear when happen Compare match with the value on OCR2 at the up counting of the TCNT0 and Set when happen compare match at the down counting of the TCNT0 */
					RESET_Bit(TCCR2, COM20);
					SET_Bit(TCCR2, COM21);
					break;
					case SetUp_ClearDowen_PCPWM:
					/* This mode operation is the signal on the OC2 is set when happen Compare match with the value on OCR2 at the up counting of the TCNT0 and clear when happen compare match at the down counting of the TCNT0 */
					SET_Bit(TCCR2, COM20);
					SET_Bit(TCCR2, COM21);
					break;
					default:
					/* Handling an error massage if the user send an incorrect wave acting state for that mode */
					break;
				}
			break;
			default: 
			
			break;
		}		
	}	
			
		
	