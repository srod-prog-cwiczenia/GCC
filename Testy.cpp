#include "Testy.h"
#include "ncurses.h"
#include <iostream>
#include <list>
#include <string>
#include <memory>
#include "biblioteczneFunkcje.h"
#include "biblioteczneEkran.h"
#include "menuClass.h"

Testy::Testy()
{
    //ctor
}

Testy::~Testy()
{
    //dtor
}
void Testy::dodajWieleOpcji(int ile, char *p...) {
    OknoAplikacji::powrotDoTrybuTekstowego();  // Powrot do zwyklego trybu 'cooked' :)
    va_list vl;
	va_start(vl, ile);
	for (int liczba = 0; liczba < ile; liczba++) {
		char *lancuch = va_arg(vl, char*);
		cout << (string)lancuch << endl;
	}
	va_end(vl);
    OknoAplikacji::powrotDoNCurses(true);
}

void Testy::probaMenuZWielokrotnymiOpcjami() {
  dodajWieleOpcji(3, "Jeden", "Dwa", "Trzy");
}
