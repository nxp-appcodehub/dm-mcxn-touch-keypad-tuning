/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _NT_MODULE_CS_PRV_H_
#define _NT_MODULE_CS_PRV_H_

/**
 * \defgroup cs_private CS module
 * \ingroup modules_private
 *
 * The Capacitive sense (CS) module describes the hardware configuration and control of elementary functionality
 * of the CS peripheral, it covers all versions of the CS peripheral by a generic
 * low-level driver API.
 *
 * The CS module is designed for processors that have a hardware CS module.
 * \{
 */
#include "../source/drivers/cs/nt_drv_cs_driver.h"
#include "../source/electrodes/nt_electrodes_prv.h"
#include "nt_modules.h"
#include "nt_types.h"
#include "nt_electrodes.h"
#include "../source/filters/nt_filters_prv.h"

struct nt_module_cs_data
{
    nt_cs_state_t cs_state; /*!< main NT driver data structure with state variables */
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/** \} */ /* end of cs_private group */

#endif /* _NT_MODULE_CS_PRV_H_ */