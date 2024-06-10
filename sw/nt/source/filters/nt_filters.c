/*
 * Copyright 2013 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "../source/electrodes/nt_electrodes_prv.h"
#include "../source/system/nt_system_prv.h"
#include "../source/filters/nt_filters_prv.h"
#include "nt_module_tsi_rat_alpha.h"

/* Extract 16 MSBs from 32bit fractional value. */
static int16_t _nt_get_msb_from_int32(int32_t lsrc);
/* Multiply 16 bit fractional value with 32bit fractional value. */
static int32_t _nt_multiply_int32_int16(int32_t lsrc1, int16_t ssrc1);
/* Multiply two 32bit fractional values. */
static int32_t _nt_multiply_int32(int32_t lsrc1, int32_t lsrc2);
/* Execute IIR filter on the signals */
static int32_t _nt_iir_iterate(int16_t x, int16_t *px, int32_t *py, int32_t p1coef);
/* Calculates coefficient in the runtime. */
static int32_t _nt_filter_fbutt_get_coef(int32_t fsample, int32_t fcutt);

int32_t nt_mult_16z( int32_t x, int32_t y )
{
    return (int32_t)((x * y) >> 15U);
}

/* filters using frac arithmetic */
#define _NT_FRAC32(x) \
    ((int32_t)((x) < 1.0 ? ((x) >= -1.0 ? (x) * ((double)0x80000000U) : ((double)-2147483648)) : ((double)0x7FFFFFFFU)))

static inline int16_t _nt_get_msb_from_int32(int32_t lsrc)
{
    uint32_t temp = ((uint32_t)lsrc >> 16U);
    return (int16_t)temp;
}

static int32_t _nt_multiply_int32_int16(int32_t lsrc1, int16_t ssrc1)
{
    uint64_t temp = ((uint64_t)lsrc1 * (uint64_t)ssrc1) >> 15U;
    return (int32_t)temp;
}

static int32_t _nt_multiply_int32(int32_t lsrc1, int32_t lsrc2)
{
    uint64_t temp = (uint64_t)((uint64_t)lsrc1 * (uint64_t)lsrc2) >> 31U;
    return (int32_t)temp;
}

uint32_t _nt_abs_int32(int32_t lsrc)
{
    if (lsrc < 0)
    {
        lsrc = -lsrc;
    }
    return (uint32_t)lsrc;
}

static int32_t _nt_iir_iterate(int16_t x, int16_t *px, int32_t *py, int32_t p1coef)
{
    int32_t sum_coef = p1coef + p1coef;
    int32_t substr   = sum_coef - 0x7FFFFFFF;
    int32_t satur_x  = _nt_multiply_int32_int16(p1coef, x);
    int32_t multiply = _nt_multiply_int32_int16(p1coef, *px) + satur_x;
    int32_t tmp      = multiply - _nt_multiply_int32(*py, substr);
    *px              = x;
    return *py       = tmp;
}

static int32_t _nt_filter_fbutt_get_coef(int32_t fsample, int32_t fcutt)
{
    int32_t ratio = fsample / fcutt;
    if (ratio < 4)
    {
        ratio = 4;
    }
    /* calculate fbutt coef by approximation equation
       minimum error = 0.03%, average error = 8%) */
    return (int32_t)((0x7fffffff / ratio) * 3);
}

void _nt_filter_fbutt_init(const struct nt_filter_fbutt *rom, struct nt_filter_fbutt_data *ram, uint32_t signal)
{
    ram->x          = (int16_t)signal;
    uint32_t temp   = (uint32_t)signal << 16U;
    ram->y          = (int32_t)temp; /* expands signal to the higher part */
    ram->coeficient = _nt_filter_fbutt_get_coef(1000 / (int32_t)(_nt_system_get()->rom->time_period), rom->cutoff);
}

uint16_t _nt_filter_fbutt_process(struct nt_filter_fbutt_data *ram, uint16_t signal)
{
    /* calculate fbutt coef by approximation function (not accurate!) */
    int32_t process_iir = _nt_iir_iterate((int16_t)signal, &ram->x, &ram->y, ram->coeficient);
    int32_t new_signal  = (int32_t)_nt_get_msb_from_int32(process_iir);
    return (uint16_t)new_signal;
}

