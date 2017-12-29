/* Copyright 2017, Ernesto Gigliotti
 * Copyright 2016, Juan Cecconi
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

/** \brief External Memory Controller (EMC) Arch source file
 **
 ** This file contains is the EMC driver Arch CortexM4\lpc43xx\lpc4337
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup EMC EMC Module
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * JuCe         Juan Cecconi 
 * ErGi         Ernesto Gigliotti
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160214 v0.0.1 JuCe initial version
 * 20171229 v0.0.2 ErGi Configuration using IP_EMC_DYN_CONFIG_T struct
 */

/*==================[inclusions]=============================================*/
#include "chip.h"
#include "EMC_Arch.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
STATIC const IP_EMC_DYN_CONFIG_T IS42S168007_config = {
		EMC_CLOCK(CIAA_EMC_LPC43XX_SDRAM_REFRESH),    // Row refresh time
		(CIAA_EMC_LPC43XX_SDRAM_RDCFG_RD << CIAA_EMC_LPC43XX_DYRDCFG_RD_BITS),    // Command Delayed
		EMC_CLOCK(CIAA_EMC_LPC43XX_SDRAM_T_RP - 1), // CRP
        	EMC_CLOCK(CIAA_EMC_LPC43XX_SDRAM_T_RAS - 1), // RAS
	        EMC_CLOCK(CIAA_EMC_LPC43XX_SDRAM_T_SREX - 1), // REX
	        EMC_CLOCK(CIAA_EMC_LPC43XX_SDRAM_T_APR - 1), // CAPR
	        EMC_CLOCK(CIAA_EMC_LPC43XX_SDRAM_T_DAL), // DAL
	        EMC_CLOCK(CIAA_EMC_LPC43XX_SDRAM_T_WR - 1), // WR
	        EMC_CLOCK(CIAA_EMC_LPC43XX_SDRAM_T_RC - 1), // RC
	        EMC_CLOCK(CIAA_EMC_LPC43XX_SDRAM_T_RFC - 1), // RFC
	        EMC_CLOCK(CIAA_EMC_LPC43XX_SDRAM_T_XSR - 1), // XSR
	        EMC_CLOCK(CIAA_EMC_LPC43XX_SDRAM_T_RRD - 1), // RRD
	        EMC_CLOCK(CIAA_EMC_LPC43XX_SDRAM_T_MRD - 1), // MRD
        	{
        	        {
        	                EMC_ADDRESS_DYCS0,    /* uses DYCS0 for SDRAM */
				CIAA_EMC_LPC43XX_SDRAM_RAS,    /* RAS */
        	                EMC_DYN_MODE_WBMODE_PROGRAMMED | // OK
        	                EMC_DYN_MODE_OPMODE_STANDARD |
        	                EMC_DYN_MODE_CAS_2 | // CAS:2
        	                EMC_DYN_MODE_BURST_TYPE_SEQUENTIAL | // OK
        	                EMC_DYN_MODE_BURST_LEN_8, // OK
        	                EMC_DYN_CONFIG_DATA_BUS_16 |
        	                EMC_DYN_CONFIG_LPSDRAM |
				EMC_DYN_CONFIG_8Mx16_4BANKS_12ROWS_9COLS |
        	                EMC_DYN_CONFIG_MD_SDRAM
        	        },
        	        {0, 0, 0, 0},
        	        {0, 0, 0, 0},
        	        {0, 0, 0, 0}
        	}
};

/*==================[internal functions declaration]=========================*/
/** \brief Initialize SDRAM Pins
 **
 ** This function initialize MUX for SDRAM Pins based on this Arch
 **/
bool EMC_Initialize_SDRAM_PinsMux(void);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

