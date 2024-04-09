/*
 * Prelab4.c
 *
 * Created: 8/04/2024 06:39:20
 * Author : Eber Alexander
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

uint8_t counter = 0;

//void initADC(void);
void initPCINT0(void);

int main(void)
{
	cli();
	DDRC |= (1 << PINC1) | (1 << PINC2) | (1 << PINC3);
	PORTC = 0;
	PORTC |= (1 << PORTC1);
	
	DDRD = 0xFF;
	PORTD = 0;
	UCSR0B = 0;
	
	PORTB |= (1 << PINB2) | (1 << PINB3);		//pins as ouput w pull up
	DDRB &= ~(1 << PINB2) | ~(1 << PINB3);		//inputs
	
	
	
	//initADC();
	initPCINT0();
	sei();

	//infinite loop
    while (1) 
    {
		//ADCSRA |= (1 << ADSC);
		//_delay_ms(100);
		PORTD = counter;
    }
}
/*
void initADC(void){
	ADMUX = 0;
	//Vref = AVcc = 5Vs
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);
	
	ADMUX |= (1 << ADLAR);	//left adjust
	
	ADCSRA = 0;
	ADCSRA |= (1 << ADEN);	//turn on ADC
	ADCSRA |= (1 << ADIE);	//interruption
	
	//prescaler 128 > 125kHz
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	DIDR0 |= (1 << ADC0D);	//disable PC0 digital input 
}

ISR (ADC_vect){
	PORTD = ADCH;			//show in portd value of adc
	ADCSRA |= (1 << ADIF);	//turn off flag
}
*/
void initPCINT0(void){
	PCICR |= (1 << PCIE0);			//pin change
	PCMSK0 |= (1 << PCINT2) | (1 << PCINT3);	//mask
}

ISR (PCINT0_vect){
	//uint8_t puerto = 0;
	//puerto = PORTB;
	if (!(PINB & (1 << PINB2))) {
		counter++;
	}else if (!(PINB & (1 << PINB3))) {
		counter--;
	}
}