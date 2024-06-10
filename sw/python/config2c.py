#!/usr/bin/env python
# -*- coding: UTF-8 -*-
#
# Copyright 2024 NXP
#
# NXP Proprietary. This software is owned or controlled by NXP and may only be
# used strictly in accordance with the applicable license terms.  By expressly 
# accepting such terms or by downloading, installing, activating and/or 
# otherwise using the software, you are agreeing that you have read, and that 
# you agree to comply with and are bound by, such license terms.  If you do 
# not agree to be bound by the applicable license terms, then you may not 
# retain, install, activate or otherwise use the software.

# Script to generate settings from JSON file
#
# $Rev: 31685 $

import numpy as np
import json
import argparse
from os.path import exists
import sys
import re

def parseArguments():
    # Read arguments from command line
    parser = argparse.ArgumentParser( description = 'Convert TSI JSON file to nt_setup.c' )
    parser.add_argument( '-i', '--inputJsonFile', help = 'Input JSON filename' )
    parser.add_argument( '-o', '--output', help = 'Output file', default = 'nt_setup.c' )
    parser.add_argument( '-v', '--verbose', action = 'store_true' )
    args = parser.parse_args()

    return args


def convertMatrix2C( actMat ):
    np.set_printoptions(threshold=np.inf) #b01800
    nSensors = actMat.shape[1]
    rounded_np = np.round( actMat ).astype(int)

    #rounded_np.flatten(), max_line_width = 80, separator = ",",
    out = np.array2string(
            rounded_np,
            formatter={'int':lambda x: "%6d" % x},
            max_line_width = np.inf, separator = ","
        )

    out = out.replace("[", "")
    out = out.replace("]", "")
    out = out.replace("\n ", "\n") # remove one space after newline
    # Make like matab
    out = '{\n' + out
    out += "};\n\n"

    return out

def checkFile( fileName ):
    if(( fileName is None ) or ( not exists( fileName ))):
        print( f'Unable to open file {fileName}' )
        sys.exit()
    return fileName

def findAllInd( text, expression ):
    # try re.findall
    ind = [m.start() for m in re.finditer( expression, text )]
    return ind

