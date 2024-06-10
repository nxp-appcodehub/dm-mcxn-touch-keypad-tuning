/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief FRDM-TOUCH board defines */

/* Push buttons - mutual electrodes */
#define EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_0 TF_TSI_MUTUAL_CAP_TX_CHANNEL_5
#define EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_1 TF_TSI_MUTUAL_CAP_TX_CHANNEL_3
#define EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_2 TF_TSI_MUTUAL_CAP_TX_CHANNEL_2
#define EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_3 TF_TSI_MUTUAL_CAP_TX_CHANNEL_1
#define EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_4 TF_TSI_MUTUAL_CAP_TX_CHANNEL_0

#define EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_0 TF_TSI_MUTUAL_CAP_RX_CHANNEL_6
#define EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_1 TF_TSI_MUTUAL_CAP_RX_CHANNEL_7
#define EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_2 TF_TSI_MUTUAL_CAP_RX_CHANNEL_8
#define EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_3 TF_TSI_MUTUAL_CAP_RX_CHANNEL_9
#define EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_4 TF_TSI_MUTUAL_CAP_RX_CHANNEL_10

#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_0  NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_0,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_0)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_1  NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_1,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_0)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_2  NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_2,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_0)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_3  NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_3,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_0)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_4  NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_4,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_0)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_5  NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_0,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_1)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_6  NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_1,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_1)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_7  NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_2,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_1)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_8  NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_3,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_1)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_9  NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_4,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_1)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_10 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_0,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_2)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_11 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_1,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_2)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_12 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_2,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_2)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_13 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_3,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_2)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_14 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_4,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_2)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_15 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_0,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_3)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_16 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_1,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_3)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_17 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_2,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_3)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_18 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_3,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_3)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_19 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_4,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_3)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_20 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_0,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_4)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_21 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_1,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_4)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_22 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_2,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_4)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_23 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_3,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_4)
#define EVB_BOARD_TSI_MUTUAL_ELECTRODE_24 NT_TSI_TRANSFORM_MUTUAL(EVB_BOARD_TSI_MUTUAL_RX_ELECTRODE_4,EVB_BOARD_TSI_MUTUAL_TX_ELECTRODE_4)

/* Spring electrodes */
#define EVB_BOARD_SPRING_ELECTRODE_1  TF_TSI_SELF_CAP_CHANNEL_20
#define EVB_BOARD_SPRING_ELECTRODE_2  TF_TSI_SELF_CAP_CHANNEL_22

/* Self-cap Touch Keys */
#define EVB_BOARD_SELF_TOUCHKEY1  TF_TSI_SELF_CAP_CHANNEL_23
#define EVB_BOARD_SELF_TOUCHKEY2  TF_TSI_SELF_CAP_CHANNEL_0

/* Touch pad electrodes */
#define EVB_BOARD_TOUCHPAD_1_ELECTRODE   TF_TSI_SELF_CAP_CHANNEL_19
#define EVB_BOARD_TOUCHPAD_2_ELECTRODE   TF_TSI_SELF_CAP_CHANNEL_18
#define EVB_BOARD_TOUCHPAD_3_ELECTRODE   TF_TSI_SELF_CAP_CHANNEL_17
#define EVB_BOARD_TOUCHPAD_4_ELECTRODE   TF_TSI_SELF_CAP_CHANNEL_16
#define EVB_BOARD_TOUCHPAD_5_ELECTRODE   TF_TSI_SELF_CAP_CHANNEL_15
#define EVB_BOARD_TOUCHPAD_6_ELECTRODE   TF_TSI_SELF_CAP_CHANNEL_10
#define EVB_BOARD_TOUCHPAD_7_ELECTRODE   TF_TSI_SELF_CAP_CHANNEL_9
#define EVB_BOARD_TOUCHPAD_8_ELECTRODE   TF_TSI_SELF_CAP_CHANNEL_11
#define EVB_BOARD_TOUCHPAD_9_ELECTRODE   TF_TSI_SELF_CAP_CHANNEL_14
#define EVB_BOARD_TOUCHPAD_10_ELECTRODE  TF_TSI_SELF_CAP_CHANNEL_13
#define EVB_BOARD_TOUCHPAD_11_ELECTRODE  TF_TSI_SELF_CAP_CHANNEL_8
#define EVB_BOARD_TOUCHPAD_12_ELECTRODE  TF_TSI_SELF_CAP_CHANNEL_6
#define EVB_BOARD_TOUCHPAD_13_ELECTRODE  TF_TSI_SELF_CAP_CHANNEL_5
#define EVB_BOARD_TOUCHPAD_14_ELECTRODE  TF_TSI_SELF_CAP_CHANNEL_3
#define EVB_BOARD_TOUCHPAD_15_ELECTRODE  TF_TSI_SELF_CAP_CHANNEL_2

