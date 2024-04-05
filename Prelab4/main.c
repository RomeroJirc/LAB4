/*
 * Prelab4.c
 *
 * Created: 04/04/2024 04:44:18 p. m.
 * Author : josei
 */ 

//LIBRERIAS
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
//VARIABLES
uint8_t contador = 0 ;

//PROTOTIPOS
void setup(void);


//MAIN
int main(void)
{
    setup(); //MANDAMOS A LLAMAR A SETUP
    
	//LOOP PRINCIPAL
	while (1) 
    {
		PORTD = contador;
    }
}

void setup(void){
	cli();
	
	DDRD = 0xFF; //PONER EL PORTD COMO SALIDAS
	UCSR0B = 0;	//ACTIVAR RX Y TX COMO PINES NORMALES
	PORTD &= ~(1 << PORTD0); //LIMPIAR PORTD0
	
	DDRC  &= ~((1 << DDC1)| (1 << DDC0));	//COMO ENTRADAS 
	PORTC |= (1 << PORTC1 | 1<< PORTC0);	//ACTIVAR PULLUP
	
	PCMSK1 |= (1 << PCINT9)|(1 << PCINT8); //HABILITANDO PCINT EN LOS PINES PCINT9 y PCINT8
	//IMPORTANTE: ESTAMOS EN LA DIRECCION DEL ISR_PCINT1 POR TENER LOS BOTONES EN EL PUERTO C

	PCICR |= (1 << PCIE1);	//HABILITANDO LA ISR PCINT[14:8]
	
	sei();					//HABILITAR INTERRUPCIONES
	
}

ISR (PCINT1_vect){
	
	if (PINC== 0b00000001)		//SI PC0 ESTA EN 1
	{
		contador++;
	}
	else if (PINC== 0b00000010)	//SI PC0 ESTA EN 1
	{
		contador--;
	}
	else
	{
		contador=contador;
	}
}