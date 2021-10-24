#include "LPC17xx.h"

#include "lpc17xx_pinsel.h"
#include "lpc17xx_pwm.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_gpio.h"

void configPin();
void configUART();
void configPWM();

int main()
{
    void configPin();
    void configUART();

    while(1){}

    return 0;
}

void configPin()
{
    PINSEL_CFG_Type PinCfg;
    
    //Confuguramos UART
    PinCfg.Funcnum = 1;                                                 //Se selecciona la primera funcion del pin
    PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;                           //Se selecciona el modo normal del pin, el drenador esta cerrado
	PinCfg.Pinmode = PINSEL_PINMODE_PULLUP;                             //Se selecciona la resistencia pull-up del pin
	PinCfg.Pinnum = 2;                                                  //Se selecciona el pin a usar
	PinCfg.Portnum = 0;                                                 //Se selecciona el puerto
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P0.2
	PinCfg.Pinnum = 3;                                                  //Se selecciona el pin a usar
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P0.3

    return;
}

void configUART()
{
    UART_CFG_Type UARTConfigStrut;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;

	UART_ConfigStructInit(&UARTConfigStrut);							//Se configura la comunicacion UART en sus valores por defecto
	UART_Init(LPC_UART0,&UARTConfigStrut);								//Se inicializa el periférico
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);					//Se configura la FIFO por defecto
	UART_FIFOConfig(LPC_UART0,&UARTFIFOConfigStruct);					//Inicializo la FIFO
	UART_TxCmd(LPC_UART0, ENABLE);
	UART_IntConfig(LPC_UART0,UART_INTCFG_RBR,ENABLE);					//Habilito la interrupcion por el RX del UART
	UART_IntConfig(LPC_UART0,UART_INTCFG_RLS,ENABLE);					//Habilito la interrupcion por el estado de la linea de recpcion de UART0

	NVIC_EnableIRQ(UART0_IRQn);
	return;
}

void 