//contador do timer 0, em modo de contador de pulsos externos pelo pino PD4
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL  //Frequ�ncia do clock interno (8 MHz)

//Defini��es de macros para o trabalho com bits
#define set_bit(y,bit) (y|=(1<<bit))//coloca em 1 o bit x da vari�vel Y
#define clr_bit(y,bit) (y&=~(1<<bit))//coloca em 0 o bit x da vari�vel Y
#define cpl_bit(y,bit) (y^=(1<<bit))//troca o estado l�gico do bit x da vari�vel Y
#define tst_bit(y,bit) (y&(1<<bit))//retorna 0 ou 1 conforme leitura do bit

//Atens�o � interrup��o por desbordamento do Timer 0
ISR(TIMER0_OVF_vect )
{ 
cpl_bit(PORTB,PORTB0);   // Alterna o estado do LED 
TCNT0=246;             // reinicia o contador
}


int main()
{
    
    set_bit(DDRB,DDB0);     // Configura o pino PB0 como sa�da
    clr_bit(PORTB,PORTB0);  // Garante que o LED esteja inicialmente desligado
     
    
    // Configura o Timer 0 para contar pulsos externos na borda de subida
    // T0 � a segunda fun��o do pino PD4, pulso ligado no pino PD4
    TCCR0A = 0x00;          // Modo normal
    TCCR0B =0x07;           // Clock externo na borda de subida
    TCNT0=246;              // Inicia a contagem em 246 para contar 10 pulsos
    set_bit(TIMSK0,TOIE0);  // Habilita a interrup��o do timer 0 por desbordamento do contador
    sei();                  // ativa todas as interrup��es
    
while(1)
    {
    
    }
}
