#include "Opis.h"
#include <sstream>
#include "ncurses.h"
#include <iostream>
#include "biblioteczneFunkcje.h"
#include "biblioteczneEkran.h"

Opis::Opis(const string &tresc)
{
// przyjazny split lancucha na czesci:
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
void Opis::pokaz() {
  erase();
  int xcent = getmaxx(stdscr) / 2;
  int ycent = getmaxy(stdscr) / 2;
  int rozmiar = -1;
  for (auto txt : vWiersze) {
    if (rozmiar < (int)txt.length())
/*
TODO: ciekawe zjawisko - rzutowanie (int) jest nieodzowne
bo inaczej nie dziala prawidlowo porownanie i -1 wcale nie
jest < od dlugosci lancucha (typu size_t).
*/
      rozmiar = txt.length();
  }
  if (rozmiar == -1) {
    return; //brak tresci
  }
  int nrY1 = - vWiersze.size() / 2;
  int lewyGornyRogY = nrY1 + ycent;
  int lewyGornyRogX = xcent - (rozmiar / 2);
  for (auto txt : vWiersze) {
  mvaddstr(nrY1++ + ycent, lewyGornyRogX, txt.c_str());
  }
  OknoAplikacji::ramka(lewyGornyRogX - 1, lewyGornyRogY - 1,
    lewyGornyRogX + rozmiar, lewyGornyRogY + vWiersze.size());
  char znak;
  do {
    znak = getch();
  } while (znak != 'q');
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
//------------------------------