/* IO Headers connected to FRDM shield board */
/* X-DC-GESTURE */
/*
Touchpad electrode positioning:
TSI1_CH 24 23  22  21  20  19 
       R6  R5  R4  R3  R2  R1
       x   x   x   x   x   x C1 18	
       x   x   x   x   x   x C2 17
       x   x   x   x   x   x C3 16
       x   x   x   x   x   x C4 15
       x   x   x   x   x   x C5 14 
       x   x   x   x   x   x C5 13
                                TSI1_CH
*/
#define EVB_BOARD_TOUCHPAD_ELECTRODE_R1 TF_TSI_SELF_CAP_CHANNEL_23
#define EVB_BOARD_TOUCHPAD_ELECTRODE_R2 TF_TSI_SELF_CAP_CHANNEL_22
#define EVB_BOARD_TOUCHPAD_ELECTRODE_R3 TF_TSI_SELF_CAP_CHANNEL_21
#define EVB_BOARD_TOUCHPAD_ELECTRODE_R4 TF_TSI_SELF_CAP_CHANNEL_20
#define EVB_BOARD_TOUCHPAD_ELECTRODE_R5 TF_TSI_SELF_CAP_CHANNEL_19
#define EVB_BOARD_TOUCHPAD_ELECTRODE_R6 TF_TSI_SELF_CAP_CHANNEL_18
                          
#define EVB_BOARD_TOUCHPAD_ELECTRODE_C1 TF_TSI_SELF_CAP_CHANNEL_17
#define EVB_BOARD_TOUCHPAD_ELECTRODE_C2 TF_TSI_SELF_CAP_CHANNEL_16
#define EVB_BOARD_TOUCHPAD_ELECTRODE_C3 TF_TSI_SELF_CAP_CHANNEL_15
#define EVB_BOARD_TOUCHPAD_ELECTRODE_C4 TF_TSI_SELF_CAP_CHANNEL_14
#define EVB_BOARD_TOUCHPAD_ELECTRODE_C5 TF_TSI_SELF_CAP_CHANNEL_13
#define EVB_BOARD_TOUCHPAD_ELECTRODE_C6 TF_TSI_SELF_CAP_CHANNEL_11

#define EVB_BOARD_TOUCHPAD_ELECTRODE_SHIELD TF_TSI_SELF_CAP_CHANNEL_12

/*! @brief The board name */
#define BOARD_NAME "FRDM-KE17Z"

/*! @brief The UART to use for debug messages. */
#define BOARD_USE_UART
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART0
#define BOARD_DEBUG_UART_INSTANCE 0U
#define BOARD_DEBUG_UART_CLKSRC   kCLOCK_IpSrcSysOscAsync
#define BOARD_UART_IRQ            LPUART0_IRQn
#define BOARD_UART_IRQ_HANDLER    LPUART0_IRQHandler

/* @Brief Board accelerator sensor configuration */
#define BOARD_ACCEL_I2C_BASEADDR   LPI2C0
#define BOARD_ACCEL_I2C_CLOCK_FREQ CLOCK_GetIpFreq(kCLOCK_Lpi2c0)

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE 115200
#endif /* BOARD_DEBUG_UART_BAUDRATE */

