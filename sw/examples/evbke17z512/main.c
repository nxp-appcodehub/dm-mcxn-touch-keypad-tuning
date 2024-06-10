/*
 * Copyright 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"

#include "fsl_ftm.h"
#include "fsl_lpit.h"

#include "main.h"

#include "pin_mux.h"
#include "board.h"

#include "fsl_gpio.h"
#include "fsl_port.h"

#include "tsi_trace.h"

#include "nt_types.h"

/* 
  NOTE: 
  "freemaster" source files have been excluded from the project build.
  See the README doc for more details, please
*/

#if NT_FREEMASTER_SUPPORT != 0  
  #include "freemaster.h"
#endif


extern void TSI_DRV_IRQHandler(uint32_t instance);

static void pit_init(void);

static void keypad_callback(const struct nt_control *control, enum nt_control_keypad_event event, uint32_t index);

/* Call when the TSI counter overflows 65535 */
static void system_callback(uint32_t event, union nt_system_event_context *context);

static void LEDS_OFF(void);

const lpit_config_t my_pit_config = {
    .enableRunInDebug = false, /*!< Timer doesn't run in debug mode*/
    .enableRunInDoze  = false, /*!< Timer doesn't run in doze mode*/
};


//------------------------------------------------------------------------------
// NXP Touch mem. pool
//------------------------------------------------------------------------------
#if defined(__ICCARM__)
uint8_t nt_memory_pool[12000]; /* IAR EWARM compiler */
#else
uint8_t nt_memory_pool[12000] __attribute__((aligned(4))); /* Keil, GCC compiler */
#endif
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// FreeMASTER TSA table
//------------------------------------------------------------------------------
#if NT_FREEMASTER_SUPPORT != 0
  #ifndef FMSTR_PE_USED
  FMSTR_TSA_TABLE_LIST_BEGIN()
  FMSTR_TSA_TABLE(nt_frmstr_tsa_table)
  FMSTR_TSA_TABLE_LIST_END()
  #endif
#endif

#define nt_printf(...) /* do nothing - the debug lines are used by FreeMASTER */

// uint16_t key_state[NBUTTONS_MAX];
volatile uint8_t ntTriggerFlag = 0;


int main(void)
{
  int32_t result;

  bool one_key_only    = false; /* one key only valid is off */

  /* Init board hardware */
  BOARD_InitPins();
  BOARD_BootClockRUN();

    LED0_INIT(1);
    LED1_INIT(1);
    LED2_INIT(1);
    LED3_INIT(1);
    LED4_INIT(1);
    LED5_INIT(1);
    LED6_INIT(1);
    LED7_INIT(1);
    LED8_INIT(1);
    LED9_INIT(1);
    LED10_INIT(1);
    LED11_INIT(1);
    LED12_INIT(1);
    LED13_INIT(1);
    LED14_INIT(1);

  /* Initialize the OS abstraction layer */
  NT_OSA_Init();

// TSI Trace using UART
#if( defined( TSI_TRACE ) && defined( TSI_TRACE_SERIAL ))
  tsi_trace_init();
#else
  /* FreeMASTER initialization */
  (void)FMSTR_Init();
#endif

  if ((result = nt_init(&System_0, nt_memory_pool, sizeof(nt_memory_pool))) != NT_SUCCESS)
  {
    switch (result)
    {
    case NT_FAILURE:
      nt_printf("\nCannot initialize NXP Touch due to a non-specific error.\n");
      break;
    case NT_OUT_OF_MEMORY:
      nt_printf("\nCannot initialize NXP Touch due to a lack of free memory.\n");
      break;
    }
    while (1)
      ; /* add code to handle this error */
  }


  nt_printf("\nNXP Touch is successfully initialized.\n");

  nt_printf("Unused memory: %d bytes, you can make the memory pool smaller without affecting the functionality.\n",
            (int)nt_mem_get_free_size());

  /* Enable electrodes and controls */
  nt_enable();

  /* Keypad electrodes*/
  //nt_control_keypad_set_autorepeat_rate(&Keypad_1, 100, 1000);
  nt_control_keypad_register_callback(&Keypad_1, &keypad_callback);

  /* System TSI overflow warning callback */
  nt_system_register_callback(&system_callback);

  if (one_key_only)
    nt_control_keypad_only_one_key_valid(&Keypad_1, true);

  pit_init();

  while (1)
  {
    nt_task();

    LPUART_task(); // Periodically check the UART traffic

    // Process trigger
    if( ntTriggerFlag >= 2 )
    {
      ntTriggerFlag = 0; // Reset Flag
      tsi_trace_set_flag( 1 );

#ifdef TSI_TRACE
      tsi_trace_process();
#endif

    }

#if( !defined( TSI_TRACE ) && !defined( TSI_TRACE_SERIAL ))
    FMSTR_Poll();
#endif

  }// while(1)
}//main


