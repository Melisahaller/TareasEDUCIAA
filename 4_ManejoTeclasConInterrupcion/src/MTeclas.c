/* Copyright 2016, miblink
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

/** \brief Blinking Bare Metal example source file
 **
 ** ** Actividad N°3: PSICODELIA (sin struct)
 ** COMO HAGO PARA QUE LOS DOS DELAY SE PUEDAN RESTAR Y PONERLOS EN OTRA VARIABLE DELAYX
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
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
#include "chip.h"
#include "led.h"       /* <= own header */
#include "pulsadores.h"

/*==================[macros and definitions]=================================*/
#define DELAY 800000
#define DELAY2 42000000

#define TiempoLargo //TParpadeo 500
#define TiempoCorto //TiempoParpadeo (TParpadeo/IntervaloDeTiempo)

#define AuxTiempoLargo (TiempoLargo / TiempoCorto)

uint32_t contTiempoLargo=AuxTiempoLargo;
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
int8_t pulsada;
char aux;
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



int main(void)
{
   /* perform the needed initialization here */

	Init_Leds();
	InicializarPulsadores();
	InitIntTimerRIT(TiempoCorto);

	pulsada=EscanearPulsadores();

	while (1)
	{
		asm("nop");
	}

}
void LeeTeclado()
{
	aux=EscanearPulsadores();
	if(aux!=0)
	pulsada=aux;
}



void TiempoInterrupcion()
{
	Tecla();/// Acá Ejecutamos la función que queramos en el CICLO CORTO (TiempoCorto definido al inicio en milisegundos)

	if (contTiempoLargo>0)
	{
		contTiempoLargo--;
	}
	else
	{
		contTiempoLargo=AuxTiempoLargo;

		ParpadeoLed(pulsada);/// Acá Ejecutamos la función que queramos en el ciclo largo (TiempoLargo definido al inicio en milisegundos)
	}
	BorrarBanderaTimerRIT();
}

void Tecla()
{
	char aux;
	aux=EscanearPulsadores();
	if(aux!=0)
	pulsada=aux;
}

void ParpadoLed(uint8_t puls)
{
	switch (puls)
	{
		case 1:
 			Toggle('R');
 			Apagar('r');
 			Apagar('a');
 			Apagar('g');
 			break;
 		case 2:
 			Toggle('r');
 			Apagar('R');
 			Apagar('a');
 			Apagar('g');
 			break;
 		case 3:
 			Toggle('a');
 			Apagar('R');
 			Apagar('r');
 			Apagar('g');
 			break;
 		case 4:
 			Toggle('g');
 			Apagar('R');
 			Apagar('r');
 			Apagar('a');
 			break;
	}
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

