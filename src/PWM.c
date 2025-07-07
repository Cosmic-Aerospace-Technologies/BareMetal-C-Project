#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void PWM_init(void){
    TCCR1A = (1<<COM1A1 ) | (1<<WGM10);
    TCCR1B = (1<<WGM12) | (1<<CS11);

}

void LED_brightness(uint8_t brighness){
    if(brighness == 0){
        TCCR1A &= ~(1 << COM1A1);     // Disconnect OC1A (stop PWM control)
PORTB &= ~(1 << PB1);         // Force pin LOW
    }else{
        TCCR1A |= (1 << COM1A1);      // Re-enable PWM (non-inverting)
    OCR1A = brighness;
    }
    
}