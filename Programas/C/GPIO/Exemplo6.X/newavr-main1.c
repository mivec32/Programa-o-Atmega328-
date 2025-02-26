#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

// Função para gerar um pulso no pino PB0
void generate_pulse(uint16_t pulse_width)
{
    PORTB |= (1 << PB0);  // Seta PB0 em nível alto
    _delay_us(pulse_width);  // Mantém o pulso pelo tempo especificado
    PORTB &= ~(1 << PB0); // Coloca PB0 em nível baixo
    _delay_ms(20);        // Período total do ciclo (20 ms)
}

int main(void)
{
    // Configurações iniciais
    DDRB |= (1 << PB0);  // Configura PB0 como saída (sinal do servo)
    DDRD &= ~(1 << PD0); // Configura PD0 como entrada (direita)
    DDRD &= ~(1 << PD1); // Configura PD1 como entrada (esquerda)
    PORTD |= (1 << PD0) | (1 << PD1); // Habilita pull-up interno para PD0 e PD1

    uint16_t pulse_width; // Largura do pulso em microssegundos

    while (1)
    {
        if (!(PIND & (1 << PD0))) // Verifica se PD0 está pressionado (direita)
        {
            pulse_width = 1000; // Pulso de 1 ms (posição 0 graus)
        }
        else if (!(PIND & (1 << PD1))) // Verifica se PD1 está pressionado (esquerda)
        {
            pulse_width = 2000; // Pulso de 2 ms (posição 180 graus)
        }
        else
        {
            pulse_width = 1500; // Pulso de 1.5 ms (posição 90 graus - central)
        }

        // Gera o pulso para o servo
        generate_pulse(pulse_width);
    }

    return 0;
}