def json2c( json1, fnOut, pinChannels, pinLabels ):
    fs = json1['fs']
    fSw = json1['fSw']
    nSensors = len( pinChannels )

    n1 = json1['n1']
    if(nSensors > n1):
        dualTSI = 1
    else:
        dualTSI = 0

    # Output file
    with open( fnOut, 'w' ) as fidOut:
        # Pre-amble
        fidOut.write( '// Auto-generated config file\n' )
        fidOut.write( f"// tuningGuide.py rev: {json1['rev']}\n\n" )
        fidOut.write( '#include "nt_setup.h"\n#include "board.h"\n\n\n' )

        # Crosstalk reduction matrix
        fidOut.write( '/* ************************** */\n' )
        fidOut.write( '/* Crosstalk reduction Matrix */\n' )
        fidOut.write( '/* ************************** */\n' )
        if( 'actMat' in json1 ):
            actMat = np.array( json1['actMat'] )
        else:
            actMat = np.eye( nSensors ) * 32767
        actMatStr = convertMatrix2C( actMat )
        fidOut.write( 'int16_t actMat[] = ' )
        fidOut.write( actMatStr )

        # Keydetector config
        fidOut.write( '\n' )
        fidOut.write( '/* ************************* */\n' )
        fidOut.write( '/* Keydetector Configuration */\n' )
        fidOut.write( '/* ************************* */\n' )
        commonConfig = ['signal_to_noise_ratio']    # Common for all keys
        commonConfig = None
        tau_smooth_signal = np.array( json1['tau_smooth_signal'] )
        min_noise_limit = np.array( json1['min_noise_limit'] )
        signal_to_noise_ratio = np.array( json1['signal_to_noise_ratio'] )
        fidOut.write( '#define DEFAULTMBW \\\n' )
        fidOut.write( '    .signal_filter.coef1 = 0, \\\n' )
        fidOut.write( '    .base_avrg.n2_order = 12, \\\n' )
        fidOut.write( '    .non_activity_avrg.n2_order = 15, \\\n' )
        fidOut.write( '    .entry_event_cnt = 0, \\\n' )
        fidOut.write( '    .deadband_cnt = 0, \\\n' )
        fidOut.write( '    .baseline_track_window = %d, \\\n' % 4000 )  # in ms
        fidOut.write( '    .baseline_track_window_touch = %d, \\\n' % 16000 )
        fidOut.write( '    .touch_limit = 3, \\\n' )
        fidOut.write( '    .tau_smooth_baseline = 5000, \\\n' )
        fidOut.write( '    .debounce_length = %d, \\\n' % json1['debounce_length'] )
        fidOut.write( '    .baseline_debounce_length = 20 \\\n\n' )


        for c2 in range( nSensors ):   # Including disabled keys
            # Start new key
            fidOut.write( 'const struct nt_keydetector_mbw nt_keydetector_mbw_%s = {\n' % pinLabels[c2] )

            # Common Parameters
            fidOut.write( '    DEFAULTMBW,\n' )
            fidOut.write( '    .tau_smooth_signal = %d,\n' % tau_smooth_signal[c2] )
            fidOut.write( '    .min_noise_limit = %d,\n' % min_noise_limit[c2] )
            fidOut.write( '    .signal_to_noise_ratio = %d' % signal_to_noise_ratio[c2] )

            # Settings for each key
            if commonConfig is not None:
                fidOut.write( ',\n' )
                for c1 in range( len( commonConfig ) ):
                    fidOut.write( '    .%s = %d' % ( commonConfig[c1], json1[commonConfig[c1]] ) )
                    if( c1 < len( commonConfig )-1 ):
                        fidOut.write( ',\n' )
                    else:
                        fidOut.write( '\n' )
            else:
                fidOut.write( '\n' )
            fidOut.write( '};\n' )
        fidOut.write( '\n' )

        # HW Config
        # Common config
        fidOut.write( '/* ********************** */\n' )
        fidOut.write( '/* Hardware Configuration */\n' )
        fidOut.write( '/* ********************** */\n' )
        fidOut.write( '#define DEFAULTHWCONFIG \\\n' )
        fidOut.write( '    .configSelfCap.commonConfig.mainClock = kTSI_MainClockSlection_%d, \\\n' % json1['mainClockSel'] )
        fidOut.write( '    .configSelfCap.commonConfig.ssc_prescaler = kTSI_ssc_div_by_%d, \\\n'% json1['prescaler'] )   # Clock div using PRBS
        if( json1['prbsT1'] == 0 ):
            fidOut.write( '    .configSelfCap.commonConfig.ssc_mode = kTSI_ssc_dissable, \\\n' )
            fidOut.write( '    .configSelfCap.commonConfig.noChargeNum = kTSI_SscNoChargeNumValue_1, \\\n' )
            fidOut.write( '    .configSelfCap.commonConfig.prbsOutsel = kTSI_SscPrbsOutsel_2, \\\n' )
            fidOut.write( '    .configSelfCap.commonConfig.chargeNum = kTSI_SscChargeNumValue_1, \\\n' )
        else:
            fidOut.write( '    .configSelfCap.commonConfig.ssc_mode = kTSI_ssc_prbs_method, \\\n' )
            fidOut.write( '    .configSelfCap.commonConfig.noChargeNum = kTSI_SscNoChargeNumValue_%d, \\\n' % json1['prbsT1'] )
            fidOut.write( '    .configSelfCap.commonConfig.prbsOutsel = kTSI_SscPrbsOutsel_%d, \\\n' % json1['prbsT2'] )
            fidOut.write( '    .configSelfCap.commonConfig.chargeNum = kTSI_SscChargeNumValue_%d, \\\n' % json1['prbsT3'] )
        fidOut.write( '    .configSelfCap.commonConfig.mode = kTSI_SensingModeSlection_Self, \\\n' )
        fidOut.write( '    .configSelfCap.commonConfig.dvolt = kTSI_DvoltOption_%d, \\\n' % json1['dvolt_option'] )
        fidOut.write( '    .configSelfCap.commonConfig.cutoff = kTSI_SincCutoffDiv_1, \\\n' )
        fidOut.write( '    .configSelfCap.commonConfig.order = kTSI_SincFilterOrder_1, \\\n' )
        fidOut.write( '    .configSelfCap.enableSensitivity = false, \\\n' )
        fidOut.write( '    .configSelfCap.inputCurrent = kTSI_CurrentMultipleInputValue_0, \\\n' )
        fidOut.write( '    .configSelfCap.xdn = kTSI_SensitivityXdnOption_0, \\\n' )
        fidOut.write( '    .configSelfCap.chargeCurrent = kTSI_CurrentMultipleChargeValue_0, \\\n' )
