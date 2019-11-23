CC=g++
CFLAGS = # tutaj mozna dodawac flagi kompilatora
LIBS = -lncurses # tutaj mozna dodawać biblioteki

OBJ =\
	glownyPlik.o\
	obslugaEkranu.o\
	zliczanieCzasu.o\
	acsPrzyklad.o\
	przyklady2.o\
	przykladoweKonstrukcjeCPP.o\
	WyswietlanieUptime.o\
	Zegar.o\
	generatorHasla.o\
	teoriaLiczb.o\
	modulULAM.o\
	showTablica.o\
	analizaWsteczna.o\
	analizaWstecznaInterface.o\
	biblioteczneEkran.o\
	biblioteczneFunkcje.o\
	dwa_cztery_siedem.o\
	menuClass.o

all: main

clean:
	rm -f *.o glownyPlik
.c.o:
	$(CC) -c $(INCLUDES) $(CFLAGS) $<

main: $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o glownyPlik
