//acende o LED conectado ao pino PD4 (porta D, pino 4)
//quando o pino PB0 (porta B, pino 0) for pressionado e apaga o LED quando o pino PB1 
//(porta B, pino 1) for pressionado:

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000UL  // Frequência do clock interno (8 MHz)
int main(void)
{
    // Configura o pino PD4 como saída (LED)
    DDRD=0B00010000;
    // Configura os pinos PB0 e PB1 como entrada (botões)
    DDRB=0B00000000;
    // Habilita pull-up resistors nos pinos PB0 e PB1
    PORTB=0B00000011;    
   
    while (1)
    {
        // Verifica se o botão PB0 está pressionado (nível baixo)
        if (!(PINB & (1 << PB0)))  // Se PB0 for pressionado (nível baixo)
        {
            // Acende o LED (coloca o pino PD4 em nível lógico alto)
            PORTD=0B00010000;
        }
        // Verifica se o botão PB1 está pressionado (nível baixo)
        else if (!(PINB & (1 << PB1)))  // Se PB1 for pressionado (nível baixo)
        {
            // Apaga o LED (coloca o pino PD4 em nível lógico baixo)
            PORTD=0B00000000;
        }
    }

    return 0;
}
