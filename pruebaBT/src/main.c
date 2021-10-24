#include "LPC17xx.h"

#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

#define ledR (uint32_t)(1<<22)
#define ledG (uint32_t)(1<<25)
#define ledB (uint32_t)(1<<26)

void configPin();
void configUART();
void UART_IntReceive();
void UART0_IRQHandler();

uint8_t info[]="";

int main()
{
	configPin();
	configUART();

	while(1)
	{
		if((info[0]==48))
		{
			GPIO_ClearValue(0,ledR);									//Enciendo el led rojo de la placa
		}
		else if(info[0]==51)
		{
			GPIO_SetValue(0,ledR);										//Apago el led rojo de la placa
		}
		else if((info[0]==49))
		{
			GPIO_ClearValue(3,ledG);									//Enciendo el led verde de la placa
		}
		else if(info[0]==52)
		{
			GPIO_SetValue(3,ledG);										//Apago el led rojo de la placa
		}
		else if((info[0]==50))
		{
			GPIO_ClearValue(3,ledB);									//Enciendo el led azul de la placa
		}
		else if(info[0]==53)
		{
			GPIO_SetValue(3,ledB);										//Apago el led rojo de la placa
		}
	}

	return 0;
}

void configPin()
{
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 2;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);											//Configuro P0.2 como TXD0
	PinCfg.Pinnum = 3;
	PINSEL_ConfigPin(&PinCfg);											//Configuro P0.3 como RXD0

	GPIO_SetDir(0,ledR,1);												//Configuro P0.22 como GPIO de salida
	GPIO_SetDir(3,ledG,1);												//Configuro P0.25 como GPIO de salida
	GPIO_SetDir(3,ledB,1);												//Configuro P0.26 como GPIO de salida

	GPIO_SetValue(0,ledR);												//Seteo en 0 el P0.22
	GPIO_SetValue(3,ledG);												//Seteo en 0 el P0.25
	GPIO_SetValue(3,ledB);												//Seteo en 0 el P0.26

	return;
}

void configUART()
{
	UART_CFG_Type UARTConfigStrut;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;

	UART_ConfigStructInit(&UARTConfigStrut);							//Configuro la comunicacion UART por defecto
	UART_Init(LPC_UART0,&UARTConfigStrut);								//Inicializo el periférico
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);					//Configuro la FIFO por defecto
	UART_FIFOConfig(LPC_UART0,&UARTFIFOConfigStruct);					//Inicializo la FIFO
	UART_TxCmd(LPC_UART0, ENABLE);
	UART_IntConfig(LPC_UART0,UART_INTCFG_RBR,ENABLE);					//Habilito la interrupcion por el RX del UART
	UART_IntConfig(LPC_UART0,UART_INTCFG_RLS,ENABLE);					//Habilito la interrupcion por el estado de la linea de recpcion de UART0

	NVIC_EnableIRQ(UART0_IRQn);

	return;
}

void UART0_IRQHandler()
{
	uint32_t intsrc, temp0, temp1;

	intsrc = UART_GetIntId(LPC_UART0);									//Obtengo el valor de la identificacion de la interrupcion
	temp0 = intsrc & UART_IIR_INTID_MASK;								//Identifico que probica la interrupcion

	if(temp0 == UART_IIR_INTID_RLS)										//Verifico el estado de la linea de recepcion de UART0
	{
		temp1 = UART_GetLineStatus(LPC_UART0);							//Almaceno el valor la linea de estado del UART
		temp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
							  | UART_LSR_BI | UART_LSR_RXFE);			//Verifico los bit de error del UART
		if(temp1)														//Verifico si no hay errores
		{
			while(1){}													//En caso de ser afirmativo, se entra en bucle infinito
		}
	}
	if((temp0 == UART_IIR_INTID_RDA) || (temp0 == UART_IIR_INTID_CTI))	//Verifico si recibi informacion o si fue un caracter fuera de tiempo
	{
		UART_IntReceive();												//En caso de ser afirmativo, lLlamo a la funcion que almacena el valor recibido y lo retransmite
	}
}

void UART_IntReceive()
{
	UART_Receive(LPC_UART0, info, sizeof(info),NONE_BLOCKING);			//Indico donde almaceno el valor recibido por RX de UART
	UART_Send(LPC_UART0, info, sizeof(info),BLOCKING);					//Indico eñ valor almacenado que tengo que sacar por TX de UART
	return;
}