/*! @brief The i2c instance used for i2c connection by default */
#define BOARD_I2C_BASEADDR I2C0

/*! @brief The CMP instance/channel used for board. */
#define BOARD_CMP_BASEADDR CMP0
#define BOARD_CMP_CHANNEL  7U

/*! @brief The rtc instance used for board. */
#define BOARD_RTC_FUNC_BASEADDR RTC

/*! @brief Define the port interrupt number for the board switches */
#define BOARD_SW2_GPIO GPIOB
#define BOARD_SW2_PORT PORTB
#define BOARD_SW2_GPIO_PIN 11U
#define BOARD_SW2_IRQ PORTBCD_IRQn
#define BOARD_SW2_IRQ_HANDLER PORTBCD_IRQHandler
#define BOARD_SW2_NAME "SW2"

/* Board RGB LED color mapping */
#define LOGIC_LED_ON 0U
#define LOGIC_LED_OFF 1U

#define BOARD_LED0_GPIO FGPIOA
#define BOARD_LED0_GPIO_PORT FPORTA
#define BOARD_LED0_GPIO_PIN 14U
#define BOARD_LED1_GPIO FGPIOC
#define BOARD_LED1_GPIO_PORT FPORTC
#define BOARD_LED1_GPIO_PIN 3U
#define BOARD_LED2_GPIO FGPIOC
#define BOARD_LED2_GPIO_PORT FPORTC
#define BOARD_LED2_GPIO_PIN 2U
#define BOARD_LED3_GPIO FGPIOD
#define BOARD_LED3_GPIO_PORT FPORTD
#define BOARD_LED3_GPIO_PIN 7U
#define BOARD_LED4_GPIO FGPIOD
#define BOARD_LED4_GPIO_PORT FPORTD
#define BOARD_LED4_GPIO_PIN 5U
#define BOARD_LED5_GPIO FGPIOB
#define BOARD_LED5_GPIO_PORT FPORTB
#define BOARD_LED5_GPIO_PIN 8U
#define BOARD_LED6_GPIO FGPIOB
#define BOARD_LED6_GPIO_PORT FPORTB
#define BOARD_LED6_GPIO_PIN 9U
#define BOARD_LED7_GPIO FGPIOB
#define BOARD_LED7_GPIO_PORT FPORTB
#define BOARD_LED7_GPIO_PIN 10U
#define BOARD_LED8_GPIO FGPIOD
#define BOARD_LED8_GPIO_PORT FPORTD
#define BOARD_LED8_GPIO_PIN 6U
#define BOARD_LED9_GPIO FGPIOD
#define BOARD_LED9_GPIO_PORT FPORTD
#define BOARD_LED9_GPIO_PIN 12U
#define BOARD_LED10_GPIO FGPIOD
#define BOARD_LED10_GPIO_PORT FPORTD
#define BOARD_LED10_GPIO_PIN 11U
#define BOARD_LED11_GPIO FGPIOD
#define BOARD_LED11_GPIO_PORT FPORTD
#define BOARD_LED11_GPIO_PIN 10U
#define BOARD_LED12_GPIO FGPIOC
#define BOARD_LED12_GPIO_PORT FPORTC
#define BOARD_LED12_GPIO_PIN 12U
#define BOARD_LED13_GPIO FGPIOB
#define BOARD_LED13_GPIO_PORT FPORTB
#define BOARD_LED13_GPIO_PIN 17U
#define BOARD_LED14_GPIO FGPIOA
#define BOARD_LED14_GPIO_PORT FPORTA
#define BOARD_LED14_GPIO_PIN 17U

#define LED0_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED0_GPIO, BOARD_LED0_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED0 */
#define LED0_ON() \
    FGPIO_PinWrite(BOARD_LED0_GPIO, BOARD_LED0_GPIO_PIN, 0)  /*!< Turn on target LED0 */
