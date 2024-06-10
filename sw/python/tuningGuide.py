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

# Script to perform tuning
# TSI trace should be set to NSTEP
#
#
# $Rev: 31503 $

import traceTsiLib
import numpy as np
# from tabulate import tabulate
import matplotlib.pyplot as plt
import json
import argparse
from os.path import exists
import os
import datetime
import sys
from matplotlib.widgets import Button, Slider, RadioButtons, CheckButtons
import scipy
import config2c
import shutil
import keyboard
import time
import msvcrt

def parseArguments():
    # Read arguments from command line
    parser = argparse.ArgumentParser( description = 'TSI Tuning' )
    parser.add_argument( '-p', '--protocol', help = 'protocol (jlink or uart)', default = 'jlink' )
    parser.add_argument( '-s', '--snrTarget', help = 'target SNR', default = 10 )
    parser.add_argument( '-f', '--filename', help='JSON filename with pin configuration', default = 'pinConfigKE17z512.json' )
    parser.add_argument( '-v', '--verbose', action='store_true' )
    args = parser.parse_args()

    return args

def getSvnRev():
#    svnRev = subprocess.check_output("svnversion -n").decode('utf-8')
#    if( svnRev[-1] == 'M' ):
#        svnRev = svnRev[:-1]
    svnRev = "$Rev: 31503 $".split(" ")[1]
    return svnRev


def nstep2petsn( nstep1, tsiConfig=None ):

    #petsn = ( np.round( np.power( 2, 20 + tsiConfig['TSICNT_SHIFT'] ) / nstep1 ))
    #petsn = np.array(())
    petsn = np.zeros( nstep1.shape )
    
    #b01800 hack for Mutual electrode DO NOT use PETSN
    if( nstep1.ndim == 2 ):
        #petsn = np.array((),())
        for c1 in range (tsiConfig['nSensors']):
            if(tsiConfig['mutual_input'][c1] == 'true'):
                petsn[:,c1] = np.round(nstep1[:,c1])
            else:
                petsn[:,c1] = ( np.round( np.power( 2, 20 + tsiConfig['TSICNT_SHIFT'][c1] ) / (nstep1[:,c1]) ))
    else:
        #petsn = np.array(())
        for c1 in range (tsiConfig['nSensors']):
            if(tsiConfig['mutual_input'][c1] == 'true'):
                petsn[c1] = np.round(nstep1[c1])
            else:
                petsn[c1] = ( np.round( np.power( 2, 20 + tsiConfig['TSICNT_SHIFT'][c1] ) / (nstep1[c1]) ))
            
    mult = np.array( tsiConfig['multiplier'] )
    mult[mult==0] = 1
    div = np.array( tsiConfig['divider'] )
    div[div==0] = 1
    petsn = ( petsn - np.array( tsiConfig['offset'] )) * mult / div
    return petsn

def optimiseDecimation( hTsi, tsiConfig, xBaseline ):
    tRefreshSec = .1
    actTarget = 2000

    # b01800 Estimate Parasitic Capacitance and store Delta NSTEP to JSON file
    nstepVals = np.zeros( hTsi.nSensors )
    tsiConfig['nstepMax'] = nstepVals.tolist()
    parasitic = np.zeros(hTsi.nSensors )
    tsiConfig['Cpar'] = parasitic.tolist()
    tsiConfig['Ctouch'] = 0.2
    tsiConfig['TsiGain'] = 6982

    # Initialisations
    conti = 1
    nstepVec = np.zeros( hTsi.nSensors )
    actMax = np.zeros( hTsi.nSensors )

    # Initialise plot
    plt.ion()   # plot interactive on
    width1 = .2

    def cb_pause( evt1 ):
        if( hB1.color == 'green' ):
            hB1.color = 'blue'
            hB1.hovercolor = 'blue'
        else:
            hB1.color = 'green'
            hB1.hovercolor = 'green'
        fig.canvas.draw()

    # Open serial port
    hTsi.hLink.open()

    # Init
    fig, ax = plt.subplots()
    plt.title( 'First pass to determine NSTEP preprocessing' )
    fig.subplots_adjust( bottom = 0.2 )
    hP = ax.bar( np.arange( hTsi.nSensors ) - width1, nstepVec, width1 )
    hPSmooth = ax.bar( np.arange( hTsi.nSensors ) + width1, nstepVec, width1 )
    ax.grid( visible=True, which='both' )
    plt.xlabel( 'Button index' )
    plt.ylabel( 'delta NSTEP' )

    hAx1 = fig.add_axes( [0.81, 0.05, 0.1, 0.075] )
    hB1 = Button( hAx1, 'Pause' )

    hB1.color = 'green'
    hB1.hovercolor = 'green'
    fig.canvas.draw()
    fig.canvas.flush_events()
    hB1.on_clicked( cb_pause )

    # Record data
    nstepFloor = np.mean( xBaseline, axis = 0 )
    while( conti ):
        # Accumulate data during tRefreshSec
        x1 = hTsi.record( tRefreshSec )

        if( hB1.color == 'green' ):
            nstepVec = x1[-1,:] # Take final measurement (not mean over time)

