CC = gcc
CFLAGS = -std=c23 -Wall

PROGS = SumarBytes SumarInts SumarInt_Ns SumarDecimalesScanf SumarDecimalesGetNextDecimal SumarX

all: $(PROGS)

SumarBytes: SumarBytes.c
	$(CC) $(CFLAGS) SumarBytes.c -o SumarBytes

SumarInts: SumarInts.c
	$(CC) $(CFLAGS) SumarInts.c -o SumarInts

SumarInt_Ns: SumarInt_Ns.c
	$(CC) $(CFLAGS) SumarInt_Ns.c -o SumarInt_Ns

SumarDecimalesScanf: SumarDecimalesScanf.c
	$(CC) $(CFLAGS) SumarDecimalesScanf.c -o SumarDecimalesScanf

SumarDecimalesGetNextDecimal: SumarDecimalesGetNextDecimal.c
	$(CC) $(CFLAGS) SumarDecimalesGetNextDecimal.c -o SumarDecimalesGetNextDecimal

SumarX: SumarX.c
	$(CC) $(CFLAGS) SumarX.c -o SumarX

#ESTRUCTURA DE LOS TEST
#@programa | tr -d '\r' | diff - <(printf "salida_esperada") && echo "OK: mensaje" || (echo "FALLO" && exit 1)
#programa — el ejecutable a testear, al que se le pasa entrada via pipe (|).
#tr -d '\r' — elimina los caracteres \r que Windows agrega al final de cada línea, para que la comparación sea correcta.
#diff - <(printf "salida_esperada") — compara la salida del programa contra la salida esperada. El - indica que diff lea de stdin y <(printf "...") genera la salida esperada.
#&& echo "OK: mensaje" — si diff no encontró diferencias (retorna 0), imprime el mensaje de éxito.
#|| (echo "FALLO" && exit 1) — si diff encontró diferencias (retorna distinto de 0), imprime el mensaje de fallo y termina el make con código de error.
test: all
	@echo ""
	@echo "Tests: SumarBytes"
	@printf "A" | ./SumarBytes | tr -d '\r' | diff - <(printf "65\n") && echo "OK: Lectura de un byte" || (echo "FALLO: Lectura de un byte" && exit 1)
	@printf "AB" | ./SumarBytes | tr -d '\r' | diff - <(printf "65\n131\n") && echo "OK: Suma de bytes" || (echo "FALLO: Suma de bytes" && exit 1)

	@echo ""
	@echo "Tests: SumarInts"
	@printf "\x01\x00\x00\x00" | ./SumarInts | tr -d '\r' | diff - <(printf "1\n") && echo "OK: Lectura de un int" || (echo "FALLO: Lectura de un int" && exit 1)
	@printf "\x01\x00\x00\x00\x02\x00\x00\x00" | ./SumarInts | tr -d '\r' | diff - <(printf "1\n3\n") && echo "OK: Suma de ints" || (echo "FALLO: Suma de ints" && exit 1)

	@echo ""
	@echo "Tests: SumarInt_Ns"
	@printf "\x01\x00\x00\x00\x00\x00\x00\x00" | ./SumarInt_Ns | tr -d '\r' | diff - <(printf "1\n") && echo "OK: Lectura de un int64_t" || (echo "FALLO: Lectura de un int64_t" && exit 1)
	@printf "\x01\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00" | ./SumarInt_Ns | tr -d '\r' | diff - <(printf "1\n3\n") && echo "OK: Suma de int64_ts" || (echo "FALLO: Suma de int64_ts" && exit 1)

	@echo ""
	@echo "Tests: SumarDecimalesScanf"
	@echo "10" | ./SumarDecimalesScanf | tr -d '\r' | diff - <(printf "10\n") && echo "OK: Lectura de decimal" || (echo "FALLO: Lectura de decimal" && exit 1)
	@echo "10 20 30" | ./SumarDecimalesScanf | tr -d '\r' | diff - <(printf "10\n30\n60\n") && echo "OK: Suma de decimales" || (echo "FALLO: Suma de decimales" && exit 1)

	@echo ""
	@echo "Tests: SumarDecimalesGetNextDecimal"
	@printf "10\n" | ./SumarDecimalesGetNextDecimal | tr -d '\r' | diff - <(printf "10\n") && echo "OK: Lectura de decimal" || (echo "FALLO: Lectura de decimal" && exit 1)
	@printf "10\n+20\n-30\n" | ./SumarDecimalesGetNextDecimal | tr -d '\r' | diff - <(printf "10\n30\n0\n") && echo "OK: Suma de decimales" || (echo "FALLO: Suma de decimales" && exit 1)
	@printf "1'000\n2'000\n" | ./SumarDecimalesGetNextDecimal | tr -d '\r' | diff - <(printf "1000\n3000\n") && echo "OK: Suma de decimales con separador de miles" || (echo "FALLO: Suma de decimales con separador de miles" && exit 1)

	@echo ""
	@echo "Tests: SumarX (Morse)"
	@printf ".----\n" | ./SumarX | tr -d '\r' | diff - <(printf "1\n") && echo "OK: Lectura de un digito" || (echo "FALLO: Lectura de un digito" && exit 1)
	@printf ".----..---\n" | ./SumarX | tr -d '\r' | diff - <(printf "12\n") && echo "OK: Lectura de numero con mas de un digito" || (echo "FALLO: Lectura de numero con mas de un digito" && exit 1)
	@printf "..... .----\n" | ./SumarX | tr -d '\r' | diff - <(printf "5\n6\n") && echo "OK: Suma de dos numeros separados por espacio" || (echo "FALLO: Suma de dos numeros separados por espacio" && exit 1)
	@printf ".----\n..---\n" | ./SumarX | tr -d '\r' | diff - <(printf "1\n3\n") && echo "OK: Suma de numeros separados por salto de linea" || (echo "FALLO: Suma de numeros separados por salto de linea" && exit 1)
	@printf ".---- ..--- ...--\n" | ./SumarX | tr -d '\r' | diff - <(printf "1\n3\n6\n") && echo "OK: Suma de numeros en una linea" || (echo "FALLO: Suma de numeros en una linea" && exit 1)

	@echo ""
	@echo "Tests OK"

clean:
	rm -f $(PROGS)
