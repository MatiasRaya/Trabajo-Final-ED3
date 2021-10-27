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
void configEXTINT();

void agarrar();
void soltar(); //Debe soltar y volver a la posicion inicial (aarba de la cinta principal)
void derecha();
void izquierda();

uint8_t info[]= "";

int main()
{
    configPin();
    configUART();
	configPWM();
	configEXTINT();

    while(1){}	//Agregar if con los valores que le paso por Bluetooth para determinar que hago

    return 0;
}

void configPin()
{
    PINSEL_CFG_Type PinCfg;

    //Confuguramos UART
    PinCfg.Funcnum = 1;                                                 //Se selecciona la segunda funcion del pin
    PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;                           //Se selecciona el modo normal del pin, el drenador esta cerrado
	PinCfg.Pinmode = PINSEL_PINMODE_PULLUP;                             //Se selecciona la resistencia pull-up del pin
	PinCfg.Pinnum = 2;                                                  //Se selecciona el pin a usar
	PinCfg.Portnum = 0;                                                 //Se selecciona el puerto
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P0.2
	PinCfg.Pinnum = 3;                                                  //Se selecciona el pin a usar
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P0.3


	//Configuramos PWM
	PinCfg.Funcnum = 1;                                                 //Se selecciona la segunda funcion del pin
	PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;                           //Se selecciona el modo normal del pin, el drenador esta cerrado
	PinCfg.Pinmode = PINSEL_PINMODE_PULLUP;                             //Se selecciona la resistencia pull-up del pin
	PinCfg.Pinnum = 0;                                                  //Se selecciona el pin a usar
	PinCfg.Portnum = 2;                                                 //Se selecciona el puerto
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P2.0
	PinCfg.Pinnum = 1;                                                  //Se selecciona el pin a usar
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P2.1
	PinCfg.Pinnum = 2;                                                  //Se selecciona el pin a usar
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P2.2
	PinCfg.Pinnum = 3;                                                  //Se selecciona el pin a usar
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P2.3

	//Configuramos EXTINT
	PinCfg.Funcnum = 0;                                                 //Se selecciona la primera funcion del pin
	PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;                           //Se selecciona el modo normal del pin, el drenador esta cerrado
	PinCfg.Pinmode = PINSEL_PINMODE_PULLUP;                             //Se selecciona la resistencia pull-up del pin
	PinCfg.Pinnum = 10;                                                 //Se selecciona el pin a usar
	PinCfg.Portnum = 2;                                                 //Se selecciona el puerto
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P2.10
	PinCfg.Pinnum = 11;                                                 //Se selecciona el pin a usar
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P2.11
	PinCfg.Pinnum = 12;                                                 //Se selecciona el pin a usar
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P2.12
	PinCfg.Pinnum = 13;                                                 //Se selecciona el pin a usar
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P2.13

    return;
}

//Configuracion UART
void configUART()
{
    UART_CFG_Type UARTConfigStrut;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;

	UART_ConfigStructInit(&UARTConfigStrut);							//Se configura la comunicacion UART en sus valores por defecto
	UART_Init(LPC_UART0,&UARTConfigStrut);								//Se inicializa el periférico
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);					//Se configura la FIFO por defecto
	UART_FIFOConfig(LPC_UART0,&UARTFIFOConfigStruct);					//Se inicializa la FIFO
	//UART_TxCmd(LPC_UART0, ENABLE);									//Se habilita la transmision serie
	UART_IntConfig(LPC_UART0,UART_INTCFG_RBR,ENABLE);					//Se habilita la interrupcion por el RX del UART
	UART_IntConfig(LPC_UART0,UART_INTCFG_RLS,ENABLE);					//Se habilita la interrupcion por el estado de la linea de recpcion de UART0

	NVIC_EnableIRQ(UART0_IRQn);											//Se habilita el vector de interrupcion UART0_IRQn
	return;
}