#b01800 Mutual mode hack
            #actVec = np.maximum( 0, nstepFloor - nstepVec )
            actVec = np.maximum( 0, np.abs(nstepFloor - nstepVec) )
            actMax = np.maximum( actMax, actVec )

            # Update plot
            for hP1, hP2, h1, h2 in zip( hP, hPSmooth, actVec, actMax ):
                hP1.set_height( h1 )
                hP2.set_height( h2 )

            hP[0].axes.relim()
            hP[0].axes.autoscale_view( True, True, True )
        fig.canvas.draw()
        fig.canvas.flush_events()

        # Check if figure is still open
        conti = len( plt.get_fignums() ) > 0

    # Determine decimation
    #targetAct = 20 //b01800
    targetAct = tsiConfig['min_nstep']
    for c1 in range( hTsi.nSensors ):
        #tsiConfig['decimation'][c1] = int( np.amin(( np.ceil( targetAct / actMax[c1] ), tsiConfig['max_decimation'] ))) #b01800 min_decimation hack
        tsiConfig['decimation'][c1] = int( np.amin(( np.ceil( (targetAct / actMax[c1]) * tsiConfig['min_decimation'] ), tsiConfig['max_decimation'] ))) #b01800 min_decimation hack
        tsiConfig['nstepMax'][c1] = np.ceil(actMax[c1])
        CparTmp = (((-1)*tsiConfig['Ctouch']) + np.sqrt((tsiConfig['Ctouch'] * tsiConfig['Ctouch']) + 4 * (tsiConfig['Ctouch'] * tsiConfig['TsiGain'] / actMax[c1])))/2
        tsiConfig['Cpar'][c1] = np.around(CparTmp, 1)

    return tsiConfig

def debounce( x1, debounceBuf ):
    if debounceBuf is None:
        return x1, debounceBuf

    len1 = debounceBuf.shape[0]
    x2 = np.vstack(( debounceBuf, x1 ))
    for c1 in range( x1.shape[0] ):
        x1[c1,:] = np.amin( x2[c1:(c1+len1),:], axis = 0 )
    debounceBuf = x2[-len1:,:]

    return x1, debounceBuf

singleButton = True #Single button mode controlled by CheckBox

def measureActivation( hTsi, tsiConfig, xBaseline, inputLabels ):
    tRefreshSec = float( tsiConfig['scantime'] ) * 10 / 1000    # 10 scans
    actTarget = 2000
    ActThresh = 2.0 # Touch Detection Threshold

    # Initialisations
    conti = 1
    nstepVec = np.zeros( hTsi.nSensors )
    petsnMax = np.zeros( hTsi.nSensors )
    actMat = np.zeros(( hTsi.nSensors, hTsi.nSensors ))
    enableMask = np.zeros( hTsi.nSensors ) #Touch Detection Enable

    # Initialise plot
    plt.ion()   # plot interactive on
    width1 = .2

    def cb_pause( evt1 ):
        if( hB1.color == 'green' ):
            hB1.color = 'blue'
            hB1.hovercolor = 'blue'
        else:
            hB1.color = 'green'
            hB1.hovercolor = 'green'
        fig.canvas.draw()


    # The function to be called anytime a slider's value changes
    def cb_slider_update(val):
        ActThresh = amp_slider.val

    # CheckBox for single button mode
    def cb_single_button( evt1 ):
        global singleButton
        singleButton = not singleButton


    # Open serial port
    hTsi.hLink.open()

            ###############################################
            # Determine PETSN Electrode and Delta Scaling #
            ###############################################
    # Reset normalization
    zz = np.zeros( hTsi.nSensors )
    tsiConfig['multiplier'] = zz
    tsiConfig['divider'] = zz
    tsiConfig['offset'] = zz
    
    #b01800
    tsiConfig['petsnJitter'] = zz
    
    petsn0 = nstep2petsn( xBaseline, tsiConfig = tsiConfig )
    petsnJitter = determineNoiseJitter( petsn0, 10, tsiConfig['fs'] )
    
    #b01800
    tsiConfig['petsnJitter'] = petsnJitter.tolist() #for debug purposes
    
    petsnJitter[petsnJitter<=5] = 5
    gainVec = 1 / ( 2 * petsnJitter )
    petsnMin = np.round( np.mean( petsn0, axis = 0 ))

    plt.ion()
    fig, axx = plt.subplots(2)
    ax = axx[0]
    fig.subplots_adjust( bottom = 0.2 )
    hP = ax.bar( np.arange( hTsi.nSensors ) - width1, nstepVec, width1 )
    hPSmooth = ax.bar( np.arange( hTsi.nSensors ) + width1, nstepVec, width1 )
    hPThres = ax.bar( np.arange( hTsi.nSensors ) + 2*width1, .7 / gainVec, width1 )
    ax.grid( visible=True, which='both' )
    ax.set_title( 'Estimating delta PETSN using averaging' )
    ax.set_xlabel( 'Button label' )
    ax.set_ylabel( 'delta PETSN' )
    try:
        ax.set_xticks( ticks = range( hTsi.nSensors ), labels = inputLabels )
        oi
    except:
        ax.set_xticks( ticks = range( hTsi.nSensors ))
        ax.set_xticklabels( labels = inputLabels )

    hActMat = axx[1].plot( np.arange( hTsi.nSensors ), np.zeros( hTsi.nSensors ))
    axx[1].set_xlabel( 'Button index' )
    axx[1].set_ylabel( 'xtalk delta PETSN' )
    axx[1].grid( visible=True, which='both' )
    try:
        axx[1].set_xticks( ticks = range( hTsi.nSensors ), labels = inputLabels )
    except:
        axx[1].set_xticks( ticks = range( hTsi.nSensors ))
        axx[1].set_xticklabels( labels = inputLabels )

    # Slider for Activity detection on button
    hSld = fig.add_axes( [0.70, 0.05, 0.1, 0.075] )
    amp_slider = Slider(
    ax=hSld,
    label="Thresh",
    valmin=0.8,
    valmax=2.0,
    valinit=ActThresh,
    orientation="vertical"
    )
    amp_slider.on_changed(cb_slider_update)  # register the update function with each slider

    # Radio buttons to select single button
    rax = fig.add_axes([0.92, 0.20, 0.04, (0.8/40)*hTsi.nSensors] )
    #radio = RadioButtons( rax, np.arange(0, hTsi.nSensors, 1 ))
    radio = RadioButtons( rax, inputLabels)
    
    for r in radio.labels: 
        r.set_fontsize(8)
    
    # adjust radius here. The default is 0.05
    for circle in radio.circles:
        #circle.set_radius(0.05)
        circle.width = 0.1
        circle.heigth = 0.1
        
    radio.activecolor = ('red')
    radio.padx = 100
    radio.set_active(0)


    # CheckBox: Single button mode
    hCB = fig.add_axes( [0.92, 0.05, 0.06, 0.075] )
    hCB1 = CheckButtons( hCB, labels = ['Singl'], actives = [singleButton])
    hCB1.on_clicked( cb_single_button )

    # Pause Button
    hAx1 = fig.add_axes( [0.81, 0.05, 0.1, 0.075] )
    hB1 = Button( hAx1, 'Pause' )
    hB1.color = 'green'
    hB1.hovercolor = 'green'
    hB1.on_clicked( cb_pause )

    petsnMax = petsnMin.copy()
    petsnCount = np.zeros( hTsi.nSensors )
    conti = 1
    tau1 = 1    # temporal smoothing
    t0 = time.time()
    dT = 0
    c1 = 1
    alphaUp = np.exp( -1 * .21 / tau1 )
    alphaDown = np.exp( -1 * .21 / tau1 )
    debounce_length = tsiConfig['debounce_length']
    if( debounce_length == 0 ):
        debounceBuf = None
    else:
        debounceBuf = np.ones(( debounce_length, hTsi.nSensors )) * 32768

    while( conti ):
        # Accumulate data during tRefreshSec
        x1 = hTsi.record( tRefreshSec )

        # Measure time and set smoothing
        t1 = time.time()
        dT = dT + t1 - t0
        t0 = t1
        if( c1 <= 20 ):
            alphaUp = np.exp( -1 * dT / c1 / tau1 )
            alphaDown = np.exp( -1 * dT / c1 / ( tau1 / 2 ))
        c1 = c1 + 1

        if( hB1.color == 'green' ):
            petsn1 = nstep2petsn( x1, tsiConfig = tsiConfig )
            petsn2, debounceBuf = debounce( petsn1, debounceBuf )
            petsnVec = np.mean( petsn2, axis = 0 )

            # Smooth activations
            #normActVec = ( petsnVec - petsnMin ) * gainVec
