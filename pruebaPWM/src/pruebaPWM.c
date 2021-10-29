#include "LPC17xx.h"

#include "lpc17xx_pinsel.h"
#include "lpc17xx_pwm.h"

void configPin();
void configPWM();

uint32_t valor0, valor1;

int main()
{
    configPin();
	configPWM();

    while(1){}

    return 0;
}

void configPin()
{
    PINSEL_CFG_Type PinCfg;

	//Configuramos PWM
	PinCfg.Funcnum = 1;                                                 //Se selecciona la segunda funcion del pin
	PinCfg.OpenDrain = PINSEL_PINMODE_NORMAL;                           //Se selecciona el modo normal del pin, el drenador esta cerrado
	PinCfg.Pinmode = PINSEL_PINMODE_PULLUP;                             //Se selecciona la resistencia pull-up del pin
	PinCfg.Pinnum = 0;                                                  //Se selecciona el pin a usar
	PinCfg.Portnum = 2;                                                 //Se selecciona el puerto
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P2.0
	PinCfg.Pinnum = 1;                                                  //Se selecciona el pin a usar
	PINSEL_ConfigPin(&PinCfg);                                          //Se pasa PinCfg para el puerto P2.1


    return;
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

	PWM_Init(LPC_PWM1,PWM_MODE_TIMER,&TymerPWMConfig);					//Se inicializa el periferico
	PWM_MatchUpdate(LPC_PWM1,0,20000,PWM_MATCH_UPDATE_NOW);				//Se configura el MATCH0 en 20ms
	PWM_MatchUpdate(LPC_PWM1,1,20,PWM_MATCH_UPDATE_NOW);
	//El canal 1 no es necesario configurarlo ya que por solo trabaja en el modo de flanco unico
	PWM_ChannelCmd(LPC_PWM1,1,ENABLE);									//Se habilita el canal 1
	PWM_CounterCmd(LPC_PWM1,ENABLE);									//Se habilita el contador del periferico
	PWM_Cmd(LPC_PWM1, ENABLE);											//Se habilita el periferico


	valor0 = LPC_PWM1->MR0;
	valor1 = LPC_PWM1->MR1;
	return;
}
