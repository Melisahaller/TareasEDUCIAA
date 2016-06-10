/* Copyright 2016, LED 2016
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

#include "led.h"
#include "chip.h"


void Init_Leds()
{
	Chip_GPIO_Init(LPC_GPIO_PORT);

	Chip_SCU_PinMux(PaqueteLedRGB,PinPaqR,MD_PUP,FUNC4);   // Remapea P2_0 en GPIO 5-0
	Chip_SCU_PinMux(PaqueteLedRGB,PinPaqG,MD_PUP,FUNC4);
	Chip_SCU_PinMux(PaqueteLedRGB,PinPaqB,MD_PUP,FUNC4);

	Chip_SCU_PinMux(PaqueteLed1,PinPaqLed1,MD_PUP,FUNC0);
	Chip_SCU_PinMux(PaqueteLed2,PinPaqLed2,MD_PUP,FUNC0);
	Chip_SCU_PinMux(PaqueteLed3,PinPaqLed3,MD_PUP,FUNC0);

	Chip_GPIO_SetDir(LPC_GPIO_PORT, PuertoLedRGB,1<<PinPuertoLedR,salida);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, PuertoLedRGB,1<<PinPuertoLedG,salida);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, PuertoLedRGB,1<<PinPuertoLedB,salida);
//	Chip_GPIO_SetDir(LPC_GPIO_PORT,PuertoLedRGB,1<<PinPuertoLedR|1<<PinPuertoLedG|1<<PinPuertoLedB,salida);
	/* setea RGB, puedo
	hacerlo entrelazado porque son todos del mismo puerto, si son distintos, tengo que hacerlo
	por separado como los de abajo*/
	Chip_GPIO_SetDir(LPC_GPIO_PORT,PuertoLed1,1<<PinPuertoLed1,salida);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,PuertoLed2,1<<PinPuertoLed2,salida);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,PuertoLed3,1<<PinPuertoLed3,salida);
}

void Prender(char a)
{
  switch (a)
  {
  	  case 'R':
  		  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PuertoLedRGB,PinPuertoLedR);
  		  break;

  	  case 'G':
  		  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PuertoLedRGB,PinPuertoLedG);
  		  break;

  	  case 'B':
  		  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PuertoLedRGB,PinPuertoLedB);
  		  break;

  	  case 'r':
  		  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PuertoLed1,PinPuertoLed1);
  		  break;

  	  case 'a':
  		  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PuertoLed2,PinPuertoLed2);
  		  break;

  	  case 'g':
  		  Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,PuertoLed3,PinPuertoLed3);
  		  break;
  }
}

void Apagar(char b)
{
	switch (b)
	{
      case 'R':
		  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PuertoLedRGB,PinPuertoLedR);
		  break;

	  case 'G':
		  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PuertoLedRGB,PinPuertoLedG);
		  break;

	  case 'B':
		  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PuertoLedRGB,PinPuertoLedB);
		  break;

	  case 'r':
		  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PuertoLed1,PinPuertoLed1);
		  break;

	  case 'a':
		  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PuertoLed2,PinPuertoLed2);
		  break;

	  case 'g':
		  Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT,PuertoLed3,PinPuertoLed3);
		  break;
	}
}

void Toggle (char b)
{
	switch (b)
	{
	  case 'R':
		  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PuertoLedRGB,PinPuertoLedR);
		  break;

	  case 'G':
		  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PuertoLedRGB,PinPuertoLedG);
		  break;

	  case 'B':
		  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PuertoLedRGB,PinPuertoLedB);
		  break;

	  case 'r':
		  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PuertoLed1,PinPuertoLed1);
		  break;

	  case 'a':
		  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PuertoLed2,PinPuertoLed2);
		  break;

	  case 'g':
		  Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,PuertoLed3,PinPuertoLed3);
		  break;
	  }
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