bool EMC_Initialize_SDRAM_PinsMux(void)
{
   /*
	* EMC pins used for SDRAM memory
   */

   /* P1.6 = WE# - SDRAM */
   Chip_SCU_PinMuxSet(0x1, 6, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));

   /* P2.10 = A1 - SDRAM */
   Chip_SCU_PinMuxSet(0x2, 10, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P2.11 = A2 - SDRAM */
   Chip_SCU_PinMuxSet(0x2, 11, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P2.12 = A3 - SDRAM */
   Chip_SCU_PinMuxSet(0x2, 12, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P2.13 = A4 - SDRAM */
   Chip_SCU_PinMuxSet(0x2, 13, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P1.0 = A5 - SDRAM */
   Chip_SCU_PinMuxSet(0x1, 0, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P1.1 = A6 - SDRAM */
   Chip_SCU_PinMuxSet(0x1, 1, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P1.2 = A7 - SDRAM */
   Chip_SCU_PinMuxSet(0x1, 2, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P2.8 = A8 - SDRAM */
   Chip_SCU_PinMuxSet(0x2, 8, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P2.7 = A9 - SDRAM */
   Chip_SCU_PinMuxSet(0x2, 7, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P2.6 = A10 - SDRAM */
   Chip_SCU_PinMuxSet(0x2, 6, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P2.2 = A11 - SDRAM */
   Chip_SCU_PinMuxSet(0x2, 2, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P2.1 = A12 - SDRAM */
//   Chip_SCU_PinMuxSet(0x2, 1, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P2.0 = BA0 for SDRAM (= A13) - SDRAM */
   Chip_SCU_PinMuxSet(0x2, 0, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P6.8 = BA1 for SDRAM (= A14) - SDRAM */
   Chip_SCU_PinMuxSet(0x6, 8, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC1));

   /* P1.7 = D0 - SDRAM */
   Chip_SCU_PinMuxSet(0x1, 7, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P1.8 = D1 - SDRAM */
   Chip_SCU_PinMuxSet(0x1, 8, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P1.9 = D2 - SDRAM */
   Chip_SCU_PinMuxSet(0x1, 9, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P1.10 = D3 - SDRAM */
   Chip_SCU_PinMuxSet(0x1, 10, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P1.11 = D4 - SDRAM */
   Chip_SCU_PinMuxSet(0x1, 11, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P1.12 = D5 - SDRAM */
   Chip_SCU_PinMuxSet(0x1, 12, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P1.13 = D6 - SDRAM */
   Chip_SCU_PinMuxSet(0x1, 13, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P1.14 = D7 - SDRAM */
   Chip_SCU_PinMuxSet(0x1, 14, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P5.4 = D8 - SDRAM */
   Chip_SCU_PinMuxSet(0x5, 4, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P5.5 = D9 - SDRAM */
   Chip_SCU_PinMuxSet(0x5, 5, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P5.6 = D10 - SDRAM */
   Chip_SCU_PinMuxSet(0x5, 6, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P5.7 = D11 - SDRAM */
   Chip_SCU_PinMuxSet(0x5, 7, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P5.0 = D12 - SDRAM */
   Chip_SCU_PinMuxSet(0x5, 0, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P5.1 = D13 - SDRAM */
   Chip_SCU_PinMuxSet(0x5, 1, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P5.2 = D14 - SDRAM */
   Chip_SCU_PinMuxSet(0x5, 2, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));
   /* P5.3 = D15 - SDRAM */
   Chip_SCU_PinMuxSet(0x5, 3, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC2));

   /*
	 * Configuration for EMC pins used only for SDRAM
	 */
   /*
	 * To use 16-bit wide and 32-bit wide SDRAM interfaces, select
	 * the EMC_CLK function and enable the input buffer (EZI = 1)
	 * in all four SFSCLKn registers in the SCU.
	 */
   /* Imaginary P-0x18.0 = CLK (CLK0) - SDRAM */
   Chip_SCU_PinMuxSet(0x18, 0, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC0));
   /* Imaginary P-0x18.1 = CLK1 - SDRAM */
   Chip_SCU_PinMuxSet(0x18, 1, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC0));
   /* Imaginary P-0x18.2 = CLK2 - SDRAM */
   Chip_SCU_PinMuxSet(0x18, 2, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC0));
   /* Imaginary P-0x18.3 = CLK3 - SDRAM */
   Chip_SCU_PinMuxSet(0x18, 3, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC0));

   /* P6.11 = CKE - SDRAM */
   Chip_SCU_PinMuxSet(0x6, 11, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P6.9 = CS# (nDYCS0) - SDRAM */
   Chip_SCU_PinMuxSet(0x6, 9, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));

   /* P6.5 = RAS# - SDRAM */
   Chip_SCU_PinMuxSet(0x6, 5, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P6.4 = CAS# - SDRAM */
   Chip_SCU_PinMuxSet(0x6, 4, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P6.12 = DQM0 - SDRAM */
   Chip_SCU_PinMuxSet(0x6, 12, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   /* P6.10 = DQM1 - SDRAM */
   Chip_SCU_PinMuxSet(0x6, 10, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));

   /* P2.9 = A0 - SDRAM */
   Chip_SCU_PinMuxSet(0x2, 9, CIAA_EMC_FAST_IO_CONFIG(SCU_MODE_FUNC3));
   
   return TRUE;
}

/*==================[external functions definition]==========================*/

extern bool EMC_Initialize_Arch(void)
{
   return EMC_Initialize_SDRAM_Arch();
}

extern bool EMC_Initialize_SDRAM_Arch(void)
{
	/*
	* Configure MCU pins
	*/
	EMC_Initialize_SDRAM_PinsMux();

	/*
	* Configure SDRAM chip
	*/
  	Chip_EMC_Dynamic_Init((IP_EMC_DYN_CONFIG_T *) &IS42S168007_config);
	Chip_EMC_Dynamic_Enable(1);

	return TRUE;
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