#b01800
            normActVec = np.abs(( petsnVec - petsnMin )) * gainVec
            

            # Single Button mode tuning selected?
            if(singleButton):
                #detect, what index is enabled to be measured
                enableMask[:] = 0
                label = radio.value_selected # Radio Button selects the channel measured
                enabledIdx = inputLabels.index(label) # Radio Button selects the channel measured
                enableMask[enabledIdx] = 1
                ind1 = np.where( enableMask == 0 )
                normActVec[ind1] = -1000

            indMax = np.argmax( normActVec )
            # Slider value controls the Activation threshold
            ActThresh = amp_slider.val
            if( normActVec[indMax] > ActThresh ):
                petsnCount[indMax] = petsnCount[indMax] + 1

                # Update peak and actMat
                if( petsnCount[indMax] == 1 ): # if it is the first one
                    petsnTmp = nstep2petsn( x1[-1,:], tsiConfig = tsiConfig )
                    petsnMax[indMax] = petsnTmp[indMax]
                    actMat[:,indMax] =  petsnTmp
                else:
                    if( petsnVec[indMax] > petsnMax[indMax] ):
                        alpha1 = alphaUp
                    else:
                        alpha1 = alphaDown
                    petsnMax[indMax] = alpha1 * petsnMax[indMax] + ( 1 - alpha1 ) * petsnVec[indMax]
                    actMat[:,indMax] = alpha1 * actMat[:,indMax] + ( 1 - alpha1 ) * petsnVec
                    hActMat[0].set_ydata( actMat[:,indMax] - petsnMin )
                    hActMat[0].axes.relim()
                    hActMat[0].axes.autoscale_view( True, True, True )

                petsnMax = np.round( petsnMax )
                indTouch = indMax
            else:
                indTouch = -1

            actVec = np.maximum( 0, petsnVec - petsnMin )

            # Update plot
            for hP1, hP2, h1, h2 in zip( hP, hPSmooth, actVec, np.maximum( 0, petsnMax - petsnMin )):
                hP1.set_height( h1 )
                hP2.set_height( h2 )
                hP1.set_color( 'blue' )
            if( indTouch != -1 ):
                hP[indTouch].set_color( 'red' )
            hP[0].axes.relim()
            hP[0].axes.autoscale_view( True, True, True )
        fig.canvas.draw()
        fig.canvas.flush_events()

        # Check if figure is still open
        conti = len( plt.get_fignums() ) > 0

    # Close serial port
    hTsi.hLink.close()

#    for c1 in range( hTsi.nSensors ):
#        actMat[:,c1] = np.maximum( 0, actMat[:,c1] )
#        actMat[:,c1] = actMat[:,c1] / ( np.amax( actMat[:,c1] ) + 1e-10 )

    return petsnMin, petsnMax, actMat

