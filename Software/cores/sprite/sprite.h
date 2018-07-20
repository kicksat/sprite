/**
 * Copyright (c) 2016 Zac Manchester
 * 
 * This file is part of the KickSat project.
 * 
 * Arduino-Sprite is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 * 
 * Arduino-Sprite is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with Arduino-Sprite; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Zac Manchester
 * Creation date: 06/25/2016
 */

#ifndef _SPRITE_H
#define _SPRITE_H

#include "cc430core.h"
#include "cc430rtc.h"
#include "cc430radio.h"
#include "wiring.h"
#include "storage.h"

/**
 * RTC definitions
 */
#define RTC_250MS    0x03   // Timer 2 prescaler = 32
#define RTC_500MS    0x04   // Timer 2 prescaler = 64
#define RTC_1S       0x05   // Timer 2 prescaler = 128
#define RTC_2S       0x06   // Timer 2 prescaler = 256
#define RTC_8S       0x07   // Timer 2 prescaler = 1024

/**
 * Class: SPRITE
 * 
 * Description:
 * panStamp main class
 */
class SPRITE
{
  public:

    /**
     * Radio interface
     */
    CC430RADIO radio;
  
    /**
     * MCU core
     */
    CC430CORE core;

    /**
     * RTC module
     */
    CC430RTC rtc;

    /**
     * PANSTAMP
     *
     * Class constructor
     */
    SPRITE(void);

    /**
     * init
     * 
     * Initialize Sprite board
     */
    void init();

    /**
     * reset
     * 
     * Reset Sprite
     */
    void reset(void);

    /**
     * sleep
     *
     * Enter LPM4
     */
    void sleep(void);

    /**
     * sleepSec
     *
     * put the MCU in sleep mode
     *
     * @param time Sleep time in seconds
     * @param source Source of interruption (RTCSRC_VLO or RTCSRC_XT1)
     */
    void sleepSec(uint16_t time, RTCSRC source=RTCSRC_XT1);
     
    /**
     * getVcc
     *
     * Read MCU's voltage supply
     *
     * @return voltage in mV
     */
     inline uint16_t getVcc(void)
     {
       return core.getVcc();
     }
     
    /**
     * wakeUp
     *
     * Wake from sleep mode
     */
     inline void wakeUp(void)
     {
       core.setNormalMode();
     }

};

/**
 * Global SPRITE object
 */
extern SPRITE Sprite;

#endif

