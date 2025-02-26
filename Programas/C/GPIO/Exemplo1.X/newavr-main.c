//Pisca led pelo pino 4 da porta D
#include <avr/io.h>
#include <util/delay.h>
void  main(void)
{
    // Configura o pino PD4 como saída
    //DDRD |= (1 << PD4);  // Define o bit 4 da porta D como saída
    DDRD=0B00010000;
    while (1)
    {
        // Acende o LED (coloca o pino PD4 em nível lógico alto)
        //PORTD |= (1 << PD4);  // Define o bit 4 da porta D como 1 (LED aceso)
        PORTD=0B00010000; 
        // Atraso para manter o LED aceso por algum tempo
        _delay_ms(1000);  // Atraso de 1 segundo

        // Apaga o LED (coloca o pino PD4 em nível lógico baixo)
        //PORTD &= ~(1 << PD4);  // Define o bit 4 da porta D como 0 (LED apagado)
        PORTD=0B00000000;
        // Atraso para manter o LED apagado por algum tempo
        _delay_ms(1000);  // Atraso de 1 segundo
    }

    
}
