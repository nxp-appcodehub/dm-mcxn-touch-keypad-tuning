/*
 * Copyright 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include "fsl_device_registers.h"

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "fsl_lpuart.h"

#include "clock_config.h"
#include "pin_mux.h"
#include "board.h"
#include "main.h"
#include "tsi_trace.h"

#include "nt_types.h"

/* 
  NOTE: 
  "freemaster" source files have been excluded from the project build.
  See the README doc for more details, please
*/

#if NT_FREEMASTER_SUPPORT != 0  
  #include "freemaster.h"
  #include "freemaster_serial_lpuart.h"
#endif


#define USE_LED_TOGGLE false

static void CTIMERInit(void);
static void keypad_callback(const struct nt_control *control, enum nt_control_keypad_event event, uint32_t index);
void LED_init(uint8_t output);
void SLED_Init_TM1620(void);
void SLED_DisplayOff(void);
void LED_OFF(GPIO_Type *base, uint32_t pin);
void LED_ON(GPIO_Type *base, uint32_t pin);
void LED_TOGGLE(GPIO_Type *base, uint32_t pin);

typedef struct _led_gpio_mapping
{
    GPIO_Type *gpio_base;
    uint8_t gpio_pin;
} led_gpio_mapping_t;

led_gpio_mapping_t led_gpio_table[] = 
{
    {BOARD_LED_D1_GPIO, BOARD_LED_D1_GPIO_PIN},
    {BOARD_LED_D2_GPIO, BOARD_LED_D2_GPIO_PIN},
    {BOARD_LED_D3_GPIO, BOARD_LED_D3_GPIO_PIN},
    {BOARD_LED_D4_GPIO, BOARD_LED_D4_GPIO_PIN},
    {BOARD_LED_D5_GPIO, BOARD_LED_D5_GPIO_PIN},
    {BOARD_LED_D6_GPIO, BOARD_LED_D6_GPIO_PIN},
    {BOARD_LED_D7_GPIO, BOARD_LED_D7_GPIO_PIN},
    {BOARD_LED_D8_GPIO, BOARD_LED_D8_GPIO_PIN},
    {BOARD_LED_D9_GPIO, BOARD_LED_D9_GPIO_PIN},
    {BOARD_LED_D10_GPIO, BOARD_LED_D10_GPIO_PIN},
    {BOARD_LED_D11_GPIO, BOARD_LED_D11_GPIO_PIN},
    {BOARD_LED_D12_GPIO, BOARD_LED_D12_GPIO_PIN},
    //end of led table
    {GPIO0, 0xFF}
};

//code table for 7-seg led
const unsigned char led_code[] = 
{
  0x3f,   //'0'
  0x06,   //'1'
  0x5b,   //'2'
  0x4f,   //'3'
  0x66,   //'4'
  0x6d,   //'5'
  0x7d,   //'6'
  0x07,   //'7'
  0x7f,   //'8'
  0x6f,   //'9'
  0x77,   //'A'
  0x7c,   //'B'
  0x39,   //'C'
  0x5e,   //'D'
  0x79,   //'E'
  0x71,   //'F'
  0x40,   //'-'
  0x00,   //BLANK
  0x76,   //'H'
  0x73,   //'P'
};

/* Call when the TSI counter overflows 65535 */
static void system_callback(uint32_t event, union nt_system_event_context *context);

#if defined(__ICCARM__)
uint8_t nt_memory_pool[8000]; /* IAR EWARM compiler */
#else
uint8_t nt_memory_pool[8000] __attribute__((aligned(4))); /* Keil, GCC compiler */
#endif

/*
 * This list describes all TSA tables that should be exported to the
 * FreeMASTER application.
 */
#if NT_FREEMASTER_SUPPORT != 0
  #ifndef FMSTR_PE_USED
  FMSTR_TSA_TABLE_LIST_BEGIN()
  FMSTR_TSA_TABLE(nt_frmstr_tsa_table)
  FMSTR_TSA_TABLE_LIST_END()
  #endif
#endif

#define nt_printf(...) /* do nothing - the debug lines are used by FreeMASTER */

