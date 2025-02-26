; Programa para o ATmega328
; Soma dois registradores e exibe o resultado na porta D

.include "m328pdef.inc"  ; Inclui defini��es para o ATmega328

.org 0x0000              ; Endere�o inicial do programa
    rjmp RESET           ; Salta para o in�cio do programa

RESET:
    ldi r16, 0xFF        ; Configura todos os bits da porta D como sa�da
    out DDRD, r16        ; Define DDRD (todos os bits da porta D como sa�da)

    ldi r17, 12          ; Carrega o valor 12 no registrador R17
    ldi r18, 36          ; Carrega o valor 36 no registrador R18

    add r17, r18         ; Soma R17 + R18, resultado armazenado em R17
    out PORTD, r17       ; Exibe o resultado na porta D

LOOP:
    rjmp LOOP            ; Loop infinito para manter o programa ativo

