/*
* VirtualWireClass:
*	Abstracts a RF link making a class with the functions in the 
*	VirtualWire Library. 
*	Added info leds while Rx or Tx if wanted. 
*  	These can be set with the 2nd constructor: VirtualWireClass(uint8_t lRx,uint8_t lTx);
*
*/
#ifndef VirtualWireClass_h
#define VirtualWireClass_h

#include "Arduino.h"
#include "VirtualWire.h"

class VirtualWireClass {
  
	private:

		/**
		* Rx and Tx buffers
		*/
		uint8_t bufRx[VW_MAX_MESSAGE_LEN],bufTx[VW_MAX_MESSAGE_LEN];
		/**
		* Buffer length
		*/
		uint8_t buflen;
		
		/**
		* Pins and pin leds for Rx y Tx and info
		*/
		uint8_t pinRx, pinTx,ledRx,ledTx;
		
		/**
		* String to store received data
		*/
		String texto_Rx;

		void onLed(uint8_t led);
		void offLed(uint8_t led);
		
	public:
 
		/**
		*@brief Constructor without info leds
		*/
		VirtualWireClass();
		
		/**
		*@brief Constructor whith info led
		*@param lRx - Notification Led for Rx
		*@param lTx - Notification Led for Tx
		*/
		VirtualWireClass(uint8_t lRx,uint8_t lTx);
		
		/**
		* @brief Inits the RF link according to the parameters
		* @param speed - In bits/second
		* @param rx_pin - Rx pin
		* @param tx_pin - Tx pin
		*/
		void init(uint16_t speed, uint8_t rx_pin, uint8_t tx_pin);

		/**
		* @brief Inits the RF link according to the parameters
		* on the default Rx,Tx pins
		* @param speed - In bits/second
		* @note By default Rx and Tx pins
		* are Rx = 11 Tx =12
		*/
		void init(uint16_t speed);

		/** 
		* @brief Checks for a new message received. If so, stores the
		* message internally. Use textRx() to get it.
		* @return true/false whether new message.
		*/
		boolean new_msg();

		/** 	
		* @brief Sends the bytes in the introduced string blocking
		* until sent
		* @param data - String text to send
		* @note Mirar comprobaciones de longitud y vacio 
		* @return void
		*/
		void operator<< (String data);
		
		/** 	
		*@brief Last received message stored
		*@return String with last received text or empty
		*/
		String textRx();

};

#endif