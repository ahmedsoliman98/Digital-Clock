/*
 *
 * @file <Keypad_Config_Driver.h>
 * @brief <This is a Header File for theKeypad Driver Which Eanbles User to use the Keypad Module>
 *
 * PostBuild Driver To Configure the Keypad 
 * @APIS
 *					  Keypad_Setup()		< Setup Keypad port and pin via MCAL >
 *						returns   void 
 *						Takes	  void 
 *					  Keypad_Read()	 <allow the user to send data from the keypad to Mc>	
 *                      returns   unsigned char
 *
 *                                IMP NOTE : THAT ALWAYS THE DATA RETURN IS IN CHAR ASSCI FORM SO IF YOU WANT TO USED AS INTEGR MUST -48 FROM THE RETURNED VALUE 
 *                                IF YOU JUST DISPLAY ON THE SCREEN IT DISPLY AS A CHAR DIRECT NO NEED TO CONVERT 
 *
 *                      Takes         void
 *                    DataCheck()    < Get The Value Of Data  by get The Raw To Matched With The Column To Get The Data From The Matrix >
 *                      return    The Number of the raw
 *                      Takes         MATRIX_COL ,  Keypad_PIN keypad
 * 	
 * @authors <ahmedsoliman>
 * @date <11/1/2020 12:45:55 PM>
 *
 */

 #include "ATmega32A_DIO_Config.h"
 #include "ATmega32A_DIO_Config.h"
 #include "StandardDataType.h"
 #include "Keypad_Config_Driver.h"
 #include <util/delay.h>
 
 
 
 /* this Value of the delay is chosen by Experiment */
 #define DELAY_FOR_BOUNCING (45)
 
 /* Its Important to make stable in the system and make sure that the Pin is return to Zero */
 #define DELAY_FOR_PINCONFIG (5)
 

	
	
	
	 
 /* This is an static function to check the value of the current data get from the keypad key */
 static unsigned char CheckData(KEYPAD_PIN keypad,MATRIX_COL col )
 {
	 /* Each time We Check If The User Is Push The button by Check the value get on The Raw Pin if HIGH the button pushed else we check the other Raw */ 
	 if (DIO_pinRead(keypad.keypadREG_Port,keypad.PINRW1))
	 {
		 /* wait Time Delay and recheck the condition of the Raw pin to Make Sure The Is Not An Noise */
		 _delay_ms(DELAY_FOR_BOUNCING);
		 if (DIO_pinRead(keypad.keypadREG_Port,keypad.PINRW1))
		 {
			 /* We Match the Value Get From The REad Function Of The Number Of The Column And The Number Of The Raw We Get Here To Get The Value From The Matrix */
			return(KeyData[ROW1][col]);
		 }			 
	 }
	 else if (DIO_pinRead(keypad.keypadREG_Port,keypad.PINRW2))
	 {
		 _delay_ms(DELAY_FOR_BOUNCING);
		 if (DIO_pinRead(keypad.keypadREG_Port,keypad.PINRW2))
		 {
			  return(KeyData[ROW2][col]);
		 }
	 }
	 else if (DIO_pinRead(keypad.keypadREG_Port,keypad.PINRW3))
	 {
		 _delay_ms(DELAY_FOR_BOUNCING);
		 if (DIO_pinRead(keypad.keypadREG_Port,keypad.PINRW3))
		 {
			return(KeyData[ROW3][col]);
		 }
	 }
	 else if (DIO_pinRead(keypad.keypadREG_Port,keypad.PINRW4))
	 {
		 _delay_ms(DELAY_FOR_BOUNCING);
		 if (DIO_pinRead(keypad.keypadREG_Port,keypad.PINRW4))
		 {
			 return(KeyData[ROW4][col]);
		 }
	 }
	 return 0;
	 
 }
 
 void keypad_Intiat (KEYPAD_PIN keypad)
 {
	 /* Set the all pins of the Keypad input & And Make Its Initial Value Is Float by Set 0 To The Port And Connect a PullDowen Resistance */
	 DIO_portConfiguration(keypad.keypadREG_Port,0x00);
	 DIO_portWrite(keypad.keypadREG_Port,0x00);
 }
 
 
 unsigned char keypad_Read(KEYPAD_PIN keypad)
 {
	 unsigned char DataRead = 0x00;
	 
	 /* CHECK IN THE COLUM 1 */
	 DIO_pinConfiguration(keypad.keypadREG_Port,keypad.PINCL1,Output);
	 DIO_pinWrite(keypad.keypadREG_Port,keypad.PINCL1,HIGH);
     
	 if (CheckData(keypad, COL1))
	 { 
		 DataRead = CheckData(keypad, COL1);
	 }
	 /* Return The Pin as Input Pin To Avoid The Short Circuit Condition if The User Pushed TWO Key At The Same Time */
	 DIO_pinConfiguration(keypad.keypadREG_Port,keypad.PINCL1,InputFloat);
	 _delay_ms(DELAY_FOR_PINCONFIG);
	
	 /* CHECK IN THE COLUM 2 */
	 DIO_pinConfiguration(keypad.keypadREG_Port,keypad.PINCL2,Output);
	 DIO_pinWrite(keypad.keypadREG_Port,keypad.PINCL2,HIGH);
     
	 if (CheckData(keypad, COL2))
	 {
		 DataRead = CheckData(keypad, COL2);
	 }
	 /* Return The Pin as Input Pin To Avoid The Short Circuit Condition if The User Pushed TWO Key At The Same Time */
	 DIO_pinConfiguration(keypad.keypadREG_Port,keypad.PINCL2,InputFloat);
	 _delay_ms(DELAY_FOR_PINCONFIG);
	 
	 /* CHECK IN THE COLUM 3 */
	 DIO_pinConfiguration(keypad.keypadREG_Port,keypad.PINCL3,Output);
	 DIO_pinWrite(keypad.keypadREG_Port,keypad.PINCL3,HIGH);
     
	 if (CheckData(keypad, COL3))
	 { 
		 DataRead = CheckData(keypad, COL3);
	 }
	 /* Return The Pin as Input Pin To Avoid The Short Circuit Condition if The User Pushed TWO Key At The Same Time */
	 DIO_pinConfiguration(keypad.keypadREG_Port,keypad.PINCL3,InputFloat);
	 _delay_ms(DELAY_FOR_PINCONFIG);
	 
	 /* CHECK IN THE COLUM 4 */
	 DIO_pinConfiguration(keypad.keypadREG_Port,keypad.PINCL4,Output);
	 DIO_pinWrite(keypad.keypadREG_Port,keypad.PINCL4,HIGH);
     
	 if (CheckData(keypad, COL4))
	 {
		 DataRead = CheckData(keypad, COL4);
	 }
	 /* Return The Pin as Input Pin To Avoid The Short Circuit Condition if The User Pushed TWO Key At The Same Time */
	 DIO_pinConfiguration(keypad.keypadREG_Port,keypad.PINCL4,InputFloat);
	 _delay_ms(DELAY_FOR_PINCONFIG);
	 return DataRead;
	 
 }