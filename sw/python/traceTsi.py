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

# Real-time TSI trace
#
# $Rev: 31299 $

import traceTsiLib
import argparse
import numpy as np

def parseArguments():
    # Read arguments from command line
    parser = argparse.ArgumentParser( description = 'TSI Combi Recording' )
    parser.add_argument( '-l', '--lenSec', help = 'Buffer length in sec', default = 10, type=float )
    parser.add_argument( '-f', '--filename', help = 'Output file' )
    parser.add_argument( '-p', '--protocol', help = 'protocol (jlink or uart)', default = 'jlink' )
    parser.add_argument( '-t', '--traceType', help = '0-delta, 1-signal, 2-raw, 3-xtalk_removed, 4-nstep, 5-baseline', default = 4 )
    parser.add_argument( '-v', '--verbose', action = 'store_true' )
    args = parser.parse_args()

    return args


def main():
    fn1 = args.filename
    traceType = int( args.traceType )

    lenBufferSec = args.lenSec
    prot1 = args.protocol

    h1 = traceTsiLib.tsiTrace( prot1 )

    h1.setTraceType( traceType )

    print( 'Please close figure to stop trace' )
    xBuffer = h1.showTrace( lenBufferSec, traceType )

    if( fn1 is not None ):
        np.savetxt( fn1, xBuffer, delimiter=', ', fmt='%.0f' )
        print( f'Trace has been saved to: {fn1}' )


if __name__ == '__main__':
    args = parseArguments()
    main()