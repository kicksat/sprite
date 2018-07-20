/**
 * Copyright (c) 2014 panStamp <contact@panstamp.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 06/03/2013
 */

#include "sprite.h"

/**
 * SPRITE
 *
 * Class constructor
 */
SPRITE::SPRITE(void)
{
  
}

/**
 * init
 * 
 * Initialize Sprite board
 */
void SPRITE::init() 
{
  // Disable wireless bootloader
  //enableWirelessBoot(false);
    
  // Initialize MCU core
  core.init();

  // Initialize onboard LED pin
  INIT_ONBOARD_LED();

  delayMicroseconds(50);
}

/**
 * sleep
 *
 * Enter LPM4
 */
void SPRITE::sleep(void)
{
  
  // If RTC calendar is running
  if (rtc.calendarIsRunning)
    core.setLowPowerMode();        // Enter LPM3
  else
    core.setLowPowerMode(true);    // Enter LPM4
  
  // Wake-up
  wakeUp();
}

/**
 * sleepSec
 *
 * put the MCU in sleep mode
 *
 * @param time Sleep time in seconds
 * @param source Source of interruption (RTCSRC_VLO or RTCSRC_XT1)
 */
void SPRITE::sleepSec(uint16_t time, RTCSRC source)
{ 
  if (time == 0)
    return;

  core.delayClockCycles(0xFFFF);

  // Sleep
  rtc.sleep(time, source);
}

/**
 * reset
 * 
 * Reset Sprite
 */
void SPRITE::reset(void)
{
  WDTCTL = 0;
  while (1) {}
}
   
/**
 * Pre-instantiate SPRITE object
 */
SPRITE Sprite;