uint32_t _nt_filter_iir_process(const struct nt_filter_iir *rom, uint32_t signal, uint32_t previous_signal)
{
    uint32_t coef = (uint32_t)rom->coef1;
    return ((signal + (coef * previous_signal)) / (coef + 1U));
}

int32_t _nt_filter_moving_average_init(const struct nt_filter_moving_average *rom,
                                       struct nt_filter_moving_average_data *ram,
                                       uint16_t value)
{
    if (rom->n2_order > NT_FILTER_MOVING_AVERAGE_MAX_ORDER)
    {
        return -1;
    }
    uint32_t temp = ((uint32_t)value << (uint32_t)rom->n2_order);
    ram->sum      = (int32_t)temp;

    return 0;
}

uint32_t _nt_filter_moving_average_process(const struct nt_filter_moving_average *rom,
                                           struct nt_filter_moving_average_data *ram,
                                           uint16_t value)
{
    uint32_t temp = ((uint32_t)ram->sum >> (uint32_t)rom->n2_order);
    ram->sum -= (int32_t)temp;
    ram->sum += (int32_t)value;
    return (uint32_t)((uint32_t)ram->sum >> (uint32_t)rom->n2_order);
}

uint16_t _nt_filter_abs(int16_t value)
{
    if (value < 0)
    {
        return (uint16_t)(-value);
    }

    return (uint16_t)value;
}

uint16_t _nt_filter_pos(int32_t value)
{
    if (value < (int32_t)0)
    {
        return 0;
    }

    return (uint16_t)value;
}

uint16_t _nt_filter_limit_u(int32_t value, uint16_t limit_l, uint16_t limit_h)
{
    if (value > (int32_t)limit_h)
    {
        return limit_h;
    }
    if (value < (int32_t)limit_l)
    {
        return limit_l;
    }
    return (uint16_t)value;
}

int32_t _nt_filter_range_s(int32_t value, uint32_t limit)
{
    int32_t sl = (int32_t)limit;

    if (value > sl)
    {
        return sl;
    }
    sl *= -1;

    if (value < sl)
    {
        return sl;
    }
    return value;
}

uint16_t _nt_filter_deadrange_u(uint16_t value, uint16_t base, uint16_t range)
{
    if ((bool)_nt_filter_is_deadrange_u(value, base, range))
    {
        if (value > base)
        {
            return _nt_filter_limit_u((int32_t)base + (int32_t)range, 0U, 0xffffU);
        }
        else
        {
            return _nt_filter_limit_u((int32_t)base - (int32_t)range, 0U, 0xffffU);
        }
    }

    return value;
}

uint16_t _nt_filter_deadrange_p(uint16_t value, uint16_t base, uint16_t range)
{
    if (value < (base + range))
    {
        return _nt_filter_limit_u((int32_t)base + (int32_t)range, 0U, 0xffffU);
    }

    return value;
}

int32_t _nt_filter_is_deadrange_u(uint16_t value, uint16_t base, uint16_t range)
{
    if (value < (base + range))
    {
        if (value > (base - range))
        {
            return 1;
        }
    }
    return 0;
}

/* Smoothing operation: y[k+1] = alpha * y[k] + ( 1 - alpha ) * x[k] */
int32_t _nt_smooth_process(const struct nt_filter_smooth *rom, int32_t signal, int32_t previous_signal)
{
    int32_t tmp1 = previous_signal * (int32_t)rom->alpha;
    int32_t tmp2 = rom->alpha1 * (int32_t)signal;
    int32_t Out  = (tmp1 + tmp2) >> 15;
    return (Out);
}

