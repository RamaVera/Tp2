/* Copyright 2017, Pablo Ridolfi, Juan Esteban Alarcón, Juan Manuel Cruz
 * All rights reserved.
 *
 * This file is part of Workspace.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
/** @brief This is a simple statechart example using Yakindu Statechart Tool
 * Plug-in (update site: http://updates.yakindu.org/sct/mars/releases/).
 */

/** \addtogroup statechart Simple UML Statechart example.
 ** @{ */

/*==================[inclusions]=============================================*/

#include "main.h"
#include "Prefix.h"
#include "sapi.h"       // <= sAPI header
#include "TimerTicks.h"

#include "sapi_debugPrint.h"	//Para poder usar la UART

DEBUG_PRINT_ENABLE

#define TICKRATE_MS 1

/*==================[internal data declaration]==============================*/

volatile bool SysTick_Time_Flag = false;

/*! This is a state machine */
static Prefix statechart;


/* Select a TimeEvents choise	*/
#define __USE_TIME_EVENTS TRUE	/* "false" without TimeEvents */
//#define __USE_TIME_EVENTS (true)	/* or "true" with TimerEvents */

/*! This is a timed state machine that requires timer services */
#if (__USE_TIME_EVENTS == TRUE)
	#define NOF_TIMERS (sizeof(PrefixTimeEvents)/sizeof(sc_boolean))
#else
	#define NOF_TIMERS 0
#endif

TimerTicks ticks[NOF_TIMERS];






/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

#define TP2_4



#ifdef TP2_1

/**/



#endif




#ifdef TP2_2




#endif







#ifdef TP2_3

	const char * NameLeds[]={"Led Red","Led Green","Led Blue","Led 1","Led 2","Led 3"};
	const char * NameForm[]={"Senoidal","Cuadrada","Triangular"};
	const char * NameMag[]={"Frecuencia","Tension"};

	void prefixIface_opLED(const Prefix* handle, const sc_integer LEDNumber, const sc_boolean State)
	{
		char aux[32];
		gpioWrite( (LEDR + LEDNumber), State);
		sprintf(aux, "Led %s en estado %d \r\n",NameLeds[LEDNumber], State);
		debugPrintString( aux  );
	}

	void prefixIface_aSetForma(const Prefix* handle, const sc_integer signalForm)
	{
		char aux[32];
		sprintf(aux, "La forma elegida es : %s \r\n",NameForm[signalForm]);
		debugPrintString( aux  );
	}

	void prefixIface_aSetMag(const Prefix* handle, const sc_integer signalMag)
	{
		char aux[32];
		sprintf(aux, "La magnitud elegida es : %s \r\n",NameMag[signalMag]);
		debugPrintString( aux  );
	}
	void prefixIface_aIncFreq(const Prefix* handle)
	{
		debugPrintString( "Incrementar frecuencia \r\n" );
	}
	void prefixIface_aDecFreq(const Prefix* handle)
	{
		debugPrintString( "Decrementar frecuencia \r\n" );
	}
	void prefixIface_aIncTens(const Prefix* handle)
	{
		debugPrintString( "Incrementar tension \r\n" );
	}
	void prefixIface_aDecTens(const Prefix* handle)
	{
		debugPrintString( "Decrementar tension\r\n" );
	}

	void myTickHook( void *ptr ){
		SysTick_Time_Flag = true;
	}

	void prefix_setTimer(Prefix* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic)
	{
		SetNewTimerTick(ticks, NOF_TIMERS, evid, time_ms, periodic);
	}

	void prefix_unsetTimer(Prefix* handle, const sc_eventid evid)
	{
		UnsetTimerTick(ticks, NOF_TIMERS, evid);
	}

	int main(void)
	{
		#if (__USE_TIME_EVENTS == TRUE)
			uint32_t i;
		#endif


		boardConfig();
		debugPrintConfigUart( UART_USB, 115200 );
		debugPrintString( "DEBUG c/sAPI\r\n" );

		tickConfig( TICKRATE_MS );
		tickCallbackSet( myTickHook, (void*)NULL );

		/* Statechart Initialization */
		#if (__USE_TIME_EVENTS == TRUE)
		InitTimerTicks(ticks, NOF_TIMERS);
		#endif

		prefix_init(&statechart);
		prefix_enter(&statechart);



		while (1) {
			__WFI();

			if (SysTick_Time_Flag == true) {
				SysTick_Time_Flag = false;

				#if (__USE_TIME_EVENTS == TRUE)
				UpdateTimers(ticks, NOF_TIMERS);
				for (i = 0; i < NOF_TIMERS; i++) {
					if (IsPendEvent(ticks, NOF_TIMERS, ticks[i].evid) == true) {

						prefix_raiseTimeEvent(&statechart, ticks[i].evid);	// Event -> Ticks.evid => OK
						MarkAsAttEvent(ticks, NOF_TIMERS, ticks[i].evid);
					}
				}
				#else
				prefixIface_raise_evTick(&statechart);					// Event -> evTick => OK
				#endif

				prefix_runCycle(&statechart);							// Run Cycle of Statechart
			}
		}
	}
