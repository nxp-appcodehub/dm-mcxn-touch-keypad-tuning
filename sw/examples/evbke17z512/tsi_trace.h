/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TSI_TRACE_H
#define TSI_TRACE_H

#include "fsl_lpuart.h"
#include "nt_electrodes_prv.h"
#include "nt_setup.h"
#include "board.h"

void tsi_trace_init( void );
void tsi_trace_process(void);
void tsi_trace_set_flag( uint8_t );

//------------------------------------------------------------------------------
// UART Rx Tx
//------------------------------------------------------------------------------
#define ECHO_BUFFER_LENGTH 1 // byte per byte echo
void init_uart_rx_tx(void);
void LPUART_UserCallback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);
void LPUART_task(void);
void uart_send_message(uint8_t *msg, uint8_t len);
void LPUART_cmd_handle(lpuart_transfer_t *xfer);

//------------------------------------------------------------------------------


#endif