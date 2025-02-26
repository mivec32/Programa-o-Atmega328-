; Programa para o ATmega328
; Acende o led 5 da porta D

.org 0x0000              ; Endere�o inicial do programa
    rjmp RESET           ; Salta para o in�cio do programa

RESET:
    ldi r16, 0b11111111        ; Configura todos os bits da porta D como sa�da
    out DDRD, r16        ; Define DDRD (todos os bits da porta D como sa�da)


    ldi r16, 0B11100000  ; Carrega registrador r16 com os dados
    out PORTD, r16       ; Escreve na pora D, para acender o bit 5
    
MAIN_LOOP:    
    
    rjmp MAIN_LOOP       ; Repete o loop principal