volatile uint8_t ntTriggerFlag = 0;

int main(void)
{ 
    int32_t result;
    bool one_key_only    = false; /* one key only valid is off */

    /* Init board hardware */
    /* attach FRO 12M to FLEXCOMM4 (debug console) */
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom9Clk, 1u);
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);


    BOARD_InitPins();
    BOARD_InitBootClocks();

    /*LED init*/
    LED_init(kGPIO_InterruptLogicOne);
    /*segment display init*/
    SLED_Init_TM1620();
    SLED_DisplayOff();
    /* Initialize the OS abstraction layer */
    NT_OSA_Init();
    
    // TSI trace
    tsi_trace_init();

#if NT_FREEMASTER_SUPPORT != 0
    /* FreeMASTER initialization */
    (void)FMSTR_Init();
#endif

    if ((result = nt_init(&System_0, nt_memory_pool, sizeof(nt_memory_pool))) != NT_SUCCESS)
    {
        /* red colour signalizes the error, to solve is increase nt_memory_pool or debug it */ 
        //LED_RED_ON();
                        
        switch (result)
        {
            case NT_FAILURE:
                nt_printf("\nCannot initialize NXP Touch due to a non-specific error.\n");
                break;
            case NT_OUT_OF_MEMORY:
                nt_printf("\nCannot initialize NXP Touch due to a lack of free memory.\n");
                printf("\nCannot initialize NXP Touch due to a non-specific error.\n");
                break;
        }
        while (1); /* add code to handle this error */
    }
    /* Get free memory size of the nt_memory_pool  */
    volatile uint32_t free_mem;
    free_mem = nt_mem_get_free_size();
 
    nt_printf("\nNXP Touch is successfully initialized.\n");
    nt_printf("Unused memory: %d bytes, you can make the memory pool smaller without affecting the functionality.\n",
              free_mem);

    /* Enable electrodes and controls */
    nt_enable();


    /* Keypad electrodes*/
    nt_control_keypad_set_autorepeat_rate(&Keypad_1, 100, 1000);
    nt_control_keypad_register_callback(&Keypad_1, &keypad_callback);
    
    if (one_key_only)
        nt_control_keypad_only_one_key_valid(&Keypad_1, true);


    /* System TSI overflow warning callback */
    nt_system_register_callback(&system_callback);

    CTIMERInit();
    
    while (1)
    {
      nt_task();
      
#if NT_FREEMASTER_SUPPORT != 0
      FMSTR_Poll();
#endif
      
      // Process trigger
      if( ntTriggerFlag )
      {
        ntTriggerFlag = 0; // Reset Flag
        tsi_trace_set_flag( 1 );          
        tsi_trace_process();
      }
      
    }
}

void CTIMER0_IRQHandler(void)
{
    /* Clear the interrupt flag.*/
    nt_trigger();

    /* Clear the match interrupt flag. */
    CTIMER0->IR |= CTIMER_IR_MR0INT(1U);
    
    /* Add empty instructions for correct interrupt flag clearing */
    __DSB();
    __ISB();
}

void TSI_END_OF_SCAN_DriverIRQHandler(void)
{
    TSI_DRV_IRQHandler(0);
}
void TSI_OUT_OF_SCAN_DriverIRQHandler(void)
{
    TSI_DRV_IRQHandler(0);
}

