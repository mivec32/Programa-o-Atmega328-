; Programa para o ATmega328
; Espelha os primeiros 4 bits (PD0-PD3) nos �ltimos 4 bits (PD4-PD7) da porta D

.org 0x0000              ; Endere�o inicial do programa
    rjmp RESET           ; Salta para o in�cio do programa

RESET:
    ldi r16, 0xF0        ; Configura os 4 primeiros bits como entrada
    out DDRD, r16        ; Configura os 4 �ltimos bits como sa�da

MAIN_LOOP:
    in r16, PIND         ; L� os estados dos pinos da porta D
    andi r16, 0x0F       ; Isola os 4 primeiros bits (PD0-PD3)
    swap r16             ; Troca os 4 primeiros bits com os 4 �ltimos
    out PORTD, r16       ; Escreve os valores espelhados nos 4 �ltimos bits (PD4-PD7)
    rjmp MAIN_LOOP       ; Repete o loop principal




