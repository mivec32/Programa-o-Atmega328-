#include <avr/io.h>
#include <util/delay.h>

void motor_step(uint8_t step)
{
    // Define os pinos de controle (PD0 a PD3) de acordo com o passo
    PORTB = (PORTB & 0xF0) | (step & 0x0F);  // Limpa os 4 bits inferiores e escreve o passo
    
}

int main(void)
{
    // Configura os pinos PB0 a PB3 como sa�da para controlar o ULN2003
    DDRB = 0B00001111;
    DDRD = 0B00000000;
    while (1)
    {
        
         // Verifica se o bot�o PB0 est� pressionado (n�vel baixo)
        if (!(PIND & (1 << PD0)))  // Se PB0 for pressionado (n�vel baixo)
        {
                // Gira o motor no sentido horario
        motor_step(0x01);  // Passo 1  0B0000 0001
        _delay_ms(800);    // Atraso para o motor avan�ar
        motor_step(0x02);  // Passo 2  0B 0000 0010
        _delay_ms(800);    // Atraso para o motor avan�ar
        motor_step(0x04);  // Passo 3  0B 0000 0100
        _delay_ms(800);    // Atraso para o motor avan�ar
        motor_step(0x08);  // Passo 4 0B 0000 1000
        _delay_ms(800);    // Atraso para o motor avan�ar
        
        }
        // Verifica se o bot�o PB1 est� pressionado (n�vel baixo)
        else if (!(PIND & (1 << PD1)))  // Se PB1 for pressionado (n�vel baixo)
        {
                  // Gira o motor no sentido antihorario
        motor_step(0x08);  // Passo 1  0B0000 0001
        _delay_ms(800);    // Atraso para o motor avan�ar
        motor_step(0x04);  // Passo 2  0B 0000 0010
        _delay_ms(800);    // Atraso para o motor avan�ar
        motor_step(0x02);  // Passo 3  0B 0000 0100
        _delay_ms(800);    // Atraso para o motor avan�ar
        motor_step(0x01);  // Passo 4 0B 0000 1000
        _delay_ms(800);    // Atraso para o motor avan�ar
        
        }
        
        
        
        
       
    }

    return 0;
}
