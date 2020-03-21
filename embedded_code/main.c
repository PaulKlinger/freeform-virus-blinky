#define F_CPU 1000000

#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>

#include "sequence.h"
#include "sars_cov_2_sequence.h"

#define LIGHT_DURATION_MS 100
#define INTERVAL_DURATION_MS 50

FUSES = 
{
	.APPEND = 0,
	.BODCFG = ACTIVE_DIS_gc | LVL_BODLEVEL0_gc | SAMPFREQ_1KHZ_gc | SLEEP_DIS_gc,
	.BOOTEND = 0,
	.OSCCFG = FREQSEL_16MHZ_gc,
	.SYSCFG0 = CRCSRC_NOCRC_gc | RSTPINCFG_UPDI_gc,
	.SYSCFG1 = SUT_64MS_gc,
	.WDTCFG = PERIOD_OFF_gc | WINDOW_OFF_gc,
}; 



void show_base(Base b) {
    switch (b) {
        case A: // green
            // cast to prevent warning caused by integer promotion to signed...
            VPORTA.OUT = (uint8_t) ~PIN7_bm;
            break;
        case C: // blue
            VPORTB.OUT = (uint8_t) ~PIN1_bm;
            break;
        case G: // yellow
            VPORTB.OUT = (uint8_t) ~PIN2_bm;
            break;
        case T: // red
            VPORTA.OUT = (uint8_t) ~PIN5_bm;
            break;
    }
};

void switch_off_leds() {
    VPORTA.OUT = ~0;
    VPORTB.OUT = ~0;
}


int main(int argc, char** argv) {
    /* Configure clock prescaler for 1MHz  */
    _PROTECTED_WRITE(
            CLKCTRL.MCLKCTRLB,
            CLKCTRL_PDIV_16X_gc /* Prescaler division: 16X */
            | CLKCTRL_PEN_bm /* Prescaler enable: enabled */
            );
    
    /* set LED pins to output */
    VPORTA.DIR = PIN5_bm | PIN7_bm;
    VPORTB.DIR = PIN2_bm | PIN1_bm;
    switch_off_leds();
    
    uint32_t i = 0;
    while (1) {
        show_base(read_base(&sars_cov_2_sequence, i));
        _delay_ms(LIGHT_DURATION_MS);
        switch_off_leds();
        _delay_ms(INTERVAL_DURATION_MS);
        i = (i + 1) % (sars_cov_2_sequence.n_bases);
    }
    
    return (EXIT_SUCCESS);
}

