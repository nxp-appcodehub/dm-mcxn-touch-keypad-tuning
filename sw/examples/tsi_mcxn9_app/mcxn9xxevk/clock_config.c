/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/
/*
 * How to setup clock using clock driver functions:
 *
 * 1. Setup clock sources.
 *
 * 2. Set up wait states of the flash.
 *
 * 3. Set up all dividers.
 *
 * 4. Set up all selectors to provide selected clocks.
 *
 */

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v10.0
processor: MCXN947
package_id: MCXN947VDF
mcu_data: ksdk2_0
processor_version: 0.12.3
board: MCX-N9XX-EVK
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

#include "clock_config.h"
#include "fsl_clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* System clock frequency. */
extern uint32_t SystemCoreClock;

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockPLL150M();
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO12M **********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFRO12M
outputs:
- {id: CLK_144M_clock.outFreq, value: 144 MHz}
- {id: CLK_48M_clock.outFreq, value: 48 MHz}
- {id: FRO_12M_clock.outFreq, value: 12 MHz}
- {id: MAIN_clock.outFreq, value: 12 MHz}
- {id: Slow_clock.outFreq, value: 3 MHz}
- {id: System_clock.outFreq, value: 12 MHz}
- {id: gdet_clock.outFreq, value: 48 MHz}
- {id: trng_clock.outFreq, value: 48 MHz}
settings:
- {id: SCGMode, value: SIRC}
- {id: SCG.SCSSEL.sel, value: SCG.SIRC}
- {id: SCG_FIRCCSR_FIRCEN_CFG, value: Disabled}
- {id: SYSCON.FREQMEREFCLKSEL.sel, value: SYSCON.evtg_out0a}
- {id: SYSCON.FREQMETARGETCLKSEL.sel, value: SYSCON.evtg_out0a}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockFRO12M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFRO12M configuration
 ******************************************************************************/
void BOARD_BootClockFRO12M(void)
{
    /*!< Enable SCG clock */
    CLOCK_EnableClock(kCLOCK_Scg);

    /*!< Set up clock selectors - Attach clocks to the peripheries */
    CLOCK_AttachClk(kFRO12M_to_MAIN_CLK);                 /*!< Switch MAIN_CLK to FRO12M */

    /*!< Set up dividers */
    CLOCK_SetClkDiv(kCLOCK_DivAhbClk, 1U);           /*!< Set AHBCLKDIV divider to value 1 */

    /* Set SystemCoreClock variable */
    SystemCoreClock = BOARD_BOOTCLOCKFRO12M_CORE_CLOCK;
}

/*******************************************************************************
 ******************* Configuration BOARD_BootClockFROHF48M *********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFROHF48M
outputs:
- {id: CLK_144M_clock.outFreq, value: 144 MHz}
- {id: CLK_48M_clock.outFreq, value: 48 MHz}
- {id: FRO_12M_clock.outFreq, value: 12 MHz}
- {id: FRO_HF_clock.outFreq, value: 48 MHz}
- {id: MAIN_clock.outFreq, value: 48 MHz}
- {id: Slow_clock.outFreq, value: 12 MHz}
- {id: System_clock.outFreq, value: 48 MHz}
- {id: gdet_clock.outFreq, value: 48 MHz}
- {id: trng_clock.outFreq, value: 48 MHz}
settings:
- {id: SYSCON.FLEXCAN0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FLEXCAN1CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FREQMEREFCLKSEL.sel, value: SYSCON.evtg_out0a}
- {id: SYSCON.FREQMETARGETCLKSEL.sel, value: SYSCON.evtg_out0a}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockFROHF48M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFROHF48M configuration
 ******************************************************************************/
void BOARD_BootClockFROHF48M(void)
{
    /*!< Enable SCG clock */
    CLOCK_EnableClock(kCLOCK_Scg);

    CLOCK_SetupFROHFClocking(48000000U);                /*!< Enable FRO HF(48MHz) output */

    /*!< Set up clock selectors - Attach clocks to the peripheries */
    CLOCK_AttachClk(kFRO_HF_to_MAIN_CLK);                 /*!< Switch MAIN_CLK to FRO_HF */

    /*!< Set up dividers */
    CLOCK_SetClkDiv(kCLOCK_DivAhbClk, 1U);           /*!< Set AHBCLKDIV divider to value 1 */

    /* Set SystemCoreClock variable */
    SystemCoreClock = BOARD_BOOTCLOCKFROHF48M_CORE_CLOCK;
}