int16_t _nt_smooth_init( int16_t tau, int16_t ts, struct nt_filter_smooth *param)
{
    int16_t rat10;
    int16_t alpha;
    uint16_t c1 = 1;

    /* Compute ratio between tau and sampling period */
    /* factor 10 because that is how they have been stored in the header file */
    rat10 = 10 * tau / ts;

    /* tau_max=rat10_max/10*time_period = 2000/10*time_period = 200 * 1 ms */
    /* alpha = exp( -1 * time_period / tau ) */

    /* First or last elements of lookup table */
    if( rat10 > ratVec[RAT_ALPHA_N-1] )
    {
        alpha = alphaVec[RAT_ALPHA_N-1];
        param->alpha1 = 32768 - alpha;
        param->alpha = alpha;
        return 0;
    }
    if( rat10 <= ratVec[0] )
    {
        alpha = alphaVec[0];
        param->alpha1 = 32768 - alpha;
        param->alpha = alpha;
        return 0;
    }

    /* Lookup table */
    while( rat10 > ratVec[c1] )
    {
        c1++;
    }
    alpha = alphaVec[c1-1];
    param->alpha1 = 32768 - alpha;
    param->alpha = alpha;
    return 0;
}

/* Asymmetrical smoothing operation: y[k+1] = alpha * y[k] + ( 1 - alpha ) * x[k] */
/* with alpha = alpha_up or alpha_down */
int32_t _nt_asym_smooth_process( const struct nt_filter_asym_smooth *rom, int32_t signal,
        int32_t previous_signal )
{
    int32_t alpha;
    int32_t alpha1;

    /* Determine smoothing coefficient */
    if( signal > previous_signal )
    {
        alpha = rom->alpha_up;
        alpha1 = rom->alpha_up1;
    }
    else
    {
        alpha = rom->alpha_down;
        alpha1 = rom->alpha_down1;
    }

    int32_t tmp1 = previous_signal * (int32_t)alpha;
    int32_t tmp2 = alpha1 * (int32_t)signal;
    int32_t Out  = (tmp1 + tmp2) >> 15;
    return (Out);
}

int16_t _nt_asym_smooth_init( int16_t tau_up, int16_t tau_down, int16_t ts, struct nt_filter_asym_smooth *param )
{
    int16_t rat10;
    int16_t alpha;
    uint16_t c1 = 1;

    /* Compute ratio between tau and sampling period */
    /* factor 10 because that is how they have been stored in the header file */
    rat10 = 10 * tau_up / ts;

    /* tau_max=rat10_max/10*time_period = 2000/10*time_period = 200 * 1 ms */
    /* alpha = exp( -1 * time_period / tau ) */

    /* First or last elements of lookup table */
    if( rat10 > ratVec[RAT_ALPHA_N-1] )
    {
        alpha = alphaVec[RAT_ALPHA_N-1];
        param->alpha_up1 = 32768 - alpha;
        param->alpha_up = alpha;
        return 0;
    }
    if( rat10 <= ratVec[0] )
    {
        alpha = alphaVec[0];
        param->alpha_up1 = 32768 - alpha;
        param->alpha_up = alpha;
        return 0;
    }

    /* Lookup table */
    while( rat10 > ratVec[c1] )
    {
        c1++;
    }
    alpha = alphaVec[c1-1];
    param->alpha_up1 = 32768 - alpha;
    param->alpha_up = alpha;


    /* Compute ratio between tau and sampling period */
    /* factor 10 because that is how they have been stored in the header file */
    rat10 = 10 * tau_down / ts;
    c1 = 1;

    /* tau_max=rat10_max/10*time_period = 2000/10*time_period = 200 * 1 ms */
    /* alpha = exp( -1 * time_period / tau ) */

    /* First or last elements of lookup table */
    if( rat10 > ratVec[RAT_ALPHA_N-1] )
    {
        alpha = alphaVec[RAT_ALPHA_N-1];
        param->alpha_down1 = 32768 - alpha;
        param->alpha_down = alpha;
        return 0;
    }
    if( rat10 <= ratVec[0] )
    {
        alpha = alphaVec[0];
        param->alpha_down1 = 32768 - alpha;
        param->alpha_down = alpha;
        return 0;
    }

    /* Lookup table */
    while( rat10 > ratVec[c1] )
    {
        c1++;
    }
    alpha = alphaVec[c1-1];
    param->alpha_down1 = 32768 - alpha;
    param->alpha_down = alpha;



    return 0;
}


