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

# Script to measure sampling rate
#
# $Rev: 31292 $

import traceTsiLib
import argparse

def parseArguments():
    # Read arguments from command line
    parser = argparse.ArgumentParser( description = 'TSI Combi Recording' )
    parser.add_argument( '-l', '--lenSec', help = 'Length for estimation in sec', default = 5, type=float )
    parser.add_argument( '-p', '--protocol', help = 'protocol (jlink or uart)', default = 'jlink' )
    parser.add_argument( '-v', '--verbose', action = 'store_true' )
    args = parser.parse_args()

    return args


def main():
    lenSec = args.lenSec
    prot1 = args.protocol

    h1 = traceTsiLib.tsiTrace( prot1 )

    print( 'Measuring fs' )
    fs = h1.measureFs()

    print( f'fs = {fs} Hz' )
    print( f'time_period = {1000/fs} ms' )


if __name__ == '__main__':
    args = parseArguments()
    main()

