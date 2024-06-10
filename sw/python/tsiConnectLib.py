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

# Library for serial interface to TSI via J-link or UART
# containing separate class defs for jlink and uart with matching methods
#   measureFs( lenSec )
#   record( lenSec )
#   open()
#   close()
#
# $Rev: 31346 $

import time
import datetime
import numpy as np
import matplotlib.pyplot as plt

import sys
import pylink
import serial   # pip install pyserial

class tsiJlink:
    nSensors = 0
    fs = 160    # TODO measure fs

    def __init__( self ):
        # TSI Data
        # Kinetis TSI RAM data table moved to 0x20000000 due compatibility, "tsi_specific_rw" region in KE Linker file
        #ke_data_start = 0x14000000 # Kinetis RAM offset area for the TSI data table
        ke_data_start = 0x20000000 # Kinetis RAM offset area for the TSI data table
        ke_buff_size = 64          # Kinetis data buffer size

        self.trace_type_ad8 = (ke_data_start)
        self.sync_ad8 = (ke_data_start + 1)
        self.nbuttons_ad8 = (ke_data_start + 2)
        self.buffsize_ad8 = (ke_data_start + 3)
        self.raw_signals_ad16 = (ke_data_start + 4)

        flag1 = 0
        t0 = time.time()
        t1 = time.time()
        tTimeOut = 20
        self.jlink = pylink.JLink()
        n1 = len( self.jlink.connected_emulators() )
        while(( t1 - t0 < tTimeOut ) and ( n1 == 0 )):
            try:
                n1 = len( self.jlink.connected_emulators() )
            except:
                pass
            t1 = time.time()

        # Get serial number
        serial_no = self.jlink.connected_emulators()[0].SerialNumber

        # Open a connection
        self.jlink.open(serial_no)
        self.jlink.set_tif(pylink.enums.JLinkInterfaces.SWD)
        #b01800 EMC better connection immunity?
        self.jlink.set_speed(50)
        
        jname = self.jlink.product_name
#        print(jname)

        # Connect to the target device
        conti = 1
        while( conti ):
            try:
                self.jlink.connect('MKE15Z128XXX7', verbose = False)
                conti = 0
            except:
                pass

        if( not self.jlink.target_connected() ):
           print('Kinetis connection failed')

        trace_type = self.jlink.memory_read8(self.trace_type_ad8, 1)

        # Determine number of channels
        nbuttons = self.jlink.memory_read8(self.nbuttons_ad8, 1)
        self.nSensors = nbuttons[0]

        # Measure fs
        self.fs = self.measureFs( 1 )

    def __del__( self ):
        self.jlink.close()

    def open( self ):
        pass

    def close( self ):
        pass

    def measureFs( self, lenSec = 1 ):
        t0 = time.time()
        t1 = time.time()

        # Initialise buffer
        count1 = 0
        while( t1 - t0 < lenSec ):
            sync_flag = self.jlink.memory_read8(self.sync_ad8, 1) #read sync. byte
            if(sync_flag[0] == 1):
                sync_flag[0] = 0
                self.jlink.memory_write8(self.sync_ad8, sync_flag) #clear sync. byte
                count1 = count1 + 1
                t3 = time.time()
            t1 = time.time()

        fs = count1 / ( t3 - t0 )
        return fs

    def record( self, lenSec ):
        t0 = time.time()
        t1 = time.time()

        # Initialise buffer TODO should start from empty buffer
        buffer1 = np.zeros(( 0, self.nSensors ))
        while( t1 - t0 < lenSec ):
            #Add synchronization Handshake here
            sync_flag = self.jlink.memory_read8(self.sync_ad8, 1) #read sync. byte
            if(sync_flag[0] == 1):
                sync_flag[0] = 0
                self.jlink.memory_write8(self.sync_ad8, sync_flag) #clear sync. byte
                raw_signals = self.jlink.memory_read16(self.raw_signals_ad16, self.nSensors)
                buffer1 = np.vstack(( buffer1, np.array( raw_signals )))
            t1 = time.time()

        return buffer1

    def setTraceType( self, traceType ):
        aux1 = self.jlink.memory_read8(self.trace_type_ad8, 1)
        if( aux1[0] != traceType ):
            # print( f'Changing traceType from {aux1[0]} to {traceType}' )
            aux1[0] = traceType
            self.jlink.memory_write8( self.trace_type_ad8, aux1 )



