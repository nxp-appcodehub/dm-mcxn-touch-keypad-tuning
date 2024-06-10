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
 32767,  3612,  2004,  2238,  2012,  1976,  2047,  1966,  1962,  1906,  2051,  1953,  1939,  1961,  1961,  1973,  1966,  1157,  1197,  1090,  1733,  1606,  1932,
  5766, 32767,  6212,  4655,  5433,  4578,  3966,  3870,  4191,  3647,  3860,  3680,  4468,  4245,  4533,  4634,  3102,  1613,  1832,  2212,  2541,  2669,  3002,
     0,  1543, 32767,     0,     0,   583,     1,    19,     0,     0,     0,     0,     0,     0,     0,    11,  1263,   508,   776,  1113,  1264,  1095,  1474,
  2011,  1704,  1660, 32767,  3322,  1624,  2406,  1659,  1651,  1220,  1508,  1534,  1195,  1099,   869,  1250,   338,   789,   664,   857,  1082,   747,   704,
  2695,  3110,  2844,  4233, 32767,  3941,  2804,  3064,  2769,  2189,  2561,  2459,  2465,  1853,  2124,  1680,  1428,  1465,  1398,  1417,  1433,  1420,  1410,
     1,   464,  1525,   213,  1581, 32767,   225,   344,  1569,     3,     0,    35,   162,    14,     0,    19,    69,    47,    60,     0,   247,   113,    88,
   438,   891,  1178,  2151,  2024,  1226, 32767,  2125,  1843,  2090,  2084,  1700,  1084,   598,   639,   571,   146,   241,   484,   408,   920,   557,   764,
    84,   582,   488,  1416,  1882,  1715,  1816, 32767,  3044,   745,  1812,  1464,   361,    83,   202,   320,   431,   523,   785,   586,  1006,   887,   721,
    75,   523,   859,   694,  1363,  1876,  1195,  3307, 32767,   712,  1509,  1881,   432,   408,   222,  1086,   299,   901,   824,   828,  1019,   901,   601,
  1016,  1636,  2065,  2367,  2356,  1779,  2984,  2804,  2672, 32767,  3087,  2505,  2514,  2338,  2133,  2522,  2320,  2829,  2766,  2799,  3099,  2860,  2865,
    51,   106,   403,    67,    92,    27,   370,  1721,   659,  1340, 32767,  2558,   113,     5,    28,     0,    23,   161,   153,    45,   305,   164,   139,
    66,   284,   765,   473,   508,   456,   678,   920,  2446,   417,  3189, 32767,   548,   335,   499,   698,   273,   880,  1265,  1096,  2013,  1640,  1177,
     0,   738,  1587,  1056,   787,   698,  1466,   807,  1133,  1107,   989,  1571, 32767,  3451,  1603,  2015,  2234,  2491,  3123,  2976,  3231,  2931,  2937,
   576,  1360,  1765,  1721,  2048,  1398,  1709,  1231,  1828,  1576,  1885,  2260,  2820, 32767,  2201,  2336,  2419,  2561,  2656,  2733,  2706,  2422,  2660,
   658,   695,   717,   629,   721,   480,   722,   622,   775,   792,   653,   535,   405,   847, 32767, 19305, 15659,  9915, 16879, 11242,  7538, 13881,  8844,
   907,   598,   406,   854,   177,   600,   787,   654,   742,   861,   761,   445,   484,  1034, 20185, 32767, 18415, 14069, 12144, 12908, 13001,  9847, 11477,
   867,   989,   865,   939,   689,   782,   993,   735,  1059,  1110,   853,   700,  1014,  1091, 15681, 21348, 32767, 12556, 18631, 10009, 10319, 14230,  6979,
    43,    69,    60,   115,    34,     8,    82,    76,    26,    22,     0,     8,     8,   115,  6714, 12746, 11718, 32767, 25974, 19322,  9554, 14890, 11285,
    23,   341,   251,   240,     0,   283,   606,   285,   265,   501,   127,   127,     0,   521, 10708,  7803, 10747, 21416, 32767, 16882, 12989, 10511, 10933,
     0,    73,    88,     8,     8,     8,     8,    26,     0,   104,    21,    39,     8,    26, 11004, 15527,  8329, 19035, 30265, 32767, 12841, 16575,  9324,
     0,    30,     0,     0,     0,     0,     8,    14,     0,    28,     8,    27,     0,    43,  5151, 10267,  8235,  6775, 14828,  9710, 32767, 21215, 13116,
   248,   204,   584,   471,   364,   231,   570,   440,   274,   448,   172,   235,   244,   463,  9635,  7347,  9893, 11540,  7777,  9800, 17446, 32767, 14383,
     0,    52,     0,   189,     0,   228,     0,    39,    74,    16,    60,     0,     0,   126,  9389, 13697,  7468, 12780, 19735,  7864, 18756, 26958, 32767};


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
    .tau_smooth_signal = 7,
    .min_noise_limit = 127,
    .signal_to_noise_ratio = 13
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_2 = {
    DEFAULTMBW,
    .tau_smooth_signal = 0,
    .min_noise_limit = 31,
    .signal_to_noise_ratio = 53
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_3 = {
    DEFAULTMBW,
    .tau_smooth_signal = 6,
    .min_noise_limit = 110,
    .signal_to_noise_ratio = 15
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_4 = {
    DEFAULTMBW,
    .tau_smooth_signal = 0,
    .min_noise_limit = 72,
    .signal_to_noise_ratio = 23
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_5 = {
    DEFAULTMBW,
    .tau_smooth_signal = 5,
    .min_noise_limit = 87,
    .signal_to_noise_ratio = 19
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_6 = {
    DEFAULTMBW,
    .tau_smooth_signal = 0,
    .min_noise_limit = 64,
    .signal_to_noise_ratio = 26
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_7 = {
    DEFAULTMBW,
    .tau_smooth_signal = 0,
    .min_noise_limit = 36,
    .signal_to_noise_ratio = 46
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_8 = {
    DEFAULTMBW,
    .tau_smooth_signal = 0,
    .min_noise_limit = 79,
    .signal_to_noise_ratio = 21
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_9 = {
    DEFAULTMBW,
    .tau_smooth_signal = 7,
    .min_noise_limit = 118,
    .signal_to_noise_ratio = 14
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_10 = {
    DEFAULTMBW,
    .tau_smooth_signal = 9,
    .min_noise_limit = 235,
    .signal_to_noise_ratio = 7
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_11 = {
    DEFAULTMBW,
    .tau_smooth_signal = 8,
    .min_noise_limit = 183,
    .signal_to_noise_ratio = 9
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_12 = {
    DEFAULTMBW,
    .tau_smooth_signal = 0,
    .min_noise_limit = 36,
    .signal_to_noise_ratio = 46
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_13 = {
    DEFAULTMBW,
    .tau_smooth_signal = 27,
    .min_noise_limit = 329,
    .signal_to_noise_ratio = 5
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_14 = {
    DEFAULTMBW,
    .tau_smooth_signal = 32,
    .min_noise_limit = 329,
    .signal_to_noise_ratio = 5
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_15 = {
    DEFAULTMBW,
    .tau_smooth_signal = 9,
    .min_noise_limit = 150,
    .signal_to_noise_ratio = 11
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_16 = {
    DEFAULTMBW,
    .tau_smooth_signal = 0,
    .min_noise_limit = 83,
    .signal_to_noise_ratio = 20
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_17 = {
    DEFAULTMBW,
    .tau_smooth_signal = 11,
    .min_noise_limit = 118,
    .signal_to_noise_ratio = 14
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_18 = {
    DEFAULTMBW,
    .tau_smooth_signal = 0,
    .min_noise_limit = 6,
    .signal_to_noise_ratio = 274
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_19 = {
    DEFAULTMBW,
    .tau_smooth_signal = 20,
    .min_noise_limit = 183,
    .signal_to_noise_ratio = 9
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_20 = {
    DEFAULTMBW,
    .tau_smooth_signal = 0,
    .min_noise_limit = 38,
    .signal_to_noise_ratio = 43
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_21 = {
    DEFAULTMBW,
    .tau_smooth_signal = 8,
    .min_noise_limit = 137,
    .signal_to_noise_ratio = 12
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_22 = {
    DEFAULTMBW,
    .tau_smooth_signal = 9,
    .min_noise_limit = 137,
    .signal_to_noise_ratio = 12
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_23 = {
    DEFAULTMBW,
    .tau_smooth_signal = 11,
    .min_noise_limit = 274,
    .signal_to_noise_ratio = 6
};

/* ********************** */
/* Hardware Configuration */
/* ********************** */
#define DEFAULTHWCONFIG \
    .configSelfCap.commonConfig.mainClock = kTSI_MainClockSlection_0, \
    .configSelfCap.commonConfig.ssc_prescaler = kTSI_ssc_div_by_1, \
    .configSelfCap.commonConfig.ssc_mode = kTSI_ssc_prbs_method, \
    .configSelfCap.commonConfig.noChargeNum = kTSI_SscNoChargeNumValue_1, \
    .configSelfCap.commonConfig.prbsOutsel = kTSI_SscPrbsOutsel_8, \
    .configSelfCap.commonConfig.chargeNum = kTSI_SscChargeNumValue_5, \
    .configSelfCap.commonConfig.mode = kTSI_SensingModeSlection_Self, \
    .configSelfCap.commonConfig.dvolt = kTSI_DvoltOption_5, \
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
    .configMutual.commonConfig.prbsOutsel = kTSI_SscPrbsOutsel_8, \
    .configMutual.commonConfig.chargeNum = kTSI_SscChargeNumValue_5, \
    .configMutual.commonConfig.mode           = kTSI_SensingModeSlection_Mutual, \
    .configMutual.commonConfig.dvolt          = kTSI_DvoltOption_5, \
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
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_4, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_2 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_3, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_3 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_3, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_4 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_3, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_5 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_3, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_6 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_3, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_7 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_4, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_8 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_3, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_9 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_3, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_10 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_5, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_11 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_5, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_12 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_7, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_13 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_8, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_14 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_9, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_15 = {
    DEFAULTHWCONFIG,
    .configMutual.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_16 = {
    DEFAULTHWCONFIG,
    .configMutual.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_17 = {
    DEFAULTHWCONFIG,
    .configMutual.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_18 = {
    DEFAULTHWCONFIG,
    .configMutual.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_19 = {
    DEFAULTHWCONFIG,
    .configMutual.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_20 = {
    DEFAULTHWCONFIG,
    .configMutual.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_21 = {
    DEFAULTHWCONFIG,
    .configMutual.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_22 = {
    DEFAULTHWCONFIG,
    .configMutual.commonConfig.decimation = kTSI_SincDecimationValue_3, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_23 = {
    DEFAULTHWCONFIG,
    .configMutual.commonConfig.decimation = kTSI_SincDecimationValue_2, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};


/* *********************** */
/* Electrode Configuration */
/* *********************** */
const struct nt_electrode El_1 = {
    .multiplier = 69,
    .divider = 10,
    .offset = 4292,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_1,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_1,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_1
};
const struct nt_electrode El_2 = {
    .multiplier = 66,
    .divider = 15,
    .offset = 5483,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_2,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_2,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_2
};
const struct nt_electrode El_3 = {
    .multiplier = 65,
    .divider = 13,
    .offset = 5305,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_3,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_3,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_3
};
const struct nt_electrode El_4 = {
    .multiplier = 66,
    .divider = 14,
    .offset = 5437,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_4,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_4,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_4
};
const struct nt_electrode El_5 = {
    .multiplier = 64,
    .divider = 15,
    .offset = 5290,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_5,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_5,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_5
};
const struct nt_electrode El_6 = {
    .multiplier = 66,
    .divider = 14,
    .offset = 5319,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_6,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_6,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_6
};
const struct nt_electrode El_7 = {
    .multiplier = 71,
    .divider = 10,
    .offset = 4356,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_7,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_7,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_7
};
const struct nt_electrode El_8 = {
    .multiplier = 66,
    .divider = 14,
    .offset = 5706,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_8,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_8,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_8
};
const struct nt_electrode El_9 = {
    .multiplier = 66,
    .divider = 13,
    .offset = 5592,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_9,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_9,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_9
};
const struct nt_electrode El_10 = {
    .multiplier = 73,
    .divider = 7,
    .offset = 3764,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_10,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_10,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_10
};
const struct nt_electrode El_11 = {
    .multiplier = 69,
    .divider = 7,
    .offset = 3752,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_11,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_11,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_11
};
const struct nt_electrode El_12 = {
    .multiplier = 70,
    .divider = 4,
    .offset = 2883,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_12,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_12,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_12
};
const struct nt_electrode El_13 = {
    .multiplier = 95,
    .divider = 3,
    .offset = 2213,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_13,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SPRING_ELECTRODE_1,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_13
};
const struct nt_electrode El_14 = {
    .multiplier = 70,
    .divider = 2,
    .offset = 2062,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_14,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SPRING_ELECTRODE_2,
    .tsicnt_shift = 3,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_14
};
const struct nt_electrode El_15 = {
    .multiplier = 70,
    .divider = 2,
    .offset = 721,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_15,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_MUTUAL_ELECTRODE_1,
    .tsicnt_shift = 0,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_15
};
const struct nt_electrode El_16 = {
    .multiplier = 80,
    .divider = 2,
    .offset = 686,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_16,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_MUTUAL_ELECTRODE_2,
    .tsicnt_shift = 0,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_16
};
const struct nt_electrode El_17 = {
    .multiplier = 84,
    .divider = 3,
    .offset = 778,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_17,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_MUTUAL_ELECTRODE_3,
    .tsicnt_shift = 0,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_17
};
const struct nt_electrode El_18 = {
    .multiplier = 79,
    .divider = 2,
    .offset = 665,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_18,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_MUTUAL_ELECTRODE_4,
    .tsicnt_shift = 0,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_18
};
const struct nt_electrode El_19 = {
    .multiplier = 89,
    .divider = 2,
    .offset = 621,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_19,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_MUTUAL_ELECTRODE_5,
    .tsicnt_shift = 0,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_19
};
const struct nt_electrode El_20 = {
    .multiplier = 73,
    .divider = 2,
    .offset = 701,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_20,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_MUTUAL_ELECTRODE_6,
    .tsicnt_shift = 0,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_20
};
const struct nt_electrode El_21 = {
    .multiplier = 67,
    .divider = 2,
    .offset = 711,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_21,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_MUTUAL_ELECTRODE_7,
    .tsicnt_shift = 0,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_21
};
const struct nt_electrode El_22 = {
    .multiplier = 67,
    .divider = 3,
    .offset = 1002,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_22,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_MUTUAL_ELECTRODE_8,
    .tsicnt_shift = 0,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_22
};
const struct nt_electrode El_23 = {
    .multiplier = 70,
    .divider = 2,
    .offset = 752,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_23,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_MUTUAL_ELECTRODE_9,
    .tsicnt_shift = 0,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_23
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
    &El_1, &El_2, &El_3, &El_4, &El_5, &El_6, &El_7, &El_8, &El_9, &El_10, &El_11, &El_12, &El_13, &El_14, &El_15, &El_16, &El_17, &El_18, &El_19, &El_20, &El_21, &El_22, &El_23, NULL};

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
};


/* **************************** */
/* Module and System Definition */
/* **************************** */
const struct nt_electrode *const nt_tsi_module_electrodes[] = {
    &El_1, &El_2, &El_3, &El_4, &El_5, &El_6, &El_7, &El_8, &El_9, &El_10, &El_11, &El_12, &El_13, &El_14, &El_15, &El_16, &El_17, &El_18, &El_19, &El_20, &El_21, &El_22, &El_23, NULL};

const struct nt_electrode *const nt_tsi_module_xtalk_electrodes[] = {
    &El_1, &El_2, &El_3, &El_4, &El_5, &El_6, &El_7, &El_8, &El_9, &El_10, &El_11, &El_12, &El_13, &El_14, &El_15, &El_16, &El_17, &El_18, &El_19, &El_20, &El_21, &El_22, &El_23, NULL};

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
    .time_period            = 17,
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
    nt_electrode_enable( &El_16, 0 );
    nt_electrode_enable( &El_17, 0 );
    nt_electrode_enable( &El_18, 0 );
    nt_electrode_enable( &El_19, 0 );
    nt_electrode_enable( &El_20, 0 );
    nt_electrode_enable( &El_21, 0 );
    nt_electrode_enable( &El_22, 0 );
    nt_electrode_enable( &El_23, 0 );
    nt_control_enable( &Keypad_1 );
}