def gain2MultDiv( gainFloat, maxIntGain ):
    if( hasattr( gainFloat, 'size' )):
        nSensors = gainFloat.size
    else:
        nSensors = 1
        gainFloat = np.array( [gainFloat] )

    multVec = []
    divVec = []
    for gain1 in gainFloat:
        if( gain1 > 1 ):
            div1 = np.ceil( maxIntGain / 2 / gain1 )
            mult1 = np.maximum( 1, np.round( gain1 * div1 ))
        else:
            mult1 = np.ceil( maxIntGain / 2 * gain1 )
            div1 = np.maximum( 1, np.round( mult1 / gain1 ))
        multVec = np.append( multVec, mult1 )
        divVec = np.append( divVec, div1 )

    return multVec, divVec

def determineNoiseJitter( petsn1, tau1, fs ):
    # Filter
    if( tau1 == 0 ):
        alpha1 = 0
    else:
        alpha1 = np.exp( -1 / fs / tau1 )
    b1 = np.array(( 1-alpha1, ))
    a1 = np.array(( 1, -alpha1 ))
    zi = scipy.signal.lfilter_zi( b1, a1 )
    petsn2 = petsn1
    for c1 in range( petsn1.shape[1] ):
        petsn2[:,c1], _ = scipy.signal.lfilter( b1, a1, petsn1[:,c1], zi = petsn1[0,c1]*zi )

    # Determine min_noise_level (divide by two because of flooring after baseline subtraction
    petsnJitter = np.amax( petsn2, axis = 0 ) - np.amin( petsn2, axis = 0 )

    return petsnJitter


            #######################################
            # Phase 1: Baseline Level Measurement #
            #######################################
def measureBaseline( tsiConfig, h1, lenSec = 2 ):
    # Make recording
    xBaseline = h1.record( lenSec )
    fs = xBaseline.shape[0] / lenSec

    # Compute average nstep
    nstep1 = np.mean( xBaseline, axis = 0 )

    # Compute TSICNT_SHIFT to boost accuracy
    #nstepMin = np.amin( xBaseline )
    nstepMin = np.amin( nstep1 )

    #b01800
    #TSICNT_SHIFT = np.floor( 16 - np.log2( 65536 / nstepMin )) - 4 # There is a fixed shift of 4 in code
    TSICNT_SHIFT = np.floor( 16 - np.log2( 65536 / (nstepMin + 1) )) - 4 # There is a fixed shift of 4 in code
    TSICNT_SHIFT = TSICNT_SHIFT - 2 # 2 bits margin
    TSICNT_SHIFT = min( TSICNT_SHIFT, 11 )

    # Output
    petsn1 = nstep2petsn( nstep1, tsiConfig )
    nSensors = nstep1.size
    aux1 = np.stack(( np.arange( nSensors ), nstep1, petsn1.astype( int )), axis = 1 )

    # Generate JSON
    now = datetime.datetime.now();
    tsiConfig['measurePhase1Date'] = now.strftime( "%m/%d/%Y, %H:%M:%S" )
    tsiConfig['fs'] = fs
    tsiConfig['scantime'] = np.round( 1000 / fs  * ( 1 + float( tsiConfig['time_period_percentual_headroom'] ) / 100 ))
    tsiConfig['nstepBaseline'] = nstep1.tolist()
    #b01800
    #tsiConfig['TSICNT_SHIFT'] = TSICNT_SHIFT
    
    #b01800 hack for Mutual electrode DO NOT use PETSN
    for c1 in range (tsiConfig['nSensors']):
        if(tsiConfig['mutual_input'][c1] == 'true'):
            tsiConfig['TSICNT_SHIFT'][c1] = 0
        else:
            tsiConfig['TSICNT_SHIFT'][c1] = TSICNT_SHIFT
            
    petsn1 = nstep2petsn( np.array( tsiConfig['nstepBaseline']) , tsiConfig=tsiConfig )
    tsiConfig['petsnBaseline'] = petsn1.tolist()

    return tsiConfig, xBaseline

            #########################################
            # Phase 2: Activation Level Measurement #
            #########################################
def tuningPhase2( tsiConfig, h1, xBaseline, inputLabels ):
    petsnMin, petsnMax, actMat = measureActivation( h1, tsiConfig, xBaseline, inputLabels )

    # Determine electrode normalisation offset
    offsetVec = np.round( np.array( petsnMin ) * .7 )

    # Electrode normalisation
    deltaVec = petsnMax - np.array( petsnMin )
    deltaTarget1 = np.amax( deltaVec )
    gainVec1 = np.maximum( 1, deltaTarget1 / ( deltaVec + 1e-10 ) ) # Gain to align deltas to max delta

    # Peak activation should be at intTarget
    intTarget = 32768;
    #intTarget = 10000;
    gainLim = intTarget / np.amax( gainVec1 * ( petsnMax - offsetVec ) + 1e-10 )
    gainVec2 = gainVec1 * gainLim
    deltaTarget1 = deltaTarget1 * gainLim
    #deltaTarget1 = min( deltaTarget1, 1000 ) #b01800 limitation

    # Convert to multiplier and divider
    maxIntGain = 128
    multVec, divVec = gain2MultDiv( gainVec2, maxIntGain )

    # Equalise delta (using delta_normalization)
    if("delta_target" in  tsiConfig ):
        deltaTarget = tsiConfig['delta_target']
    else:
        deltaTarget = deltaTarget1 #b01800
        
    thres1 = np.round( deltaTarget * .8 )
    #gainVec3 = np.ones( gainVec2.shape ) * deltaTarget / deltaTarget1
    gainVec3 = deltaTarget / ( gainVec2 * deltaVec + 1e-10 ) #b01800
    deltaMultVec, deltaDivVec = gain2MultDiv( gainVec3, maxIntGain )
    petsnBaseline = np.round(( petsnMin - offsetVec )* multVec / ( divVec + 1e-10 ))

    # Apply normalisation to actMat
    actMat0 = actMat;   # Without electrode and delta normalisation
    for c1 in range( h1.nSensors ):
        # Electrode normalization
        actMat[:,c1] = ( actMat[:,c1] - offsetVec ) * multVec / divVec - petsnBaseline
        actMat[:,c1] = np.maximum( 0, actMat[:,c1] )

        # Delta scaling
        actMat[:,c1] = actMat[:,c1] * deltaMultVec[c1] / deltaDivVec

        actMat[:,c1] = np.round( actMat[:,c1] * 32767 / ( np.amax( actMat[:,c1] ) + 1e-10 ))

    # Generate JSON
    tsiConfig['petsnMin'] = petsnMin.tolist()
    tsiConfig['petsnMax'] = petsnMax.tolist()
    tsiConfig['multiplier'] = multVec.tolist()
    tsiConfig['divider'] = divVec.tolist()
    tsiConfig['offset'] = offsetVec.tolist()
    tsiConfig['delta_multiplier'] = deltaMultVec.tolist()
    tsiConfig['delta_divider'] = deltaDivVec.tolist()
    tsiConfig['deltaTarget'] = deltaTarget
    tsiConfig['actMat'] = actMat.tolist()
    tsiConfig['actMat0'] = actMat0.tolist()
    tsiConfig['petsnBaseline'] = petsnBaseline.tolist()

    # Generate JSON
    tsiConfig['threshold'] = thres1

    return tsiConfig

            ###################################
            # Phase 3: Smoothing Optimisation #
            ###################################