uint32_t loopcnt = 0;
uint8_t failflag=0;
int16_t aux1 = 0;

void LPIT0_IRQHandler(void)
{
    /* Clear the interrupt flag.*/
    LPIT_ClearStatusFlags(LPIT0, LPIT_MSR_TIF0_MASK);
    nt_trigger();

    loopcnt++;
}

void TSI0_IRQHandler(void)
{
    TSI_DRV_IRQHandler(0);
}

void TSI1_IRQHandler(void)
{
    TSI_DRV_IRQHandler(1);
}


static void pit_init(void)
{
  /* Set the source for the LPIT module */
  CLOCK_SetIpSrc(kCLOCK_Lpit0, kCLOCK_IpSrcSircAsync);

  /* Init PIT */
  LPIT_Init(LPIT0, &my_pit_config);

  /* Set PIT0 period 5ms */
  LPIT_SetTimerPeriod(LPIT0, kLPIT_Chnl_0, nt_kernel_data.rom->time_period * CLOCK_GetFreq(kCLOCK_ScgSircAsyncDiv2Clk) / 1000);

  /* Enable the PIT interrupt */
  LPIT_EnableInterrupts(LPIT0, LPIT_MIER_TIE0_MASK);
  EnableIRQ(LPIT0_IRQn);

  /* Start the PIT timer */
  LPIT_StartTimer(LPIT0, kLPIT_Chnl_0);
}

static void keypad_callback(const struct nt_control *control, enum nt_control_keypad_event event, uint32_t index)
{
  switch (event)
  {
  case NT_KEYPAD_RELEASE:
   
    LEDS_OFF();

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
    case 4:
      break;
    case 5:
      break;
    default:
      break;
    }
    break;


  case NT_KEYPAD_TOUCH:

    switch (index)
    {
    case 0:
      LED0_ON();
      break;
    case 1:
      LED1_ON();
      break;
    case 2:
      LED2_ON();
      break;
    case 3:
      LED3_ON();
      break;
    case 4:
      LED4_ON();
      break;
    case 5:
      LED5_ON();
      break;
    case 6:
      LED6_ON();
      break;
    case 7:
      LED7_ON();
      break;
    case 8:
      LED8_ON();
      break;
    case 9:
      LED9_ON();
      break;
    case 10:
      LED10_ON();
      break;
    case 11:
      LED11_ON();
      break;
    case 12:
      LED12_ON();
      break;
    case 13:
      LED13_ON();
      break;
    case 14:
      LED14_ON();
      break;
    default:
      break;
    }
    break;


  default:
    break;
  }
}

/* Call on the TSI CNTR overflow 16-bit range (65535) */
void system_callback(uint32_t event, union nt_system_event_context *context)
{
    switch (event)
    {
        case NT_SYSTEM_EVENT_OVERRUN:
            // your code
        asm("NOP");
        break;
        case NT_SYSTEM_EVENT_DATA_READY:
            // your code
        break;
        case NT_SYSTEM_EVENT_MODULE_DATA_READY:
            // your code
            ntTriggerFlag++;
        break;
        case NT_SYSTEM_EVENT_DATA_OVERFLOW:
            // your code
        break;
        case NT_SYSTEM_EVENT_SIGNAL_LOW:
            // your code
        break;
        case NT_SYSTEM_EVENT_SIGNAL_HIGH:
            // your code
        break;
        case NT_SYSTEM_EVENT_ELEC_SHORT_VDD:
            // your code
        break;
        case NT_SYSTEM_EVENT_ELEC_SHORT_GND:
            // your code
        break;
        case NT_SYSTEM_EVENT_ELEC_SHORT_ADJ:
            // your code
        break;
    }
}


void LEDS_OFF(void)
{
  LED0_OFF();
  LED1_OFF();
  LED2_OFF();
  LED3_OFF();
  LED4_OFF();
  LED5_OFF();
  LED6_OFF();
  LED7_OFF();
  LED8_OFF();
  LED9_OFF();
  LED10_OFF();
  LED11_OFF();
  LED12_OFF();
  LED13_OFF();
  LED14_OFF();
}







