void UART0_IRQHandler()
{
	uint32_t intsrc, temp0, temp1;

	intsrc = UART_GetIntId(LPC_UART0);									//Se obtiene el valor de la identificacion de la interrupcion
	temp0 = intsrc & UART_IIR_INTID_MASK;								//Se identifica que probica la interrupcion

	if(temp0 == UART_IIR_INTID_RLS)										//Se verifica el estado de la linea de recepcion de UART0
	{
		temp1 = UART_GetLineStatus(LPC_UART0);							//Se almacena el valor la linea de estado del UART
		temp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
							  | UART_LSR_BI | UART_LSR_RXFE);			//Se verifica los bit de error del UART
		if(temp1)														//Se verifica si no hay errores
		{
			while(1){}													//En caso de ser afirmativo, se entra en bucle infinito
		}
	}
	if((temp0 == UART_IIR_INTID_RDA) || (temp0 == UART_IIR_INTID_CTI))	//Se verifica si recibi informacion o si fue un caracter fuera de tiempo
	{
		UART_Receive(LPC_UART0, info, sizeof(info),NONE_BLOCKING);		//En caso de ser afirmativo, se indica donde almaceno el valor recibido por RX de UART
	}
}

//Configuracion PWM
void configPWM()
{
	PWM_TIMERCFG_Type TymerPWMConfig;
	PWM_MATCHCFG_Type MatchPWMConfig;

	TymerPWMConfig.PrescaleOption = PWM_TIMER_PRESCALE_TICKVAL;			//Se coloca el prescaler en valor absoluto
	TymerPWMConfig.PrescaleValue = 25;									//Se selecciona el valor del prescaler
	MatchPWMConfig.IntOnMatch = DISABLE;								//Se desactiva la interrupcion al hacer MATCH
	MatchPWMConfig.MatchChannel = 0;									//Se selecciona el canal de MATCH
	MatchPWMConfig.ResetOnMatch = ENABLE;								//Se activa el RESET después de hacer MATCH
	MatchPWMConfig.StopOnMatch = DISABLE;								//Se desactiva la detencion despues de hacer MATCH
	PWM_ConfigMatch(LPC_PWM1,&MatchPWMConfig);							//Se pasa MatchPWMConfig del MATCH0
	MatchPWMConfig.ResetOnMatch = DISABLE;								//Se desactiva el RESET después de hacer MATCH
	MatchPWMConfig.MatchChannel = 1;									//Se selecciona el canal de MATCH
	PWM_ConfigMatch(LPC_PWM1,&MatchPWMConfig);							//Se pasa MatchPWMConfig del MATCH1
	MatchPWMConfig.MatchChannel = 2;									//Se selecciona el canal de MATCH
	PWM_ConfigMatch(LPC_PWM1,&MatchPWMConfig);									//Se pasa MatchPWMConfig del MATCH2
	MatchPWMConfig.MatchChannel = 3;									//Se selecciona el canal de MATCH
	PWM_ConfigMatch(LPC_PWM1,&MatchPWMConfig);							//Se pasa MatchPWMConfig del MATCH3
	MatchPWMConfig.MatchChannel = 4;									//Se selecciona el canal de MATCH
	PWM_ConfigMatch(LPC_PWM1,&MatchPWMConfig);							//Se pasa MatchPWMConfig del MATCH4

	PWM_Init(LPC_PWM1,PWM_MODE_TIMER,&TymerPWMConfig);					//Se inicializa el periferico
	PWM_MatchUpdate(LPC_PWM1,0,20000,PWM_MATCH_UPDATE_NOW);				//Se configura el MATCH0 en 20ms
	PWM_ChannelConfig(LPC_PWM1,2,PWM_CHANNEL_SINGLE_EDGE);				//Se configura el canal en modo de flanco unico
	PWM_ChannelConfig(LPC_PWM1,3,PWM_CHANNEL_SINGLE_EDGE);				//Se configura el canal en modo de flanco unico
	PWM_ChannelConfig(LPC_PWM1,4,PWM_CHANNEL_SINGLE_EDGE);				//Se configura el canal en modo de flanco unico
	//El canal 1 no es necesario configurarlo ya que por solo trabaja en el modo de flanco unico
	PWM_ChannelCmd(LPC_PWM1,1,ENABLE);									//Se habilita el canal 1
	PWM_ChannelCmd(LPC_PWM1,2,ENABLE);									//Se habilita el canal 2
	PWM_ChannelCmd(LPC_PWM1,3,ENABLE);									//Se habilita el canal 3
	PWM_ChannelCmd(LPC_PWM1,4,ENABLE);									//Se habilita el canal 4
	PWM_CounterCmd(LPC_PWM1,ENABLE);									//Se habilita el contador del periferico
	PWM_Cmd(LPC_PWM1, ENABLE);											//Se habilita el periferico

	return;
}

