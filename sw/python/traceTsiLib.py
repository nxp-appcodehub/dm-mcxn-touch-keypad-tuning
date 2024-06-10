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

# Library for serial interface to TSI via USB (serial port)
# h1 = traceTsiLib.tsiTrace( 'uart' );
# h1 = traceTsiLib.tsiTrace( 'jlink' );
# h1.record( lenSec )
# h1.setTraceType( traceType )  # only supported for uart
# h1.showTrace()        # show trace of all electrodes over time
#
# TODO
# h1 = traceTsiLib.serialTrace()
# h1.showActivation()   # show bar plot of activations + max
# traceTsiLib.nstep2cap( nstep1 )   # Convert nstep (not taking into account ctrim)
#
# $Rev: 31505 $

import sys
import glob
import serial   # pip install pyserial
import time

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import CheckButtons
from matplotlib.widgets import RadioButtons

import tsiConnectLib

class tsiTrace:
    cI = 90
    dVolt = 2       # kTSI_DvoltOption (0) 1V, (1) 1.3V, (2) 1.6V, (3) 2V
    vdd3v = 3.3

    s_xin = .125    # kTSI_CurrentMultipleInputValue (0) 1/8, (1) 1/4
    s_xch = .0625   # kTSI_CurrentMultipleChargeValue (0) 1/16, (4) 1/1, (7) 8/1

#    s_ctrim = 0
    s_xdn = .0625   # For simplicity, this should be equal to s_xch

    def __init__( self, connectionType = 'uart' ):

        if( connectionType == 'uart' ):
            self.hLink = tsiConnectLib.tsiUart()

        if( connectionType == 'jlink' ):
            self.hLink = tsiConnectLib.tsiJlink()
        self.protocol = connectionType

        self.fs = self.hLink.fs
        self.nSensors = self.hLink.nSensors

    def close( self ):
        self.hLink.close()

    def setTraceType( self, traceType ):
        self.hLink.setTraceType( traceType )
        self.traceType = traceType

    def getTraceType( self ):
        return self.traceType

    def record( self, lenSec ):
        x1 = self.hLink.record( lenSec )

        return x1

    def cb_subtractBaseline( self, evt1 ):
        self.subtractBaseline = not self.subtractBaseline

    def showTrace( self, lenSec, traceType = 4 ):
        tRefreshSec = .1

        plt.ion()   # plot interactive on
        fig = plt.figure()
        conti = 1
        indBuffer = 0
        lenBuffer = round( self.hLink.fs * lenSec )
        xBuffer = np.zeros(( lenBuffer, self.nSensors ))
        xBuffer[:] = np.NaN
        xBase = np.zeros( self.nSensors )

        # Initialise plot
        xx = np.tile( np.expand_dims( np.arange( lenBuffer ) / self.hLink.fs, axis = 1 ),
                ( 1, self.nSensors ));
        hP = plt.plot( xx, xBuffer )
        plt.grid( visible=True, which='both' )
        hAx = plt.gca()
        hL = plt.plot( np.array( [0, 0] ), hAx.get_ylim() )
        hL[0].set_color( 'k' )
        hP[0].axes.set_xlim( 0, lenSec )

        # Radio buttons to select traceType
        rax = fig.add_axes([0.05, 0.01, 0.15, 0.15] )
        radio = RadioButtons( rax, ['delta', 'signal', 'raw', 'xtalk_red', 'nstep', 'baseline'] )
        self.setTraceType( traceType )
        radio.set_active( traceType )
