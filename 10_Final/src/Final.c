/* Copyright 2016, FINAL
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

/** \brief Final
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Serial
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
#include "stdint.h"
#include "led.h"
#include "adconv.h"
#include "serial.h"
#include "pulsadores.h"
#include "timers.h"
#include "analogpin.h"
#include "chip.h"

/*==================[macros and definitions]=================================*/
#define INICIO_FACTOR    127
#define TiempoInt 10
#define TU           700
#define U2           2
#define B_RATE          115200
#define GANANCIA        3

/*==================[internal data declaration]==============================*/
uint8_t auxiliar;
uint8_t estado;
uint32_t teclas_count[4];
uint32_t etec3_TU;

uint8_t estado_led;
uint8_t acumulado;
uint8_t DAC_EST;
uint8_t SERIAL;
uint8_t  valor_dac;

uint8_t aux_pulsador;
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

void Cambiar_Estado_Led()
{
	Toggle ('r');
}


void TiempoInterrupcion()
{
		aux_pulsador = EscanearPulsadores();
	    switch(aux_pulsador)
		{
		   case Tecla1:
			   	   	   DAC_EST = 1;
			   	   	   acumulado += GANANCIA;

			   	   	   break;

		   case Tecla2:
		    	   	   DAC_EST = 1;
		    	   	   acumulado -= GANANCIA;

		    	   	   break;

		   case Tecla3:
			   	   	   DAC_EST = 0;
			   	   	   break;

		   case Tecla4:
			   	   	   break;
}


	uint8_t auxserie;
	uint16_t aux;
	uint32_t aux2;
	aux = RecibirADC();
	if(aux > 0)
		{
	     Cambiar_Estado_Led();
		}
	aux2 = (uint32_t) (aux*(10*acumulado/INICIO_FACTOR)/10);
    if(aux2>1024)
    {
    	valor_dac = 1024;
    }
    else
    {
	valor_dac = (uint16_t) aux2;
    }

	while(!Enviar_DAC(valor_dac));

    auxserie = (uint8_t) aux;
	while(!Enviar_num( auxserie));
	Chip_RIT_ClearInt(LPC_RITIMER);

}

int main(void)
{
   /*
    * Inicializaciones
    *
    */
	Init_Leds();
	Inicializar_Pulsadores();
	InitIntTimerRIT(TiempoInt);
	Init_Serial(U2,B_RATE);
	Init_AD(1,1);
	Init_DAC(0);
	Init_Timers();

//	while (!Init_Teclas(&pulsador[0],0,4,1,0,0));
//    while (!Init_Teclas(&pulsador[1],0,8,1,1,0));
//	while (!Init_Teclas(&pulsador[2],0,9,1,2,0));
//	while (!Init_Teclas(&pulsador[3],1,9,1,6,0));

	 /*
	  * SETEOS
	  *
	  */

    Setear_Tiempo(TiempoInt);
    acumulado = INICIO_FACTOR;

   while(1)
   {

   }

}

void Enviar_Aumento()
{
	int i;
	char puls1[] = "Aumenta Amplitud";
	for (i=0; i<strlen(puls1); i++)
	{
		Enviar(puls1[i]);
	}
}

void Enviar_Disminuye()
{
	int i;
	char puls2[] = "Disminuye Amplitud";
	for (i=0; i<strlen(puls2); i++)
	{
		Enviar(puls2[i]);
	}
}

void Enviar_Cero()
{
	int i;
	char puls3[] = "Cero Amplitud";
	for (i=0; i<strlen(puls3); i++)
	{
		Enviar(puls3[i]);
	}
}

void Enviar_FINAL()
{
	int i;
	char puls4[] = "HALLER APRUEBA";
	for (i=0; i<strlen(puls4); i++)
	{
		Enviar(puls4[i]);
	}
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