def tuningPhase3( tsiConfig, h1, xBaseline, snrTarget ):
    plt.ioff()
    fig = plt.figure()

    # Convert NSTEP to PETSN
    petsn1 = nstep2petsn( xBaseline, tsiConfig = tsiConfig )

    # Sweep tau
    tauVec = np.arange( 0, .1, .001 )
    traceN = np.array(())
    traceS = np.array(())
    traceN = np.zeros(( 0, h1.nSensors ))
    for tau1 in tauVec:
        petsnJitter = determineNoiseJitter( petsn1, tau1, tsiConfig['fs'] )
        petsnJitter[petsnJitter<=5] = 5
        traceN = np.vstack(( traceN, petsnJitter ))
    snr1 = tsiConfig['deltaTarget'] / ( traceN )
    
    #b01800 Debug
    tsiConfig['petsnJitter'] = petsnJitter.tolist() #debug purposes

    # Proposed smoothing to reach desired SNR
    aux1 = ( snr1 < snrTarget )
    ind1 = sum( aux1.astype( int )) - 1 #correct index
    #ind1 = sum( aux1.astype( int )) #correct index
    ind1[ind1 < 0] = 0
    
    tauOpt = tauVec[ind1] * 1000
    min_noise_limit = np.zeros( h1.nSensors )
    for c1 in range( h1.nSensors ):
        min_noise_limit[c1] = traceN[ind1[c1],c1]

    # Detection threshold at delta_threshold (ratio)
    target = float( tsiConfig['delta_threshold'] ) * float( tsiConfig['deltaTarget'] )
    snrVec = np.floor( target / min_noise_limit )
    min_noise_limit = target / snrVec

    # Proposed smoothing to reach 5% jitter
    aux2 = ( traceN > target * .05 )
    ind2 = sum( aux2.astype( int )) - 1 #correct index
    ind2[ind2 < 0] = 0
    tauOpt2 = tauVec[ind2] * 1000

    # Take highest tauOpt (meeting SNR and jitter criterion)
    tauOpt = np.maximum( tauOpt, tauOpt2 )

    tau_smooth_signal = np.round( tauOpt ).astype( 'int' )
    min_noise_limit = np.ceil( min_noise_limit ).astype( 'int' )
    snrTarget = int( snrTarget )
    snrVec = np.round( target / min_noise_limit )

    # Plot
    plt.subplot( 2,1,1 )
    plt.plot( tauVec * 1000, traceN )
    plt.grid()
    plt.ylabel( 'min_noise_limit' )
    yMax = np.amax( traceN )
    if( np.isnan( yMax )):
        yMax = 1
    plt.axis( [tauVec[0]*1000, tauVec[-1]*1000, 0, yMax] )
    plt.plot(( tauOpt, tauOpt ), ( 0, yMax ), linestyle = 'dashed', color = 'k' )

    plt.subplot( 2,1,2 )
    plt.plot( tauVec * 1000, snr1 )
    plt.grid()
    snrMax = np.max( snr1 )
    yMax = np.amin(( np.amax( snr1[0] ) * 4, snrMax ))
    if( np.isnan( yMax )):
        yMax = 1
    plt.axis( [tauVec[0]*1000, tauVec[-1]*1000, 0, yMax] )
    plt.xlabel( 'tau_smooth_signal [ms]' )
    plt.ylabel( 'SNR' )
    plt.plot(( tauOpt, tauOpt ), ( 0, yMax ), linestyle = 'dashed', color = 'k' )

    plt.show()

    # Generate JSON
    now = datetime.datetime.now();
    tsiConfig['measurePhase3Date'] = now.strftime( "%m/%d/%Y, %H:%M:%S" )
    tsiConfig['tau_smooth_signal'] = tau_smooth_signal.tolist()
    tsiConfig['min_noise_limit'] = min_noise_limit.tolist()
#    tsiConfig['signal_to_noise_ratio'] = int( np.round( 0.8 * snrTarget ))
    tsiConfig['signal_to_noise_ratio'] = snrVec.tolist()

    return tsiConfig

