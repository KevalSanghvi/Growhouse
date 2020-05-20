/***************************************************************************//**
 * @file
 * @brief Interrupt Module - Silicon Labs - Efm32Gg-Dk3750
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

/********************************************************************************************************
 ********************************************************************************************************
 *                                               MODULE
 ********************************************************************************************************
 *******************************************************************************************************/

#ifndef  _BSP_INT_H_
#define  _BSP_INT_H_

/********************************************************************************************************
 ********************************************************************************************************
 *                                            INCLUDE FILES
 ********************************************************************************************************
 *******************************************************************************************************/

#include  <cpu/include/cpu.h>
#include "em_device.h"

/********************************************************************************************************
 ********************************************************************************************************
 *                                     EXTERNAL C LANGUAGE LINKAGE
 *
 * Note(s) : (1) C++ compilers MUST 'extern'ally declare ALL C function prototypes & variable/object
 *               declarations for correct C language linkage.
 ********************************************************************************************************
 *******************************************************************************************************/

#ifdef __cplusplus
extern  "C" {                                                   // See Note #1.
#endif

/********************************************************************************************************
 ********************************************************************************************************
 *                                               DEFINES
 ********************************************************************************************************
 *******************************************************************************************************/

/********************************************************************************************************
 *                                          INTERRUPT SOURCES
 *******************************************************************************************************/

#define  BSP_INT_OFFSET                      16u

#define  BSP_INT_ID_DMA                (BSP_INT_OFFSET + DMA_IRQn)
#define  BSP_INT_ID_GPIO_EVEN          (BSP_INT_OFFSET + GPIO_EVEN_IRQn)
#define  BSP_INT_ID_TIMER0             (BSP_INT_OFFSET + TIMER0_IRQn)
#define  BSP_INT_ID_USART0_RX          (BSP_INT_OFFSET + USART0_RX_IRQn)
#define  BSP_INT_ID_USART0_TX          (BSP_INT_OFFSET + USART0_TX_IRQn)
#define  BSP_INT_ID_USB                (BSP_INT_OFFSET + USB_IRQn)
#define  BSP_INT_ID_ACMP0_ACMP1        (BSP_INT_OFFSET + ACMP0_IRQn)
#define  BSP_INT_ID_ADC0               (BSP_INT_OFFSET + ADC0_IRQn)
#define  BSP_INT_ID_DAC0               (BSP_INT_OFFSET + DAC0_IRQn)
#define  BSP_INT_ID_I2C0               (BSP_INT_OFFSET + I2C0_IRQn)
#define  BSP_INT_ID_I2C1               (BSP_INT_OFFSET + I2C1_IRQn)
#define  BSP_INT_ID_GPIO_ODD           (BSP_INT_OFFSET + GPIO_ODD_IRQn)
#define  BSP_INT_ID_TIMER1             (BSP_INT_OFFSET + TIMER1_IRQn)
#define  BSP_INT_ID_TIMER2             (BSP_INT_OFFSET + TIMER2_IRQn)
#define  BSP_INT_ID_TIMER3             (BSP_INT_OFFSET + TIMER3_IRQn)
#define  BSP_INT_ID_USART1_RX          (BSP_INT_OFFSET + USART1_RX_IRQn)
#define  BSP_INT_ID_USART1_TX          (BSP_INT_OFFSET + USART1_TX_IRQn)
#define  BSP_INT_ID_LESENSE            (BSP_INT_OFFSET + LESENSE_IRQn)
#define  BSP_INT_ID_USART2_RX          (BSP_INT_OFFSET + USART2_RX_IRQn)
#define  BSP_INT_ID_USART2_TX          (BSP_INT_OFFSET + USART2_TX_IRQn)
#define  BSP_INT_ID_UART0_RX           (BSP_INT_OFFSET + UART0_RX_IRQn)
#define  BSP_INT_ID_UART0_TX           (BSP_INT_OFFSET + UART0_TX_IRQn)
#define  BSP_INT_ID_UART1_RX           (BSP_INT_OFFSET + UART1_RX_IRQn)
#define  BSP_INT_ID_UART1_TX           (BSP_INT_OFFSET + UART1_TX_IRQn)
#define  BSP_INT_ID_LEUART0            (BSP_INT_OFFSET + LEUART0_IRQn)
#define  BSP_INT_ID_LEUART1            (BSP_INT_OFFSET + LEUART1_IRQn)
#define  BSP_INT_ID_LETIMER0           (BSP_INT_OFFSET + LETIMER0_IRQn)
#define  BSP_INT_ID_PCNT0              (BSP_INT_OFFSET + PCNT0_IRQn)
#define  BSP_INT_ID_PCNT1              (BSP_INT_OFFSET + PCNT1_IRQn)
#define  BSP_INT_ID_PCNT2              (BSP_INT_OFFSET + PCNT2_IRQn)
#define  BSP_INT_ID_RTC                (BSP_INT_OFFSET + RTC_IRQn)
#define  BSP_INT_ID_BURTC              (BSP_INT_OFFSET + BURTC_IRQn)
#define  BSP_INT_ID_CMU                (BSP_INT_OFFSET + CMU_IRQn)
#define  BSP_INT_ID_VCMP               (BSP_INT_OFFSET + VCMP_IRQn)
#define  BSP_INT_ID_LCD                (BSP_INT_OFFSET + LCD_IRQn)
#define  BSP_INT_ID_MSC                (BSP_INT_OFFSET + MSC_IRQn)
#define  BSP_INT_ID_AES                (BSP_INT_OFFSET + AES_IRQn)
#define  BSP_INT_ID_EBI                (BSP_INT_OFFSET + EBI_IRQn)
#define  BSP_INT_ID_EMU                (BSP_INT_OFFSET + EMU_IRQn)

#define  BSP_INT_ID_MAX                      39u                // # interrupts sources.

/********************************************************************************************************
 ********************************************************************************************************
 *                                         FUNCTION PROTOTYPES
 ********************************************************************************************************
 *******************************************************************************************************/

/********************************************************************************************************
 ********************************************************************************************************
 *                                   EXTERNAL C LANGUAGE LINKAGE END
 ********************************************************************************************************
 *******************************************************************************************************/

#ifdef __cplusplus
}                                                               // End of 'extern'al C lang linkage.
#endif

/********************************************************************************************************
 ********************************************************************************************************
 *                                             MODULE END
 ********************************************************************************************************
 *******************************************************************************************************/

#endif // End of module include.