#define LED0_OFF() \
    FGPIO_PinWrite(BOARD_LED0_GPIO, BOARD_LED0_GPIO_PIN, 1)    /*!< Turn off target LED0 */
#define LED0_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED0_GPIO, 1U << BOARD_LED0_GPIO_PIN) /*!< Toggle on target LED0 */

#define LED1_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED1_GPIO, BOARD_LED1_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED1 */
#define LED1_ON() \
    FGPIO_PinWrite(BOARD_LED1_GPIO, BOARD_LED1_GPIO_PIN, 0)  /*!< Turn on target LED1 */
#define LED1_OFF() \
    FGPIO_PinWrite(BOARD_LED1_GPIO, BOARD_LED1_GPIO_PIN, 1)    /*!< Turn off target LED1 */
#define LED1_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED1_GPIO, 1U << BOARD_LED1_GPIO_PIN) /*!< Toggle on target LED1 */
        
#define LED2_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED2_GPIO, BOARD_LED2_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED2 */
#define LED2_ON() \
    FGPIO_PinWrite(BOARD_LED2_GPIO, BOARD_LED2_GPIO_PIN, 0)  /*!< Turn on target LED2 */
#define LED2_OFF() \
    FGPIO_PinWrite(BOARD_LED2_GPIO, BOARD_LED2_GPIO_PIN, 1)    /*!< Turn off target LED2 */
#define LED2_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED2_GPIO, 1U << BOARD_LED2_GPIO_PIN) /*!< Toggle on target LED2 */

#define LED3_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED3_GPIO, BOARD_LED3_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED3 */
#define LED3_ON() \
    FGPIO_PinWrite(BOARD_LED3_GPIO, BOARD_LED3_GPIO_PIN, 0)  /*!< Turn on target LED3 */
#define LED3_OFF() \
    FGPIO_PinWrite(BOARD_LED3_GPIO, BOARD_LED3_GPIO_PIN, 1)    /*!< Turn off target LED3 */
#define LED3_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED3_GPIO, 1U << BOARD_LED3_GPIO_PIN) /*!< Toggle on target LED3 */

#define LED4_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED4_GPIO, BOARD_LED4_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED4 */
#define LED4_ON() \
    FGPIO_PinWrite(BOARD_LED4_GPIO, BOARD_LED4_GPIO_PIN, 0)  /*!< Turn on target LED4 */
#define LED4_OFF() \
    FGPIO_PinWrite(BOARD_LED4_GPIO, BOARD_LED4_GPIO_PIN, 1)    /*!< Turn off target LED4 */
#define LED4_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED4_GPIO, 1U << BOARD_LED4_GPIO_PIN) /*!< Toggle on target LED4 */

#define LED5_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED5_GPIO, BOARD_LED5_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED5 */
#define LED5_ON() \
    FGPIO_PinWrite(BOARD_LED5_GPIO, BOARD_LED5_GPIO_PIN, 0)  /*!< Turn on target LED5 */
#define LED5_OFF() \
    FGPIO_PinWrite(BOARD_LED5_GPIO, BOARD_LED5_GPIO_PIN, 1)    /*!< Turn off target LED5 */
#define LED5_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED5_GPIO, 1U << BOARD_LED5_GPIO_PIN) /*!< Toggle on target LED5 */

#define LED6_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED6_GPIO, BOARD_LED6_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED6 */
#define LED6_ON() \
    FGPIO_PinWrite(BOARD_LED6_GPIO, BOARD_LED6_GPIO_PIN, 0)  /*!< Turn on target LED6 */
#define LED6_OFF() \
    FGPIO_PinWrite(BOARD_LED6_GPIO, BOARD_LED6_GPIO_PIN, 1)    /*!< Turn off target LED6 */
#define LED6_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED6_GPIO, 1U << BOARD_LED6_GPIO_PIN) /*!< Toggle on target LED6 */