#        if( traceType == 0 ):
#            radio.set_active( 0 )
#        elif( traceType == 2 ):
#            radio.set_active( 1 )
#        else:
#            radio.set_active( 2 )
#            traceType = 4
        def cb1( label ):
            dat = {'delta': 0, 'signal': 1, 'raw': 2, 'xtalk_red': 3, 'nstep': 4, 'baseline': 5}
            traceType = dat[label]
            if( traceType != self.getTraceType() ):
                xBuffer[:] = np.NaN
                self.setTraceType( traceType )

        radio.on_clicked( cb1 )

        # Open port (so that serial can keep it open)
        self.hLink.open()

        self.subtractBaseline = False

        hAx1 = fig.add_axes( [0.71, 0.01, 0.28, 0.075] )
        # hB1 = Button( hAx1, 'Subtract\nbaseline' )
        hB1 = CheckButtons( hAx1, labels = ['subtract baseline'], actives = [self.subtractBaseline] )
        hB1.on_clicked( self.cb_subtractBaseline )

        subtractBaselinePrev = self.subtractBaseline
        while( conti ):
            # Read segment
            x1 = self.hLink.record( tRefreshSec )

            # Store in circular buffer
            if( x1.shape[0] > 0 ):
                indVec = indBuffer + np.arange( x1.shape[0] )
                ind2 = np.where( indVec >= lenBuffer )
                indVec[ind2] = indVec[ind2] - lenBuffer
                xBuffer[indVec,:] = x1
                indBuffer = indVec[-1]

            if( self.subtractBaseline ):
                if( self.traceType == 4 ):
                    xBase = np.nanmax( xBuffer, axis = 0 )
                else:
                    xBase = np.nanmin( xBuffer, axis = 0 )
            else:
                xBase[:] = 0

            if( self.subtractBaseline != subtractBaselinePrev ):
                subtractBaselinePrev = self.subtractBaseline
                xBuffer[:] = np.NaN
                indBuffer = 0
                continue

            # Update plot
            cm = plt.get_cmap('gist_rainbow')
            c1 = 0
            xPlot = xBuffer - xBase
            for hP1 in hP:
                hP1.set_ydata( xPlot[:,c1] )
                hP[0].set_color('k')
                c1 = c1 + 1
            hP[0].axes.relim()
            hP[0].axes.autoscale_view( True, True, True )
            t1 = indVec[-1] / self.fs
            hL[0].set_xdata( np.array( [t1, t1] ))
            yLim1 = np.floor( np.nanmin( xPlot[:] ) / 10 ) * 10
            yLim2 = np.ceil( np.nanmax( xPlot[:] ) / 10 ) * 10
            hL[0].set_ydata( np.array( [yLim1, yLim2] ))
            hP[0].axes.set_ylim( yLim1, yLim2 )
            fig.canvas.draw()
            fig.canvas.flush_events()

            # Check if figure is still open
            conti = len( plt.get_fignums() ) > 0

            pass

        # Close serial port
        self.hLink.close()

        return xBuffer

    def showActivationTODO( self ):
        tRefreshSec = .1
        tau1 = 2
        alpha1 = np.exp( -1 * tRefreshSec / tau1 )

        plt.ion()   # plot interactive on
        fig = plt.figure()
        conti = 1
        indBuffer = 0
        actVec = np.zeros( self.nSensors )
        actSmoothVec = np.zeros( self.nSensors )

        # Initialise plot
        width1 = .2
        hP = plt.bar( np.arange( self.nSensors ) - width1, actVec, width1 )
        hPSmooth = plt.bar( np.arange( self.nSensors ) + width1, actVec, width1 )
        plt.grid( visible=True, which='both' )

        # Open serial port
        self.hSer.open()

        while( conti ):
            # Accumulate data during tRefreshSec
            t0 = time.time()
            t1 = time.time()
            bytes1 = bytearray( [] )
            while( t1 - t0 < tRefreshSec ):
                aux1 = bytearray( self.hSer.read( 100 ))
                bytes1.extend( aux1 )
                t1 = time.time()

            # Convert bytes to array
            x1 = self.parseBytes( bytes1 )
            actVec = x1[-1,:]

            # Smooth activations
#            actSmoothVec = alpha1 * actSmoothVec + ( 1 - alpha1 ) * actVec
            actSmoothVec = np.maximum( actSmoothVec, actVec )

#            # Store in circular buffer
#            indVec = indBuffer + np.arange( x1.shape[0] )
#            ind2 = np.where( indVec >= lenBuffer )
#            indVec[ind2] = indVec[ind2] - lenBuffer
#            xBuffer[indVec,:] = x1
#            indBuffer = indVec[-1]

            # Update plot
            for hP1, hP2, h1, h2 in zip( hP, hPSmooth, actVec, actSmoothVec ):
                hP1.set_height( h1 )
                hP2.set_height( h2 )
            hP[0].axes.relim()
            hP[0].axes.autoscale_view( True, True, True )
            fig.canvas.draw()
            fig.canvas.flush_events()

            # Check if figure is still open
            conti = len( plt.get_fignums() ) > 0

        # Close serial port
        self.hSer.close()

        print( actSmoothVec )


    def measureFs( self, lenSec = 5 ):
        fs = self.hLink.measureFs( lenSec )

        return fs

    def nstep2cap( self, nstep1 ):
        cap1 = self.cI * self.dVolt / ( self.vdd3v * nstep1 * self.s_xin * self.s_xch )
#            + self.s_ctrim * self.s_xdn / self.s_xch
        return cap1

# def findSerialPort():
#     """ Lists serial port names

#         :raises EnvironmentError:
#             On unsupported or unknown platforms
#         :returns:
#             A list of the serial ports available on the system
#     """
#     if sys.platform.startswith('win'):
#         ports = ['COM%s' % (i + 1) for i in range(256)]
#     elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
#         # this excludes your current terminal "/dev/tty"
#         ports = glob.glob('/dev/tty[A-Za-z]*')
#     elif sys.platform.startswith('darwin'):
#         ports = glob.glob('/dev/tty.*')
#     else:
#         raise EnvironmentError('Unsupported platform')

#     result = []
#     for port in ports:
#         try:
#             s = serial.Serial(port)
#             s.close()
#             result.append(port)
#         except (OSError, serial.SerialException):
#             pass

#     return result


def findTsiSerialPort():
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