#endif











#ifdef TP2_4

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/* Funciones para Yakindu, Ejercicio 4: Puerta automatica por proximidad */

void prefixIface_opShowMessage(const Prefix* handle, const sc_integer DoorState)
{
	switch(DoorState)
	{
	case 0: gpioWrite(LEDG, false);
			gpioWrite(LEDR, true);
			debugPrintString( "CERRADO\r\n" );
			break;

	case 1: gpioWrite(LEDR, false);
			gpioWrite(LEDG, true);
			debugPrintString( "ABIERTO\r\n" );
			break;

	default: break;
	}

}


void prefixIface_opStartCloseDoor(const Prefix* handle)
{
	/* Enciende el motor para cerrar la puerta */

	gpioWrite(LEDG, false);
	gpioWrite(LED2, true);
	debugPrintString( "Cerrando puerta\r\n" );
}


void prefixIface_opStartOpenDoor(const Prefix* handle)
{
	/* Enciende el motor para abrir la puerta */

	gpioWrite(LEDR, false);
	gpioWrite(LED3, true);
	debugPrintString( "Abriendo puerta\r\n" );
}

void prefixIface_opStopDoor(const Prefix* handle)
{
	/* Detiene los motores */

	gpioWrite(LED3, false);
	gpioWrite(LED2, false);

	debugPrintString( "Motor Parado\r\n" );
}




typedef enum {FULL_OPENED_ENDSTOP_SW, FULL_CLOSED_ENDSTOP_SW} switch_t;

bool_t is_endstop_pressed(switch_t endstop_switch)
{
	switch(endstop_switch)
	{
		case FULL_OPENED_ENDSTOP_SW:
			return !gpioRead(TEC4);

		case FULL_CLOSED_ENDSTOP_SW:
			return !gpioRead(TEC3);

		default:
			break;
	}

	return false;
}


bool_t is_presence_triggered(void)
{
	return !gpioRead(TEC1);
}