#MUTUAL mode
        fidOut.write( '    .configMutual.commonConfig.mainClock      = kTSI_MainClockSlection_%d, \\\n' % json1['mainClockSel'] )
        fidOut.write( '    .configMutual.commonConfig.ssc_prescaler  = kTSI_ssc_div_by_%d, \\\n'% json1['prescaler'] )
        if( json1['prbsT1'] == 0 ):
            fidOut.write( '    .configMutual.commonConfig.ssc_mode = kTSI_ssc_dissable, \\\n' )
            fidOut.write( '    .configMutual.commonConfig.noChargeNum = kTSI_SscNoChargeNumValue_1, \\\n' )
            fidOut.write( '    .configMutual.commonConfig.prbsOutsel = kTSI_SscPrbsOutsel_2, \\\n' )
            fidOut.write( '    .configMutual.commonConfig.chargeNum = kTSI_SscChargeNumValue_1, \\\n' )
        else:
            fidOut.write( '    .configMutual.commonConfig.ssc_mode = kTSI_ssc_prbs_method, \\\n' )
            fidOut.write( '    .configMutual.commonConfig.noChargeNum = kTSI_SscNoChargeNumValue_%d, \\\n' % json1['prbsT1'] )
            fidOut.write( '    .configMutual.commonConfig.prbsOutsel = kTSI_SscPrbsOutsel_%d, \\\n' % json1['prbsT2'] )
            fidOut.write( '    .configMutual.commonConfig.chargeNum = kTSI_SscChargeNumValue_%d, \\\n' % json1['prbsT3'] )
        fidOut.write( '    .configMutual.commonConfig.mode           = kTSI_SensingModeSlection_Mutual, \\\n' )
        fidOut.write( '    .configMutual.commonConfig.dvolt          = kTSI_DvoltOption_%d, \\\n' % json1['dvolt_option'] )
        fidOut.write( '    .configMutual.commonConfig.cutoff         = kTSI_SincCutoffDiv_1, \\\n' )
        fidOut.write( '    .configMutual.commonConfig.order          = kTSI_SincFilterOrder_1, \\\n' ) 
        fidOut.write( '    .configMutual.preCurrent                  = kTSI_MutualPreCurrent_4uA, \\\n' )
        fidOut.write( '    .configMutual.preResistor                 = kTSI_MutualPreResistor_4k, \\\n' )
        fidOut.write( '    .configMutual.senseResistor               = kTSI_MutualSenseResistor_10k, \\\n' )
        fidOut.write( '    .configMutual.boostCurrent                = kTSI_MutualSenseBoostCurrent_0uA, \\\n' )
        fidOut.write( '    .configMutual.txDriveMode                 = kTSI_MutualTxDriveModeOption_0, \\\n' )
        fidOut.write( '    .configMutual.pmosLeftCurrent             = kTSI_MutualPmosCurrentMirrorLeft_32, \\\n' )
        fidOut.write( '    .configMutual.pmosRightCurrent            = kTSI_MutualPmosCurrentMirrorRight_1, \\\n' )
        fidOut.write( '    .configMutual.enableNmosMirror            = true, \\\n' )
        fidOut.write( '    .configMutual.nmosCurrent                 = kTSI_MutualNmosCurrentMirror_1, \\\n' )
        fidOut.write( '    .newCalc = true\n\n' )       
        
        
        for c2 in range( nSensors ):
            # Get name
            name1 = pinLabels[c2]
            fidOut.write( 'const tsi_config_t tsi_hw_config_%s = {\n' % name1 )
            fidOut.write( '    DEFAULTHWCONFIG,\n' )
            #b01800 mutual
            if(json1['mutual_input'][c2] == 'true'):
                fidOut.write( '    .configMutual.commonConfig.decimation = kTSI_SincDecimationValue_%d, \\\n' % json1['decimation'][c2] )
            else:
                fidOut.write( '    .configSelfCap.commonConfig.decimation = kTSI_SincDecimationValue_%d, \\\n' % json1['decimation'][c2] )
            fidOut.write( '    .configSelfCap.enableShield = %s \\\n' % json1['enable_shield'][c2] )
            fidOut.write( '};\n' )

        # Electrode Config
        fidOut.write( '\n\n' )
        fidOut.write( '/* *********************** */\n' )
        fidOut.write( '/* Electrode Configuration */\n' )
        fidOut.write( '/* *********************** */\n' )
        for c2 in range( nSensors ):   # Only enabled keys (params in json)
            fidOut.write( 'const struct nt_electrode %s = {\n' % pinLabels[c2] )
            fidOut.write( '    .multiplier = %d,\n' % json1['multiplier'][c2] )
            fidOut.write( '    .divider = %d,\n' % json1['divider'][c2] )
            fidOut.write( '    .offset = %d,\n' % json1['offset'][c2] )
            fidOut.write( '    .delta_multiplier = %d,\n' % json1['delta_multiplier'][c2] )
            fidOut.write( '    .delta_divider = %d,\n' % json1['delta_divider'][c2] )
            fidOut.write( '    .keydetector_params.mbw = &nt_keydetector_mbw_%s,\n' % pinLabels[c2] )
            fidOut.write( '    .keydetector_interface= &nt_keydetector_mbw_interface,\n' )
            fidOut.write( '    .pin_input = %s,\n' % pinChannels[c2] )
            if( 'gpio_input' in json1 ):
                fidOut.write( '    .gpio_input = %s,\n' % json1['gpio_input'][c2] )
