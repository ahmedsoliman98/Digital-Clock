/*
 *
 * @file <BCD_7Segment.h>
 * @brief <This is a Header File for the seven segment connecting to the BCD driver Which Eanbles User to Control an seven segment Write even it Common Cathod Or Common Ando>
 *
 * @APIS
 *					  sevenSegment_setup()		< Setup driver Port and Pin via MCAL >
 *						returns   void 
 *						Takes	  SevenSegment
 *					  sevenSegment_write()		<it defines haw and which write on the seven segment>
 *                      return  void
 *                      Takes              SevenSegment         ,      unsigned char
 *
 * @authors <ahmedsoliman>
 * @date <7/18/2020 3:56:23 PM>
 *
 */

#ifndef BCD_7SEGMENT_H_
#define BCD_7SEGMENT_H_


  
    /*
	 *
	 * @brief <SevenSegment>
	 *		  GPIO *		LedPort < Should assign Port Address to it >
	 *        pinNumber     APin  <should assign pin A Address to it >
	 *        pinNumber     Bpin  <should assign pin B Address to it >
	 *        pinNumber     Cpin  <should assign pin C Address to it >
	 *        pinNumber     Dpin  <should assign pin D Address to it >
	 */  
   typedef struct
   {
	   GPIO * drivPORT;
	   pinNumber Apin;
	   pinNumber Bpin;
	   pinNumber Cpin;
	   pinNumber Dpin;
	   
   }SevenSegment;


    /*
	 *
	 * @brief <sevenSegment_setup>
	 *
	 * <this function is to setup seven segment driver with the microcontroller to be able to define it port and pin and it is input or output>
	 *
	 * @const SevenSegment  <struct>       <Should Pass a predefined SevenSegment Variable which has the Internal Values Filled >
	 *
	 *
	 * @return < void>
	 */
    void sevenSegment_setup(SevenSegment pins);
	
	
	 /*
	 *
	 * @brief <sevenSegment_write>
	 *
	 * <this function is responcible to get the output on the seven segment by output the BCD to the driver >
	 *
	 * @const segDriver_dataType  <struct>       <Should Pass a predefined segDriver_dataType Variable which has the Internal Values Filled >
	 *         number          <unsigned char>   <should pass the number or the charavhter to write on the seven segment>
	 *
	 * @return < void>
	 */
  void sevenSegment_write(SevenSegment pins, unsigned char number);



#endif /* BCD_7SEGMENT_H_ */