/**
 * @file main.c
 * @brief Software DAC example for Attiny 25 / 45 / 85
 * @author SkyWodd
 * @version 1.0
 * @see http://skyduino.wordpress.com/
 *
 * @section intro_sec Introduction
 * This is a example for the ATtiny SoftwareDAC library.\n
 * This version use the two PWM output to display a XY image on the screen of an oscilloscope.\n
 * \n
 * Please report bug to <skywodd at gmail.com>
 *
 * @section licence_sec Licence
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 * \n
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 * \n
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */
 
/* Includes */
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/io.h>
#include "soft_dac.h"

/* Wavetable */
#include "samples.h"

/* Wavetble iterator */
volatile uint16_t counter = 0;

/**
 * Sampling ISR
 */
ISR(TIMER1_COMPA_vect) {

  /* output current sample */
  soft_dac_output_A(pgm_read_byte(samples_x_data + counter));
  soft_dac_output_B(pgm_read_byte(samples_y_data + counter));

  /* Go to next sample */
  if(++counter >= samples_length) counter = 0; 
  
  /* Re-arm sampling timer */
  soft_dac_sampling_reset();
}

/**
 * Programm entry point
 */
int main( void ) {

  /* Initialize pin PB2 (for debug) */
  DDRB |= (1 << PIN2);   // PB2 as output
  PORTB &= ~(1 << PIN2); // PB2 at low state
  
  /* Debug Hello */
  uint8_t i;
  for(i = 0; i < 5; ++i) {
    PORTB ^= (1 << PIN2);
    _delay_ms(100);
  }

  /* Initialize software DAC */
  soft_dac_initialize();
  
  /* Set sampling frequency */
  soft_dac_sampling_frequency(samples_length * 25UL);
  
  /* Start software ADC */
  soft_dac_start();
  
  /* Infinite loop */
  for(;;) {
    // Nothing to do
  }
}