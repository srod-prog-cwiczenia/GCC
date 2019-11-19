#include <ncurses.h>
#include <string>
#include "obslugaEkranu.h"
#include "zliczanieCzasu.h"
#include "acsPrzyklad.h"
#include "przykladoweKonstrukcjeCPP.h"
#include "WyswietlanieUptime.h"
#include "Zegar.h"
#include "generatorHasla.h"
#include "teoriaLiczb.h"
#include "modulULAM.h"
#include "analizaWstecznaInterface.h"
#include "biblioteczneEkran.h"
#include "biblioteczneFunkcje.h"
#include "menuClass.h"
//-----------------------------------

void pokaz_w_kolorze() {
 /* if (!OknoAplikacji::startTrybKolorowy()) {
    return;
  }*/ // Teraz jest zbedne bo startTrybKolorowy jest wykonywane zaraz na poczatku programu.  

  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLUE);

  attron(COLOR_PAIR(1));
  mvaddstr(1, 1, "Pierwsza paleta kolorow");
  mvaddstr(3, 1, "Wcisnij 'd' aby przejsc dalej");
  attroff(COLOR_PAIR(1));

  attron(COLOR_PAIR(2));
  mvaddstr(2, 1, "Inna paleta kolorow.");
  attroff(COLOR_PAIR(2));

  refresh();

  while (getch() != 'd') {};

  mvaddstr(4, 1, "Teraz zmiana kolorow palet:");

  init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(2, COLOR_YELLOW, COLOR_CYAN);

  mvaddstr(3, 1, "Wcisnij 'w' aby wyjsc              ");  

  while (getch() != 'w') {};
}

//--------------------------------------------------------

void proba_bold_oraz_F1() {
  mvaddstr(0, 0, "Type any character to see it in bold\n");
  char ch = getch();/* If raw() hadn't been called
		* we have to press enter before it
		* gets to the program */

  mvaddstr(1, 0, "The pressed key is ");
  attron(A_BOLD);
  mvaddch(2, 0, ch);
  attroff(A_BOLD);
}

//--------------------------
void pokazEkran() {
  OknoAplikacji *okno = new OknoAplikacji();
  int wybor = -1;
  
  do {
    erase();
    okno->winieta();
    MenuClass *menu1 = new MenuClass();
    menu1->Opcja("Przyklady do obslugi ekranu");
    menu1->Opcja("Analiza wsteczna");
    menu1->Opcja("Inne rzeczy, jeszcze nie uporzadkowane");  
    menu1->Opcja("Opcja pusta");
    menu1->Opcja("Przyklady do konstrukcji w C++");
    menu1->Opcja("Opcje zwiazane z obsluga czasu.");
    menu1->Opcja("Rozne narzedzia");
    menu1->OpcjaWyjscia("Wyjscie");
    menu1->ustawienieWersji(wmDrabinka);

    wybor = menu1->Run();

    delete menu1;

    switch (wybor) {
      case 0: {
        erase();
        MenuClass *menu0 = new MenuClass();
        menu0->Opcja("Wypisz znak - przyklad");
        menu0->Opcja("Pokaz w kolorze");
        menu0->Opcja("Pokaz znaki ACS");

        menu0->OpcjaWyjscia("Wyjscie");
       
        int wybor0 = menu0->Run();

        switch (wybor0) {
          case 0:
            clear();
  	/* wypisz znak na zadanej pozycji */
            mvaddch(2, 8, '@');
            mvaddstr(5, 5, "Wcisnij q aby przejsc dalej");

	/* oczekiwanie na nacisniecie q */
            while (getch()!='q');
            break;
          case 1:
            clear();
            pokaz_w_kolorze();
            break;
          case 2:
            clear();
            pokazACS();
            break;
        } 
        
        delete menu0;
	break;
      }

      case 1:
        clear();
        analizaWsteczna();
	break;

      case 2: {
        clear();
        proba_bold_oraz_F1();
        mvaddstr(10, 0, "Wcisnij F2 aby wyjsc, F3 aby uruchomic zliczanie czasu z pliku.");
        int cc;
        int miejsce = 11;

        do {
          cc = getch();

          if (cc == KEY_F(3)) {
            mvaddstr(miejsce++, 0, "Procedurka zliczanie czasu.");
            zliczanieCzasu();
          }
        } while (cc != KEY_F(2)) ; 
        break;
      }

      case 3: 
        dummy();
        break;
    /* Without keypad enabled this will */
  /*  not get to us either*/
  /* Without noecho() some ugly escape
   * charachters might have been printed
   * on screen*/
      case 4:
        przykladoweKonstrukcjeCPP();
        break;

      case 5: {
        erase();
        MenuClass *menu2 = new MenuClass();
        menu2->Opcja("Wyswietlanie uptime");
        menu2->Opcja("Wyswietlanie czasu");
        menu2->OpcjaWyjscia("Wyjscie");
       
        int wybor2 = menu2->Run();

        switch (wybor2) {
          case 0:
            wyswietlanieUptime();
            break;
          case 1:
            wyswietlanieCzasu();
            break;
        } 
        
        delete menu2;
        break;
      }

      case 6: {
        int wybor6 = -1;

        do {
          erase();
          MenuClass *menu6 = new MenuClass();
          menu6->Opcja("Generowane losowego hasla");
          menu6->Opcja("Teoria liczb");
          menu6->Opcja("Ulam");
          menu6->OpcjaWyjscia("Wyjscie");
       
          wybor6 = menu6->Run();

          switch (wybor6) {
            case 0:
              generatorHasla();
              break;
            case 1:
              teoriaLiczbMain();
              break;  
            case 2:
              funkcjaUlam();
              break;
          } 
        
          delete menu6;
        } while (wybor6 != -1);
        break;
      }
    }
  } while (wybor != -1);

  delete okno;
  return;
}


//----------------------------------------------------