//Configuracion EXTINT
void configEXTINT()
{
	EXTI_InitTypeDef ExtIntCfg;

	EXTI_Init();														//Se setea por defecto los valores de las interrupciones externas

	ExtIntCfg.EXTI_Line = EXTI_EINT0;									//Se selecciona el pin de interrupcion externa
	ExtIntCfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;						//Se selecciona el modo de interrupcion por flanco
	ExtIntCfg.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE; //Se selecciona el flanco de bajada
	EXTI_Config(&ExtIntCfg);											//Se pasa ExtIntCfg de la interrupcion externa EINT0
	ExtIntCfg.EXTI_Line = EXTI_EINT1;									//Se selecciona el pin de interrupcion externa
	EXTI_Config(&ExtIntCfg);											//Se pasa ExtIntCfg de la interrupcion externa EINT1
	ExtIntCfg.EXTI_Line = EXTI_EINT2;									//Se selecciona el pin de interrupcion externa
	EXTI_Config(&ExtIntCfg);											//Se pasa ExtIntCfg de la interrupcion externa EINT2
	ExtIntCfg.EXTI_Line = EXTI_EINT3;									//Se selecciona el pin de interrupcion externa
	EXTI_Config(&ExtIntCfg);											//Se pasa ExtIntCfg de la interrupcion externa EINT3

	NVIC_EnableIRQ(EINT0_IRQn);											//Se habilita el vector de interrupcion EINT0_IRQn
	NVIC_EnableIRQ(EINT1_IRQn);											//Se habilita el vector de interrupcion EINT1_IRQn
	NVIC_EnableIRQ(EINT2_IRQn);											//Se habilita el vector de interrupcion EINT2_IRQn
	NVIC_EnableIRQ(EINT3_IRQn);											//Se habilita el vector de interrupcion EINT3_IRQn

	return;
}

void EINT0_IRQHandler()
{
	agarrar();															//Se llama a la funcion agarrar

	EXTI_ClearEXTIFlag(EXTI_EINT0);										//Se limpia el flag de interrupcion de EINT0

	return;
}

void EINT1_IRQHandler()
{
	soltar();															//Se llama a la funcion soltar

	EXTI_ClearEXTIFlag(EXTI_EINT1);										//Se limpia el flag de interrupcion de EINT1

	return;
}

void EINT2_IRQHandler()
{
	derecha();															//Se llama a la funcion derecha

	EXTI_ClearEXTIFlag(EXTI_EINT2);										//Se limpia el flag de interrupcion de EINT2

	return;
}

void EINT3_IRQHandler()
{
	izquierda();														//Se llama a la funcion izquierda

	EXTI_ClearEXTIFlag(EXTI_EINT3);										//Se limpia el flag de interrupcion de EINT3

	return;
}

//Configuro las funciones adicionales
void agarrar()
{
	
}

void soltar()
{

}

void derecha()
{

}

void izquierda()
{
	
}