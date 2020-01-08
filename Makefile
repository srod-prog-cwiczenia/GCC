CC=g++
CFLAGS = # tutaj mozna dodawac flagi kompilatora
LIBS = -lncurses # tutaj mozna dodawać biblioteki
#### trzeba uporzadkowac opcje, bo te powyzej sa specyficzne dla tego
#### pliku a te ponizej stadardowe dla Makefile uzytego dla C++
CXX = g++
CXXFLAGS = -Wall -std=c++17 $(DEBUG)
CPPFLAGS += # pre-processor flags, for include paths etc.

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
	menuClass.o\
	Testy.o\
	Opis.o

all: main

clean:
	rm -f *.o glownyPlik
.c.o:
	$(CC) -std=c++17 -c $(INCLUDES) $(CFLAGS) $<

main: $(OBJ)
	$(CC) -std=c++17 $(OBJ) $(LIBS) -o glownyPlik
