/*
 * Copyright 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// Auto-generated config file
// tuningGuide.py rev: 31503

#include "nt_setup.h"
#include "board.h"


/* ************************** */
/* Crosstalk reduction Matrix */
/* ************************** */
int16_t actMat[] = {
 32767,  2171,   447,   765,   772,   605,   537,   628,   291,   411,   272,   250,   484,   501,   458,
  1425, 32767,  1524,   502,   817,   849,   435,   612,   402,   592,   303,   524,   540,   537,   416,
     0,   661, 32767,   511,     0,   329,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   502,   479,   521, 32767,  2016,   535,   507,   505,   499,   484,   499,   469,   471,   448,   505,
   233,   744,   295,  1506, 32767,  1837,   562,   829,   698,   305,   136,   326,   263,   372,   230,
   165,   367,   675,   432,  2496, 32767,  1539,   820,   905,   428,   446,   447,   428,   538,   544,
   128,   162,    75,   753,   664,  1252, 32767,  1579,   589,   625,   576,   459,   387,   547,   498,
     0,    63,     0,    76,   538,   378,  1422, 32767,  2449,   329,   615,   341,   264,   151,   303,
   369,   491,   463,   535,   655,  1222,   736,  2070, 32767,  1292,   779,  1117,   679,   678,   902,
     0,     0,     0,     0,    32,   138,   553,   556,   880, 32767,   780,   195,   669,   538,   315,
   562,   643,   483,   623,   615,   674,   629,   924,   694,  1601, 32767,  2059,   944,  1558,  1263,
     0,     0,     0,     0,     0,    49,    84,    24,   125,    25,   897, 32767,   438,   139,   600,
   242,   179,   293,   374,   442,   507,   294,   643,   412,  1156,   681,  1416, 32767,  1810,   730,
     0,     0,     0,     0,    46,    76,    41,    37,     0,   183,   199,   235,   627, 32767,   901,
   333,   219,   185,   160,   373,   322,   225,   342,   302,   261,   298,   583,   548,  1691, 32767};


/* ************************* */
/* Keydetector Configuration */
/* ************************* */
#define DEFAULTMBW \
    .signal_filter.coef1 = 0, \
    .base_avrg.n2_order = 12, \
    .non_activity_avrg.n2_order = 15, \
    .entry_event_cnt = 0, \
    .deadband_cnt = 0, \
    .baseline_track_window = 4000, \
    .baseline_track_window_touch = 16000, \
    .touch_limit = 3, \
    .tau_smooth_baseline = 5000, \
    .debounce_length = 0, \
    .baseline_debounce_length = 20 \

