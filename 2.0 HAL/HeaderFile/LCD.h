/*
 * LCD.h
 *
 * Created: 11/6/2020 3:29:05 PM
 *  Author: AhmedSoliman
 *
 ********************* Internal Structure *********************
 *
 * The LCD contains two 8-bit register (Instruction register for storing the instruction) and (Data register that sores the data income )
 * Character Generator ROM CGROM contain the 208 charcters 5 * 8 dot font and 32 characters 5 * 10 dot font 
 * Character Display RAM  DDRAM (In the character Generate RAM the user can rewrite the new character by programing )
 *
 ***************** Operating Mode *****************************
 *
 * The LCD can be operated by two operating mode 
 * 8-bit operating mode   (all eight bus line from DB0 to DB7 are used )
 * 4-bit operating mode  (only used buses from DB4 to DB7 the other remain idle)
 *
 **************** Pin Out Function ***************************
 *
 *                  * Control Pins *
 *  RS            Select 0 for instruction register, 1 for data register 
 *  R/W           Select 0  for write the data from the Mc to LCD and 1 to Read the Data
 *  E             Start Data read or write (Transaction from High to Low Write Mode , Transaction from Low to High Read Mode )
 * 
 *                * Data Pins *
 *  DB0 to DB3    Four lower order bidirectional pins. Used to transmit or receive data between the Mc and the LCD
 *  DB4 to DB7    Four Higher order bidirectional pins. Used to transmit or receive data between the Mc and the LCD
 *  DB7            Can be Used as reflect the state of the Busy Flag BF
 *
 *                * Power Pins *
 *  VSS          Power Supply Pin Should Be Connected To The Ground 
 *  VDD          Power Supply pin Should Be Connected To The Vcc (3.3 ~ 9 )Volt
 *  VO           Power Supply Pin Control The LCD Construct Should Connect To The Variable PullDown Resistance
 *  A            The Anode Terminal of The Back LCD  (Should Be Driven High 3.3V)
 *  K            The Cathode Terminal of The back LCD (GND)  
 *
 ***************** Function Discreption ***********************
 * Busy Flag When The BF is 1 The LCD is Busy Can not Take instruction You Can Check The Busy Flag When The RS = 0, RW = 1 @DB7
 *
 *								Operation Selection
 *				RS				R/W				Operation
 *				0				0			    IR write as an internal operation (display clear, etc.)
 *				0				1				Read busy flag (DB7) and address counter (DB0 to DB6)
 *				1				0				Write To LCD
 *				1				1				Read The Contents of The LCD
 * 
 ******************************** Instructions ************************************
 *
 *	Clear display							Clears entire display and sets DDRAM address 0 in address counter.
 *	Return home				 (1.52ms)		Sets DDRAM address 0 in address counter. Also returns display from being shifted to original position DDRAM contents remain unchanged.
 *	Entry mode set			 (37 us )		Sets cursor move direction	and specifies display shift.
 *	Display on/off control	 (37 us )		Controls LCD , Cursor , Blinking.
 *  Cursor or display shift	 (37 us )		shifts LCD without changing it's Content.
 *  Function set			 (37 us )		Sets interface data length (DL),number of display lines(N),and character font (F).
 *	Read busy flag & address (0 us )	    Reads busy flag (BF)
 *	Set DDRAM address		 (37 us )
 *	Set CGRAM address		 (37 us )
 *
 *
 * 
 */ 


#ifndef LCD_H_
#define LCD_H_

  /* Hardware connection */
  #define RS    PIN0
  #define RW    PIN1
  #define E     PIN2
  
  #define LCD_CONTROL_REG_DIR   GPIOA->DDR
  #define LCD_CONTROL_REG_OP    GPIOA->PORT
  #define LCD_CONTROL_REG_IP    GPIOA->PIN
  
  #define LCD_DATA_REG_DIR      GPIOA->DDR
  #define LCD_DATA_REG_OP       GPIOA->PORT
  #define LCD_DATA_REG_IP       GPIOA->PIN
  
  /* Operation Mode */
  /* Select one of Them and Comment the Other */
  /* Connect the Bits From 4 To 7 In The LCD To The Pins From 4 To 7 In The Micro controller  */
  #define LCD_UPPER_DATA_PORT
  //#define LCD_LOWER_DATA_PORT
  
  /* Initiate Instruction */
  #define CURSER              0     /* 1 To Enable , 0 To Disable */
  #define BLINK               0     /* 1 To Enable , 0 To Disable */
  #define EIGHTBIT_DATA_MODE  0     /* 1 Enable 8-Bit Interface Mode , 0 Enable 4-Bit Interface Mode */
  #define FONT_5x10_DOT       0     /* 1 To Enable 5x10 Dot, 0 To Enable 5x8 Dot */
  #define TWO_LINE_EN         1     /* 1 To Enable Two Line , 0 To Enable One Line (NOTE !! : Cannot Display two Line With The Font 5x10 ) */
  
     #if (FONT && LINE_NUM)
	     #pragma GCC error "Cannot Display two Line With The Font 5x10"
    #endif
  
  /* Command List Code */
  #define CLEAR_DISPALY       0x01
  #define RETURN_HOME         0x02
  #define DISPLAY_OFF         0x08
  #define DISPLAY_ON          ( (0x0C) | (CURSER << 1) | (BLINK) )
  #define CURSER_SHIFT_RT     0x14
  #define CURSER_SHIFT_LF     0x10
  #define DISPLAY_SHIFT_RT    0x1C
  #define DISPLAY_SHIFT_LF    0x18
  #define FUNCTION_SET        ( (0x20) | (EIGHTBIT_DATA_MODE << 4) | (TWO_LINE_EN << 3) | (FONT_5x10_DOT << 2))
  #define DDRAM_CONST         0x80
  #define CGRAM_CONST         0x40
  
  
  
  #define LCD_1ST_ROW 0x00
  #define LCD_2ND_ROW 0x40
  #define LCD_3RD_ROW 0x10
  #define LCD_4TH_ROW 0x50

  #define LCD_LEFT  1
  #define LCD_RIGHT 0
  
  
  #define LCD_Shift(DIR)	    ((DIR == LCD_LEFT)? Send_instruction(DISPLAY_SHIFT_LF) : Send_instruction(DISPLAY_SHIFT_RT))
  #define LCD_CURSOR_Shift(DIR) ((DIR == LCD_LEFT)? Send_instruction(CURSER_SHIFT_LF) : Send_instruction(CURSER_SHIFT_RT))

  void Send_instruction(unsigned char instruction);
  void LCD_init(void);
  void LCD_Clear(void);
  void LCD_DisplayChar(unsigned char Data);
  void LCD_DisplayString(char * ptr);
  void LCD_Select_RowCol(unsigned char Row , unsigned char col);
  void LCD_DisplayInt(long int data);
  
  /*
   * pattern : is 8 address sequence that store in the CGRAM to illuminate the shape of the new char 
   * index : it is number from 0 to 7 refere to place, CGRAM is 64 bit each index form from 8bit so it can hold 8 char 5*8 
   */
  void LCD_StoreCustomchar(unsigned char*pattern,unsigned char CGRAM_index);
  


#endif /* LCD_H_ */