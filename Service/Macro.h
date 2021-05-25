/*
 * Macro.h
 *
 * Created: 9/30/2020 1:33:03 PM
 *  Author: ahmedsoliman
 */ 


#ifndef MACRO_H_
#define MACRO_H_


   #define SET_Bit(Reg,bit)  ((Reg) |= (1 << (bit)))
   #define RESET_Bit(Reg,bit)  ((Reg) &= ( ~( 1 << (bit) ) ) )
   #define TOGGLE_Bit(Reg,bit) ((Reg) ^= (1 << (bit)))
   
   #define READ_Bit(Reg,bit)   (((Reg) & (1 << (bit))) >> (bit))


#endif /* MACRO_H_ */