#include "Testy.h"
#include "ncurses.h"
#include <iostream>
#include <list>
#include <string>
#include <memory>
#include "biblioteczneFunkcje.h"
#include "biblioteczneEkran.h"
#include "menuClass.h"
#include "Opis.h"

Testy::Testy()
{
    //ctor
}

Testy::~Testy()
{
    //dtor
}
void Testy::dodajWieleOpcji(int ile, char *p...) {
    va_list vl;
	va_start(vl, ile);
	for (int liczba = 0; liczba < ile; liczba++) {
		char *lancuch = va_arg(vl, char*);
		cout << (string)lancuch << endl;
	}
	va_end(vl);
}
//--------------------------
void Testy::dodajWieleOpcji2(int ile, char *p...) {
  dodajWieleOpcji(ile, "", p);
}
//--------------------------
void Testy::probaMenuZWielokrotnymiOpcjami() {
  OknoAplikacji::powrotDoTrybuTekstowego();  // Powrot do zwyklego trybu 'cooked' :)
  dodajWieleOpcji(3, "", "Jeden", "Dwa", "Trzy");
  dodajWieleOpcji2(3, "Jeden", "Dwa", "Trzy"); //to nie dziala poprawnie jak przypuszczalnie powinno
  OknoAplikacji::powrotDoNCurses(true);
}
//--------------------------
void Testy::opcjaTestowa() {
  Opis oo("uno|dos|tres");
  oo.dumpWierszeNaEkran();
}
