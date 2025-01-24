;/*****************************************************************************/
;/* py32f002b_OPT.S: y32f002b Flash Option Bytes                              */
;/*****************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                          */
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2008 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/


;// <e> Flash Option Bytes
FLASH_OPT       EQU     0
;// </e>


                IF      FLASH_OPT <> 0
                AREA    |.ARM.__AT_0x1FFF0080|, CODE, READONLY
                DCB     0xAA,  0xDE,  0x55,  0x21
                DCB     0x0B,  0x00,  0xF4,  0xFF
                DCB     0x00,  0x00,  0xFF,  0xFF    
                DCB     0x3F,  0x00,  0xC0,  0xFF  
                ENDIF


                END
