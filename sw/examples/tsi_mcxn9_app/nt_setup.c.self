// Auto-generated config file
// tuningGuide.py rev: 31503

#include "nt_setup.h"
#include "board.h"


/* ************************** */
/* Crosstalk reduction Matrix */
/* ************************** */
int16_t actMat[] = {
 32767,  3824,   876,  3817,  1953,   896,  1690,   713,  1543,  1139,  1236,   970,
  2823, 32767,  1552,  1938,  2173,   510,   277,   164,   214,    89,    35,   203,
  1974,  2302, 32767,  2068,  2137,  2096,  1874,  1517,  1705,  1599,  1503,  1325,
  1844,  1527,   880, 32767,  2822,  1350,  1774,  1720,  1041,  1363,  1165,   986,
  1479,  1827,   582,  3710, 32767,  1907,  1855,  1868,  1824,  1225,  1159,   762,
   847,  1215,  1190,  1190,  1567, 32767,  1210,  1233,  1295,   865,  1036,   902,
   194,   101,    21,  1628,   847,   214, 32767,  1578,   509,  1704,  1096,   394,
  1183,  1183,   535,  1481,  2527,  1416,  2807, 32767,  2810,  1721,  2382,  1388,
     6,    35,     0,    27,    25,  2526,    48,  1746, 32767,   211,   243,   448,
     0,     0,     0,     0,     8,    10,  1607,     1,     0, 32767,  1603,     7,
   567,   488,   503,   581,   621,   579,   605,  1542,   595,  2460, 32767,  2257,
  1452,  1612,   987,  1657,  1766,  1497,  1959,  1986,  2205,  1780,  3436, 32767};


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
    .tau_smooth_signal = 6,
    .min_noise_limit = 174,
    .signal_to_noise_ratio = 13
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_2 = {
    DEFAULTMBW,
    .tau_smooth_signal = 5,
    .min_noise_limit = 189,
    .signal_to_noise_ratio = 12
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_3 = {
    DEFAULTMBW,
    .tau_smooth_signal = 14,
    .min_noise_limit = 252,
    .signal_to_noise_ratio = 9
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_4 = {
    DEFAULTMBW,
    .tau_smooth_signal = 6,
    .min_noise_limit = 206,
    .signal_to_noise_ratio = 11
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_5 = {
    DEFAULTMBW,
    .tau_smooth_signal = 7,
    .min_noise_limit = 283,
    .signal_to_noise_ratio = 8
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_6 = {
    DEFAULTMBW,
    .tau_smooth_signal = 9,
    .min_noise_limit = 206,
    .signal_to_noise_ratio = 11
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_7 = {
    DEFAULTMBW,
    .tau_smooth_signal = 6,
    .min_noise_limit = 227,
    .signal_to_noise_ratio = 10
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_8 = {
    DEFAULTMBW,
    .tau_smooth_signal = 5,
    .min_noise_limit = 174,
    .signal_to_noise_ratio = 13
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_9 = {
    DEFAULTMBW,
    .tau_smooth_signal = 5,
    .min_noise_limit = 151,
    .signal_to_noise_ratio = 15
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_10 = {
    DEFAULTMBW,
    .tau_smooth_signal = 6,
    .min_noise_limit = 189,
    .signal_to_noise_ratio = 12
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_11 = {
    DEFAULTMBW,
    .tau_smooth_signal = 7,
    .min_noise_limit = 283,
    .signal_to_noise_ratio = 8
};
const struct nt_keydetector_mbw nt_keydetector_mbw_El_12 = {
    DEFAULTMBW,
    .tau_smooth_signal = 8,
    .min_noise_limit = 252,
    .signal_to_noise_ratio = 9
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
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_6, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_2 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_5, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_3 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_5, \
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
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_4, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_7 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_3, \
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
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_3, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_11 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_3, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};
const tsi_config_t tsi_hw_config_El_12 = {
    DEFAULTHWCONFIG,
    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_4, \
    .configSelfCap.enableShield = kTSI_shieldAllOff \
};


/* *********************** */
/* Electrode Configuration */
/* *********************** */
const struct nt_electrode El_1 = {
    .multiplier = 73,
    .divider = 7,
    .offset = 6726,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_1,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_1,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_1
};
const struct nt_electrode El_2 = {
    .multiplier = 67,
    .divider = 10,
    .offset = 7504,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_2,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_2,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_2
};
const struct nt_electrode El_3 = {
    .multiplier = 66,
    .divider = 9,
    .offset = 7534,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_3,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_3,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_3
};
const struct nt_electrode El_4 = {
    .multiplier = 65,
    .divider = 20,
    .offset = 11185,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_4,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_4,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_4
};
const struct nt_electrode El_5 = {
    .multiplier = 67,
    .divider = 20,
    .offset = 11413,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_5,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_5,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_5
};
const struct nt_electrode El_6 = {
    .multiplier = 69,
    .divider = 13,
    .offset = 8724,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_6,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_6,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_6
};
const struct nt_electrode El_7 = {
    .multiplier = 65,
    .divider = 20,
    .offset = 10638,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_7,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_7,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_7
};
const struct nt_electrode El_8 = {
    .multiplier = 65,
    .divider = 22,
    .offset = 10609,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_8,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_8,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_8
};
const struct nt_electrode El_9 = {
    .multiplier = 65,
    .divider = 19,
    .offset = 10904,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_9,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_9,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_9
};
const struct nt_electrode El_10 = {
    .multiplier = 65,
    .divider = 19,
    .offset = 10609,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_10,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_10,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_10
};
const struct nt_electrode El_11 = {
    .multiplier = 65,
    .divider = 19,
    .offset = 11017,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_11,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_11,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_11
};
const struct nt_electrode El_12 = {
    .multiplier = 65,
    .divider = 12,
    .offset = 8586,
    .delta_multiplier = 64,
    .delta_divider = 64,
    .keydetector_params.mbw = &nt_keydetector_mbw_El_12,
    .keydetector_interface= &nt_keydetector_mbw_interface,
    .pin_input = BOARD_TSI_SELF_ELECTRODE_12,
    .tsicnt_shift = 4,
    .tsi_hw_config = ( void* )&tsi_hw_config_El_12
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
    &El_1, &El_2, &El_3, &El_4, &El_5, &El_6, &El_7, &El_8, &El_9, &El_10, &El_11, &El_12, NULL};

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
    &El_1, &El_2, &El_3, &El_4, &El_5, &El_6, &El_7, &El_8, &El_9, &El_10, &El_11, &El_12, NULL};

const struct nt_electrode *const nt_tsi_module_xtalk_electrodes[] = {
    &El_1, &El_2, &El_3, &El_4, &El_5, &El_6, &El_7, &El_8, &El_9, &El_10, &El_11, &El_12, NULL};

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
    .time_period            = 11,
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
    nt_control_enable( &Keypad_1 );
}
