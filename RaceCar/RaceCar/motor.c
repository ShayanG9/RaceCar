/*
 * motor.c
 *
 * Created: 2022-02-23 14:31:36
 * Author : han_c
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define Power_left PIND5
#define Power_right PIND6
#define Left_motor PIND2
#define Right_motor PIND7
#define Left_motor_back PIND4
#define Right_motor_back PINB0

int main(void)
{
	TCCR0A |= (1<<WGM02) | (1<<WGM01) | (1<<WGM00) | (1<<COM0B1) | (1<<COM0A1);
	TCCR0B |= (1<<CS00);

	DDRD |= (1<< Power_left) | (1 << Power_right);	
	OCR0A = 0x66;
	OCR0B = 0x66;
	PORTD |= (1<<Left_motor) | (1<<Right_motor);
	_delay_ms(3000);
	OCR0A = 0xCC;
	PORTD |= (1<<Left_motor) | (1<<Right_motor);
	_delay_ms(1000);
	OCR0A = 0x33;
	OCR0B = 0x33;
	PORTD |= (1<<Left_motor) | (1<<Right_motor);
	_delay_ms(2000);
	OCR0B = 0xCC;
	PORTD |= (1<<Left_motor) | (1<<Right_motor);
	_delay_ms(1000);
	OCR0A = 0x66;
	OCR0B = 0x66;
	PORTD |= (1<<Left_motor) | (1<<Right_motor);
	


	//PORTD &= ~(1 << Left_motor);
	//_delay_ms(1000);
	//PORTD |= (1 << Left_motor);
    while (1) 
    {
			
    }
}


