/*
 * RealTime_ClK.h
 *
 * The Idea of this application is to make a real time clock system represent the time throw a six 7-segment display 2 for hour, 2 for minute and 2 for second
 * and this clock can be set up it is time by instruction setting appear on the LCD display " Set Time Click 1 "
 * The user can click '1' throw the keypad and it will appear on the LCD the "Hour :  _:_ " to inform that it will set the hour then the minute and second will appear in the same way 
 * the clock will represent time in the 24h form not 12 the minute and the second max value can appear is 59 then it will increase the next dimension and it will return to 0
 *
 * The Implementation 
 * We used the Timer 2 with the external crystal clock with the value 32768 Hz frequency to make it has an overflow exactly after a 1 second 
 * so we makes its ISR to increase a generic volatile second counter and display this value on the 7-segment E5, E6 after the sec counter reach 60 it increase min counter by 1 display on the 7-segment E4, E3 and return to 0
 * same way after min counter reach 60 it will increase the hour counter by 1 display on the 7-segment Enable 2 & 1  
 *
 * We used the Timer0 to setup an counter after a 5msec to used the multiplexing feature to operate the six 7-segment on the same pins 
 *
 * Created: 1/12/2021 6:25:45 PM
 *  Author: ahmedsoliman
 */ 


#ifndef REALTIME_CLK_H_
#define REALTIME_CLK_H_


    
	void RealTime_ClK_INTIA(void);
	void RealTime_ClK_OPERATE(void);


#endif /* REALTIME_CLK_H_ */