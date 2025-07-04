#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_init(void){

ADMUX = (1<<REFS0); //Reference to 5volts, ADC to channel 0
ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1);

}

uint16_t ADC_read(uint8_t channel){
    ADMUX = (ADMUX & 0b11110000) | (channel & 0b00001111);
    ADCSRA |= (1<<ADSC);
    while(ADCSRA & (1<<ADSC));
    return ADC;
}
