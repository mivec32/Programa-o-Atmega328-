#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL  // Frequ�ncia do clock interno (8 MHz)

#define cpl_bit(y,bit) (y^=(1<<bit)) //troca o estado l�gico do bit x da vari�vel Y



// Configura��o do TIMER 0


// Interrup��o do TIMER 0
ISR(TIMER0_OVF_vect) { 
cpl_bit(PORTB,PORTB0);  // Alterna o estado do LED 
TCNT0 = 131;   // carrega contador para 1m s
}

int main(void) {
    // Configura o pino PB0 como sa�da
    DDRB =0B00000001;
    // Garante que o LED esteja inicialmente desligado
    PORTB=0B00000000;
    // Configura��o do TIMER 0
    //configura do TIMER 0 com interrup��o de overflow para criar a base de tempo
    TCCR0A = 0x00; // Modo normal
    TCCR0B = 0x03; // Prescaler de 1:64
    TIMSK0 = 0x01; // Habilita interrup��o do timer 0
    TCNT0 = 131; // Inicializa o contador para iniciar em 131, assim teremos 1ms
    //T=(prescaler*(MAX-TCNT0))/Fclock, onde max neste casso 256
    sei(); // Habilita interrup��es globais
    
    

    while (1) {
        // Loop principal vazio, a l�gica est� na interrup��o
    }

    return 0;
}
