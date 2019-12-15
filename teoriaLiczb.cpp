/*
  Modul szuka liczb pierwszych Wilsona i liczb Wiefericha
*/

#include <ncurses.h>
#include <string>
#include "menuClass.h"
#include "teoriaLiczb.h"
#include "dwa_cztery_siedem.h"

using namespace std;

void liczbyWilsona() {
  long int x, p, n, baza;
  long int doIlu;

  WINDOW *biezace_okno = stdscr;

  erase();

  int xcent = getmaxx(biezace_okno) / 2;
  int ycent = getmaxy(biezace_okno) / 2;

  string tresc = "Prosze podac do jakiej liczby przeszukiwac?\n";
  mvaddstr(ycent, xcent - tresc.length() / 2, tresc.c_str());

  echo();
  scanw("%ld", &doIlu);
  noecho();
  
  printw("%s", "Trwa mielenie liczby...\n");
  printw("%s", "Znalezione liczby Wilsona:");

  for (p = 2; p <= doIlu; p++) {
      //    printf("%ld", p);

    baza = p * p;
    x = 1;

    for (n = 2; n <= p - 1; n++) {
      x *= (n % baza);
      x %= baza;
    }

    if (++x == baza) {
	printw("%s", "\n");
	printw("%ld", p);
    }
  }
  
  printw("%s", "\n");
  printw("%s", "q - Wyjscie\n");
  
  while(getch() != 'q'){
  }
}
//----------------------------------------------------------------------------------------------

void liczbyWiefericha() {
  long int x, p, n, baza;
  long int doIlu;

  WINDOW *biezace_okno = stdscr;

  erase();

  int xcent = getmaxx(biezace_okno) / 2;
  int ycent = getmaxy(biezace_okno) / 2;

/*  const string tresc = R"(
    "Liczba pierwsza p jest liczba Wiefericha gdy p * p dzieli 2^{p - 1} - 1\n" 
    "Znane sa na razie tylko dwie takie liczby : 1093 i 3511.\n"
    "Prosze podac do jakiej liczby przeszukiwac?\n"
  )"; */ 
//R oznacza literalne traktowanie lancucha? W kazdym razie to
//powoduje ze na ekranie pojawia sie \n zamiast wysuwu linii - zapewne trzeba je usunac
//TODO: napisac rozdzielenie lancucha i rozmieszczenie go na ekranie (split)
  const string tresc = "Prosze podac do jakiej liczby przeszukiwac?\n";
  mvaddstr(ycent, xcent - tresc.length() / 2, tresc.c_str());

  echo();
  scanw("%ld", &doIlu);
  noecho();
  
  printw("%s", "Trwa mielenie liczby...\n");
  printw("%s", "Znalezione liczby Wiefericha:");

  for (p = 2; p <= doIlu; p++) {
      //    printf("%ld", p);

    baza = p * p;
    x = 1;

    for (n = 1; n <= p - 1; n++) {
      x *= 2;
      x %= baza;
    }

    if (x == 1) {
	printw("%s", "\n");
	printw("%ld", p);
    }
  }
  
  printw("%s", "\n");
  printw("%s", "q - Wyjscie\n");
  
  while(getch() != 'q'){
  }
}
//----------------------------------------------------------------------------------------------
void teoriaLiczbMain() {
  int wybor1 = -1;

  do {
    erase();
    MenuClass *menu1 = new MenuClass();
    menu1->Opcja("Szukanie liczb pierwszych Wilsona");
    menu1->Opcja("Szukanie liczb pierwszych Wiefericha");
    menu1->Opcja("Wlasciwosc liczby 247");
    menu1->OpcjaWyjscia("Wyjscie");
       
    wybor1 = menu1->Run();

    switch (wybor1) {
      case 0:
        liczbyWilsona();
        break;  
      case 1:
        liczbyWiefericha();
        break;     
      case 2:
        dwa_cztery_siedem();
        break;
    }
      
    delete menu1;
  } while (wybor1 != -1);
}
//----------------------------------------------------------------------------------------------
