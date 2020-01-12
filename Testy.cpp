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
  Opis oo("Lorem ipsum dolor sit amet"
    "|consectetur adipiscing elit."
    "|In rhoncus elementum justo nec maximus."
    "|Nam ac blandit purus."
    "|Donec euismod ac nisi eget egestas."
    "|Cras in turpis vestibulum, vestibulum mi sed, viverra arcu."
    "|Duis sollicitudin massa lobortis porta laoreet."
    "|Proin aliquam mollis lacinia."
    "|Aenean tincidunt lacus quam, in porta velit vulputate ac."
    "|Aenean vel nisi sem."
    "|Vestibulum vitae nibh a erat vestibulum sollicitudin at vitae risus."
    "|Etiam ut eleifend ligula, eu congue leo."
    "|Sed eleifend blandit sapien, vel posuere enim."
    "|Donec sagittis ligula ac turpis venenatis blandit."
    "|Pellentesque magna nunc, cursus at dui ac,"
    "|agittis hendrerit erat."
    "|Sed luctus velit quis tempor gravida.");
  //oo.dumpWierszeNaEkran();
  oo.pokaz();
}