void prefixIface_opLED(Prefix* handle, sc_integer LEDNumber, sc_boolean State)
{
	gpioWrite( (LEDR + LEDNumber), !State);
	debugPrintInt( LEDNumber );
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////



/*!
 * This is a timed state machine that requires timer services
 */

#if (__USE_TIME_EVENTS == TRUE)
/*! This function has to set up timers for the time events that are required by the state machine. */
/*!
	This function will be called for each time event that is relevant for a state when a state will be entered.
	\param evid An unique identifier of the event.
	\time_ms The time in milli seconds
	\periodic Indicates the the time event must be raised periodically until the timer is unset
*/
void prefix_setTimer(Prefix* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic)
{
	SetNewTimerTick(ticks, NOF_TIMERS, evid, time_ms, periodic);
}

/*! This function has to unset timers for the time events that are required by the state machine. */
/*!
	This function will be called for each time event taht is relevant for a state when a state will be left.
	\param evid An unique identifier of the event.
*/
void prefix_unsetTimer(Prefix* handle, const sc_eventid evid)
{
	UnsetTimerTick(ticks, NOF_TIMERS, evid);
}
#endif




void myTickHook( void *ptr ){

	SysTick_Time_Flag = true;
}





/* Ejercicio 4: Puerta automatica por proximidad
 *
 * Las senales son la TEC1 para el sensor de proximidad, TEC3 para fin de carrera de cierre y TEC4
 * para el fin de carrera de apertura.
 *
 * El LED RGB queda VERDE si la puerta esta ABIERTA o ROJO si esta CERRADA.
 * El LED3 se enciende cuando se esta ABRIENDO la puerta hasta que se active el final de carrera (TEC4)
 * El LED2 se enciende cuando se esta CERRANDO la puerta hasta que se active el final de carrera (TEC3)
 *
 * Tamien se mandan mensajes por UART para ver el estado */

int main(void)
{
	#if (__USE_TIME_EVENTS == TRUE)
	uint32_t i;
	#endif


	boardConfig();
	debugPrintConfigUart( UART_USB, 115200 );
	debugPrintString( "DEBUG c/sAPI\r\n" );

	tickConfig( TICKRATE_MS );
	tickCallbackSet( myTickHook, (void*)NULL );

	/* Statechart Initialization */
	#if (__USE_TIME_EVENTS == TRUE)
	InitTimerTicks(ticks, NOF_TIMERS);
	#endif

	prefix_init(&statechart);
	prefix_enter(&statechart);



	while (1) {
		__WFI();

		if (SysTick_Time_Flag == true) {
			SysTick_Time_Flag = false;

			#if (__USE_TIME_EVENTS == TRUE)
			UpdateTimers(ticks, NOF_TIMERS);
			for (i = 0; i < NOF_TIMERS; i++) {
				if (IsPendEvent(ticks, NOF_TIMERS, ticks[i].evid) == true) {

					prefix_raiseTimeEvent(&statechart, ticks[i].evid);	// Event -> Ticks.evid => OK
					MarkAsAttEvent(ticks, NOF_TIMERS, ticks[i].evid);
				}
			}
			#else
			prefixIface_raise_evTick(&statechart);					// Event -> evTick => OK
			#endif



			if(is_endstop_pressed(FULL_OPENED_ENDSTOP_SW))
			{
				prefixIface_raise_evFullyOpened(&statechart);
			}


			if(is_endstop_pressed(FULL_CLOSED_ENDSTOP_SW))
			{
				prefixIface_raise_evFullyClosed(&statechart);
			}


			if(is_presence_triggered())
			{
				prefixIface_raise_evPresenceTriggered(&statechart);
			}
			else
				prefixIface_raise_evPresenceNonTriggered(&statechart);



			prefix_runCycle(&statechart);							// Run Cycle of Statechart
		}



	}
}

#endif





#ifdef TP2_5

/* Funciones requeridas por YAKINDU */
void prefixIface_opStartCloseDoor(const Prefix* handle)
{
	debugPrintString( "Cerrando puerta\r\n" );
}

void prefixIface_opStartOpenDoor(const Prefix* handle)
{
	debugPrintString( "Abriendo puerta\r\n" );
}

void prefixIface_opStopDoor(const Prefix* handle)
{
	debugPrintString( "Motor Parado\r\n" );
}


/* OJO ESTO*/
void prefixIface_opLED(Prefix* handle, sc_integer LEDNumber, sc_boolean State)
{
	gpioWrite( (LEDR + LEDNumber), !State);
}




/* Funciones para el MAIN */
typedef enum {FULL_OPENED_ENDSTOP_SW, FULL_CLOSED_ENDSTOP_SW} switch_t;

bool_t is_endstop_pressed(switch_t endstop_switch)
{
	switch(endstop_switch)
	{
		case FULL_OPENED_ENDSTOP_SW:
			return !gpioRead(TEC3);

		case FULL_CLOSED_ENDSTOP_SW:
			return !gpioRead(TEC4);

		default:
			break;
	}

	return false;
}


int button_detect(void)
{
	if(!gpioRead(TEC1))
		return 1;

	if(!gpioRead(TEC2))
		return 2;

	return 0;
}



/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////



/*!
 * This is a timed state machine that requires timer services
 */

#if (__USE_TIME_EVENTS == TRUE)
/*! This function has to set up timers for the time events that are required by the state machine. */
/*!
	This function will be called for each time event that is relevant for a state when a state will be entered.
	\param evid An unique identifier of the event.
	\time_ms The time in milli seconds
	\periodic Indicates the the time event must be raised periodically until the timer is unset
*/
void prefix_setTimer(Prefix* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic)
{
	SetNewTimerTick(ticks, NOF_TIMERS, evid, time_ms, periodic);
}

/*! This function has to unset timers for the time events that are required by the state machine. */
/*!
	This function will be called for each time event taht is relevant for a state when a state will be left.
	\param evid An unique identifier of the event.
*/
void prefix_unsetTimer(Prefix* handle, const sc_eventid evid)
{
	UnsetTimerTick(ticks, NOF_TIMERS, evid);
}
#endif




void myTickHook( void *ptr ){

	SysTick_Time_Flag = true;
}





/* Ejercicio 5: Porton automatico
 *
 *
 *
 */

int main(void)
{
	#if (__USE_TIME_EVENTS == TRUE)
	uint32_t i;
	#endif

	int button_pressed;

	boardConfig();
	debugPrintConfigUart( UART_USB, 115200 );
	debugPrintString( "DEBUG c/sAPI\r\n" );

	tickConfig( TICKRATE_MS );
	tickCallbackSet( myTickHook, (void*)NULL );

	/* Statechart Initialization */
	#if (__USE_TIME_EVENTS == TRUE)
	InitTimerTicks(ticks, NOF_TIMERS);
	#endif

	prefix_init(&statechart);
	prefix_enter(&statechart);



	while (1) {
		__WFI();

		if (SysTick_Time_Flag == true) {
			SysTick_Time_Flag = false;

			#if (__USE_TIME_EVENTS == TRUE)
			UpdateTimers(ticks, NOF_TIMERS);
			for (i = 0; i < NOF_TIMERS; i++) {
				if (IsPendEvent(ticks, NOF_TIMERS, ticks[i].evid) == true) {

					prefix_raiseTimeEvent(&statechart, ticks[i].evid);	// Event -> Ticks.evid => OK
					MarkAsAttEvent(ticks, NOF_TIMERS, ticks[i].evid);
				}
			}
			#else
			prefixIface_raise_evTick(&statechart);					// Event -> evTick => OK
			#endif



			if(is_endstop_pressed(FULL_OPENED_ENDSTOP_SW))
			{
				prefixIface_raise_evFullyOpened(&statechart);
			}


			if(is_endstop_pressed(FULL_CLOSED_ENDSTOP_SW))
			{
				prefixIface_raise_evFullyClosed(&statechart);
			}


			button_pressed = button_detect();
			switch(button_pressed)
			{
				case 1: prefixIface_raise_evButtonTriggered(&statechart, button_pressed);
						break;
				case 2: prefixIface_raise_evButtonTriggered(&statechart, button_pressed);
						break;
				default: prefixIface_raise_evButtonNonTriggered(&statechart);
						 break;
			}


			prefix_runCycle(&statechart);							// Run Cycle of Statechart
		}



	}
}



#endif

#ifdef TP2_6   /* Ej de la escalera mecánica */

/* Funciones requeridas por YAKINDU */

void prefixIface_opLED(Prefix* handle, sc_integer LEDNumber, sc_boolean State)
{
	gpioWrite( (LEDR + LEDNumber), !State);
}


/* Funciones para el MAIN */

uint32_t Buttons_GetStatusP2_(void) {
	uint8_t ret = false;

	if (gpioRead( TEC2 ) == 0)
		ret = true;

	return ret;
}

uint32_t Buttons_GetStatusP1_(void) {
	uint8_t ret = false;

	if (gpioRead( TEC3 ) == 0)
		ret = true;

	return ret;
}

uint32_t Buttons_GetStatusVEL_(void) {
	uint8_t ret = false;

	if (gpioRead( TEC4 ) == 0)
		ret = true;

	return ret;
}


/*!
 * This is a timed state machine that requires timer services
 */

#if (__USE_TIME_EVENTS == TRUE)
/*! This function has to set up timers for the time events that are required by the state machine. */
/*!
	This function will be called for each time event that is relevant for a state when a state will be entered.
	\param evid An unique identifier of the event.
	\time_ms The time in milli seconds
	\periodic Indicates the the time event must be raised periodically until the timer is unset
*/
void prefix_setTimer(Prefix* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic)
{
	SetNewTimerTick(ticks, NOF_TIMERS, evid, time_ms, periodic);
}

/*! This function has to unset timers for the time events that are required by the state machine. */
/*!
	This function will be called for each time event taht is relevant for a state when a state will be left.
	\param evid An unique identifier of the event.
*/
void prefix_unsetTimer(Prefix* handle, const sc_eventid evid)
{
	UnsetTimerTick(ticks, NOF_TIMERS, evid);
}
#endif

void myTickHook( void *ptr ){

	SysTick_Time_Flag = true;
}

int main(void)
{
	#if (__USE_TIME_EVENTS == TRUE)
		uint32_t i;
	#endif

	boardConfig();
	debugPrintConfigUart( UART_USB, 115200 );
	debugPrintString( "DEBUG c/sAPI\r\n" );

	tickConfig( TICKRATE_MS );
	tickCallbackSet( myTickHook, (void*)NULL );

	/* Statechart Initialization */
	#if (__USE_TIME_EVENTS == TRUE)
		InitTimerTicks(ticks, NOF_TIMERS);
	#endif

	prefix_init(&statechart);
	prefix_enter(&statechart);

	uint32_t BUTTON_StatusP1;
	uint32_t BUTTON_StatusP2;
	uint32_t BUTTON_StatusVEL;

	while (1) {                                 //Time events debe estar en false
		__WFI();
		if (SysTick_Time_Flag == true) {
			SysTick_Time_Flag = false;

			#if (__USE_TIME_EVENTS == TRUE)
				UpdateTimers(ticks, NOF_TIMERS);
				for (i = 0; i < NOF_TIMERS; i++) {
					if (IsPendEvent(ticks, NOF_TIMERS, ticks[i].evid) == true) {

						prefix_raiseTimeEvent(&statechart, ticks[i].evid);	// Event -> Ticks.evid => OK
						MarkAsAttEvent(ticks, NOF_TIMERS, ticks[i].evid);
					}
				}
			//#else
				//prefixIface_raise_evTick(&statechart);					// Event -> evTick => OK
			#endif
			BUTTON_StatusP2 = Buttons_GetStatusP2_();
				if (BUTTON_StatusP2 != 0) {
					prefixIface_raise_evSensorP2(&statechart);
				}

			BUTTON_StatusP1 = Buttons_GetStatusP1_();
				if (BUTTON_StatusP1 != 0) {
					prefixIface_raise_evSensorP1(&statechart);
				}
			BUTTON_StatusVEL = Buttons_GetStatusVEL_();
								if (BUTTON_StatusVEL != 0) {
									prefixIface_raise_evCambioVel(&statechart);
									delay(500);
								}

			prefix_runCycle(&statechart);							// Run Cycle of Statechart
		}

	}


}


#endif


#ifdef TP2_7

//Macros para el microondas---------------------------------------------------
#define BOTON_MODO	(1)					//CONSTANTE QUE HACE REFERENCIA A QUE SE PRESIONÓ EL BOTÓN DE CAMBIO DE MODO
#define BOTON_START_STOP (2)			//CONSTANTE QUE HACE REFERENCIA AL BOTÓN DE INICIO DEL MICROONDAS
#define BOTON_PUERTA (3)				//CONSTANTE QUE HACE REFERENCIA AL BOTÓN QUE INDICA QUE SE ABRIÓ O SE CERRÓ LA PUERTA

#define TEC_MODO (TEC1)					//ASOCIACION ENTRE BOTONES DEL MICROONDAS Y DE LA EDU-CIAA
#define TEC_START_STOP (TEC2)
#define TEC_PUERTA (TEC3)

#define NINGUN_BOTON_PRESIONADO 0		//Macro que indica que ningún botón fue presionado

#define MENSAJE_MODO_NO_SELECCIONADO "Debe seleccionar un modo: 1. Horno, 2. Grill, 3. H+G \r\n"

#define MENSAJE_PUERTA_ABIERTA "Cierre la puerta por favor \r\n"

#define MENSAJE_PAUSA "Pausa \r\n"

#define MENSAJE_CONTINUAR "Continuando \r\n"


void prefixIface_opLED(Prefix* handle, sc_integer LEDNumber, sc_boolean State)
{
	gpioWrite( (LEDG + LEDNumber), State);
}

extern void prefixIface_opModo_No_Seleccionado(const Prefix* handle)
{
	/*Función que envía un mensaje al usuario por UART, diciéndole
	 *que no ha seleccionado ningún modo, y entonces no puede comenzar
	 *a usar el microondas.*/

	debugPrintString( MENSAJE_MODO_NO_SELECCIONADO );
}

extern void prefixIface_opMensaje_Puerta_Abierta(const Prefix* handle)
{
	/*Función que envía un mensaje advirtiendo que la puerta del
	 *microondas está abierta y por ende no puede prenderse.*/

	debugPrintString( MENSAJE_PUERTA_ABIERTA);
}
extern void prefixIface_opMensaje_Pausa(const Prefix* handle)
{
	/*Función que envía un mensaje informadno que el microondas
	 *está en pausa.*/
	debugPrintString( MENSAJE_PAUSA);
}
extern void prefixIface_opMensaje_Continuar(const Prefix* handle)
{
	/*Función que envía un mensaje informando que el microondas
	 *vuelve a funcionar*/
	debugPrintString( MENSAJE_CONTINUAR);
}


#if (__USE_TIME_EVENTS == true)
/*! This function has to set up timers for the time events that are required by the state machine. */
/*!
	This function will be called for each time event that is relevant for a state when a state will be entered.
	\param evid An unique identifier of the event.
	\time_ms The time in milli seconds
	\periodic Indicates the the time event must be raised periodically until the timer is unset
*/
void prefix_setTimer(Prefix* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic)
{
	SetNewTimerTick(ticks, NOF_TIMERS, evid, time_ms, periodic);
}

/*! This function has to unset timers for the time events that are required by the state machine. */
/*!
	This function will be called for each time event taht is relevant for a state when a state will be left.
	\param evid An unique identifier of the event.
*/
void prefix_unsetTimer(Prefix* handle, const sc_eventid evid)
{
	UnsetTimerTick(ticks, NOF_TIMERS, evid);
}
#endif


/**
 * @brief	Hook on Handle interrupt from SysTick timer
 * @return	Nothing
 */
void myTickHook( void *ptr ){
	SysTick_Time_Flag = true;
}


uint32_t chequear_botones(void)
{
	/*Función que chequea qué botón de la EDU-CIAA se presionó.
	  No recibe parámetros, devuelve una variable uint32_t que
	  dice qué botón se presionó. De valer 0, entonces no se
	  presionó ninguno.*/

	uint32_t boton_presionado = 0;

	if(gpioRead(TEC_MODO) == 0)
	{
		boton_presionado = BOTON_MODO;
	}
	else if(gpioRead(TEC_START_STOP) == 0)
	{
		boton_presionado = BOTON_START_STOP;
	}
	else if(gpioRead(TEC_PUERTA) == 0)
	{
		boton_presionado = BOTON_PUERTA;
	}
	return boton_presionado;
}




int main(void)
{
	#if (__USE_TIME_EVENTS == true)
		uint32_t i;
	#endif

	/* Generic Initialization */
	boardConfig();

	/* Init Ticks counter => TICKRATE_MS */
	tickConfig( TICKRATE_MS );

	/* Add Tick Hook */
	tickCallbackSet( myTickHook, (void*)NULL );

	debugPrintConfigUart( UART_USB, 115200 );		//Configuro la UART por USB para enviar mensajes

	/* Statechart Initialization */
	#if (__USE_TIME_EVENTS == true)
	InitTimerTicks(ticks, NOF_TIMERS);
	#endif

	uint32_t boton_presionado = 0;			//Variable que indica qué botón se presionó: Si vale 0, ninguno

	prefix_init(&statechart);
	prefix_enter(&statechart);
//	prefix_runCycle(&statechart);		//Salgo del estado "INICIO"

	/* LEDs toggle in main */
	while (1) {
		__WFI();

		if (SysTick_Time_Flag == true)
		{
			SysTick_Time_Flag = false;

			//Se chequea si hay timers que deben cumplir su tiempo

			#if (__USE_TIME_EVENTS == true)
			UpdateTimers(ticks, NOF_TIMERS);
			for (i = 0; i < NOF_TIMERS; i++)
			{
				if (IsPendEvent(ticks, NOF_TIMERS, ticks[i].evid) == true)
				{

					prefix_raiseTimeEvent(&statechart, ticks[i].evid);	// Event -> Ticks.evid => OK
					MarkAsAttEvent(ticks, NOF_TIMERS, ticks[i].evid);
				}
			}
			#else
			prefixIface_raise_evTick(&statechart);					// Event -> evTick => OK
			#endif

			//Se chequea si alguno de los botones fue presionado

			if((boton_presionado = chequear_botones())!=NINGUN_BOTON_PRESIONADO)
			{
				prefixIface_raise_evTECXOprimido(&statechart, boton_presionado);
			}
			else
			{
				prefixIface_raise_evTECXNoOprimido(&statechart);
			}
			prefix_runCycle(&statechart);							// Run Cycle of Statechart
		}
	}
}





#endif
