#include "ncurses.h"
#include <sstream>
#include <list>
#include <stdarg.h>

#include "menuClass.h"
#define ZNAK_ENTER 10
//w ncurses zwykly <Enter> to 10, numeryczny <Enter> to KEY_ENTER
//TODO: mozna ewentualnie dodac warunek jeszcze or na KEY_ENTER
//jako osobna procedure
//--------------------------------
MenuClass::MenuClass() {
  liczbaOpcji = 0;
  nrOpcjiWyjscia = -1;  // Na poczatku nie masz takowej :)
  wersjaMenu = wmStandardowe;
  aktualnaOpcja = 1;
}
//--------------------------------
void MenuClass::ustawienieWersji(WersjaMenu wersja) {
  wersjaMenu = wersja;
}
//--------------------------------
void MenuClass::Opcja(string opcja) {
//  opcja = IntToStr(liczbaOpcji + 1) + opcja;
  ostringstream strumien;
  strumien << (liczbaOpcji + 1);
  string linijka = strumien.str();
  linijka += " ";
  linijka += opcja;

  lista.push_back(linijka);
  liczbaOpcji++;
  //  mvaddstr(liczbaOpcji++ * 2, 0, linijka.c_str());
}
//--------------------------------
void MenuClass::OpcjaWyjscia(string opcja) {
  string linijka = "w";
  linijka += " ";
  linijka += opcja;
  nrOpcjiWyjscia = liczbaOpcji;

  lista.push_back(linijka);
  liczbaOpcji++;
  //  mvaddstr(liczbaOpcji++ * 2, 0, linijka.c_str());
}
//-------------------------------
int MenuClass::getMaxDlugoscOpcji() {
  int odp = -1; // Nie wiem czy tak moze zostac, ale jesli w ogole nie ma opcji to -1

/*  listaLancuchow::iterator it;
  for (it = lista.begin() ; it != lista.end() ; it++) {
    int len = it->length();
    odp = odp > len ? odp : len;
  }*/ // stara wersja petli

  for (auto txt : lista) {
    int len = txt.length();
    odp = odp > len ? odp : len;
  }

  return odp;
}
//--------------------------------
MenuClass::~MenuClass() {

}
//--------------------------------
bool MenuClass::dobryZnak(int znak) {
  if (znak == KEY_UP || znak == KEY_DOWN || znak == ZNAK_ENTER || znak == KEY_ENTER)
    return true;
  int dolnyZnak, gornyZnak;
  dolnyZnak = '1';
  gornyZnak = '1' + liczbaOpcji - 1;
  int znakZablokowany = 0;

  if (nrOpcjiWyjscia >= 0) {
    znakZablokowany = '1' + nrOpcjiWyjscia;
  }

  return (znak >= dolnyZnak && znak <= gornyZnak)
  && (nrOpcjiWyjscia < 0 || znakZablokowany != znak) ||
    (znak == 'w' || znak == 'W') && (nrOpcjiWyjscia >= 0);
}
//--------------------------------
int MenuClass::wybranaOpcja(int znak) {
  if (znak == ZNAK_ENTER || znak == KEY_ENTER) {
    if (nrOpcjiWyjscia < 0 || nrOpcjiWyjscia + 1 != aktualnaOpcja) {
      return aktualnaOpcja - 1;
    } else {
      return - 1;
    }
  }
  int odp = znak - '1';
  if (nrOpcjiWyjscia < 0) {
    return odp;
  } else {
    return (znak == 'w' || znak == 'W') ? - 1 : odp;
  }
}
//--------------------------------
void MenuClass::ramkaWokolMenu() {
  int xcent = getmaxx(stdscr) / 2;
  int ycent = getmaxy(stdscr) / 2;
  int maxDlug = getMaxDlugoscOpcji();

  int y1 = ycent - liczbaOpcji - 1;
  int y2 = ycent + liczbaOpcji - 1;
  int x1 = xcent - (maxDlug / 2) - 1;
  int x2 = xcent - (maxDlug / 2) + maxDlug;

  mvaddch(y1, x1, ACS_ULCORNER);
  mvaddch(y2, x1, ACS_LLCORNER);
  mvaddch(y1, x2, ACS_URCORNER);
  mvaddch(y2, x2, ACS_LRCORNER);

  for (int xx = x1 + 1; xx < x2; xx++) {
    mvaddch(y1, xx, ACS_HLINE);
    mvaddch(y2, xx, ACS_HLINE);
  }

  for (int yy = y1 + 1; yy < y2; yy++) {
    switch (wersjaMenu) {
      case wmStandardowe:
        mvaddch(yy, x1, ACS_VLINE);
        mvaddch(yy, x2, ACS_VLINE);
        break;
      case wmDrabinka:
        mvaddch(yy, x1, (yy - y1) % 2 ? ACS_VLINE : ACS_LTEE);
        mvaddch(yy, x2, (yy - y1) % 2 ? ACS_VLINE : ACS_RTEE);

        if ((yy - y1) % 2 == 0) {
          for (int xxx = x1 + 1; xxx < x2; xxx++) {
            mvaddch(yy, xxx, ACS_HLINE);
          }
        }
        break;
    }
  }
}
//--------------------------------
void MenuClass::wyswietlenie() {
  int xcent = getmaxx(stdscr) / 2;
  int ycent = getmaxy(stdscr) / 2;

//  listaLancuchow::iterator it;
  int nrPom = 0;
  int xx = getMaxDlugoscOpcji();

//  for (it = lista.begin() ; it != lista.end() ; it++) {
  for (auto txt : lista) {
    bool wylaczABold = false;
    if (nrPom + 1 == aktualnaOpcja) {
      attron(A_BOLD);
      wylaczABold = true;
    }
    mvaddstr(nrPom++ * 2 + ycent - liczbaOpcji, xcent - (xx / 2), txt.c_str());
    if (wylaczABold) {
      attroff(A_BOLD);
    }
  }

  ramkaWokolMenu();
}
//--------------------------------
int MenuClass::Run() {
  if (!liczbaOpcji) {
    return -1;
  }
  int znak;
  do {
    wyswietlenie();
    /*TODO: nie robic za kazdym nacisnieciem strzalki
    rysowania na nowo calego menu tylko uaktualnic zmienione dwa wiersze
    (podswietlenia)*/
    while (!dobryZnak(znak = getch())) {};
    if (liczbaOpcji && znak == KEY_DOWN) {
      aktualnaOpcja = (aktualnaOpcja % liczbaOpcji) + 1;
    }
    if (liczbaOpcji && znak == KEY_UP) {
      aktualnaOpcja = ((aktualnaOpcja - 1) % liczbaOpcji);
      if (!aktualnaOpcja)
        aktualnaOpcja = liczbaOpcji;
    }
  } while (znak == KEY_UP || znak == KEY_DOWN);
  return wybranaOpcja(znak);
}
//---------------------------------
void MenuClass::dodajWieleOpcji(int ile, char *p...) {
/*
z jakis niejasnych dla mnie powodow w gcc trzeba pierwsza
opcje w tej metodzie zadac pusta, wiec na przyklad
tak: dodajWieleOpcji(3, "", "pierwsza", "druga", "trzecia");
W przypadku np. vc jest to zbedne (przy tym samym kodzie!)
*/
    va_list vl;
	va_start(vl, ile);
	for (int liczba = 0; liczba < ile; liczba++) {
		char *lancuch = va_arg(vl, char*);
		Opcja((string)lancuch);
	}
	va_end(vl);
}
//---------------------------------
