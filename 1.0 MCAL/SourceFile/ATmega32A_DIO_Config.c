/*
 * ATmega32A_DIO_Config.c
 *
 * Created: 7/10/2020 4:10:05 PM
 *  Author: ahmedsoliman
 */ 

#include <ATmega32A_Config.h>
#include <ATmega32A_DIO_Config.h>



#define MAX_uint8_VALUE		(255)
#define MIN_uint8_VALUE      (0)
/* We Need This Value To And TO The Port Value To Get Read */
#define ANDINGV_to_readPORT (0xFF)


static void DIO_ErrorIndication(Errortype Type)
{
	switch(Type)
	{
		case invalidArgument:
		default:
		break;
	}
}





/***************************************************************** PIN Function ****************************************************************************************************************************************************/





void DIO_pinConfiguration(GPIO * pinC, pinNumber pin_num, pinMode pin_M)
{
	switch (pin_M)
	{
		case InputPullup:
		/* In This Case We Make The Pin Input By Get Low in The DDR And Make It Default State (idle) HIgh By Set The Port */
		RESET_Bit(pinC -> DDR, pin_num);
		SET_Bit(pinC -> PORT, pin_num);
		break;
		case InputFloat:
		/* In This Case We Make The Pin Input By Get Low in The DDR And Make It Default State (idle) LOW By RESET The Port And Make A Pull down Resistance  */
		RESET_Bit(pinC -> DDR,pin_num);
		RESET_Bit(pinC -> PORT,pin_num);
		break;
		case Output:
		/* In This Case We Make The Pin Output By  SET The DDR And Make It Default State (idle) LOW By Set The Port TO Make It reverse Connection Sink Source to Avoid Error Value When The Number Of The Output Increace */
		SET_Bit(pinC -> DDR, pin_num);
		RESET_Bit(pinC -> PORT,pin_num);
		break;
		default:
		/* In This Case The User Send Error Value On The Function So It Call The Error Function To Execute An error Handle For THis Case */
		DIO_ErrorIndication(invalidArgument);
		break;
	}
}




 void DIO_pinWrite(GPIO * pinC, pinNumber pin_num, DigitalValue state)
 {
	 switch(state)
	 {
		 case HIGH:
		 /* The Pin Get Output High State */
		 SET_Bit(pinC -> PORT, pin_num);
		 break;
		 case LOW:
		 /* The Pin Get Output Low State */
		 RESET_Bit(pinC -> PORT, pin_num);
		 break;
		 default:
		 /* In This Case The User Send Error Value On The Function So It Call The Error Function To Execute An error Handle For THis Case */
		 DIO_ErrorIndication(invalidArgument);
		 break;
	 }
 }
 
 
 
 DigitalValue DIO_pinRead(GPIO * pinC, pinNumber pin_num)
 {
	 /* This Function Return The Current State Of The Pin by Use The READ_Bit Definition In The Macro Header */
	 return (READ_Bit(pinC -> PIN, pin_num));
 }
 
 
 
 
 
 /****************************************************************************** Port Functions ****************************************************************************************************************************************************************/
 
 
 
 
 
 
  void DIO_portConfiguration(GPIO * portC, uint8 portValue)
  {
	  /* We Must Check That THe Value Of The configuration Of The Port Does Not exceed The 8 bit (0 <-> 255) */
	  
	  if (portValue <= MAX_uint8_VALUE && portValue >= MIN_uint8_VALUE)
	  {
		  /* The Value On The 8 bit DDR To Define Each Pin From The 8 Pins Of The Port As input Or Output */
		  /* equal the port to the 0xFF to get the output */
		  portC->DDR = portValue;
	  }
	  else
	  {
		  //DIO_ErrorIndication()
	  }
  } 




 void DIO_portWrite(GPIO * portC, uint8 portValue)
 {
	  /* We Must Check That THe Value Of The configuration Of The Port Does Not exceed The 8 bit (0 <-> 255) */
	 if (portValue <= MAX_uint8_VALUE && portValue >= MIN_uint8_VALUE)
	 {
		 /* Get Out The 8bit Value On The * Pins Of The Port */
		 portC->PORT = portValue;
	 }
	 else if (portValue > MAX_uint8_VALUE)
	 {
		 portC->PORT = 0xFF;
	 }
	 else if (portValue < MIN_uint8_VALUE)
	 {
		 portC->PORT = 0x00;
	 }
 }
 
 
 
 uint8 DIO_portRead(GPIO * portC)
 {
	 /* we And THe Value Of The Port With 1111 1111 And return the result To Get Port State */
	 return (READ_Bit(portC->PORT,ANDINGV_to_readPORT));
	 
 }
 
 
 
 
 
 
 
 
 /*********************************************************************************************************** End Of The DIO Configuration ***********************************************************************************************************************************************************************************/
 