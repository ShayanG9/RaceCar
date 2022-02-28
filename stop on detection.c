/*
 * stop on detection.c
 *
 * Created: 2022-02-25 11:17:09
 * Author : han_c
 */ 
#define BAUD 9600
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

#define Power_left PIND5
#define Power_right PIND6
#define Left_motor PIND2
#define Right_motor PIND7
#define Left_motor_back PIND4
#define Right_motor_back PINB0

static volatile int pulse = 0;
static volatile int i = 0;


int main(void)
{
	TCCR0A |= (1<<WGM02) | (1<<WGM01) | (1<<WGM00) | (1<<COM0B1) | (1<<COM0A1);
	TCCR0B |= (1<<CS00);

	DDRD |= (1<< Power_left) | (1 << Power_right);
	OCR0A = 0x66;
	OCR0B = 0x66;
	PORTD |= (1<<Left_motor) | (1<<Right_motor);
	
	int16_t count = 0;

	DDRC |= 1 << PINC3 | 0 << PINC2;
	
	EICRA |= 1 << ISC00;
	PCMSK1 |= 1 << PCINT10 | 1 << PCINT11;
	PCICR |= 1 << PCIE1;

	sei();
    /* Replace with your application code */
    while (1) 
    {
		PORTC |= 1 << PINC3;
		_delay_ms(15);
		PORTC &= ~(1 << PINC3);
		count = pulse/100;
		_delay_ms(15);
		if(count < 10){
			PORTD &= ~ ((1<<Left_motor) | (1 << Right_motor));
			
		}else{
			PORTD |= ((1<<Left_motor) | (1 << Right_motor));
		}
	}
	return 0;
}

ISR(PCINT1_vect){
	if(i == 0){
		TCCR1B |= 1 << CS11;
		i = 1;
	}else{
		TCCR1B = 0;
		pulse = TCNT1;
		TCNT1 = 0;
		i = 0;
	}
}

