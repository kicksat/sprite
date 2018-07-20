/*
 *  cpu430_cs.h - msp430x2 cpu using CS clock implementation (msp430fr57xxx)
 *
 * Created: Dec 12, 2012
 *  Author: rick@kimballsoftware.com
 *    Date: 03-02-2013
 * Version: 1.0.2
 *
 * =========================================================================
 *  Copyright © 2013 Rick Kimball
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CPU430_UCS_RF_H
#define CPU430_UCS_RF_H

#ifdef __MSP430_HAS_UCS_RF__

#include "cpu.h"
#include "pmm.h"

template <unsigned long FREQ=F_CPU>
struct cpu430_cs_t
    : cpu_base_t<F_CPU> {
	static const unsigned long MCLK_FREQ=FREQ;

	static void init_clock(void) {
#if 0
#elif F_CPU == 8000000L
    /**
     * Pin mapping
     */
    PMAPPWD = 0x02D52;            // Get write-access to port mapping regs
    PMAPCTL |= PMAPRECFG;         // Leave Pin mapping open
#ifdef SHOW_CLOCKS
    P2MAP2 = PM_SMCLK;            // Map SMCLK output to P2.2
    P2MAP4 = PM_MCLK;             // Map MCLK output to P2.4
    P2MAP5 = PM_ACLK;             // Map SMCLK output to P2.5
#endif
    PMAPPWD = 0;                  // Lock port mapping registers

#ifdef SHOW_CLOCKS
    P2DIR |= BIT5 | BIT2 | BIT4;  // ACLK, MCLK, SMCLK set out to pins
    P2SEL |= BIT5 | BIT2 | BIT4;  // P2.5, P2.2, P2.4 for debugging
#endif

    // Configure PMM
    SetVCore(1);

    // Set the High-Power Mode Request Enable bit so LPM3 can be entered
    // with active radio enabled
    PMMCTL0_H = 0xA5;
    PMMCTL0_L |= PMMHPMRE_L;
    PMMCTL0_H = 0x00;

    /*
     * Select internal RC oscillator as FLL reference
     */
    UCSCTL3 |= SELREF_2;        // Set DCO FLL reference = REFO
    UCSCTL4 |= SELA_2; 		// Set ACLK = REFO

    /**
     * Configure CPU clock for 8MHz
     */
    _BIS_SR(SCG0);              // Disable the FLL control loop
    UCSCTL0 = 0x0000;// Set lowest possible DCOx, MODx
    UCSCTL1 = DCORSEL_5;// Select suitable range
    UCSCTL2 = FLLD_1 + 0xF4;// Set DCO Multiplier
    _BIC_SR(SCG0);// Enable the FLL control loop

    // Worst-case settling time for the DCO when the DCO range bits have been
    // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
    // UG for optimization.
    // 32 x 32 x 8 MHz / 32,768 Hz = 250000 = MCLK cycles for DCO to settle
    __delay_cycles(250000);

    /*
     * Select Interrupt edge for PA_PD and SYNC signal:
     * Interrupt Edge select register: 1 == Interrupt on High to Low transition.
     */
    RF1AIES = BIT0 | BIT9;

#else
 #warning F_CPU is not a know frequency value, expecting your code to set clock
#endif
  }

	static void enable_clkout(void) {
	}
};

typedef cpu430_cs_t<F_CPU> CPU;

#endif /* __MSP430_HAS_UCS_RF__ */
#endif /* CPU430_UCS_RF_H */
