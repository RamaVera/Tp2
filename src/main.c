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
#include "sapi.h"       // <= sAPI header


#include "Prefix.h"
#include "TimerTicks.h"

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