static void CTIMERInit(void)
{
    /* Use 96 MHz clock for some of the Ctimer0. */
    CLOCK_SetClkDiv(kCLOCK_DivCtimer0Clk, 1u);
    CLOCK_AttachClk(kFRO_HF_to_CTIMER0);
    
    /* Enable Timer0 clock. */
    SYSCON->AHBCLKCTRLSET[1] |= SYSCON_AHBCLKCTRL1_TIMER0_MASK;

    /* Enable Timer0 clock reset. */
    SYSCON->PRESETCTRLSET[1] = SYSCON_PRESETCTRL1_TIMER0_RST_MASK;             /* Set bit. */
    while (0u == (SYSCON->PRESETCTRL1 & SYSCON_PRESETCTRL1_TIMER0_RST_MASK))   /* Wait until it reads 0b1 */
    {
    }
    
    /* Clear Timer0 clock reset. */                                  
    SYSCON->PRESETCTRLCLR[1] = SYSCON_PRESETCTRL1_TIMER0_RST_MASK;             /* Clear bit */
    while (SYSCON_PRESETCTRL1_TIMER0_RST_MASK ==                               /* Wait until it reads 0b0 */     
          (SYSCON->PRESETCTRL1 & SYSCON_PRESETCTRL1_TIMER0_RST_MASK))
    {
    }

    /* Configure match control register. */
    CTIMER0->MCR |= CTIMER_MCR_MR0R(1U)  |   /* Enable reset of TC after it matches with MR0. */
                    CTIMER_MCR_MR0I(1U);     /* Enable interrupt generation after TC matches with MR0. */
    
    /* Configure match register. */
    CTIMER0->MR[0] = (nt_kernel_data.rom->time_period * CLOCK_GetFreq(kCLOCK_FroHf)) / 1000;/* Get CTimer0 frequency for correct set Match register value. */
                                    
    
    /* Configure interrupt register. */
    CTIMER0->IR = CTIMER_IR_MR0INT_MASK;     /* Set interrupt flag for match channel 0. */
    NVIC_SetPriority(CTIMER0_IRQn, 1U);
    NVIC_EnableIRQ(CTIMER0_IRQn);            /* Enable LEVEL1 interrupt and update the call back function. */

    /* Configure timer control register. */
    CTIMER0->TCR |= CTIMER_TCR_CEN_MASK;     /* Start the timer counter. */
}

void LED_OFF(GPIO_Type *base, uint32_t pin)
{
    GPIO_PortSet(base, 1U << pin); /*!< Turn off target LED */
}

void LED_ON(GPIO_Type *base, uint32_t pin)
{
    GPIO_PortClear(base, 1U << pin); /*!< Turn on target LED */
}

void LED_TOGGLE(GPIO_Type *base, uint32_t pin)
{
    GPIO_PortToggle(base, 1U << pin);
}

void LED_init(uint8_t output)
{
    uint8_t led_index = 0;
    
    while (led_gpio_table[led_index].gpio_pin != 0xFF)
    {
        GPIO_PinWrite(led_gpio_table[led_index].gpio_base, led_gpio_table[led_index].gpio_pin, output);
        led_gpio_table[led_index].gpio_base->PDDR |= (1U << led_gpio_table[led_index].gpio_pin);  
        led_index++;
    }    
}

void ALL_LED_OFF(void)                      //turn off all LEDs
{
    uint8_t led_index = 0xFF;
    led_index = 0;
    while (led_gpio_table[led_index].gpio_pin != 0xFF)
    {
        GPIO_PortSet(led_gpio_table[led_index].gpio_base, 1U << led_gpio_table[led_index].gpio_pin);
        led_index++;
    }
}

void STB_clear(void)
{
   //clear STB
   GPIO_PortClear(BOARD_SLED_STB_GPIO, 1<<BOARD_SLED_STB_GPIO_PIN);
}

void STB_set(void)
{
   //set STB
   GPIO_PortSet(BOARD_SLED_STB_GPIO, 1<<BOARD_SLED_STB_GPIO_PIN);
}

void CLK_clear(void)
{
   //clear CLK
   GPIO_PortClear(BOARD_SLED_CLK_GPIO, 1<<BOARD_SLED_CLK_GPIO_PIN);
}

void CLK_set(void)
{
   //set CLK
   GPIO_PortSet(BOARD_SLED_CLK_GPIO, 1<<BOARD_SLED_CLK_GPIO_PIN);
}

void DIO_clear(void)
{
   //clear DIN
   GPIO_PortClear(BOARD_SLED_DIN_GPIO, 1<<BOARD_SLED_DIN_GPIO_PIN);
}

void DIO_set(void)
{
   //set DIN
   GPIO_PortSet(BOARD_SLED_DIN_GPIO, 1<<BOARD_SLED_DIN_GPIO_PIN);
}

