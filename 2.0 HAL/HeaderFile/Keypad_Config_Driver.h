
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
 *                      Takes         void
 * 	
 * @authors <ahmedsoliman>
 * @date <11/1/2020 12:45:55 PM>
 *
 */



#ifndef KEYPAD_CONFIG_DRIVER_H_
#define KEYPAD_CONFIG_DRIVER_H_


  /* Define The columns and Rows used in the Array */
   typedef enum
   {
	    COL1 ,
		COL2 ,
		COL3 ,
		COL4 ,
   }MATRIX_COL;		
   
   typedef enum
   {
	   ROW1 ,
	   ROW2 ,
	   ROW3 ,
	   ROW4 ,
   }MATRIX_ROW;
   
   /* HW connection */
   typedef struct
   {
	   GPIO *keypadREG_Port;
	   pinNumber PINRW1;
	   pinNumber PINRW2;
	   pinNumber PINRW3;
	   pinNumber PINRW4;
	   pinNumber PINCL1;
	   pinNumber PINCL2;
	   pinNumber PINCL3;
	   pinNumber PINCL4;
   }KEYPAD_PIN;
   
   /* we make this variable as global to allow the user to change it is value */
   #define  ROW   4
   #define  COL   4
   extern unsigned  char KeyData[COL][ROW];
							 
	void keypad_Intiat (KEYPAD_PIN keypad);
	unsigned char keypad_Read(KEYPAD_PIN keypad);


#endif /* KEYPAD_CONFIG_DRIVER_H_ */