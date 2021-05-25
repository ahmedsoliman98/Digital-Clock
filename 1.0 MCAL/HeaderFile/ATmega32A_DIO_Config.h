/*
 *
 * @file <ATmega32A_DIO_Config.h>
 * @brief <This is a Header File for the driver Input Output Configuration>
 *
 * @APIS
 *					  DIO_pinConfiguration()		< to configure the pin adderss ,port, input/output to the Mc >
 *						returns   void 
 *						Takes	  GPIO *   ,      pinNumber        , pinMode
 *
 *					  DIO_portConfiguration()		<to configure the port value to the Mc>
 *                      return  void
 *                      Takes              GPIO *         ,      uint8
 *
 *
 *                    DIO_pinWrite()            <to send the data from the Mc out throw the pin>
 *                     return  void
 *                      Takes              GPIO *         ,      pinNumber   , digitalValue
 *
 *                    DIO_portWrite()          <to send the data from the Mc out throw the port>
 *                     return  void
 *                      Takes              GPIO *         ,     uint8
 *
 *                    DIO_pinRead()          <to receive the data from the throw the pin to the Mc>
 *                     return  digitalValue
 *                      Takes              GPIO *         ,     pinNaumber
 *
 *                    DIO_portRead()          <to receive the data from the throw the port to the Mc>
 *                     return  digitalValue
 *                      Takes              GPIO *       
 *
 * @authors <ahmedsoliman>
 * @date  7/10/2020 4:09:25 PM>
 *
 */


#ifndef ATMEGA32A_DIO_CONFIG_H_
#define ATMEGA32A_DIO_CONFIG_H_


  #include <ATmega32A_Config.h>
  #include <StandardDataType.h>
  #include <Macro.h>
  
  /* configure the Pin State Mode InputFloat is ( idle State 0) InputPullup (idle State 1) or Output) */
  typedef enum
  {
	  InputFloat,
	  InputPullup,
	  Output,
  }pinMode;
  
  typedef enum
  {
	  PIN0,PIN1,PIN2,PIN3,
	  PIN4,PIN5,PIN6,PIN7,
  }pinNumber;
  
  
     /*
	 *
	 * @brief <DIO_pinConfiguration>
	 *
	 * <this function is to configure the pin by define it is PORT , PIN number , input or output to the Mc>
	 *
	 * @const pinC  <GPIO *>       <Should Pass a PORT of the Pin >
	 *        pin_num <pinNumber>  <should pass the number of the pin>
	 *        pin_M   <pinMode>    <should pass the mode of the pin output or input>
	 *
	 * @return < void>
	 */
	
void DIO_pinConfiguration(GPIO * pinC, pinNumber pin_num, pinMode pin_M);

    /*
	 *
	 * @brief <DIO_portConfiguration>
	 *
	 * <this function is to configure the port by define it is PORT name and the value to the Mc>
	 *
	 * @const pinC  <GPIO *>       <Should Pass a PORT of the Pin >
	 *        portValue <unint8>  <should pass the value of the port>
	 *       
	 *
	 * @return < void>
	 */
void DIO_portConfiguration(GPIO * portC, uint8 portValue);

    /*
	 *
	 * @brief <DIO_pinWrite>
	 *
	 * <this function is to write the data from the Mc throw the pin>
	 *
	 * @const pinC  <GPIO *>       <Should Pass a PORT of the Pin >
	 *        pin_num <pinNumber>  <should pass the number of the pin>
	 *        digitalValue   <state>    <should pass the state of the pin HIGH/LOw>
	 *
	 * @return < void>
	 */
	
void DIO_pinWrite(GPIO * pinC, pinNumber pin_num, DigitalValue state);
    /*
	 *
	 * @brief < DIO_portWrite>
	 *
	 * <this function is to write a data from the Mc throw the port>
	 *
	 * @const pinC  <GPIO *>       <Should Pass a PORT of the Pin >
	 *        portValue <unint8>  <should pass the value of the data write>
	 *       
	 *
	 * @return < void>
	 */
void DIO_portWrite(GPIO * portC, uint8 portValue);

    /*
	 *
	 * @brief <DIO_pinRead>
	 *
	 * <this function is to read the data from the pin to the Mc>
	 *
	 * @const pinC  <GPIO *>       <Should Pass a PORT of the Pin >
	 *        pin_num <pinNumber>  <should pass the number of the pin>
	 *
	 * @return < digitalValue>
	 */
DigitalValue DIO_pinRead(GPIO * pinC, pinNumber pin_num);

    /*
	 *
	 * @brief < DIO_portWrite>
	 *
	 * <this function is to read the data from the port to the Mc>
	 *
	 * @const pinC  <GPIO *>       <Should Pass a PORT name of the Pin >
	 *       
	 *
	 * @return < uint8>
	 */
uint8 DIO_portRead(GPIO * portC);

#endif /* ATMEGA32A_DIO_CONFIG_H_ */