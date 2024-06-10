/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "tsi_trace.h"

/**************************************************************************
* Global variables
**************************************************************************/
#define NBUTTONS_MAX 25      // For mem alloc

// Log struct
struct TsiTraceData
{
  char tracetype;       // delta (0), signal(1), raw(2), after xtalk (3), nstep (4), baseline (5), key_state(6)
  char syncflag;
  char nbuttons;
  char buffsize;
  uint16_t signals[64]; // TSI Trace buffer
}traceTsi @ "tsi_specific_rw"; /* 512 Bytes reserved RAM table @ 0x20_000_000, see Linker file */

lpuart_handle_t g_lpuartHandle;
char uart_buff[128]; // buffer for UART outgoing messages

uint8_t g_txBuffer[ECHO_BUFFER_LENGTH] = {0};
uint8_t g_rxBuffer[ECHO_BUFFER_LENGTH] = {0};
volatile bool uart_rxBufferEmpty = true;
volatile bool uart_txBufferFull = false;
volatile bool uart_txOnGoing = false;
volatile bool uart_rxOnGoing = false;

lpuart_config_t   uart_config;
lpuart_transfer_t uart_xfer;
lpuart_transfer_t uart_sendXfer;
lpuart_transfer_t uart_receiveXfer;


void tsi_trace_init( void )
{
  traceTsi.tracetype = 4;
  traceTsi.nbuttons = NBUTTONS_MAX;

  //init_uart_rx_tx();
}

void tsi_trace_set_flag( uint8_t flag1 )
{
  traceTsi.syncflag = flag1;
}

// TSI Signal Tracing function
void tsi_trace_process(void)
{

  uint32_t c1;

  for( c1 = 0; c1 < NBUTTONS_MAX; c1++ )
  {

    struct nt_electrode const *elec = Keypad_1.electrodes[c1];
    
    if( elec == NULL )
    {
      break;
    }
    int32_t aux1;
    struct nt_electrode_data *elecData = _nt_electrode_get_data( elec );
    switch( traceTsi.tracetype )
    {
    case 0:
      aux1 = ( uint32_t )nt_electrode_get_delta( elec );        // smoothed delta
      break;
    case 1:
      aux1 = ( uint32_t )nt_electrode_get_signal( elec );       // smoothed delta + baseline
      break;
    case 2:
      aux1 = ( uint32_t )nt_electrode_get_raw_signal( elec );   // raw signal (PETSN or TSICNT)
      break;
    case 3:
      aux1 = ( uint32_t )nt_electrode_get_delta_red( elec );    // xtalk reduced (zero if xtalk off)
      break;
    case 4:
      aux1 = ( uint32_t )elecData->nstep;                       // NSTEP (most basic measurement)
      break;
    case 5:
      aux1 = ( uint32_t )elecData->baseline;                    // Baseline
      break;
    // case 6:
    //   aux1 = ( uint32_t )key_state[c1];                         // Key state
    //   break;

    default:
      break;
    }
    if( aux1 > 65535 )
    {
      aux1 = 65535;
    }
    if( aux1 < 0 )
    {
      aux1 = 0;
    }
    traceTsi.signals[c1] = ( uint16_t )aux1;
  }

  traceTsi.nbuttons = c1;

/*  
  // Formatting the UART data output, Delimiter: "RAW "
  char *pChar = ( char* )traceTsi.signals;
  char *pMsg = (char *)uart_buff;

  //sprintf(uart_buff, "RAW ");
  uart_buff[0] = 'R';
  uart_buff[1] = 'A';
  uart_buff[2] = 'W';
  uart_buff[3] = ' ';

  pMsg = pMsg + 4;

  for( c1 = 0; c1 < (2 * traceTsi.nbuttons); c1++ )
  {

    *pMsg = *pChar;
    pMsg++;
    pChar++;
  }

  *pMsg = '\n';

  if(uart_txOnGoing == false)
  {
    uart_send_message((uint8_t*)uart_buff, ((2 * traceTsi.nbuttons) + 5));
  }
 */
}



/*!
 * @brief UART Module initialization
 */

/*
void init_uart_rx_tx(void)
{
    lpuart_config_t lpuartConfig;

    //CLOCK_SetIpSrc(kCLOCK_Lpuart1, BOARD_DEBUG_UART_CLKSRC);
    //uint32_t uartClkSrcFreq = CLOCK_GetIpFreq(kCLOCK_Lpuart1);
    // UART configuration structure 
    LPUART_GetDefaultConfig(&lpuartConfig);
    lpuartConfig.baudRate_Bps     = BOARD_DEBUG_UART_BAUDRATE;
    lpuartConfig.enableTx         = true;
    lpuartConfig.enableRx         = true;

    // Init UART
    LPUART_Init((LPUART_Type *)BOARD_DEBUG_UART_BASEADDR, &lpuartConfig, BOARD_DEBUG_UART_CLK_FREQ);
    
    //LPUART_Init((LPUART_Type *)BOARD_DEBUG_UART_BASEADDR, &lpuartConfig, uartClkSrcFreq);
    LPUART_TransferCreateHandle((LPUART_Type *)BOARD_DEBUG_UART_BASEADDR, &g_lpuartHandle, LPUART_UserCallback, NULL);

    // Enable UART interrupt 
    EnableIRQ(BOARD_UART_IRQ);

    // Start to echo. 
    uart_sendXfer.data = g_txBuffer;
    uart_sendXfer.dataSize = ECHO_BUFFER_LENGTH;
    uart_receiveXfer.data = g_rxBuffer;
    uart_receiveXfer.dataSize = ECHO_BUFFER_LENGTH;
    uart_rxBufferEmpty = true;
}

void uart_send_message(uint8_t *msg, uint8_t len)
{
  uart_xfer.data = msg;
  uart_xfer.dataSize = len;
  uart_txOnGoing = true;

  LPUART_TransferSendNonBlocking((LPUART_Type *)BOARD_DEBUG_UART_BASEADDR, &g_lpuartHandle, &uart_xfer);
}

// UART callback
void LPUART_UserCallback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
  userData = userData;

  if (kStatus_LPUART_TxIdle == status)
  {
    uart_txBufferFull = false;
    uart_txOnGoing = false;
  }

  if (kStatus_LPUART_RxIdle == status)
  {
    uart_rxBufferEmpty = false;
    uart_rxOnGoing = false;
  }
}


//---------------------- LPUART handling ---------------------------------------
void LPUART_cmd_handle(lpuart_transfer_t *xfer)
{
  uint8_t type;

  type = xfer->data[0];
  type = type - 0x30; // ASCII characters or value?

  if(type <= 6) //Check if the value is in proper range
  {
    traceTsi.tracetype = type;
  }
}


//------------------------------------------------------------------------------
void LPUART_task(void)
{
  if ((!uart_rxOnGoing) && uart_rxBufferEmpty)
  {
    uart_rxOnGoing = true;
    LPUART_TransferReceiveNonBlocking((LPUART_Type *)BOARD_DEBUG_UART_BASEADDR, &g_lpuartHandle, &uart_receiveXfer, NULL);
  }

  if (!uart_rxBufferEmpty)
  {
    LPUART_cmd_handle(&uart_receiveXfer);
    uart_rxBufferEmpty = true;
  }
}
//------------------------------------------------------------------------------
*/