def writeJson( tsiConfig, fn1 ):
    # Write JSON
    with open( fn1, 'w' ) as fp:
        json.dump( tsiConfig, fp, indent = 4 )
    print( f'\tResults written to {fn1}' )


def readJson( fn1 ):
    # Read JSON file (this allows to skip phases if desired, to be implemented)
    if( exists( fn1 )):
        with open( fn1, 'r' ) as fp:
            # Load existing file
            if( args.verbose ):
                print( f'\tReading file: {fn1}' )
            try:
                str1 = json.load( fp )
            except:
                print( f'Error opening {fn1}' )
                sys.exit()

    return str1

def copySetup( tsiConfig, pinInputs, inputLabels, fn1, outputName, waitForEnter = True ):
    config2c.json2c( tsiConfig, fn1, pinInputs, inputLabels )
    print( f'\t- Written {fn1}' )
    if( outputName is not None ):
        shutil.copyfile( fn1, outputName )
        if( waitForEnter ):
            print( '\t- nt_setup.c has been copied.  Please make and run TSI application' )
    else:
        print( f'Copy {fn1} to TSI directory, and make and run TSI application' )
    print( '\t* Press enter when TSI is running' )
    keyboard.wait( '\n' )
    flushStdin()


def resetPhase1( tsiConfig, pinConfig ):
    zz = np.zeros( tsiConfig['nSensors'] )
    zz = zz.astype( int ).tolist()
    oo = np.ones( tsiConfig['nSensors'] )
    oo = oo.astype( int ).tolist()
    oo50 = np.ones( tsiConfig['nSensors'] )
    oo50 = oo50.astype( int ).tolist()
    pinInputs = pinConfig['pin_input']
    inputLabels = pinConfig['input_label']
    #b01800
    #tsiConfig['decimation'] = oo
    tsiConfig['decimation'] = tsiConfig['min_decimation']
    
    return tsiConfig

def resetPhase2( tsiConfig , pinConfig):
    zz = np.zeros( tsiConfig['nSensors'] )
    zz = zz.astype( int ).tolist()
    oo = np.ones( tsiConfig['nSensors'] )
    oo = oo.astype( int ).tolist()
    oo50 = np.ones( tsiConfig['nSensors'] )
    oo50 = oo50.astype( int ).tolist()
    pinInputs = pinConfig['pin_input']
    inputLabels = pinConfig['input_label']

    tsiConfig = resetPhase1( tsiConfig, pinConfig )

    tsiConfig['petsnMin'] = zz
    tsiConfig['petsnMax'] = zz
    tsiConfig['multiplier'] = zz
    tsiConfig['divider'] = zz
    tsiConfig['offset'] = zz
    tsiConfig['delta_multiplier'] = zz
    tsiConfig['delta_divider'] = zz
    tsiConfig.pop( 'actMat' )
    tsiConfig.pop( 'actMat0' )

    tsiConfig['tau_smooth_signal'] = zz
    tsiConfig['min_noise_limit'] = oo50
    tsiConfig['signal_to_noise_ratio'] = oo

    return tsiConfig

def generateRootSetup( pinInputs, inputLabels, enableShield, n1, dvoltOption, minDecimation ):
    nSensors = len( pinInputs )

    zz = np.zeros( nSensors )
    zz = zz.astype( int ).tolist()
    oo = np.ones( nSensors )
    oo = oo.astype( int ).tolist()
    oo50 = np.ones( nSensors )
    oo50 = oo50.astype( int ).tolist()
    

    tsiConfig = {}
    tsiConfig['name'] = 'Ruby'
    tsiConfig['nSensors'] = nSensors
    
    #b01800
    #tsiConfig['TSICNT_SHIFT'] = 3
    tsiConfig['TSICNT_SHIFT'] = zz
    tsiConfig['decimation'] = oo
    tsiConfig['tau_smooth_signal'] = zz
    tsiConfig['min_noise_limit'] = oo50
    tsiConfig['signal_to_noise_ratio'] = oo
    tsiConfig['fs'] = 200
    tsiConfig['scantime'] = np.round( 1000 / float( tsiConfig['fs'] ))
    tsiConfig['multiplier'] = zz
    tsiConfig['divider'] = zz
    tsiConfig['offset'] = zz
    tsiConfig['delta_multiplier'] = zz
    tsiConfig['delta_divider'] = zz
    #tsiConfig['TSICNT_SHIFT'] = 3
    tsiConfig['enable_shield'] = enableShield
    tsiConfig['n1'] = n1            # number of 1st TSI module, in case of 2nd TSI exists
    tsiConfig['dvolt_option'] = dvoltOption
    
    # Select shift 3 at the beginning
    for c1 in range(nSensors):
        tsiConfig['TSICNT_SHIFT'][c1] = 3
        
    #Apply minDecimation at the beginning
    #b01800
    for c1 in range(nSensors):
        tsiConfig['decimation'][c1] = minDecimation
        tsiConfig['min_decimation'] = minDecimation

    # Clock
    t1 = input( '\t* Specify desired switching clock (< 3.8 MHz for PRBS), max. 2.0 MHz for Active Shield: ' )
    fSw = float( t1 )

    clockVec = np.array( [20.72, 16.65, 13.87, 11.91] ) # Possible main clocks
    if( fSw > 3.8 ):
        # Do not use PRBS
        if( fSw > 3.8 ):
            # clock div 1
            #indF = np.argmin( abs( clockVec - fSw ))
            indF = np.argmin(abs(( clockVec / 4 ) - fSw))

            tsiConfig['mainClockSel'] = int( indF )
            tsiConfig['prescaler'] = 4
        if(fSw > 6.0):
            # clock div 2
            indF = np.argmin( abs( (clockVec / 2) - fSw ))
            tsiConfig['mainClockSel'] = int( indF )
            tsiConfig['prescaler'] = 2

        tsiConfig['prbsT1'] = 0
        tsiConfig['prbsT2'] = 0
        tsiConfig['prbsT3'] = 0
        tsiConfig['fSw'] = fSw

        print( 'PRBS disabled, TSI clock too high \n')
    else:
        # Use PRBS
        # fSw = fMainClock / (t1 + t2 + t3 )
        t1 = 1
        if(fSw > 2.0):
            t3 = 3
        else:
            t3 = 5
        t2Vec = [100, 100]

        prescaler = 0
        while( all( x >= 15.5 for x in t2Vec )):
            prescaler = prescaler + 1

            # t2-values for possible main clocks
            t2Vec = 2 * clockVec / prescaler / fSw - 2 * t1 - 2 * t3 - 1

            # set those out of bounds to 0.5 (unlikely to be picked)
            t2Vec[np.round(t2Vec)<2] = 0.5

            # Find t2-value that is nearest to an integer
            indF = np.argmin( abs( t2Vec - np.round( t2Vec )))
            t2 = np.round( t2Vec[indF] )

        clockDiv = ( t1 + ( t2 + 1 ) / 2 + t3 )
        print( f'\t- Expected clock freq: {clockVec[indF] / prescaler / clockDiv} MHz' )

        tsiConfig['mainClockSel'] = int( indF )
        tsiConfig['prescaler'] = prescaler
        tsiConfig['prbsT1'] = t1
        tsiConfig['prbsT2'] = int( np.round( t2Vec[indF] ))
        tsiConfig['prbsT3'] = t3
        tsiConfig['fSw'] = fSw

    return tsiConfig