class tsiUart:
    nSensors = 0
    fs = 0
    hSer = 0

    def __init__( self ):
        # Find serial port
        portName = self.findTsiSerialPort()
        if( portName == -1 ):
            print( 'Failed to detect port' )
            sys.exit()
        print( f'Using {portName}' )

        # Open serial port
        self.hSer = serial.Serial( portName )
        self.hSer.baudrate = 115200
        self.hSer.timeout = 1

        # Determine number of channels and sampling rate
        t0 = time.time()
        s1 = self.hSer.read( 1000 )
        s2 = s1.split( b'RAW ' )
        self.nSensors = int(( len( s2[2] ) - 1 ) / 2 )
        # t1 = time.time()
        # self.fs = len( s2 ) / ( t1 - t0 )
        self.fs = self.measureFs( 1 )

        # Close serial port
        self.hSer.close()

    def open( self ):
        self.hSer.open()

    def close( self ):
        self.hSer.close()

    def measureFs( self, lenSec = 1 ):
        x1 = self.record( lenSec )
        count1 = x1.shape[0]

        fs = count1 / lenSec
        return fs


    def record( self, lenSec ): # TODO keep buffer of partial line
        # Open serial port
        if( self.hSer.is_open ):
            flagKeepOpen = 1
        else:
            flagKeepOpen = 0
            self.hSer.open()

        # Loop until time up
        bytes1 = bytearray( [] )
        t0 = time.time()
        t1 = time.time()
        while( t1 - t0 < lenSec ):
            aux1 = bytearray( self.hSer.read( 100 ))
            bytes1.extend( aux1 )
            t1 = time.time()

        # Convert byte array to TSI activation signals
        x1 = self.parseBytes( bytes1 )

        # Close serial port
        if( flagKeepOpen ==  0 ):
            self.close()

        return x1

    # Parse byte stream into TSI activity signal
    def parseBytes( self, bytes1 ):
        # Split on prefix 'RAW '
        s2 = bytes1.split( b'RAW ' )

        # Parse each line
        x1 = np.zeros(( len( s2 ), self.nSensors ))
        c2 = 0
        for b1 in s2:
            # Only retain lines with correct length
            if( len( b1 ) == self.nSensors * 2 + 1 ):
                for c1 in np.arange( 0, self.nSensors ):
                    x1[c2,c1] = int( b1[c1*2] ) + int( b1[c1*2+1] ) * 256
                c2 = c2 + 1
        x1 = x1[0:c2,:]

        return x1


    def findTsiSerialPort( self ):
        """ Find TSI serial port (assuming trace is on)
        """
        if sys.platform.startswith( 'win' ):
            ports = ['COM%s' % (i + 1) for i in range(256)]
        elif sys.platform.startswith( 'linux' ) or sys.platform.startswith( 'cygwin' ):
            # this excludes your current terminal "/dev/tty"
            ports = glob.glob('/dev/tty[A-Za-z]*')
        elif sys.platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError('Unsupported platform')

        portOut = -1
        for port in ports:
            flag1 = 0
            try:
                hS = serial.Serial( port )
                flag1 = 1

            except (OSError, serial.SerialException):
                pass

            # Port exists, check for TSI
            if( flag1 ):
                hS.baudrate = 115200
                hS.timeout = 1  # Long time-out appears to be necessary
                s1 = hS.read( 1000 )
                ind1 = s1.find( b'RAW ' )
                hS.close()
                if( ind1 != -1 ):
                    portOut = port

        return portOut

    def setTraceType( self, traceType ):
        # print( f'Changing traceType to {traceType}' )
        flag1 = self.hSer.is_open
        if( not flag1 ):
            self.hSer.open()
        s1 = self.hSer.write( bytes( str( traceType ), 'ascii' ))
        if( not flag1 ):
            self.hSer.close()
