//contador do timer 0, em modo de contador de pulsos externos pelo pino PD4
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL  //Frequência do clock interno (8 MHz)

//Definições de macros para o trabalho com bits
#define set_bit(y,bit) (y|=(1<<bit))//coloca em 1 o bit x da variável Y
#define clr_bit(y,bit) (y&=~(1<<bit))//coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit))//troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) (y&(1<<bit))//retorna 0 ou 1 conforme leitura do bit

//Atensão à interrupção por desbordamento do Timer 0
ISR(TIMER0_OVF_vect )
{ 
cpl_bit(PORTB,PORTB0);   // Alterna o estado do LED 
TCNT0=246;             // reinicia o contador
}


int main()
{
    
    set_bit(DDRB,DDB0);     // Configura o pino PB0 como saída
    clr_bit(PORTB,PORTB0);  // Garante que o LED esteja inicialmente desligado
     
    
    // Configura o Timer 0 para contar pulsos externos na borda de subida
    // T0 é a segunda função do pino PD4, pulso ligado no pino PD4
    TCCR0A = 0x00;          // Modo normal
    TCCR0B =0x07;           // Clock externo na borda de subida
    TCNT0=246;              // Inicia a contagem em 246 para contar 10 pulsos
    set_bit(TIMSK0,TOIE0);  // Habilita a interrupção do timer 0 por desbordamento do contador
    sei();                  // ativa todas as interrupções
    
while(1)
    {
    
    }
}
