/*
 * LCD.c
 *
 * Created: 11/6/2020 3:29:19 PM
 *  Author: ahmedsoliman
 */ 

  #include "ATmega32A_Config.h"
  #include "ATmega32A_DIO_Config.h"
  #include "LCD.h"
  #include <util/delay.h>
  #include <stdlib.h>
  
  
  #define MAX_NWCHAR   (8)
  
    void Send_instruction(unsigned char instruction)
	{
		/* The RS And The RW Must Be RESET When Send Instruction To The LCD */
		RESET_Bit(LCD_CONTROL_REG_OP, RS);
		RESET_Bit(LCD_CONTROL_REG_OP, RW);
		/* Delay of Address Set 60ns minimum This In The Ideal State */
		_delay_ms(1);
		
		/* We WriteTo the LCD InThe Falling Of The Enable Pin */
		/* Set The Enable Pin */
		SET_Bit(LCD_CONTROL_REG_OP, E);
		/* delay for processing PW min 450ns This In The Ideal State */
		_delay_ms(1);
		
		#if (EIGHTBIT_DATA_MODE)
		
		     LCD_DATA_REG_OP = instruction;
			 /* Data set-up time delay  Tdsw = 195 ns This In The Ideal State */
			 _delay_ms(1);
			 /* disable LCD E=0 */
			 RESET_Bit(LCD_CONTROL_REG_OP,E);
			 /* Data Hold delay Th = 10ns This In The Ideal State */
			 _delay_ms(1);
		
	   #else 
	        /* At The First We Send The MSB 4-bit Of The Instruction So We handle If The User Connect LCD in The Upper Or Lower Pin Of The Port */
	        #ifdef LCD_UPPER_DATA_PORT
			       /* Setup The Data Port To hold The Data By Reset the Upper Pin */
				   LCD_DATA_REG_OP &= 0x0F ; 
				   LCD_DATA_REG_OP |= (instruction & 0xF0);
		    #else
			       /* Setup The Data Port To hold The Data By Reset the Lower Pin */
			       LCD_DATA_REG_OP &= 0xF0 ;
			       LCD_DATA_REG_OP |= ((instruction >> 4) & 0x0F);
            #endif
			
			/* Data set-up time delay  Tdsw = 195 ns This In The Ideal State */
			_delay_ms(1);
			
			/* disable LCD E=0 */
			RESET_Bit(LCD_CONTROL_REG_OP,E);
			/* Data Hold delay Th = 10ns */
			_delay_ms(1);
		    
			/* Reconfigure The E Pin To Prepare To Send The Next 4-bit LSB */
		    SET_Bit(LCD_CONTROL_REG_OP, E);
		    /* delay for processing PW min 450ns This In The Ideal State */
		    _delay_ms(1);
			
			#ifdef LCD_UPPER_DATA_PORT
			       /* Setup The Data Port To hold The Data By Reset the Upper Pin */
			       LCD_DATA_REG_OP &= 0x0F ;
			       LCD_DATA_REG_OP |= ((instruction << 4) & 0xF0);
				   #else
				   /* Setup The Data Port To hold The Data By Reset the Lower Pin */
				   LCD_DATA_REG_OP &= 0xF0 ;
		     	   LCD_DATA_REG_OP |= (instruction & 0x0F);  
            #endif
			/* Data set-up time delay  Tdsw = 195 ns This In The Ideal State */
			_delay_ms(1);
			/* disable LCD E=0 */
			RESET_Bit(LCD_CONTROL_REG_OP,E);
			/* Data Hold delay Th = 10ns This In The Ideal State*/
			_delay_ms(1);
			#endif
	}	
	
	
	
		
    void LCD_init(void)
	{
		#if (EIGHTBIT_DATA_MODE)
		/* Set The Direction Of The 8 Data Bit As Output */
		LCD_DATA_REG_DIR = 0xFF;
		#else
		#ifdef LCD_UPPER_DATA_PORT
		/* Set The Direction Of The Higher 4 Data Bit As Output */
		LCD_DATA_REG_DIR |= 0xF0;
		#else
		/* Set The Direction Of The Lower 4 Data Bit As Output */
		LCD_DATA_REG_DIR |= 0x0F;
		#endif
		/* Setup The Control Pin As A Output Pin */
		LCD_CONTROL_REG_DIR |= (1 << E) | (1 << RS) | (1 << RW);
		
		
			 /* Set LCD to Use 4 bits Op */
			 Send_instruction(RETURN_HOME);
	   #endif
	   Send_instruction(FUNCTION_SET);
	   Send_instruction(DISPLAY_ON);
	   Send_instruction(CLEAR_DISPALY);
		
	}
	
	
			
    void LCD_Clear(void)
	{
		/* Clear Instruction */
		Send_instruction(CLEAR_DISPALY);
	}	
	
	
	
		
    void LCD_DisplayChar(unsigned char Data)
	{
		/* The RS  Must Be RESET and The RW must be SET When Send Data To The LCD */
		SET_Bit(LCD_CONTROL_REG_OP, RS);
		RESET_Bit(LCD_CONTROL_REG_OP, RW);
		/* Delay of Address Set 60ns minimum This In The Ideal State */
		_delay_ms(1);
		/* We WriteTo the LCD InThe Falling Of The Enable Pin */
		/* Set The Enable Pin */
		SET_Bit(LCD_CONTROL_REG_OP, E);
		/* delay for processing PW min 450ns This In The Ideal State */
		_delay_ms(1);
		
		#if (EIGHTBIT_DATA_MODE)
		
		LCD_DATA_REG_OP = Data;
		/* Data set-up time delay  Tdsw = 195 ns This In The Ideal State */
		_delay_ms(1);
		/* disable LCD E=0 */
		RESET_Bit(LCD_CONTROL_REG_OP,E);
		/* Data Hold delay Th = 10ns This In The Ideal State */
		_delay_ms(1);
		
		#else
		/* At The First We Send The MSB 4-bit Of The Instruction So We handle If The User Connect LCD in The Upper Or Lower Pin Of The Port */
		#ifdef LCD_UPPER_DATA_PORT
		/* Setup The Data Port To hold The Data By Reset the Upper Pin */
		LCD_DATA_REG_OP &= 0x0F ;
		LCD_DATA_REG_OP |= (Data & 0xF0);
		#else
		/* Setup The Data Port To hold The Data By Reset the Lower Pin */
		LCD_DATA_REG_OP &= 0xF0 ;
		LCD_DATA_REG_OP |= ((Data >> 4) & 0x0F);
		#endif
		
		/* Data set-up time delay  Tdsw = 195 ns This In The Ideal State */
		_delay_ms(1);
		
		/* disable LCD E=0 */
		RESET_Bit(LCD_CONTROL_REG_OP,E);
		/* Data Hold delay Th = 10ns */
		_delay_ms(1);
		
		/* Reconfigure The E Pin To Prepare To Send The Next 4-bit LSB */
		SET_Bit(LCD_CONTROL_REG_OP, E);
		/* delay for processing PW min 450ns This In The Ideal State */
		_delay_ms(1);
		
		#ifdef LCD_UPPER_DATA_PORT
		/* Setup The Data Port To hold The Data By Reset the Upper Pin */
		LCD_DATA_REG_OP &= 0x0F ;
		LCD_DATA_REG_OP |= ((Data << 4) & 0xF0);
		#else
		/* Setup The Data Port To hold The Data By Reset the Lower Pin */
		LCD_DATA_REG_OP &= 0xF0 ;
		LCD_DATA_REG_OP |= (Data & 0x0F);
		#endif
		/* Data set-up time delay  Tdsw = 195 ns This In The Ideal State */
		_delay_ms(1);
		/* disable LCD E=0 */
		RESET_Bit(LCD_CONTROL_REG_OP,E);
		/* Data Hold delay Th = 10ns This In The Ideal State*/
		_delay_ms(1);
		#endif
	}	
	
	
		
    void LCD_DisplayString(char * ptr)
	{
		while(*ptr != '\0')
		{
			LCD_DisplayChar(*ptr);
			ptr++;
		}
	}
	
	
			
    void LCD_Select_RowCol(unsigned char Row , unsigned char col)
	{
		char ADDRESS = 0x00;
		switch(Row)
		{
			case 0: 
			       /* When Writing To LCD 1st Col The Base Address is 0x00 */
			       ADDRESS= col | LCD_1ST_ROW;
			       break;
			case 1:
			      /* When Writing To LCD 1st Col The Base Address is 0x40 */
			      ADDRESS= col | LCD_2ND_ROW;
			      break;
			case 2:
			       /* When Writing To LCD 1st Col The Base Address is 0x10 */
			       ADDRESS= col | LCD_3RD_ROW;
			       break;
			case 3:
			       /* When Writing To LCD 1st Col The Base Address is 0x50 */
			       ADDRESS= col | LCD_4TH_ROW;
			       break;
		}
		/* Form The Data Sheet it must Set The Bit 7 Before Send The Address */
		(ADDRESS) |= (1<<7);
		Send_instruction(ADDRESS);
	}
			
    void LCD_DisplayInt(long int data)
	{
		/* String to hold the ASCI result */
		char Result[21];
		/* 10 for decimal */
		utoa(data,Result,10);
		/* Display The Result */
		LCD_DisplayString(Result);
	} 
	
	void LCD_StoreCustomchar(unsigned char*pattern,unsigned char CGRAM_index)
	{
		char ADDRESS = 0x00;
		char index;
		if (CGRAM_index < MAX_NWCHAR)
		{
			/* We Need To Move AC To Make it Point To The CGRAM at The Address Config By The User */
			ADDRESS = CGRAM_index;
			ADDRESS |= CGRAM_CONST; /* To Set The Bit Number 6 To point On The CGRAM Address Get From Datasheet */
			Send_instruction(ADDRESS);
			/* Note That The AC increase Automatically After Write On The Address It Point To */
			for (index = 0; index < 8; index++)
			{
				LCD_DisplayChar(pattern[index]);
			}
			/* We Need To Return The AC to point To The DDRAM */
			Send_instruction(RETURN_HOME);
		}
	}   
	
	
	