/*******************************************************************************
 ******************* Configuration BOARD_BootClockFROHF144M ********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockFROHF144M
outputs:
- {id: CLK_144M_clock.outFreq, value: 144 MHz}
- {id: CLK_48M_clock.outFreq, value: 48 MHz}
- {id: FRO_12M_clock.outFreq, value: 12 MHz}
- {id: FRO_HF_clock.outFreq, value: 144 MHz}
- {id: MAIN_clock.outFreq, value: 144 MHz}
- {id: Slow_clock.outFreq, value: 18 MHz}
- {id: System_clock.outFreq, value: 72 MHz}
- {id: gdet_clock.outFreq, value: 48 MHz}
- {id: trng_clock.outFreq, value: 48 MHz}
settings:
- {id: SYSCON.AHBCLKDIV.scale, value: '2', locked: true}
- {id: SYSCON.FLEXCAN0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FLEXCAN1CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FREQMEREFCLKSEL.sel, value: SYSCON.evtg_out0a}
- {id: SYSCON.FREQMETARGETCLKSEL.sel, value: SYSCON.evtg_out0a}
sources:
- {id: SCG.FIRC.outFreq, value: 144 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockFROHF144M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockFROHF144M configuration
 ******************************************************************************/
void BOARD_BootClockFROHF144M(void)
{
    /*!< Enable SCG clock */
    CLOCK_EnableClock(kCLOCK_Scg);

    CLOCK_SetupFROHFClocking(144000000U);               /*!< Enable FRO HF(144MHz) output */

    /*!< Set up clock selectors - Attach clocks to the peripheries */
    CLOCK_AttachClk(kFRO_HF_to_MAIN_CLK);                 /*!< Switch MAIN_CLK to FRO_HF */

    /*!< Set up dividers */
    CLOCK_SetClkDiv(kCLOCK_DivAhbClk, 2U);           /*!< Set AHBCLKDIV divider to value 2 */

    /* Set SystemCoreClock variable */
    SystemCoreClock = BOARD_BOOTCLOCKFROHF144M_CORE_CLOCK;
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockPLL150M *********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockPLL150M
called_from_default_init: true
outputs:
- {id: CLK_144M_clock.outFreq, value: 144 MHz}
- {id: CLK_48M_clock.outFreq, value: 48 MHz}
- {id: FRO_12M_clock.outFreq, value: 12 MHz}
- {id: FRO_HF_clock.outFreq, value: 48 MHz}
- {id: MAIN_clock.outFreq, value: 150 MHz}
- {id: PLL0_CLK_clock.outFreq, value: 150 MHz}
- {id: Slow_clock.outFreq, value: 37.5 MHz}
- {id: System_clock.outFreq, value: 150 MHz}
- {id: gdet_clock.outFreq, value: 48 MHz}
- {id: trng_clock.outFreq, value: 48 MHz}
settings:
- {id: PLL0_Mode, value: Normal}
- {id: RunPowerMode, value: OD}
- {id: SCGMode, value: PLL0}
- {id: SCG.PLL0M_MULT.scale, value: '50', locked: true}
- {id: SCG.PLL0SRCSEL.sel, value: SCG.FIRC_48M}
- {id: SCG.PLL0_NDIV.scale, value: '8', locked: true}
- {id: SCG.SCSSEL.sel, value: SCG.PLL0_CLK}
- {id: SYSCON.FLEXCAN0CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FLEXCAN1CLKSEL.sel, value: NO_CLOCK}
- {id: SYSCON.FREQMEREFCLKSEL.sel, value: SYSCON.evtg_out0a}
- {id: SYSCON.FREQMETARGETCLKSEL.sel, value: SYSCON.evtg_out0a}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockPLL150M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockPLL150M configuration
 ******************************************************************************/
void BOARD_BootClockPLL150M(void)
{
    /*!< Enable SCG clock */
    CLOCK_EnableClock(kCLOCK_Scg);

    CLOCK_SetupFROHFClocking(48000000U);                /*!< Enable FRO HF(48MHz) output */

    /*!< Set up PLL0 */
    const pll_setup_t pll0Setup = {
        .pllctrl = SCG_APLLCTRL_SOURCE(1U) | SCG_APLLCTRL_SELI(27U) | SCG_APLLCTRL_SELP(13U),
        .pllndiv = SCG_APLLNDIV_NDIV(8U),
        .pllpdiv = SCG_APLLPDIV_PDIV(1U),
        .pllmdiv = SCG_APLLMDIV_MDIV(50U),
        .pllRate = 150000000U
    };
    CLOCK_SetPLL0Freq(&pll0Setup);                       /*!< Configure PLL0 to the desired values */
    CLOCK_SetPll0MonitorMode(kSCG_Pll0MonitorDisable);    /* Pll0 Monitor is disabled */

    /*!< Set up clock selectors - Attach clocks to the peripheries */
    CLOCK_AttachClk(kPLL0_to_MAIN_CLK);                 /*!< Switch MAIN_CLK to PLL0 */

    /*!< Set up dividers */
    CLOCK_SetClkDiv(kCLOCK_DivAhbClk, 1U);           /*!< Set AHBCLKDIV divider to value 1 */

    /* Set SystemCoreClock variable */
    SystemCoreClock = BOARD_BOOTCLOCKPLL150M_CORE_CLOCK;
}

/*******************************************************************************
 ******************** Configuration BOARD_BootClockPLL100M *********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockPLL100M
outputs:
- {id: CLK_144M_clock.outFreq, value: 144 MHz}
- {id: CLK_48M_clock.outFreq, value: 48 MHz}
- {id: CLK_IN_clock.outFreq, value: 24 MHz}
- {id: FRO_12M_clock.outFreq, value: 12 MHz}
- {id: MAIN_clock.outFreq, value: 100 MHz}
- {id: PLL1_CLK_clock.outFreq, value: 100 MHz}
- {id: Slow_clock.outFreq, value: 25 MHz}
- {id: System_clock.outFreq, value: 100 MHz}
- {id: gdet_clock.outFreq, value: 48 MHz}
- {id: trng_clock.outFreq, value: 48 MHz}
settings:
- {id: PLL1_Mode, value: Normal}
- {id: SCGMode, value: PLL1}
- {id: SCG.PLL1M_MULT.scale, value: '100', locked: true}
- {id: SCG.PLL1_NDIV.scale, value: '6', locked: true}
- {id: SCG.PLL1_PDIV.scale, value: '4', locked: true}
- {id: SCG.SCSSEL.sel, value: SCG.PLL1_CLK}
- {id: SCG_FIRCCSR_FIRCEN_CFG, value: Disabled}
- {id: SCG_SOSCCSR_SOSCEN_CFG, value: Enabled}
- {id: SYSCON.FREQMEREFCLKSEL.sel, value: SYSCON.evtg_out0a}
- {id: SYSCON.FREQMETARGETCLKSEL.sel, value: SYSCON.evtg_out0a}
sources:
- {id: SCG.SOSC.outFreq, value: 24 MHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockPLL100M configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockPLL100M configuration
 ******************************************************************************/
void BOARD_BootClockPLL100M(void)
{
    /*!< Enable SCG clock */
    CLOCK_EnableClock(kCLOCK_Scg);

    CLOCK_SetupExtClocking(24000000U);
    CLOCK_SetSysOscMonitorMode(kSCG_SysOscMonitorDisable);    /* System OSC Clock Monitor is disabled */

    /*!< Set up PLL1 */
    const pll_setup_t pll1Setup = {
        .pllctrl = SCG_SPLLCTRL_SOURCE(0U) | SCG_SPLLCTRL_SELI(53U) | SCG_SPLLCTRL_SELP(26U),
        .pllndiv = SCG_SPLLNDIV_NDIV(6U),
        .pllpdiv = SCG_SPLLPDIV_PDIV(2U),
        .pllmdiv = SCG_SPLLMDIV_MDIV(100U),
        .pllRate = 100000000U
    };
    CLOCK_SetPLL1Freq(&pll1Setup);                       /*!< Configure PLL1 to the desired values */
    CLOCK_SetPll1MonitorMode(kSCG_Pll1MonitorDisable);    /* Pll1 Monitor is disabled */

    /*!< Set up clock selectors - Attach clocks to the peripheries */
    CLOCK_AttachClk(kPLL1_to_MAIN_CLK);                 /*!< Switch MAIN_CLK to PLL1 */

    /*!< Set up dividers */
    CLOCK_SetClkDiv(kCLOCK_DivAhbClk, 1U);           /*!< Set AHBCLKDIV divider to value 1 */

    /* Set SystemCoreClock variable */
    SystemCoreClock = BOARD_BOOTCLOCKPLL100M_CORE_CLOCK;
}