void SLED_WriteData(uint8_t data)
{
    uint8_t i;
    uint8_t j;
    
    for(i=0;i<8;i++)
    {
        CLK_clear();
        asm("NOP");
        asm("NOP");
        
        if(data&0x01)
        {
            DIO_set();
        }	
        else
        {
            DIO_clear();
        }
        
        for (j=0; j<16; j++)
        {
           asm("NOP");
        }

        data>>=1;

        CLK_set();
        asm("NOP");
        asm("NOP");
    }
}

void SLED_WriteCom(uint8_t cmd)
{
	STB_clear();
	asm("NOP");
	asm("NOP");
        
	SLED_WriteData(cmd);
        
	STB_set();
	asm("NOP");
	asm("NOP");
}

void SLED_Init_TM1620(void)
{
    unsigned char i;
    
    SLED_WriteCom(0x02);
    SLED_WriteCom(0x40); 
    
    STB_clear();
    asm("NOP");
    asm("NOP");
    
    //write led with address increased automatically
    SLED_WriteData(0xc0);
    
    for(i=0;i<10;i++)
    {
       //display "0" at each position of the 7-seg led
        SLED_WriteData(led_code[0]);
    }
    
    STB_set();
    asm("NOP");
    asm("NOP");	
    
    //set the lightness of the 7-seg led
    SLED_WriteCom(0x8a);
}

void SLED_Display(uint16_t data)
{
    uint8_t position;

    //set display mode
    SLED_WriteCom(0x02);
    //set write fixed address
    SLED_WriteCom(0x44); 

    for(position=0; position<3; position++)
    {
        STB_clear();
        asm("NOP");
        asm("NOP");
        
        SLED_WriteData((0xc0 + position*2));
        SLED_WriteData(led_code[data%10]);
        data /= 10;
        
        STB_set();
        asm("NOP");
        asm("NOP");	
    }

    //set the lightness of the 7-seg led
    SLED_WriteCom(0x8a);
}

void SLED_DisplayOff(void)
{
    uint8_t position;

    //set display mode
    SLED_WriteCom(0x02);
    //set write fixed address
    SLED_WriteCom(0x44); 

    for(position=0; position<4; position++)
    {
        STB_clear();
        asm("NOP");
        asm("NOP");
        
        SLED_WriteData((0xc0 + position*2));
        SLED_WriteData(0x40);

        STB_set();
        asm("NOP");
        asm("NOP");	
    }

    //set the lightness of the 7-seg led
    SLED_WriteCom(0x8a);
}