def flushStdin():
    time.sleep( .1 )
    while msvcrt.kbhit():
        msvcrt.getch()

def showMenu( tsiConfig ):
    if( tsiConfig is None ):
        nn = -1
    else:
        nn = tsiConfig['tuning_phase']
    menuItems = ['Generate root setup', 'Phase 1', 'Phase 2 and 3']
    c1 = 0
    print( '\n' )
    for menu1 in menuItems:
        if( c1 <= nn + 1 ):
            print( f' {c1}. {menu1}' )
        else:
            print( f' -. {menu1}' )
        c1 = c1 + 1
    print( '\nl. Load tsiConfig' )
    print( 's. Save tsiConfig' )
    print( 'g. Generate nt_setup.c' )
#    print( 't. Trace delta' )
    print( 'q. Quit' )

def main():
    prot1 = args.protocol
    snrTarget = float( args.snrTarget )
    fn0 = args.filename
    fn1 = 'tuning_output.json'

    svnRev = getSvnRev()

    # Read tsiConfig for pin configuration
    pinConfig = readJson( fn0 )
    pinInputs = pinConfig['pin_input']
    inputLabels = pinConfig['input_label']
    # for KE17, dual TSI
    if( 'pin_input2' in pinConfig ):
        n1 = len(  pinInputs )
        pinInputs2 = pinConfig['pin_input2']
        inputLabels2 = pinConfig['input_label2']
        pinInputs += pinInputs2
        inputLabels +=inputLabels2
    else:
        n1 = len(  pinInputs ) #store number of inputs of 1st TSI module
            
    if( 'dvolt_option' in pinConfig ):
        dvoltOption = pinConfig['dvolt_option']
    else:
        dvoltOption = 3
    
