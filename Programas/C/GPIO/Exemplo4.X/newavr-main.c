#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Configura o pino PD4 como sa�da
    DDRD |= (1 << PD4);  // Define o bit 4 da porta D como sa�da

    while (1)
    {
        // Acende o LED (coloca o pino PD4 em n�vel l�gico alto)
        PORTD |= (1 << PD4);  // Define o bit 4 da porta D como 1 (LED aceso)
        
        // Atraso para manter o LED aceso por algum tempo
        _delay_ms(1000);  // Atraso de 1 segundo

        // Apaga o LED (coloca o pino PD4 em n�vel l�gico baixo)
        PORTD &= ~(1 << PD4);  // Define o bit 4 da porta D como 0 (LED apagado)
        
        // Atraso para manter o LED apagado por algum tempo
        _delay_ms(1000);  // Atraso de 1 segundo
    }

    return 0;
}