#b01800     #fidOut.write( '    .tsicnt_shift = %d,\n' % json1['TSICNT_SHIFT'] )
            fidOut.write( '    .tsicnt_shift = %d,\n' % json1['TSICNT_SHIFT'][c2] )
            if( 'shield_mask' in json1 ):
                fidOut.write( '    .shield_mask = %s,\n' % json1['shield_mask'][c2] )
            fidOut.write( '    .tsi_hw_config = ( void* )&tsi_hw_config_%s\n' % pinLabels[c2] )
            fidOut.write( '};\n' )


        # Necessary Bits
        fidOut.write( 'const struct nt_tsi_recalib_config recalib_configuration = {\n' )
        fidOut.write( '    .SelfRangeMin      = 50000,\n' )
        fidOut.write( '    .SelfRangeMax      = 62000,\n' )
        fidOut.write( '    .SelfRangeDeltaMin = 150,\n' )
        fidOut.write( '    .SelfRangeDeltaMax = 7000,\n' )
        fidOut.write( '    .MutRangeMin       = 9000,\n' )
        fidOut.write( '    .MutRangeMax       = 16000,\n' )
        fidOut.write( '    .MutRangeDeltaMin  = 150,\n' )
        fidOut.write( '    .MutRangeDeltaMax  = 7000,\n' )
        fidOut.write( '};\n\n' )

        #fidOut.write( 'const struct nt_module_safety_gpio_params my_safety_params = {\n' )
        #fidOut.write( '    .delay_interval = 0,\n' )
        #fidOut.write( '    .user_interface = &gpio_interface,\n' )
        #fidOut.write( '};\n' )

        # Xtalk Params
        fidOut.write( 'const struct nt_system_xtalk_params my_xtalk_params = {\n' )
        fidOut.write( '    .actMat =(uint16_t*)actMat,\n' )
        fidOut.write( '    .nt_xtalk_neighbours = 4,\n' )
        fidOut.write( '    .nt_xtalk_adapt_touch_time = 25,\n' )
        fidOut.write( '};\n' )


        # Keypad Definition
        fidOut.write( '\n\n' )
        fidOut.write( '/* ***************** */\n' )
        fidOut.write( '/* Keypad Definition */\n' )
        fidOut.write( '/* ***************** */\n' )
        fidOut.write( 'const struct nt_electrode *const Keypad_1_controls[] = {\n    ' )
        for c1 in range( nSensors ):
            fidOut.write( '&%s, '% pinLabels[c1] )
        fidOut.write( 'NULL};\n\n' )

        fidOut.write( 'const struct nt_control_keypad nt_control_keypad_Keypad_1 = {\n' )
        fidOut.write( '    .groups           = NULL,\n' )
        fidOut.write( '    .groups_size      = 0,\n' )
        fidOut.write( '    .multi_touch      = (uint32_t[]){0x0C, 0x18, 0x30, 0x24, 0x3C, 0},\n' )
        fidOut.write( '    .multi_touch_size = 5,\n' )
        fidOut.write( '};\n\n' )

        fidOut.write( 'const struct nt_control Keypad_1 = {\n' )
        fidOut.write( '    .electrodes            = &Keypad_1_controls[0],\n' )
        fidOut.write( '    .control_params.keypad = &nt_control_keypad_Keypad_1,\n' )
        fidOut.write( '    .interface             = &nt_control_keypad_interface,\n' )
        if( 'adjacent_electrodes' in json1 ):
            fidOut.write( '    .adjacent_electrodes = %s,\n' % json1['adjacent_electrodes'] )
        fidOut.write('};\n' )

        # Module Definition
        fidOut.write('\n\n' )
        fidOut.write( '/* **************************** */\n' )
        fidOut.write( '/* Module and System Definition */\n' )
        fidOut.write( '/* **************************** */\n' )
        fidOut.write( 'const struct nt_electrode *const nt_tsi_module_electrodes[] = {\n    ' )
        for c1 in range( n1 ):
            fidOut.write( '&%s, '% pinLabels[c1] )
        fidOut.write( 'NULL};\n\n' )

        # 2nd TSI module if used
        if(dualTSI):
            fidOut.write( 'const struct nt_electrode *const nt_tsi_module_electrodes2[] = {\n    ' )
            for c1 in range( n1, nSensors):
                fidOut.write( '&%s, '% pinLabels[c1] )
            fidOut.write( 'NULL};\n\n' )

        fidOut.write( 'const struct nt_electrode *const nt_tsi_module_xtalk_electrodes[] = {\n    ' )
        for c1 in range( nSensors ):
            fidOut.write( '&%s, ' % pinLabels[c1] )
        fidOut.write( 'NULL};\n\n' )

        fidOut.write( 'const struct nt_module nt_tsi_module = {\n' )
        fidOut.write( '    .interface          = &nt_module_tsi_interface,\n' )
        fidOut.write( '    .wtrmark_hi         = 65535,\n' )
        fidOut.write( '    .wtrmark_lo         = 0,\n' )
        fidOut.write( '    .config             = (void *)&tsi_hw_config_%s,\n' % pinLabels[0] )
        fidOut.write( '    .instance           = 0,\n' )
        fidOut.write( '    .electrodes         = &nt_tsi_module_electrodes[0],\n' )
        fidOut.write( '    .safety_interface   = NULL,\n' )
        fidOut.write( '    .safety_params.gpio = (void *)NULL,\n' )
        fidOut.write( '    .recalib_config     = (void *)&recalib_configuration,\n' )
        fidOut.write( '};\n\n' )

        # 2nd TSI module if used
        if(dualTSI):
            fidOut.write( 'const struct nt_module nt_tsi_module2 = {\n' )
            fidOut.write( '    .interface          = &nt_module_tsi_interface,\n' )
            fidOut.write( '    .wtrmark_hi         = 65535,\n' )
            fidOut.write( '    .wtrmark_lo         = 0,\n' )
            fidOut.write( '    .config             = (void *)&tsi_hw_config_%s,\n' % pinLabels[n1] )
            fidOut.write( '    .instance           = 1,\n' )
            fidOut.write( '    .electrodes         = &nt_tsi_module_electrodes2[0],\n' )
            fidOut.write( '    .safety_interface   = NULL,\n' )
            fidOut.write( '    .safety_params.gpio = (void *)NULL,\n' )
            fidOut.write( '    .recalib_config     = (void *)&recalib_configuration,\n' )
            fidOut.write( '};\n\n' )

        fidOut.write( 'const struct nt_control *const System_0_controls[] = {&Keypad_1, NULL};\n' )
        if(dualTSI):
            fidOut.write( 'const struct nt_module *const System_0_modules[]   = {&nt_tsi_module, &nt_tsi_module2, NULL};\n' )
        else:
            fidOut.write( 'const struct nt_module *const System_0_modules[]   = {&nt_tsi_module, NULL};\n' )
        fidOut.write( 'const struct nt_system System_0                    = {\n' )
        #fidOut.write( '    .time_period            = SCANTIME,\n' )
        fidOut.write( '    .time_period            = %d,\n' % json1['scantime'] )
        fidOut.write( '    .init_time              = 1000,\n' )     # Keydetector wil be reset after this time [ms]
        fidOut.write( '    .safety_period_multiple = 0,\n' )
        fidOut.write( '    .safety_crc_hw          = true,\n' )
        fidOut.write( '    .controls               = &System_0_controls[0],\n' )
        fidOut.write( '    .modules                = &System_0_modules[0],\n' )
        fidOut.write( '//    .xtalk_interface        = &nt_system_xtalk_interface,\n' )
        fidOut.write( '//    .xtalk_params           = (void *)&my_xtalk_params,\n' )
        fidOut.write( '//    .xtalk_electrodes       = &nt_tsi_module_xtalk_electrodes[0],\n' )
        fidOut.write( '};\n' )
        fidOut.write( '\n\n' )

        # Enable electrodes
        fidOut.write( 'void nt_enable(void)\n' )
        fidOut.write( '{\n' )
        for c1 in range( nSensors ):
            fidOut.write( '    nt_electrode_enable( &%s, 0 );\n' % pinLabels[c1] )
        fidOut.write( '    nt_control_enable( &Keypad_1 );\n' )
        fidOut.write( '}\n' )


