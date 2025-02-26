#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

// Fun��o para gerar um pulso no pino PB0
void generate_pulse(uint16_t pulse_width)
{
    PORTB |= (1 << PB0);  // Seta PB0 em n�vel alto
    _delay_us(pulse_width);  // Mant�m o pulso pelo tempo especificado
    PORTB &= ~(1 << PB0); // Coloca PB0 em n�vel baixo
    _delay_ms(20);        // Per�odo total do ciclo (20 ms)
}

int main(void)
{
    // Configura��es iniciais
    DDRB |= (1 << PB0);  // Configura PB0 como sa�da (sinal do servo)
    DDRD &= ~(1 << PD0); // Configura PD0 como entrada (direita)
    DDRD &= ~(1 << PD1); // Configura PD1 como entrada (esquerda)
    PORTD |= (1 << PD0) | (1 << PD1); // Habilita pull-up interno para PD0 e PD1

    uint16_t pulse_width; // Largura do pulso em microssegundos

    while (1)
    {
        if (!(PIND & (1 << PD0))) // Verifica se PD0 est� pressionado (direita)
        {
            pulse_width = 1000; // Pulso de 1 ms (posi��o 0 graus)
        }
        else if (!(PIND & (1 << PD1))) // Verifica se PD1 est� pressionado (esquerda)
        {
            pulse_width = 2000; // Pulso de 2 ms (posi��o 180 graus)
        }
        else
        {
            pulse_width = 1500; // Pulso de 1.5 ms (posi��o 90 graus - central)
        }

        // Gera o pulso para o servo
        generate_pulse(pulse_width);
    }

    return 0;
}
