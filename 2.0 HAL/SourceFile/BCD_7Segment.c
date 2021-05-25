/*
 * BCD_7Segment.c
 *
 * Created: 7/18/2020 3:56:51 PM
 *  Author: ahmedsoliman
 */ 

  #include <ATmega32A_Config.h>
  #include <ATmega32A_DIO_Config.h>
  #include <StandardDataType.h>
  #include <BCD_7Segment.h>
  
  /* BCD Code Define The Number From 0 To 9 So it 4 bit Number each one Of The A,B,C,D represent One Bit */
  /* This Number Define To read Each bit From The Four Bit Of The Number */
  #define bit_0_num (0)
  #define bit_1_num (1)
  #define bit_2_num (2)
  #define bit_3_num (3)
  
  
  void sevenSegment_setup(SevenSegment pins)
  {
	  /* define The Pins Of The BCD IC As Output Pins */
	  DIO_pinConfiguration(pins.drivPORT,pins.Apin,Output);
	  DIO_pinConfiguration(pins.drivPORT,pins.Bpin,Output);
	  DIO_pinConfiguration(pins.drivPORT,pins.Cpin,Output);
	  DIO_pinConfiguration(pins.drivPORT,pins.Dpin,Output);
  }
  
  
  void sevenSegment_write(SevenSegment pins, unsigned char number)
  {
	  /* read The Bit Zero from The Number And represent By The Pin A */
	  DIO_pinWrite(pins.drivPORT,pins.Apin, (READ_Bit(number,bit_0_num)));
	  /* read The Bit 1 from The Number And represent By The Pin B */
	  DIO_pinWrite(pins.drivPORT,pins.Bpin, (READ_Bit(number,bit_1_num)));
	  /* read The Bit 2 from The Number And represent By The Pin C */
	  DIO_pinWrite(pins.drivPORT,pins.Cpin, (READ_Bit(number,bit_2_num)));
	  /* read The Bit 3 from The Number And represent By The Pin D */
	  DIO_pinWrite(pins.drivPORT,pins.Dpin, (READ_Bit(number,bit_3_num)));
  }