def readJson( fn1, pinChannels ):
    nSensors = len( pinChannels )
    if( fn1 is None ):  # Make default JSON
        json1 = {}
        json1['TSICNT_SHIFT'] = 3
        json1['tau_smooth_signal'] = np.zeros( nSensors )
        json1['min_noise_limit'] = np.ones( nSensors ) * 50
        json1['signal_to_noise_ratio'] = 5
        json1['fs'] = 100
        json1['delta_multiplier'] = np.zeros( nSensors )
        json1['delta_divider'] = np.zeros( nSensors )
        json1['TSICNT_SHIFT'] = 3
    else:
        with open( fn1, 'r' ) as fp:
            json1 = json.load( fp )

    return json1

def main():
    args = parseArguments()
    fn1 = args.inputJsonFile
    fnOut = args.output

    PIN_INPUT_VEC = ['TF_TSI_SELF_CAP_CHANNEL_0', 'TF_TSI_SELF_CAP_CHANNEL_2', 'TF_TSI_SELF_CAP_CHANNEL_4', \
        'TF_TSI_SELF_CAP_CHANNEL_5', 'TF_TSI_SELF_CAP_CHANNEL_13', 'TF_TSI_SELF_CAP_CHANNEL_14', \
        'TF_TSI_SELF_CAP_CHANNEL_19', 'TF_TSI_SELF_CAP_CHANNEL_17', 'TF_TSI_SELF_CAP_CHANNEL_22', \
        'TF_TSI_SELF_CAP_CHANNEL_23', 'TF_TSI_SELF_CAP_CHANNEL_24']
    INPUT_LABELS = ['P2', 'P4', 'P5', 'P6', 'P7', 'P8', 'P9', 'P10', 'P11', 'P12', 'P13']

    # MAIN_CLOCK = 0  # 0U (20.72MHz) 1U (16.65MHz) 2U (13.87MHz) 3U (11.91MHz)
    # CLOCK_DIV = 1   # use powers of 2, between 1 and 128

    # Read JSON file
    json1 = readJson( fn1, PIN_INPUT_VEC )

    # Convert JSON and write output
    json2c( json1, fnOut, PIN_INPUT_VEC, INPUT_LABELS )

if __name__ == '__main__':
    main()


