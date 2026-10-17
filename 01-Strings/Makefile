CC = gcc
CFLAGS = -std=c23 -Wall

all: StringTest.exe mayorlongitud.exe todosiguales.exe enlineas.exe longitudes.exe suma.exe

clear:
	rm -f *.exe

test: StringTest.exe
	./StringTest.exe

StringTest.exe: StringTest.c String.c
	$(CC) $(CFLAGS) StringTest.c String.c -o StringTest.exe

mayorlongitud.exe: mayorlongitud.c String.c
	$(CC) $(CFLAGS) mayorlongitud.c String.c -o mayorlongitud.exe

todosiguales.exe: todosiguales.c String.c
	$(CC) $(CFLAGS) todosiguales.c String.c -o todosiguales.exe

enlineas.exe: enlineas.c
	$(CC) $(CFLAGS) enlineas.c -o enlineas.exe

longitudes.exe: longitudes.c String.c
	$(CC) $(CFLAGS) longitudes.c String.c -o longitudes.exe

suma.exe: suma.c String.c
	$(CC) $(CFLAGS) suma.c String.c -o suma.exe