#define LED7_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED7_GPIO, BOARD_LED7_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED7 */
#define LED7_ON() \
    FGPIO_PinWrite(BOARD_LED7_GPIO, BOARD_LED7_GPIO_PIN, 0)  /*!< Turn on target LED7 */
#define LED7_OFF() \
    FGPIO_PinWrite(BOARD_LED7_GPIO, BOARD_LED7_GPIO_PIN, 1)    /*!< Turn off target LED7 */
#define LED7_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED7_GPIO, 1U << BOARD_LED7_GPIO_PIN) /*!< Toggle on target LED7 */

#define LED8_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED8_GPIO, BOARD_LED8_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED8 */
#define LED8_ON() \
    FGPIO_PinWrite(BOARD_LED8_GPIO, BOARD_LED8_GPIO_PIN, 0)  /*!< Turn on target LED8 */
#define LED8_OFF() \
    FGPIO_PinWrite(BOARD_LED8_GPIO, BOARD_LED8_GPIO_PIN, 1)    /*!< Turn off target LED8 */
#define LED8_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED8_GPIO, 1U << BOARD_LED8_GPIO_PIN) /*!< Toggle on target LED8 */

#define LED9_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED9_GPIO, BOARD_LED9_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED9 */
#define LED9_ON() \
    FGPIO_PinWrite(BOARD_LED9_GPIO, BOARD_LED9_GPIO_PIN, 0)  /*!< Turn on target LED9 */
#define LED9_OFF() \
    FGPIO_PinWrite(BOARD_LED9_GPIO, BOARD_LED9_GPIO_PIN, 1)    /*!< Turn off target LED9 */
#define LED9_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED9_GPIO, 1U << BOARD_LED9_GPIO_PIN) /*!< Toggle on target LED9 */

#define LED10_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED10_GPIO, BOARD_LED10_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED10 */
#define LED10_ON() \
    FGPIO_PinWrite(BOARD_LED10_GPIO, BOARD_LED10_GPIO_PIN, 0)  /*!< Turn on target LED10 */
#define LED10_OFF() \
    FGPIO_PinWrite(BOARD_LED10_GPIO, BOARD_LED10_GPIO_PIN, 1)    /*!< Turn off target LED10 */
#define LED10_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED10_GPIO, 1U << BOARD_LED10_GPIO_PIN) /*!< Toggle on target LED10 */

#define LED11_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED11_GPIO, BOARD_LED11_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED11 */
#define LED11_ON() \
    FGPIO_PinWrite(BOARD_LED11_GPIO, BOARD_LED11_GPIO_PIN, 0)  /*!< Turn on target LED11 */
#define LED11_OFF() \
    FGPIO_PinWrite(BOARD_LED11_GPIO, BOARD_LED11_GPIO_PIN, 1)    /*!< Turn off target LED11 */
#define LED11_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED11_GPIO, 1U << BOARD_LED11_GPIO_PIN) /*!< Toggle on target LED11 */

#define LED12_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED12_GPIO, BOARD_LED12_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED12 */
#define LED12_ON() \
    FGPIO_PinWrite(BOARD_LED12_GPIO, BOARD_LED12_GPIO_PIN, 0)  /*!< Turn on target LED12 */
#define LED12_OFF() \
    FGPIO_PinWrite(BOARD_LED12_GPIO, BOARD_LED12_GPIO_PIN, 1)    /*!< Turn off target LED12 */
#define LED12_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED12_GPIO, 1U << BOARD_LED12_GPIO_PIN) /*!< Toggle on target LED12 */

#define LED13_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED13_GPIO, BOARD_LED13_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED13 */
#define LED13_ON() \
    FGPIO_PinWrite(BOARD_LED13_GPIO, BOARD_LED13_GPIO_PIN, 0)  /*!< Turn on target LED13 */
#define LED13_OFF() \
    FGPIO_PinWrite(BOARD_LED13_GPIO, BOARD_LED13_GPIO_PIN, 1)    /*!< Turn off target LED13 */
