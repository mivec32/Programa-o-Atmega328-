//mostra o numero 5 no display de 7 segmentos de catodo comum
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Configura os pinos PB0 a PB6 como sa�da para controlar os segmentos
    DDRB= 0B11111111;
   
    uint8_t number_5 = 0b1101101; // Representa��o bin�ria do n�mero "5"

    while (1)
    {
        // Exibe o n�mero "5" no display de 7 segmentos
        PORTB = number_5;  // Envia o padr�o para os pinos da porta B
        
        // Atraso para manter o n�mero "5" vis�vel por algum tempo
       // _delay_ms(1000);  // Atraso de 1 segundo (opcional, pode ser ajustado)
    }

    return 0;
}