#if (defined(USE_LED_TOGGLE) && USE_LED_TOGGLE) //lEDs mode
static void keypad_callback(const struct nt_control *control, enum nt_control_keypad_event event, uint32_t index)
{
    switch (event)
    {
        case NT_KEYPAD_RELEASE:
            {  
//            LED_BLUE_OFF();
            }
            break;
        case NT_KEYPAD_TOUCH:

            switch (index)
            {
                case 0:
                    LED_TOGGLE(BOARD_LED_D1_GPIO, BOARD_LED_D1_GPIO_PIN);
                    break;
                case 1:
                    LED_TOGGLE(BOARD_LED_D2_GPIO, BOARD_LED_D2_GPIO_PIN);
                    break;
                case 2:
                    LED_TOGGLE(BOARD_LED_D3_GPIO, BOARD_LED_D3_GPIO_PIN);
                    break;
                case 3:
                    LED_TOGGLE(BOARD_LED_D4_GPIO, BOARD_LED_D4_GPIO_PIN);
                    break;
                case 4:
                    LED_TOGGLE(BOARD_LED_D5_GPIO, BOARD_LED_D5_GPIO_PIN);
                    break;
                case 5:
                    LED_TOGGLE(BOARD_LED_D6_GPIO, BOARD_LED_D6_GPIO_PIN);
                    break;
                case 6:
                    LED_TOGGLE(BOARD_LED_D7_GPIO, BOARD_LED_D7_GPIO_PIN);
                    break;
                case 7:
                    LED_TOGGLE(BOARD_LED_D8_GPIO, BOARD_LED_D8_GPIO_PIN);
                    break;
                case 8:
                    LED_TOGGLE(BOARD_LED_D9_GPIO, BOARD_LED_D9_GPIO_PIN);
                    break;
                case 9:
                    LED_TOGGLE(BOARD_LED_D10_GPIO, BOARD_LED_D10_GPIO_PIN);
                    break;
                case 10:
                    LED_TOGGLE(BOARD_LED_D11_GPIO, BOARD_LED_D11_GPIO_PIN);
                    break;
                case 11:
                    LED_TOGGLE(BOARD_LED_D12_GPIO, BOARD_LED_D12_GPIO_PIN);
                    break;
                default:
                    break;
            }
            break;

        case NT_KEYPAD_AUTOREPEAT:

            break;

        case NT_KEYPAD_MULTI_TOUCH:
            switch (index)
            {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}
#else
static void keypad_callback(const struct nt_control *control, enum nt_control_keypad_event event, uint32_t index)
{
    switch (event)
    {
        case NT_KEYPAD_RELEASE:
            {  
                ALL_LED_OFF();
                SLED_DisplayOff();
            }
            break;
        case NT_KEYPAD_TOUCH:
            SLED_Display(index);
            switch (index)
            { 
                case 11:
                    LED_TOGGLE(BOARD_LED_D1_GPIO, BOARD_LED_D1_GPIO_PIN);
                    break;
                case 10:
                    LED_TOGGLE(BOARD_LED_D2_GPIO, BOARD_LED_D2_GPIO_PIN);
                    break;
                case 9:
                    LED_TOGGLE(BOARD_LED_D3_GPIO, BOARD_LED_D3_GPIO_PIN);
                    break;
                case 8:
                    LED_TOGGLE(BOARD_LED_D4_GPIO, BOARD_LED_D4_GPIO_PIN);
                    break;
                case 7:
                    LED_TOGGLE(BOARD_LED_D5_GPIO, BOARD_LED_D5_GPIO_PIN);
                    break;
                case 6:
                    LED_TOGGLE(BOARD_LED_D6_GPIO, BOARD_LED_D6_GPIO_PIN);
                    break;
                case 5:
                    LED_TOGGLE(BOARD_LED_D7_GPIO, BOARD_LED_D7_GPIO_PIN);
                    break;
                case 4:
                    LED_TOGGLE(BOARD_LED_D8_GPIO, BOARD_LED_D8_GPIO_PIN);
                    break;
                case 3:
                    LED_TOGGLE(BOARD_LED_D9_GPIO, BOARD_LED_D9_GPIO_PIN);
                    break;
                case 2:
                    LED_TOGGLE(BOARD_LED_D10_GPIO, BOARD_LED_D10_GPIO_PIN);
                    break;
                case 1:
                    LED_TOGGLE(BOARD_LED_D11_GPIO, BOARD_LED_D11_GPIO_PIN);
                    break;
                case 0:
                    LED_TOGGLE(BOARD_LED_D12_GPIO, BOARD_LED_D12_GPIO_PIN);
                    break;
                default:
                    break;
            }
            break;

        case NT_KEYPAD_AUTOREPEAT:

            break;

        case NT_KEYPAD_MULTI_TOUCH:
            switch (index)
            {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
}
#endif 


/* Call on the TSI CNTR overflow 16-bit range (65535) */
void system_callback(uint32_t event, union nt_system_event_context *context)
{
    switch (event)
    {
        case NT_SYSTEM_EVENT_OVERRUN:
        {
            /* red colour signalize the error, to solve it increase nt_kernel_data.rom->time_period  */
            //LED_RED_ON();
            nt_printf("\n Overrun occured increase nt_kernel_data.rom->time_period param \n");
            printf("\n Overrun occured increase nt_kernel_data.rom->time_period param \n");

        }
        case NT_SYSTEM_EVENT_DATA_READY:
            // your code
        break;
        case NT_SYSTEM_EVENT_MODULE_DATA_READY:
            // your code
            ntTriggerFlag = 1; // Set trigger for signal trace
        break;
        case NT_SYSTEM_EVENT_DATA_OVERFLOW:
            // your code
        break;
    }
}

