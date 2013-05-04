/*
* VirtualWireClass Functions:
*	Abstracts a RF link making a class with the functions in the 
*	VirtualWire Library. 
*	Added info leds while Rx or Tx if wanted. These can be set with the 2nd constructor
*
*
*
*
*/

#include "VirtualWireClass.h"

VirtualWireClass::VirtualWireClass(){
 
	// longitud máxima del buffer
	buflen = VW_MAX_MESSAGE_LEN;
	// variables de estado del enlace
	// onRTx = onRx = onTx = false;
	// leds para informar de la recepción y transmision nulo
	ledRx = ledTx = -1;
	texto_Rx = "";
     
}

VirtualWireClass::VirtualWireClass(uint8_t lRx,uint8_t lTx){
     
	// longitud máxima del buffer
	buflen = VW_MAX_MESSAGE_LEN;
	// variables de estado del enlace
	// onRTx = onRx = onTx = false;
	// led para informar de la recepción 
	ledRx = lRx;
	// led para informar de la transmisión 
	ledTx = lTx;
	texto_Rx = "";
	pinMode(ledRx,OUTPUT);
	pinMode(ledTx,OUTPUT);
}
   
void VirtualWireClass::init(uint16_t speed, uint8_t rx_pin, uint8_t tx_pin){  
	// configura y guarda los pines
	vw_set_tx_pin(tx_pin);
	vw_set_rx_pin(rx_pin);
	pinRx = rx_pin;
	pinTx = tx_pin;
	// inicia comunicación a speed b/s 
	vw_setup(speed);	 
	// inicia rececpión
	vw_rx_start();  
	// variables de estado
	// onRTx = onRx = onTx = true; 
}
   
void VirtualWireClass::init(uint16_t speed){
   
	// inicia comunicación a speed b/s 
	vw_setup(speed);	 
	// inicia rececpión
	vw_rx_start();  
	// variables de estado
	// onRTx = onRx = onTx = true;
      
}
   
boolean VirtualWireClass::new_msg(){
     
	// variable de control
	uint8_t mensaje = false;
	// longitud máxima del buffer
	buflen = VW_MAX_MESSAGE_LEN;
	// obtiene mensaje si existe
	if (mensaje = vw_get_message(bufRx, &buflen)){
		// enciende led de info de Rx si habilitado
		onLed(ledRx);
		// inicializa cadena
		texto_Rx = "";
		// obtiene datos recibidos en cadena
		for (int i = 0; i < buflen; i++) texto_Rx += char(bufRx[i]);    
		// apaga led de info de Rx si habilitado
		delay(50);offLed(ledRx);
	}
    return(boolean(mensaje));
 }
 
 void VirtualWireClass::operator<< (String data){
  
    // pasa cadena al buffer
	data.getBytes(bufTx,data.length()+1);
	// enciende led de info de Tx si habilitado
	onLed(ledTx);
	// envia los datos
	vw_send((uint8_t *)bufTx, data.length()+1);
	// espera a que sean enviados
	vw_wait_tx(); 
	// apaga led de info de Tx si habilitado
	offLed(ledTx);
   
}

String VirtualWireClass::textRx(){return(texto_Rx);}

void VirtualWireClass::onLed(uint8_t led){if(led > 0)digitalWrite(led, HIGH);}
 
void VirtualWireClass::offLed(uint8_t led){if(led > 0)digitalWrite(led, LOW);}
  









