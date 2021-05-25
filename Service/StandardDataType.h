 /*
 *
 * @file <StandardDataType.h>
 * @brief <This is a Header File for Standard Data Type Size>
 *
 *Post built Driver for The Standard Data
 * @APIS			  
 *					
 * @authors <ahmedsoliman>
 * @date <7/10/2020 4:08:31 PM>
 *
 */

#ifndef STANDARDDATATYPE_H_
#define STANDARDDATATYPE_H_


	typedef unsigned char uint8;
	typedef signed   char int8;

	typedef unsigned short uint16;
	typedef signed   short int16;

	typedef unsigned long uint32;
	typedef signed   long int32;

	typedef unsigned long long uint64;
	typedef signed   long long int64;

	typedef float  float32;
	typedef double float64;

	typedef enum
	{
		TRUE,
		FALSE,
	}bool;

	typedef enum
	{
		invalidArgument,
		overflow,
		invalidState,
	}Errortype;

	typedef enum
	{
		LOW,
		HIGH,
	}DigitalValue;





#endif /* STANDARDDATATYPE_H_ */