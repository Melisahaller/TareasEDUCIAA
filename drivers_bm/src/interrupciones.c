/* Copyright 2016, XXXXXXXXX  
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
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

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/


#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#elif (mk60fx512vlq15 == CPU)
#else
#endif

#include "chip.h"
#include "interrupciones.h"



/*Inicializa la interrupción de timer
Parametro: Intervalo :setea el intervalo entre interrupciones
					  del timer en milisegundos*/

void InitIntTimerRIT(uint32_t Intervalo)
{
	Chip_RIT_Init(LPC_RITIMER);
	Chip_RIT_SetTimerInterval(LPC_RITIMER,Intervalo);
	NVIC_EnableIRQ(11);
}

void BorrarBanderaTimerRIT()
{
	Chip_RIT_ClearInt(LPC_RITIMER);
}

/*
 *  Inicializa y habilita el timer0 seteando el tiempo de disparo
 */
void InitIntTimer0(uint32_t milisegundos)
{
//	uint32_t FrecuenciaClk = Chip_Clock_GetBaseClocktHz (CLK_BASE_MX); // Leo la vellocidad del micro en khz
//	uint32_t MatchCount= milisegundos*FrecuenciaClk;                   // Establesco el valor de cuentas correspondiente a los milisegundos

	Chip_TIMER_Init(LPC_TIMER0);
//	Chip_TIMER_PrescaleSet(LPC_TIMER0, 0);
//	Chip_TIMER_TIMER_SetCountClockSrc (LPC_TIMER0, TIMER_CAPSRC_RISING_PCLK, 0); // Establee la fuente del reloj del timer. El terer paramatro no tiene funcion
	NVIC_EnableIRQ(12);																				//  si uso el PClk como fuente de reloj
//	Chip_TIMER_SetMatch(LPC_TIMER0, 1, MatchCount);
	Chip_TIMER_SetMatch(LPC_TIMER0, 1, 10000000000);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, 1);
	Chip_TIMER_MatchEnableInt(LPC_TIMER0, 1);
//	Chip_TIMER_Reset(LPC_TIMER0);
	Chip_TIMER_Enable(LPC_TIMER0);

	NVIC_EnableIRQ(12);

}

void BorrarBanderaTimer0()
{
	Chip_RIT_ClearInt(LPC_RITIMER);
}

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */




/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