const struct nt_keydetector_mbw nt_keydetector_mbw_El_1 = {
    DEFAULTMBW,
    .tau_smooth_signal = 20,
    .min_noise_limit = 192,
    .signal_to_noise_ratio = 5
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_2 = {
    DEFAULTMBW,
    .tau_smooth_signal = 29,
    .min_noise_limit = 192,
    .signal_to_noise_ratio = 5
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_3 = {
    DEFAULTMBW,
    .tau_smooth_signal = 73,
    .min_noise_limit = 192,
    .signal_to_noise_ratio = 5
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_4 = {
    DEFAULTMBW,
    .tau_smooth_signal = 23,
    .min_noise_limit = 192,
    .signal_to_noise_ratio = 5
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_5 = {
    DEFAULTMBW,
    .tau_smooth_signal = 22,
    .min_noise_limit = 192,
    .signal_to_noise_ratio = 5
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_6 = {
    DEFAULTMBW,
    .tau_smooth_signal = 27,
    .min_noise_limit = 192,
    .signal_to_noise_ratio = 5
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_7 = {
    DEFAULTMBW,
    .tau_smooth_signal = 8,
    .min_noise_limit = 69,
    .signal_to_noise_ratio = 14
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_8 = {
    DEFAULTMBW,
    .tau_smooth_signal = 13,
    .min_noise_limit = 138,
    .signal_to_noise_ratio = 7
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_9 = {
    DEFAULTMBW,
    .tau_smooth_signal = 50,
    .min_noise_limit = 192,
    .signal_to_noise_ratio = 5
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_10 = {
    DEFAULTMBW,
    .tau_smooth_signal = 66,
    .min_noise_limit = 192,
    .signal_to_noise_ratio = 5
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_11 = {
    DEFAULTMBW,
    .tau_smooth_signal = 53,
    .min_noise_limit = 192,
    .signal_to_noise_ratio = 5
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_12 = {
    DEFAULTMBW,
    .tau_smooth_signal = 12,
    .min_noise_limit = 120,
    .signal_to_noise_ratio = 8
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_13 = {
    DEFAULTMBW,
    .tau_smooth_signal = 26,
    .min_noise_limit = 192,
    .signal_to_noise_ratio = 5
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_14 = {
    DEFAULTMBW,
    .tau_smooth_signal = 32,
    .min_noise_limit = 192,
    .signal_to_noise_ratio = 5
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_15 = {
    DEFAULTMBW,
    .tau_smooth_signal = 23,
    .min_noise_limit = 192,
    .signal_to_noise_ratio = 5
};

/* ********************** */
/* Hardware Configuration */
/* ********************** */
#define DEFAULTHWCONFIG \
    .configSelfCap.commonConfig.mainClock = kTSI_MainClockSlection_0, \
    .configSelfCap.commonConfig.ssc_prescaler = kTSI_ssc_div_by_1, \
    .configSelfCap.commonConfig.ssc_mode = kTSI_ssc_prbs_method, \
    .configSelfCap.commonConfig.noChargeNum = kTSI_SscNoChargeNumValue_1, \
    .configSelfCap.commonConfig.prbsOutsel = kTSI_SscPrbsOutsel_2, \
    .configSelfCap.commonConfig.chargeNum = kTSI_SscChargeNumValue_3, \
    .configSelfCap.commonConfig.mode = kTSI_SensingModeSlection_Self, \
    .configSelfCap.commonConfig.dvolt = kTSI_DvoltOption_3, \
    .configSelfCap.commonConfig.cutoff = kTSI_SincCutoffDiv_1, \
    .configSelfCap.commonConfig.order = kTSI_SincFilterOrder_1, \
    .configSelfCap.enableSensitivity = false, \
    .configSelfCap.inputCurrent = kTSI_CurrentMultipleInputValue_0, \
    .configSelfCap.xdn = kTSI_SensitivityXdnOption_0, \
    .configSelfCap.chargeCurrent = kTSI_CurrentMultipleChargeValue_0, \
    .configMutual.commonConfig.mainClock      = kTSI_MainClockSlection_0, \
    .configMutual.commonConfig.ssc_prescaler  = kTSI_ssc_div_by_1, \
    .configMutual.commonConfig.ssc_mode = kTSI_ssc_prbs_method, \
    .configMutual.commonConfig.noChargeNum = kTSI_SscNoChargeNumValue_1, \
    .configMutual.commonConfig.prbsOutsel = kTSI_SscPrbsOutsel_2, \
    .configMutual.commonConfig.chargeNum = kTSI_SscChargeNumValue_3, \
    .configMutual.commonConfig.mode           = kTSI_SensingModeSlection_Mutual, \
    .configMutual.commonConfig.dvolt          = kTSI_DvoltOption_3, \
    .configMutual.commonConfig.cutoff         = kTSI_SincCutoffDiv_1, \
    .configMutual.commonConfig.order          = kTSI_SincFilterOrder_1, \
    .configMutual.preCurrent                  = kTSI_MutualPreCurrent_4uA, \
    .configMutual.preResistor                 = kTSI_MutualPreResistor_4k, \
    .configMutual.senseResistor               = kTSI_MutualSenseResistor_10k, \
    .configMutual.boostCurrent                = kTSI_MutualSenseBoostCurrent_0uA, \
    .configMutual.txDriveMode                 = kTSI_MutualTxDriveModeOption_0, \
    .configMutual.pmosLeftCurrent             = kTSI_MutualPmosCurrentMirrorLeft_32, \
    .configMutual.pmosRightCurrent            = kTSI_MutualPmosCurrentMirrorRight_1, \
    .configMutual.enableNmosMirror            = true, \
    .configMutual.nmosCurrent                 = kTSI_MutualNmosCurrentMirror_1, \
    .newCalc = true

const tsi_config_t tsi_hw_config_El_1 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_3, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_2 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_3 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_4 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_5 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_6 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_7 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_8 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_9 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_10 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_11 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_12 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_13 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_14 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_15 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};


/* *********************** */
/* Electrode Configuration */
/* *********************** */
const struct nt_electrode El_1 = {
    .multiplier = 68,
    .divider = 9,
    .offset = 8585,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_1,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_1_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_1
};
const struct nt_electrode El_2 = {
    .multiplier = 67,
    .divider = 13,
    .offset = 10784,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_2,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_2_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_2
};
const struct nt_electrode El_3 = {
    .multiplier = 65,
    .divider = 12,
    .offset = 10862,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_3,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_3_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_3
};
const struct nt_electrode El_4 = {
    .multiplier = 65,
    .divider = 12,
    .offset = 10476,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_4,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_4_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_4
};
const struct nt_electrode El_5 = {
    .multiplier = 68,
    .divider = 13,
    .offset = 9969,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_5,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_5_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_5
};
const struct nt_electrode El_6 = {
    .multiplier = 68,
    .divider = 11,
    .offset = 9247,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_6,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_6_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_6
};
const struct nt_electrode El_7 = {
    .multiplier = 69,
    .divider = 14,
    .offset = 10486,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_7,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_7_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_7
};
const struct nt_electrode El_8 = {
    .multiplier = 65,
    .divider = 13,
    .offset = 10523,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_8,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_8_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_8
};
const struct nt_electrode El_9 = {
    .multiplier = 69,
    .divider = 13,
    .offset = 9277,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_9,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_9_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_9
};
const struct nt_electrode El_10 = {
    .multiplier = 65,
    .divider = 13,
    .offset = 10803,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_10,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_10_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_10
};
const struct nt_electrode El_11 = {
    .multiplier = 67,
    .divider = 14,
    .offset = 9635,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_11,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_11_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_11
};
const struct nt_electrode El_12 = {
    .multiplier = 67,
    .divider = 13,
    .offset = 9626,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_12,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_12_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_12
};
const struct nt_electrode El_13 = {
    .multiplier = 66,
    .divider = 13,
    .offset = 10628,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_13,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_13_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_13
};
const struct nt_electrode El_14 = {
    .multiplier = 66,
    .divider = 13,
    .offset = 9835,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_14,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_14_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_14
};
const struct nt_electrode El_15 = {
    .multiplier = 66,
    .divider = 13,
    .offset = 9995,
    .delta_multiplier = 16,
    .delta_divider = 65,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_15,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = EVB_BOARD_TOUCHPAD_15_ELECTRODE,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_15
};
const struct nt_tsi_recalib_config recalib_configuration = {
    .SelfRangeMin      = 50000,
    .SelfRangeMax      = 62000,
    .SelfRangeDeltaMin = 150,
    .SelfRangeDeltaMax = 7000,
    .MutRangeMin       = 9000,
    .MutRangeMax       = 16000,
    .MutRangeDeltaMin  = 150,
    .MutRangeDeltaMax  = 7000,
};

const struct nt_system_xtalk_params my_xtalk_params = {
    .actMat =(uint16_t*)actMat,
    .nt_xtalk_neighbours = 4,
    .nt_xtalk_adapt_touch_time = 25,
};


/* ***************** */
/* Keypad Definition */
/* ***************** */
const struct nt_electrode *const Keypad_1_controls[] = {
    &El_1, &El_2, &El_3, &El_4, &El_5, &El_6, &El_7, &El_8, &El_9, &El_10, &El_11, &El_12, &El_13, &El_14, &El_15, NULL};

const struct nt_control_keypad nt_control_keypad_Keypad_1 = {
    .groups           = NULL,
    .groups_size      = 0,
    .multi_touch      = (uint32_t[]){0x0C, 0x18, 0x30, 0x24, 0x3C, 0},
    .multi_touch_size = 5,
};

const struct nt_control Keypad_1 = {
    .electrodes            = &Keypad_1_controls[0],
    .control_params.keypad = &nt_control_keypad_Keypad_1,
    .interface             = &nt_control_keypad_interface,
    .adjacent_electrodes = kAdj_disable,
};


/* **************************** */
/* Module and System Definition */
/* **************************** */
const struct nt_electrode *const nt_tsi_module_electrodes[] = {
    &El_1, &El_2, &El_3, &El_4, &El_5, &El_6, &El_7, &El_8, &El_9, &El_10, &El_11, &El_12, &El_13, &El_14, &El_15, NULL};

const struct nt_electrode *const nt_tsi_module_xtalk_electrodes[] = {
    &El_1, &El_2, &El_3, &El_4, &El_5, &El_6, &El_7, &El_8, &El_9, &El_10, &El_11, &El_12, &El_13, &El_14, &El_15, NULL};

const struct nt_module nt_tsi_module = {
    .interface          = &nt_module_tsi_interface,
    .wtrmark_hi         = 65535,
    .wtrmark_lo         = 0,
    .config             = (void *)&tsi_hw_config_El_1,
    .instance           = 0,
    .electrodes         = &nt_tsi_module_electrodes[0],
    .safety_interface   = NULL,
    .safety_params.gpio = (void *)NULL,
    .recalib_config     = (void *)&recalib_configuration,
};

const struct nt_control *const System_0_controls[] = {&Keypad_1, NULL};
const struct nt_module *const System_0_modules[]   = {&nt_tsi_module, NULL};
const struct nt_system System_0                    = {
    .time_period            = 23,
    .init_time              = 1000,
    .safety_period_multiple = 0,
    .safety_crc_hw          = true,
    .controls               = &System_0_controls[0],
    .modules                = &System_0_modules[0],
//    .xtalk_interface        = &nt_system_xtalk_interface,
//    .xtalk_params           = (void *)&my_xtalk_params,
//    .xtalk_electrodes       = &nt_tsi_module_xtalk_electrodes[0],
};


void nt_enable(void)
{
    nt_electrode_enable( &El_1, 0 );
    nt_electrode_enable( &El_2, 0 );
    nt_electrode_enable( &El_3, 0 );
    nt_electrode_enable( &El_4, 0 );
    nt_electrode_enable( &El_5, 0 );
    nt_electrode_enable( &El_6, 0 );
    nt_electrode_enable( &El_7, 0 );
    nt_electrode_enable( &El_8, 0 );
    nt_electrode_enable( &El_9, 0 );
    nt_electrode_enable( &El_10, 0 );
    nt_electrode_enable( &El_11, 0 );
    nt_electrode_enable( &El_12, 0 );
    nt_electrode_enable( &El_13, 0 );
    nt_electrode_enable( &El_14, 0 );
    nt_electrode_enable( &El_15, 0 );
    nt_control_enable( &Keypad_1 );
}
