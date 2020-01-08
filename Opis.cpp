#include "Opis.h"
#include <sstream>
#include "ncurses.h"
#include <iostream>
#include "biblioteczneFunkcje.h"
#include "biblioteczneEkran.h"

Opis::Opis(const string &tresc)
{
    stringstream strumien (tresc);
    string wiersz;

    while (getline (strumien, wiersz, '|')) {
        vWiersze.push_back (wiersz);
    }
}
//------------------------------
Opis::~Opis()
{
    //dtor
}
//------------------------------
void Opis::dumpWektorStringowNaEkran(const vector<string> &vv) {
  OknoAplikacji::powrotDoTrybuTekstowego();  // Powrot do zwyklego trybu 'cooked' :)
  for (auto txt : vv) {
    cout << txt << endl;
  }
  OknoAplikacji::powrotDoNCurses(true);
}
//------------------------------
void Opis::dumpWierszeNaEkran() {
  dumpWektorStringowNaEkran(vWiersze);
}
