/* Interrupção externa INT0 pela borda de subida, alterna PB0 a cada interrupção*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


//Definições de macros - empregadas para o trabalho com bits
#define set_bit(Y,bit_x) (Y|=(1<<bit_x)) //ativa o bit x da variável
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) //limpa o bit x da variável
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x)) //troca o estado do bit x


// Rotina de serviço de interrupção (ISR) para INT0
ISR(INT0_vect) { 
    cpl_bit(PORTB,PB0); // Alterna o estado do LED
}

void main(void) {
    // Inicializa portas
    set_bit(DDRB,PB0);  // Configura o pino do LED como saída
    clr_bit(DDRD,PD2);  // Configura o pino PD2 como entrada
    set_bit(PORTD,PD2); // Ativa o pull-up interno no pino PD2 

    // Inicializa o INT0
    EICRA=0B00000011;   // Configura o INT0 para ser acionado por borda de subida
    EIMSK=0B00000001;   // Habilita a interrupção INT0
    sei();              // Habilita interrupções globais
    

    
    while (1) {
        
    }


}