#define LED13_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED13_GPIO, 1U << BOARD_LED13_GPIO_PIN) /*!< Toggle on target LED13 */

#define LED14_INIT(output)                                  \
    FGPIO_PinInit(BOARD_LED14_GPIO, BOARD_LED14_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED14 */
#define LED14_ON() \
    FGPIO_PinWrite(BOARD_LED14_GPIO, BOARD_LED14_GPIO_PIN, 0)  /*!< Turn on target LED14 */
#define LED14_OFF() \
    FGPIO_PinWrite(BOARD_LED14_GPIO, BOARD_LED14_GPIO_PIN, 1)    /*!< Turn off target LED14 */
#define LED14_TOGGLE() \
    //GPIO_TogglePinsOutput(BOARD_LED14_GPIO, 1U << BOARD_LED14_GPIO_PIN) /*!< Toggle on target LED14 */

/* Board RGB LED color mapping */
#define LOGIC_LED_ON  0U
#define LOGIC_LED_OFF 1U
#ifndef BOARD_LED_RED_GPIO
#define BOARD_LED_RED_GPIO GPIOD
#endif
#define BOARD_LED_RED_GPIO_PORT PORTD
#ifndef BOARD_LED_RED_GPIO_PIN
#define BOARD_LED_RED_GPIO_PIN 10U
#endif
#ifndef BOARD_LED_GREEN_GPIO
#define BOARD_LED_GREEN_GPIO GPIOD
#endif
#define BOARD_LED_GREEN_GPIO_PORT PORTD
#ifndef BOARD_LED_GREEN_GPIO_PIN
#define BOARD_LED_GREEN_GPIO_PIN 11U
#endif
#ifndef BOARD_LED_BLUE_GPIO
#define BOARD_LED_BLUE_GPIO GPIOD
#endif
#define BOARD_LED_BLUE_GPIO_PORT PORTD
#ifndef BOARD_LED_BLUE_GPIO_PIN
#define BOARD_LED_BLUE_GPIO_PIN 12U
#endif

#define LED_RED_INIT(output)                                           \
    GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, output); \
    BOARD_LED_RED_GPIO->PDDR |= (1U << BOARD_LED_RED_GPIO_PIN)                         /*!< Enable target LED_RED */
#define LED_RED_ON()  GPIO_PortClear(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn on target LED_RED */
#define LED_RED_OFF() GPIO_PortSet(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN)   /*!< Turn off target LED_RED */
#define LED_RED_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Toggle on target LED_RED1 */

#define LED_GREEN_INIT(output)                                             \
    GPIO_PinWrite(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, output); \
    BOARD_LED_GREEN_GPIO->PDDR |= (1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Enable target LED_GREEN */
#define LED_GREEN_ON() \
    GPIO_PortClear(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn on target LED_GREEN */
#define LED_GREEN_OFF() \
    GPIO_PortSet(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn off target LED_GREEN */
#define LED_GREEN_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Toggle on target LED_GREEN */

#define LED_BLUE_INIT(output)                                            \
    GPIO_PinWrite(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, output); \
    BOARD_LED_BLUE_GPIO->PDDR |= (1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Enable target LED_BLUE */
#define LED_BLUE_ON()                                                                               \
    GPIO_PortClear(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn on target LED_BLUE \
                                                                        */
#define LED_BLUE_OFF()                                                                             \
    GPIO_PortSet(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn off target LED_BLUE \
                                                                      */
#define LED_BLUE_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Toggle on target LED_BLUE */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_InitDebugConsole(void);
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_LPI2C_Init(LPI2C_Type *base, uint32_t clkSrc_Hz);
status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subaddressSize,
                          uint8_t *txBuff,
                          uint8_t txBuffSize);
status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subaddressSize,
                             uint8_t *rxBuff,
                             uint8_t rxBuffSize);
void BOARD_Accel_I2C_Init(void);
status_t BOARD_Accel_I2C_Send(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff);
status_t BOARD_Accel_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
#endif /* SDK_I2C_BASED_COMPONENT_USED */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
