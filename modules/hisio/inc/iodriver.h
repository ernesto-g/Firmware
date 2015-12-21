/* Copyright 2015, Mariano Cerdeiro
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

#ifndef IODRIVER_H
#define IODRIVER_H
/** \brief Short description of this file
 **
 ** Long description of this file
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Template Template to start a new module
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
#include "iodriver_Ext.h"
#include "iodriver_Cfg.h"

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/
/** \brief Possible return values of IO_ErrorType
 **
 ** Values between 0 and 15 are reserved for the IO Library, between 16 and 63
 ** for the IO Drivers and between 64 and 127 are implementation specific.
 ** Values above 127 are reserved for future implementations.
 **
 **/
#ifndef IO_E_OK
#define IO_E_OK                  0
#endif
#ifndef IO_E_BUSY
#define IO_E_BUSY                1
#define
#ifndef IO_E_UNKNOWN_MODE
#define IO_E_UNKNOWN_MODE        2
#endif
#define IO_E_FCN_SUSPENDED       16
#define IO_E_PARAM_IGNORED       17
#define IO_E_INVALID_CHANNEL_ID  18
#define IO_E_INVALID_VALUE       19
#define IO_E_INVALID_SIZE        20
#define IO_E_INVALID_POSITION    21
#define IO_E_INVALID_NOTIF_TYPE  22

/** \brief Returns the DIO Driver Version
 **
 ** \remarks This function shall be implemented as a macro, this is
 **          required on the specification.
 **/
#define DIO_GetVersionOfDriver   IO_Version(0,0,1,0);

/*==================[typedef]================================================*/
typedef uint8_t IO_ErrorType;

#if IO_PORT_SIZE == IO_PORT_SIZE_8
typedef uint8_t IO_ValueType;
#elif IO_PORT_SIZE == IO_PORT_SIZE_16
typedef uint16_t IO_ValueType;
#elif IO_PORT_SIZE == IO_PORT_SIZE_32
typedef uint32_t IO_ValueType;
#else
#error Not supported IO_PORT_SIZE has been defined
#endif

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/** \brief
 **/
extern IO_ErrorType DIO_InitSync(void * address);

extern IO_ErrorType DIO_DeInitSync(void * address);

extern IO_ErrorType DIO_IoctlSync(IO_ModeType mode, void * address);

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef IODRIVER_H */