#    if( 'mutual_input' in pinConfig ):
#        mutualInput = pinConfig['mutual_input']
        
    enableShield = pinConfig['shield_cfg']
    delta_threshold = pinConfig['delta_threshold']
    
    #b01800
    if('min_decimation' in pinConfig):
        #tsiConfig['min_decimation'] = pinConfig['min_decimation']
        minDecimation = pinConfig['min_decimation']
    else:
        #tsiConfig['min_decimation'] = 1
        minDecimation = 1
    
    # Check availability of prior tuning
    tsiConfig = None
    print( '\n' )
    if os.path.exists( fn1 ):
        print( f'Reading {fn1}' )
        tsiConfig = readJson( fn1 )
        try:
            tsiConfig['tuning_phase']
            tsiConfig['delta_threshold']
            tsiConfig['debounce_length']
        except:
            print( 'Outdated "tuning_ouput.json", please remove file' )
            quit()
        print( f"Assuming TSI is flashed with results from tuning phase {tsiConfig['tuning_phase']} and running" )
        print( 'If not, press g to generate nt_setup.c, and flash TSI' )

    # Main menu
    conti = 1
    while( conti ):
        showMenu( tsiConfig )
        while( True ):
            if( keyboard.is_pressed( '0' )):
                print( '\n\t\t\t** Generating root setup' )
                flushStdin()

                # Generate initial nt_setup.c and store info in tsiConfig                
                tsiConfig = generateRootSetup( pinInputs, inputLabels, enableShield, n1, dvoltOption, minDecimation )
                tsiConfig['rev'] = svnRev
                tsiConfig['time_period_percentual_headroom'] = pinConfig['time_period_percentual_headroom']
                tsiConfig['tuning_phase'] = 0
                tsiConfig['max_decimation'] = pinConfig['max_decimation']
                tsiConfig['delta_threshold'] = pinConfig['delta_threshold']
                tsiConfig['debounce_length'] = pinConfig['debounce_length']
                if('mutual_input' in pinConfig):
                    tsiConfig['mutual_input'] = pinConfig['mutual_input']
                if('adjacent_electrodes' in pinConfig):                    
                    tsiConfig['adjacent_electrodes'] = pinConfig['adjacent_electrodes']
                #b01800 Shield MUX masks KE512
                if( 'shield_mask' in pinConfig ):
                    tsiConfig['shield_mask']  = pinConfig['shield_mask']
                if('delta_target' in pinConfig):
                    tsiConfig['delta_target'] = pinConfig['delta_target']
                if('gpio_input' in pinConfig):
                    tsiConfig['gpio_input'] = pinConfig['gpio_input']
                
                # Convert JSON and write output
                copySetup( tsiConfig, pinInputs, inputLabels, 'nt_setup_tuning0.c', pinConfig['output_name'] )

                break

            elif( keyboard.is_pressed( '1' )):
                print( '\n\t\t\t** Phase 1' )
                flushStdin()

                # Check previous tuning
                if( tsiConfig['tuning_phase'] >= 1 ):
                    print( 'Resetting tsiConfig' )
                    tsiConfig = resetPhase1( tsiConfig, pinConfig )
                    copySetup( tsiConfig, pinInputs, inputLabels, 'nt_setup_tuning_tmp.c', pinConfig['output_name'] )

                # Instantiate module
                h1 = traceTsiLib.tsiTrace( prot1 )
                h1.setTraceType( 4 )    # Set traceType to 4 to log NSTEP

                # Phase 1 pre: Fast baseline Level Measurement
                tsiConfig, xBaseline0 = measureBaseline( tsiConfig, h1, .5 )
                print( f"\t- scantime = {tsiConfig['scantime']}ms" )
                tsiConfig['fs'] = 200 # Set to fast to allow for measurement
                tsiConfig['scantime'] = np.round( 1000 / float( tsiConfig['fs'] ))

                #b01800 NSTEP measurement
                tsiConfig['min_nstep'] = pinConfig['min_nstep']        # Minimal desired NSTEP value of the button, used by Decimation
                # Optimise decimation
                print( '\t- Optimising Decimation - Please touch each electrode and close figure' )
                tsiConfig = optimiseDecimation( h1, tsiConfig, xBaseline0 )

                # Convert JSON and write output
                copySetup( tsiConfig, pinInputs, inputLabels, 'nt_setup_tuning1.c', pinConfig['output_name'] )

                # Phase 1 (decimation included)
                tsiConfig, xBaseline = measureBaseline( tsiConfig, h1 )
                tsiConfig['tuning_phase'] = 1
                print( f"\t- scantime (inc decimation and headroom) = {tsiConfig['scantime']}ms" )

                h1.close()
                del h1
                break

            elif( keyboard.is_pressed( '2' )):
                print( '\n\t\t\t** Phase 2' )
                flushStdin()

                # Check previous tuning
                if( tsiConfig['tuning_phase'] >= 2 ):
                    print( 'Resetting tsiConfig' )
                    tsiConfig = resetPhase2( tsiConfig, pinConfig )
                    copySetup( tsiConfig, pinInputs, inputLabels, 'nt_setup_tuning_tmp.c', pinConfig['output_name'] )

                # Re-instantiate module
                h1 = traceTsiLib.tsiTrace( prot1 )
                h1.setTraceType( 4 )    # Set traceType to 4 to log NSTEP2

#                try: # Use previous recording if available
#                    xBaseline
#                except NameError:
                print( '\t- Recording baseline' )
                xBaseline = h1.record( 2 )

                # Phase 2: Activation Level Measurement
                print( '\t- Recording PETSN activation levels (for delta equalisation and threshold) -- Please touch each electrode and close figure' )
                tsiConfig = tuningPhase2( tsiConfig, h1, xBaseline, inputLabels )

                # Phase 3: Smoothing Optimisation
                print( '\n\t\t\t** Phase 3' )
                print( '\t- Optimising smoothing' )

                print( '\t- Please close figure' )
                tsiConfig = tuningPhase3( tsiConfig, h1, xBaseline, snrTarget )

                # Write output
                tsiConfig['tuning_phase'] = 2
                writeJson( tsiConfig, fn1 )
                copySetup( tsiConfig, pinInputs, inputLabels, 'nt_setup_tuning2.c', pinConfig['output_name'] )

                h1.close()
                del h1
                break

            elif( keyboard.is_pressed( 'l' )):
                print( f'\n\t\t\t** Load tsiConfig from {fn1}' )
                flushStdin()
                tsiConfig = readJson( fn1 )
                break

            elif( keyboard.is_pressed( 's' )):
                print( f'\n\t\t\t** Save tsiConfig to {fn1}' )
                flushStdin()
                writeJson( tsiConfig, fn1 )
                break

            elif( keyboard.is_pressed( 'g' )):
                print( f'\n\t\t\t** Generating nt_setup.c from current tsiConfig' )
                copySetup( tsiConfig, pinInputs, inputLabels, 'nt_setup_tuning_new.c', pinConfig['output_name'] )

            elif( keyboard.is_pressed( 't' )):
                print( f'\n\t\t\t** Starting delta trace' )
                print( '\tClose figure to stop trace' )
                flushStdin()

                # Re-instantiate module
                h1 = traceTsiLib.tsiTrace( prot1 )
                traceType = 0
                h1.showTrace( 20, traceType )

                h1.close()
                del h1
                break

            elif( keyboard.is_pressed( 'q' )):
                flushStdin()
                conti = 0
                break
            time.sleep( .1 )



if __name__ == '__main__':
    args = parseArguments()
    main()


