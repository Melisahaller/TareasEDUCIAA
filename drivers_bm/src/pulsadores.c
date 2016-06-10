/* Copyright 2016,  Melisa Haller  2016
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

#include "pulsadores.h"
#include "chip.h"


void InicializarPulsadores(void)
{
	Chip_GPIO_Init(LPC_GPIO_PORT);

	Chip_SCU_PinMux(PaquetePuls0,PinPaqPuls0,MD_PUP|MD_EZI|MD_ZI,FUNC0);  /* mapea P1_0 en GPIO 0[4], SW0 */
	Chip_SCU_PinMux(PaquetePuls1,PinPaqPuls1,MD_PUP|MD_EZI|MD_ZI,FUNC0);  /* mapea P1_1 en GPIO 0[8], SW1 */
	Chip_SCU_PinMux(PaquetePuls2,PinPaqPuls2,MD_PUP|MD_EZI|MD_ZI,FUNC0);  /* mapea P1_2 en GPIO 0[9], SW2 */
	Chip_SCU_PinMux(PaquetePuls3,PinPaqPuls3,MD_PUP|MD_EZI|MD_ZI,FUNC0);  /* mapea P1_6 en GPIO 1[9], SW3 */

	Chip_GPIO_SetDir(LPC_GPIO_PORT,PuertoPuls0,1<<PinPuertoPuls0,entrada);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,PuertoPuls1,1<<PinPuertoPuls1,entrada);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,PuertoPuls2,1<<PinPuertoPuls2,entrada);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,PuertoPuls3,1<<PinPuertoPuls3,entrada);


}

uint8_t LeerPulsador(uint8_t tec)
{
	switch (tec)
	{
		case 1:
			if(Chip_GPIO_GetPinState(LPC_GPIO_PORT,PuertoPuls0,PinPuertoPuls0))
				return Pulsado;
			else return NoPulsado;
			break;
		case 2:
			if(Chip_GPIO_GetPinState(LPC_GPIO_PORT,PuertoPuls1,PinPuertoPuls1))
				return Pulsado;
			else return NoPulsado;
			break;
		case 3:
			if(Chip_GPIO_GetPinState(LPC_GPIO_PORT,PuertoPuls2,PinPuertoPuls2))
				return Pulsado;
			else return NoPulsado;
			break;
		case 4:
			if(Chip_GPIO_GetPinState(LPC_GPIO_PORT,PuertoPuls3,PinPuertoPuls3))
				return Pulsado;
			else return NoPulsado;
			break;
		default: return NoPulsado;
	}

}

uint8_t EscanearPulsadores()
{
	if(!Chip_GPIO_GetPinState(LPC_GPIO_PORT,PuertoPuls0,PinPuertoPuls0))
		return Tecla1;
	else if(!Chip_GPIO_GetPinState(LPC_GPIO_PORT,PuertoPuls1,PinPuertoPuls1))
		return Tecla2;
	else if(!Chip_GPIO_GetPinState(LPC_GPIO_PORT,PuertoPuls2,PinPuertoPuls2))
		return Tecla3;
	else if(!Chip_GPIO_GetPinState(LPC_GPIO_PORT,PuertoPuls3,PinPuertoPuls3))
		return Tecla4;
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

