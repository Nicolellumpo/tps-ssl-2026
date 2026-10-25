CC = gcc
CFLAGS = -std=c23 -Wall -Wextra

.PHONY: all test clean

all: Scanner_test

Scanner_test: Scanner_test.c Scanner.c Scanner.h
	@$(CC) $(CFLAGS) Scanner_test.c Scanner.c -o Scanner_test

# $(1) nombre, $(2) entrada, $(3) salida esperada

define PRUEBA
	@printf '\nTest: $(1)\n'
	@printf -- "$(2)" | ./Scanner_test | tr -d '\r' > salida.tmp
	@printf -- "$(3)" > esperado.tmp
	@diff salida.tmp esperado.tmp && echo OK
endef

test: Scanner_test
	$(call PRUEBA,numero Morse de dos digitos,..---....-\n,NUMERO 24\nFIN_LINEA\nFIN_ENTRADA\n)
	$(call PRUEBA,asignacion,x = .----\n,IDENTIFICADOR x\n'='\nNUMERO 1\nFIN_LINEA\nFIN_ENTRADA\n)
	$(call PRUEBA,operadores y parentesis,+ - * / ^ = ( ),'+'\n'-'\n'*'\n'/'\n'^'\n'='\n'('\n')'\nFIN_ENTRADA\n)
	$(call PRUEBA,cero y numero con cero,----- .....-----,NUMERO 0\nNUMERO 50\nFIN_ENTRADA\n)
	$(call PRUEBA,espacios tabs y retorno de carro,..---\t+\t...--\r\n,NUMERO 2\n'+'\nNUMERO 3\nFIN_LINEA\nFIN_ENTRADA\n)
	$(call PRUEBA,menos pegado a un numero,..----...--,ERROR '..----...--'\nFIN_ENTRADA\n)
	$(call PRUEBA,digito con tres tramos,.-.-.,ERROR '.-.-.'\nFIN_ENTRADA\n)
	$(call PRUEBA,cantidad de simbolos no multiplo de 5,....---..,ERROR '....---..'\nFIN_ENTRADA\n)
	$(call PRUEBA,caracter ajeno,a1 +,IDENTIFICADOR a\nERROR '1'\n'+'\nFIN_ENTRADA\n)
	$(call PRUEBA,sin salto de linea final,..---,NUMERO 2\nFIN_ENTRADA\n)
	$(call PRUEBA,entrada vacia,,FIN_ENTRADA\n)
	@rm -f salida.tmp esperado.tmp

clean:
	@rm -f Scanner_test Scanner_test.exe salida.tmp esperado.tmp
