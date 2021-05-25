/*
 * ATmega32A_Interrupt.c
 *
 * Created: 10/5/2020 2:22:41 PM
 *  Author: ahmedsoliman
 */ 
  
  
  #include "ATmega32A_Config.h"
  #include "ATmega32A_DIO_Config.h"
  #include "ATmega32A_Interrupt.h"
  
  
  
  
  
  /* initiate the Pointer Of The Interrupt Function With NULL */
  void (* EXTINT0_ISR) (void) = NULL;
  void (* EXTINT1_ISR) (void) = NULL;
  void (* EXTINT2_ISR) (void) = NULL;
  
  
  

  ISR (INT0_vect,ISR_NESTED_ENABLE)
     {
		 if (EXTINT0_ISR != NULL)
		 {
			 EXTINT0_ISR();
		 }
	 }
	 
	ISR (INT1_vect,ISR_NESTED_ENABLE)
	{
		if (EXTINT1_ISR != NULL)
		{
			EXTINT1_ISR();
		}
	}




	void EXTINT_InterruptInit(EXInterrupt_Source source,ExInterrupt_Modes Mode)
	{
		switch (source)
		{
			case EXINT_INT0 :
				 switch (Mode)
				 {
					 case EXINT_LowLevel :
						  RESET_Bit(MCUCR,ISC00);
						  RESET_Bit(MCUCR,ISC01);
						  break;
					 case EXINT_Toggle :
						  SET_Bit(MCUCR,ISC00);
						  RESET_Bit(MCUCR,ISC01);
						  break;
					 case EXINT_FallingEdge :
						  RESET_Bit(MCUCR,ISC00);
						  SET_Bit(MCUCR,ISC01);
						  break;
					 case EXINT_RisingEdge :
						  SET_Bit(MCUCR,ISC00);
						  SET_Bit(MCUCR,ISC01);
						  break;
				  }
				/* Enable THe InT 0 */
				SET_Bit(GICR,INT0);	
				break;
		  case EXINT_INT1 :
				 switch (Mode)
				 {
					 case EXINT_LowLevel :
						  RESET_Bit(MCUCR,ISC10);
						  RESET_Bit(MCUCR,ISC11);
						  break;
					 case EXINT_Toggle :
						  SET_Bit(MCUCR,ISC11);
						  RESET_Bit(MCUCR,ISC10);
						  break;
					 case EXINT_FallingEdge :
						  RESET_Bit(MCUCR,ISC11);
						  SET_Bit(MCUCR,ISC10);
						  break;
					 case EXINT_RisingEdge :
						  SET_Bit(MCUCR,ISC11);
						  SET_Bit(MCUCR,ISC10);
					break;
				 }
				 /* Enable THe InT 0 */
				 SET_Bit(GICR,INT1);
				 break;
		  case EXINT_INT2 :
			   switch (Mode)
			   {
				   case EXINT_FallingEdge :
						RESET_Bit(MCUCSR,ISC2);
						break;
				   case EXINT_RisingEdge :
						SET_Bit(MCUCSR,ISC2);
						break;
				  case EXINT_LowLevel :
				  case EXINT_Toggle :
				  break;
			   }
			   /* Enable THe InT 0 */
			   SET_Bit(GICR,INT2);
			   break;
		 default:
		      /* Error Handle */
		      break;
		   }
	}