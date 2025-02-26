//* Interrup��o externa INT1 pela borda de decida, alterna PB0 a cada interrup��o
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


//Defini��es de macros - empregadas para o trabalho com bits
#define set_bit(Y,bit_x) (Y|=(1<<bit_x)) //ativa o bit x da vari�vel
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) //limpa o bit x da vari�vel
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x)) //troca o estado do bit x


// Rotina de servi�o de interrup��o (ISR) para INT1
ISR(INT1_vect) { 
    cpl_bit(PORTB,PB0); // Alterna o estado do LED
}

void main(void) {
    // Inicializa portas
    set_bit(DDRB,PB0);  // Configura o pino do LED como sa�da
    clr_bit(DDRD,PD3);  // Configura o pino PD3 como entrada
    set_bit(PORTD,PD3); // Ativa o pull-up interno no pino PD3 

    // Inicializa o INT1
    EICRA=0B00001000;   // Configura o INT1 para ser acionado por borda de decida
    EIMSK=0B00000010;   // Habilita a interrup��o INT1
    sei();              // Habilita interrup��es globais
    

    
    while (1) {
        
    }


}