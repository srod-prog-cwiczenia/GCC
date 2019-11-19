#include <ncurses.h>
#include <math.h>
#include <string.h>
#include <list>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "menuClass.h"
#include "showTablica.h"
#include "biblioteczneFunkcje.h"
#include "biblioteczneEkran.h"

#include "analizaWstecznaInterface.h"
//-----------------------------------------------------------------------
//  tutaj funkcje sluzace do sortowania listy mozliwych odpowiedzi:
//-----------------------------------------------------------------------
bool compOpcjaStanuBiale(const TOpcjaStanuStr & a, const TOpcjaStanuStr & b) 
  { 
    /*return - a.ocena < - b.ocena && -a.ocena > 0 ||
      a.ocena > b.ocena && b.ocena > 0 || 
    !a.ocena && b.ocena > 0 ||
    - a.ocena > 0 && !b.ocena; */ // to nie dzialalo dobrze, zreszta jest balaganiarskie :)
// tutaj nowsza wersja, mam nadzieje ze jest to bardziej poprawna wersja :)
    if (a.ocena <= 0 && b.ocena >= 0) return true;
    if (a.ocena < 0 && b.ocena < 0 && - a.ocena < - b.ocena) return true;
    if (a.ocena > 0 && b.ocena > 0 && a.ocena > b.ocena) return true;
    return false;
}
bool compOpcjaStanuCzarne(const TOpcjaStanuStr & a, const TOpcjaStanuStr & b) 
  { /*return a.ocena > b.ocena && b.ocena > 0 || 
            - a.ocena < - b.ocena && a.ocena < 0 || 
    !a.ocena && b.ocena > 0 ||
    - a.ocena > 0 && !b.ocena; */ // uwaga j.w. - jesli sie okaze ze ,,pracuje'' to samo to wtedy mozna to zebrac w jedno :)
    if (a.ocena <= 0 && b.ocena >= 0) return true;
    if (a.ocena < 0 && b.ocena < 0 && - a.ocena < - b.ocena) return true;
    if (a.ocena > 0 && b.ocena > 0 && a.ocena > b.ocena) return true;
    return false;
} 

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
AnalizaWstecznaInterface::AnalizaWstecznaInterface() {
  aw = new AnalizaWsteczna();
}
//-----------------------------------------------------------------------
AnalizaWstecznaInterface::~AnalizaWstecznaInterface() {
  delete aw;
}
//-----------------------------------------------------------------------
void AnalizaWstecznaInterface::runOnLine() {
  Stan st;
  Kto kto;
  int pomZnak;  
  bool czy_dalej;
  ListaStanow pamiec;
// tu trzeba sprawdzic czy analiza zostala wykonana
  if (!aw->isOcena()) {
    komunikat("Nie wykonano analizy!");
    return;
  }

  erase();
  mvaddstr(2, getmaxy(stdscr) / 4 + 1, "Prosze podac stan i kto zaczyna ...");
  
  if (!getStan(&st, &kto)) {
    return;
  }

  do {
    erase(); //o ile to oznacza skasowanie ekranu :)
    mvaddstr(getmaxy(stdscr) / 2, 0, "Ruch dla ");
    printw("%s", kto == bialy ? " BIALYCH \n" : " CZARNYCH \n");
    
    printw("%s %d", kto == bialy ? "\nBiale: " : "\nCzarne", aw->getOcena(&st, kto)); 
    TListaMozliwychRuchow *lmr = NULL;
    if (aw->getOcena(&st, kto) == 0) 
      printw("%s", "\nRemis"); //TODO: ten przypadek tez ,,uruchomic''!
    else {  
      printw("%s %s", "\nWygrana  ", ((aw->getOcena(&st, kto) > 0) ^ (kto == czarny)) ? "bialych" : "czarnych");
      if (aw->getOcena(&st, kto) != 1) {//czyli od razu jest wygrana i nie ma sensu pokazywac
//nalepszego ruchu - bo to nie bedzie z jakis tam powodow ten wygrywajacy (zbijajacy w jednym ruchu)
      //teraz pokazuje najlepszy ruch
        Stan *stNajlepszy = getNajlepszyRuch(&st, kto);
        char *rNajlepszy = getRuchFromStany(&st, stNajlepszy);
        printw("%s %s", "\nNajlepszy proponowany ruch: ", rNajlepszy); 
        delete stNajlepszy;
        free(rNajlepszy);
        string txt;
        lmr = getListaMozliwychRuchow(&st, kto);
        TListaMozliwychRuchow::iterator it_lmr;
        for (it_lmr = lmr->begin(); it_lmr != lmr->end(); it_lmr++) {
          char *sOpisRuchu = getRuchFromStany(&st, &(it_lmr->stan));
          txt.append(1, it_lmr->klawisz);
          txt.append(":");
          txt.append(sOpisRuchu);
          txt.append(" (");
          ostringstream strumien;
          strumien << it_lmr->ocena;
          txt.append(strumien.str());
          txt.append(")\t");
        }
        printw("%s %s", " Wszystkie ruchy wraz z oceną:\n", /*getSpisMozliwychRuchow(&st, kto).c_str()*/txt.c_str());
      }
    }
    showStan(&st);
    czy_dalej = dialogDoPlanszy(&st, &kto, lmr, &pamiec); 
    if (lmr) delete lmr;
  } while (czy_dalej);
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
void AnalizaWstecznaInterface::showStan(Stan *st) {
  int xrog = getmaxx(stdscr) / 2 - 4;
  int yrog = 1;

  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  
  OknoAplikacji::ramka(xrog - 1, yrog - 1, xrog - 1 + 9, yrog - 1 + 9);
    
  for (int xx = 0; xx < 8; xx++)
    for (int yy = 0; yy < 8; yy++) {
      if (!AnalizaWsteczna::isPustePole(&st->b1) && st->b1.x == xx && st->b1.y == yy) {
        attron(COLOR_PAIR(1));
        mvaddch(7 - yy + yrog, xx + xrog, ACS_DIAMOND);
        attroff(COLOR_PAIR(1));
        continue;      
      }

      if (!AnalizaWsteczna::isPustePole(&st->b2) && st->b2.x == xx && st->b2.y == yy) {
        attron(COLOR_PAIR(1));
        mvaddch(7 - yy + yrog, xx + xrog, ACS_BLOCK);
        attroff(COLOR_PAIR(1));
        continue;      
      }

      if (!AnalizaWsteczna::isPustePole(&st->c1) && st->c1.x == xx && st->c1.y == yy) {
        attron(COLOR_PAIR(2));
        mvaddch(7 - yy + yrog, xx + xrog, ACS_DIAMOND);
        attroff(COLOR_PAIR(2));
        continue;      
      }

      mvaddch(7 - yy + yrog, xx + xrog, '.');      
    }  

  for (int xx = 0; xx < 8; xx++) {
    mvaddch(9 + yrog, xrog + xx, 'A' + xx);
  }

  for (int yy = 0; yy < 8; yy++) {
    mvaddch(yrog + (7 - yy), xrog - 3, '1' + yy);
  }
}
//-----------------------------------------------------------------------
// Pomocnicza procedura
// -1 oznacza bledne pole.
int AnalizaWstecznaInterface::getKodPola(char pole, int wersja /*0 - wsp x, 1 - wsp y. */) {
  switch (wersja) {
    case 0:
      if ('a' <= pole && pole <= 'a' + 8) {
        return int (pole - 'a');
      }

      if ('A' <= pole && pole <= 'A' + 8) {
        return int (pole - 'A');
      }
 
      return -1;
    case 1:
      if ('1' <= pole && pole <= '1' + 8) {
        return int (pole - '1');
      }

      return -1;
  }
}
//-----------------------------------------------------------------------
// Pobranie stanu razem z osoba ktora zaczyna
bool AnalizaWstecznaInterface::getStan(Stan *st, Kto *oso) {
  if (!getStan(st)) {
    return false;
  }
 
  printw("%s", "\n");
  printw("%s", "b - biale");
  printw("%s", "\n"); 
  printw("%s", "c - czarne\n");
  printw("%s", "q - wyjscie\n");
  
  int pomZnak;

  do {
    pomZnak = getch();  
  } while (pomZnak != 'b' && pomZnak != 'B' && pomZnak != 'c' && pomZnak != 'C' && pomZnak != 'q' && pomZnak != 'Q');

  if (pomZnak == 'q' || pomZnak == 'Q') {
    return false;
  }

  if (pomZnak == 'b' || pomZnak == 'B') {
    *oso = bialy;
  }

  if (pomZnak == 'c' || pomZnak == 'C') {
    *oso = czarny;
  }
  
  return true;
}
//-----------------------------------------------------------------------
bool AnalizaWstecznaInterface::getStan(Stan *st) {
  char str[100];  // Jakas tam dlugosc, nie za krotka.

  printw("%s", "Podaj stan w formacie np: a3b5c7 (biale,biale,czarne)\n");
  printw("%s", "badz tez w formacie xxa3c8 (bialy pusty,bialy,czarny)\n");
  printw("%s", "albo tez w formacie a3xxc8 (bialy, drugi bialy pusty,czarny\n");
  printw("%s", "Pusty oznacza rezygnacje...\n");
  bool pierwszaPetla = true;

  while (true) {
    if (!pierwszaPetla) {
      printw("%s", 
        "\nBledny stan. Sprobuj jeszcze raz (badz zrezygnuj podajac lancuch pusty)");
    }
    
    pierwszaPetla = false;
     
    *str = 0; //A to po to ze scanw po podaniu enter (lancuch pusty)
// str w ogole nie jest zmieniany!
    echo(); //Aby wprowadzany lancuch pojawil sie na ekranie
    scanw("%99s", str);
    noecho();

    if (!strlen(str)) {
      return false;
    }

    if (strlen(str) != 6) {
      continue;
    }

    Stan stlok;

    if (str[0] == 'x' && str[1] == 'x') {
      stlok.b1.x = stlok.b1.y = DUMMY;
    } else {
      if (getKodPola(str[0], 0) == -1) {
        continue;
      } else {
        stlok.b1.x = getKodPola(str[0], 0);
      }    

      if (getKodPola(str[1], 1) == -1) {
        continue;
      } else {
        stlok.b1.y = getKodPola(str[1], 1);
      }    
    }

    if (str[2] == 'x' && str[3] == 'x') {
      stlok.b2.x = stlok.b2.y = DUMMY;
    } else {
      if (getKodPola(str[2], 0) == -1) {
        continue;
      } else {
        stlok.b2.x = getKodPola(str[2], 0);
      } 

      if (getKodPola(str[3], 1) == -1) {
        continue;
      } else {
        stlok.b2.y = getKodPola(str[3], 1);
      }    
    }

    if (getKodPola(str[4], 0) == -1) {
      continue;
    } else {
      stlok.c1.x = getKodPola(str[4], 0);
    }    

    if (getKodPola(str[5], 1) == -1) {
      continue;
    } else {
      stlok.c1.y = getKodPola(str[5], 1);
    }    

    if (stlok.b1.x == DUMMY && stlok.b2.x == DUMMY) {
      continue;
    }

    *st = stlok; 
    return true;
  }
}
//-----------------------------------------------------------------------
// Ustala mozliwy ruch na podstawie st1 i st2 po wykonaniu tego ruchu.
// Przydatna w proponowaniu najlepszego ruchu.
char *AnalizaWstecznaInterface::getRuchFromStany(Stan *st1, Stan *st2, bool skroconyZapis) {
  char *str = (char*)malloc(5); //dlugosc wraz z zerem na koncu 
  memset(str, 0, 5);
  if (st1->b1.x != DUMMY && st1->b1.y != DUMMY && st2->b1.x != DUMMY && st2->b1.y != DUMMY)
    if (st1->b1.x != st2->b1.x || st1->b1.y != st2->b1.y) {
      if (skroconyZapis) {
        str[0] = 'K';
        str[1] = st2->b1.x + 'a';
        str[2] = st2->b1.y + '1';
      } else {
        str[0] = st1->b1.x + 'a';
        str[1] = st1->b1.y + '1';
        str[2] = st2->b1.x + 'a';
        str[3] = st2->b1.y + '1';
      }
      return str;
    }

  if (st1->b2.x != DUMMY && st1->b2.y != DUMMY && st2->b2.x != DUMMY && st2->b2.y != DUMMY)
    if (st1->b2.x != st2->b2.x || st1->b2.y != st2->b2.y) {
      if (skroconyZapis) {
        str[0] = 'H';
        str[1] = st2->b2.x + 'a';
        str[2] = st2->b2.y + '1';
      } else {
        str[0] = st1->b2.x + 'a';
        str[1] = st1->b2.y + '1';
        str[2] = st2->b2.x + 'a';
        str[3] = st2->b2.y + '1';
      }
      return str;
    }

  if (st1->c1.x != DUMMY && st1->c1.y != DUMMY && st2->c1.x != DUMMY && st2->c1.y != DUMMY)
    if (st1->c1.x != st2->c1.x || st1->c1.y != st2->c1.y) {
      if (skroconyZapis) {
        str[0] = 'K';
        str[1] = st2->c1.x + 'a';
        str[2] = st2->c1.y + '1';
      } else {
        str[0] = st1->c1.x + 'a';
        str[1] = st1->c1.y + '1';
        str[2] = st2->c1.x + 'a';
        str[3] = st2->c1.y + '1';
      }
      return str;
    }

  return str;
}
//-----------------------------------------------------------------------
bool AnalizaWstecznaInterface::getRuch(Stan *st, Kto oso) {
  char str[100];  // Jakas tam dlugosc, nie za krotka.

  printw("%s", "Podaj ruch w formacie np: a3b4 (skad - dokad) \n");
  printw("%s %s", "Ruch dla ", oso == bialy ? " bialych " : "czarnych ");
  printw("%s", "\nPusty oznacza rezygnacje...\n");
  bool pierwszaPetla = true;

  while (true) {
    if (!pierwszaPetla) {
      printw("%s", 
        "\nBledny ruch. Sprobuj jeszcze raz (badz zrezygnuj podajac lancuch pusty)");
    }
    
    pierwszaPetla = false;
     
    *str = 0; //A to po to ze scanw po podaniu enter (lancuch pusty)
// str w ogole nie jest zmieniany!
    echo(); //Aby wprowadzany lancuch pojawil sie na ekranie
    scanw("%99s", str);
    noecho();

    if (!strlen(str)) {
      return false;
    }

    if (strlen(str) != 4) {
      continue;
    }

    Stan stlok = *st;

    int xfrom, yfrom, xto, yto;
    xfrom = getKodPola(str[0], 0);
    yfrom = getKodPola(str[1], 1);
    xto = getKodPola(str[2], 0);
    yto = getKodPola(str[3], 1);    

    if (xfrom == -1 || yfrom == -1 || xto == -1 || yto == -1) {
      continue;
    }

    switch (oso) {
      case bialy:
        if (xfrom == stlok.b1.x && yfrom == stlok.b1.y) {
	  stlok.b1.x = xto;
	  stlok.b1.y = yto;
	} else if (xfrom == stlok.b2.x && yfrom == stlok.b2.y) {
	  stlok.b2.x = xto;
	  stlok.b2.y = yto;
	} else {
	  continue;
	}

	break;

      case czarny:
        if (xfrom == stlok.c1.x && yfrom == stlok.c1.y) {
	  stlok.c1.x = xto;
	  stlok.c1.y = yto;
	} else {
	  continue;
	}

	if (stlok.b1.x == xto && stlok.b1.y == yto) {
	  stlok.b1.x = stlok.b1.y = DUMMY; //Zbicie bialej figury nr 1
	}

	if (stlok.b2.x == xto && stlok.b2.y == yto) {
	  stlok.b2.x = stlok.b2.y = DUMMY; //Zbicie bialej figury nr 2
	}

	break;
    }
  
    *st = stlok; 
    return true;
  }
}
//-----------------------------------------------------------------------
void AnalizaWstecznaInterface::saveToFile() {
  if (istniejePlik(NAZWA_PLIKU_Z_ANALIZA)) {
    if (!pytanieNT("Czy nadpisac ten plik?")) {
      return;
    }  
  }

  FILE *ff = fopen(NAZWA_PLIKU_Z_ANALIZA, "wb");

  if (ff) {
// Na poczatku naglowek zawierajacy opis zawartych informacji w pliku.
// Na razie pozostawiam go pustego, 
    char nag[1000];
    memset(nag, 0, 1000);
    fwrite(nag, 1, 1000, ff);
    fwrite(aw->pra->b1Pla, 1, sizeof(TPlanszaDlaPrawidelRuchu), ff);
    fwrite(aw->pra->b2Pla, 1, sizeof(TPlanszaDlaPrawidelRuchu), ff);
    fwrite(aw->pra->c1Pla, 1, sizeof(TPlanszaDlaPrawidelRuchu), ff);
    fwrite(aw->oB, 1, sizeof(Oceny), ff);
    fwrite(aw->oC, 1, sizeof(Oceny), ff);
    fclose(ff);    
  }  
}
//-----------------------------------------------------------------------
void AnalizaWstecznaInterface::loadFromFile() {

  if (!istniejePlik(NAZWA_PLIKU_Z_ANALIZA)) {
    komunikat("Nie ma pliku z zapisana analiza.");
    return;  
  }

  FILE *ff = fopen(NAZWA_PLIKU_Z_ANALIZA, "rb");

  if (ff) {
// Na poczatku naglowek zawierajacy opis zawartych informacji w pliku.
// Na razie pozostawiam go pustego, 
    char nag[1000];
    fread(nag, 1, 1000, ff);
    fread(aw->pra->b1Pla, 1, sizeof(TPlanszaDlaPrawidelRuchu), ff);
    fread(aw->pra->b2Pla, 1, sizeof(TPlanszaDlaPrawidelRuchu), ff);
    fread(aw->pra->c1Pla, 1, sizeof(TPlanszaDlaPrawidelRuchu), ff);
    fread(aw->oB, 1, sizeof(Oceny), ff);
    fread(aw->oC, 1, sizeof(Oceny), ff);
    fclose(ff);    
  }  
}
//-----------------------------------------------------------------------
TListaMozliwychRuchow *AnalizaWstecznaInterface::getListaMozliwychRuchow(Stan *st, Kto oso) {
  TListaMozliwychRuchow *lmr = new TListaMozliwychRuchow();
  ListaStanow *ls = aw->getMozliweRuchy(st, oso);                
  ListaStanow::iterator it_ls;
  for (it_ls = ls->begin(); it_ls != ls->end(); it_ls++) {
    Stan st_it = *it_ls;
    TOpcjaStanuStr oS;
    oS.stan = st_it;
    oS.ocena = aw->getOcena(&st_it, oso == bialy ? czarny : bialy);
    oS.klawisz = '\0'; // na razie niewypelnione, potem wypelnimy po posortowaniu;
    lmr->push_back(oS);
  }
  delete ls;

  if (oso == bialy) {
    lmr->sort(compOpcjaStanuBiale);
  } else {
    lmr->sort(compOpcjaStanuCzarne);
  }
  // numeracja klawiszy dostepu do stanow - na razie od 1, potem mozna wymyslec cos innego:
  TListaMozliwychRuchow::iterator it_lmr;
  char ch = '1';
  for (it_lmr = lmr->begin(); it_lmr != lmr->end(); it_lmr++) {
    it_lmr->klawisz = ch;
    if (ch++ == '9') {
      ch = 'A';  
    }
  }
  return lmr;
}
//-----------------------------------------------------------------------
// wyciaga spis mozliwych ruchow (wraz z ich ocena)
string AnalizaWstecznaInterface::getSpisMozliwychRuchow(Stan *st, Kto oso) {
  string oo;
  ListaStanow *ls = aw->getMozliweRuchy(st, oso);                
  ListaStanow::iterator it;
  for (it = ls->begin(); it != ls->end(); it++) {
    Stan st_it = *it;
    int ocenka = aw->getOcena(&st_it, oso == bialy ? czarny : bialy);
    char *sOpisRuchu = getRuchFromStany(st, &st_it);
    oo.append(sOpisRuchu);
    ostringstream strumien;
    strumien << ocenka;
    oo.append("(" + strumien.str() + ") ");
  }
  delete ls;
  return oo;
}
//-----------------------------------------------------------------------
// wyciaga najlepszy mozliwy ruch w zastanej sytuacji: <st, oso>
Stan *AnalizaWstecznaInterface::getNajlepszyRuch(Stan *st, Kto oso) {
  ListaStanow *ls = aw->getMozliweRuchy(st, oso);                
  ListaStanow::iterator it;

  int ocSzuk = aw->getOcena(st, oso);
  ocSzuk = ocSzuk > 0 ? - ocSzuk + 1 : (ocSzuk < 0 ? - ocSzuk - 1 : ocSzuk);
  Stan *stRes = NULL;  

  for (it = ls->begin(); it != ls->end(); it++) {
    Stan st_it = *it;
     
    if (aw->getOcena(&st_it, oso == bialy ? czarny : bialy) == ocSzuk) {
      stRes = new Stan();
      memcpy(stRes, &st_it, sizeof(Stan));
    }
  }

  assert(stRes);
  delete ls;
  return stRes;
}
//-----------------------------------------------------------------------
bool AnalizaWstecznaInterface::dialogDoPlanszy(Stan *st, Kto *kto, 
  TListaMozliwychRuchow *lmr, ListaStanow *pamiec) {
//majac wyswietlona plansze pozwala na wybor najlepszego ruchu,
//wpisanie swojego albo na wyjscie (wtedy wartosc tej funkcji jest ////
//false).
  int pomZnak;
  if (aw->getOcena(st, *kto) == 1) {
    mvaddstr(getmaxy(stdscr) / 2 + 10, 0, "KONIEC:");
    printw("%s", (*kto == bialy ? " q - wyjscie. z - cofnij. Biale wygraly.\n" : "q - wyjscie. z - cofnij. Czarne wygraly.\n"));
//TODO: koniecznie potem polaczyc ten przypadek z przypadkiem ponizej (tylko biorac pod uwage pusta liste mozliwych ruchow).
    do {
      pomZnak = getch();  
    } while (pomZnak != 'q' && pomZnak != 'Q' && pomZnak != 'z' && pomZnak != 'Z');
    if (!pamiec->empty()) {
      memcpy(st, &(pamiec->back()), sizeof(Stan));
      pamiec->pop_back();
      *kto = *kto == bialy ? czarny : bialy;
    }
    return pomZnak != 'q' && pomZnak != 'Q';
  }

  mvaddstr(getmaxy(stdscr) / 2 + 10, 0, "q - wyjscie, \nr - wykonaj proponowany najlepszy ruch,\ns - wykonaj swoj ruch\nz - cofnij");
  string dozwoloneKlawisze = "qrszQRSZ";
  if (lmr) {
    for (TListaMozliwychRuchow::iterator it_lmr = lmr->begin(); it_lmr != lmr->end(); it_lmr++) {
      dozwoloneKlawisze.append(1, it_lmr->klawisz);   
    }
  }
  do {
    pomZnak = getch();  
  } while (dozwoloneKlawisze.find(pomZnak) == string::npos);
  
  switch (pomZnak) {
    case 'q': case 'Q': 
      return false;
    case 'r': case 'R': {
      Stan *stNast = getNajlepszyRuch(st, *kto);

      if (!stNast) {
        komunikat("WEWNETRZNY BLAD: Wskaznik do nastepnego stanu jest niezainicjowany!");
        return false;
      }
      pamiec->push_back(*st);
      memcpy(st, stNast, sizeof(Stan));      
      delete stNast; 
      *kto = *kto == bialy ? czarny : bialy;
      return true;
    }
    case 's': case 'S':
      pamiec->push_back(*st);
      if (getRuch(st, *kto)) {
        *kto = *kto == bialy ? czarny : bialy;
      } else {
        if (!pamiec->empty()) { //to nadmiarowe bo w tej sytuacji nie powinno byc puste!
          pamiec->pop_back();
        }
        komunikat("Nieprawidlowy ruch");
      } //TODO: w dalszej kolejnosci mozna to wyrzucic!
      return true;
    case 'z': case 'Z':
      if (!pamiec->empty()) {
        memcpy(st, &(pamiec->back()), sizeof(Stan));
        pamiec->pop_back();
        *kto = *kto == bialy ? czarny : bialy;
      }
      return true;
    default: { // czyli ruch wybrany z listy ruchow, jak mniemam?
      if (lmr) {
        for (TListaMozliwychRuchow::iterator it_lmr = lmr->begin(); it_lmr != lmr->end(); it_lmr++) {
          if (it_lmr->klawisz == pomZnak) {
            pamiec->push_back(*st);
            memcpy(st, &(it_lmr->stan), sizeof(Stan));      
            *kto = *kto == bialy ? czarny : bialy;
            return true;
          } 
        }
      }
      komunikat("Wewnetrzny blad - nacisnieto jakis nieoprogramowany klawisz!");
      return true;
    }
  } // do switcha na pomZnak
}
//-----------------------------------------------------------------------
void AnalizaWstecznaInterface::ustawianiePrawidel() {
  char str[100];
  bool zmiana = false;
  do {
    erase(); 
    int tab[MAX_ROZ_PLANSZY_PRAWIDLA][MAX_ROZ_PLANSZY_PRAWIDLA];
    int *ptab[20];
    for (int qx = 0; qx < MAX_ROZ_PLANSZY_PRAWIDLA; qx++)
      for (int qy = 0; qy < MAX_ROZ_PLANSZY_PRAWIDLA; qy++)
        tab[qx][qy] = aw->pra->b1Pla[qx][qy];
    for (int qx = 0; qx < MAX_ROZ_PLANSZY_PRAWIDLA; qx++)
      ptab[qx] = tab[qx];
    ShowTablica::show(1, 1, MAX_ROZ_PLANSZY_PRAWIDLA, 1, ptab);

    for (int qx = 0; qx < MAX_ROZ_PLANSZY_PRAWIDLA; qx++)
      for (int qy = 0; qy < MAX_ROZ_PLANSZY_PRAWIDLA; qy++)
        tab[qx][qy] = aw->pra->b2Pla[qx][qy];
    for (int qx = 0; qx < MAX_ROZ_PLANSZY_PRAWIDLA; qx++)
      ptab[qx] = tab[qx];
    ShowTablica::show(20, 1, MAX_ROZ_PLANSZY_PRAWIDLA, 1, ptab);

    for (int qx = 0; qx < MAX_ROZ_PLANSZY_PRAWIDLA; qx++)
      for (int qy = 0; qy < MAX_ROZ_PLANSZY_PRAWIDLA; qy++)
        tab[qx][qy] = aw->pra->c1Pla[qx][qy];
    for (int qx = 0; qx < MAX_ROZ_PLANSZY_PRAWIDLA; qx++)
      ptab[qx] = tab[qx];
    ShowTablica::show(40, 1, MAX_ROZ_PLANSZY_PRAWIDLA, 1, ptab);

    *str = 0; //A to po to ze scanw po podaniu enter (lancuch pusty)
// str w ogole nie jest zmieniany!
    echo(); //Aby wprowadzany lancuch pojawil sie na ekranie
    scanw("%99s", str);
    noecho();

    if (!strlen(str)) {
      return;
    }

    if (strlen(str) != 3) {
//przypadek kiedy chcemy skasowac plansze:
// c<numer planszy> oznacza - skasuj plansze nr <nr planszy>
      if (strlen(str) == 2) {
        if ((str[0] == 'c' || str[0] == 'C') &&
         '1' <= str[1] && str[1] <= '3') {
          switch (str[1]) {
            case '1':
              for (int qx = 0; qx < MAX_ROZ_PLANSZY_PRAWIDLA; qx++)
                for (int qy = 0; qy < MAX_ROZ_PLANSZY_PRAWIDLA; qy++)
                  aw->pra->b1Pla[qx][qy] = 0;
              zmiana = true;
              break;
            case '2':
              for (int qx = 0; qx < MAX_ROZ_PLANSZY_PRAWIDLA; qx++)
                for (int qy = 0; qy < MAX_ROZ_PLANSZY_PRAWIDLA; qy++)
                  aw->pra->b2Pla[qx][qy] = 0;
              zmiana = true;
              break;
            case '3':
              for (int qx = 0; qx < MAX_ROZ_PLANSZY_PRAWIDLA; qx++)
                for (int qy = 0; qy < MAX_ROZ_PLANSZY_PRAWIDLA; qy++)
                  aw->pra->c1Pla[qx][qy] = 0;
              zmiana = true;
              break;
          }
        }
      }      
      continue;
    }
    char jakaFigura = str[0];
    if (jakaFigura != 'k' && jakaFigura != 'K' && jakaFigura != 'h') 
      continue;
    int wsp1 = str[1] - 'a';
    if (!(wsp1 >= 0 && wsp1 < MAX_ROZ_PLANSZY_PRAWIDLA))
      continue;
    int wsp2 = str[2];
    if (wsp2 <= '9' && wsp2 >= '1') 
      wsp2 -= '1';
    else 
      wsp2 -= 'a' - 9; 
    if (!(wsp2 >= 0 && wsp2 < MAX_ROZ_PLANSZY_PRAWIDLA))
      continue;
    switch (jakaFigura) {
      case 'k':
        aw->pra->b1Pla[wsp1][wsp2] = !aw->pra->b1Pla[wsp1][wsp2];
        zmiana = true;
        break;
      case 'h':
        aw->pra->b2Pla[wsp1][wsp2] = !aw->pra->b2Pla[wsp1][wsp2];
        zmiana = true;
        break;
      case 'K':
        aw->pra->c1Pla[wsp1][wsp2] = !aw->pra->c1Pla[wsp1][wsp2];
        zmiana = true;
        break;
    }
    if (zmiana) {
      aw->clearOceny();
    }
  } while (true);
}
//-----------------------------------------------------------------------
void analizaWsteczna() {
  AnalizaWstecznaInterface *awi = new AnalizaWstecznaInterface();
  int wybor1 = -1;

  do {
    erase();
    MenuClass *menu1 = new MenuClass();
    menu1->Opcja("Wykonaj analize");
    menu1->Opcja("Zapisz wynik analizy do pliku");
    menu1->Opcja("Wczytaj wynik analizy z pliku");
    menu1->Opcja("Test klasy ShowTablica");
    menu1->Opcja("Proba online");
    menu1->Opcja("Ustawianie prawidel ruchu");
    menu1->OpcjaWyjscia("Wyjscie");
       
    wybor1 = menu1->Run();

    switch (wybor1) {
      case 0:
        awi->aw->analiza();
        komunikat("Analiza wykonana");
        break;  
      case 1:
        if (!awi->aw->isOcena()) {
          komunikat("Nie wykonano analizy!");
        } else {
          awi->saveToFile();
        }
        break;     
      case 2:
        awi->loadFromFile();
        break;
      case 3: {
// to problematyczne, chyba do usuniecia, na razie jednak pozostawiam to poki co 
        ShowTablica::test();
        break;
      }
      case 4:
        if (!awi->aw->isOcena()) {
          komunikat("Nie wykonano analizy!");
        } else {
          awi->runOnLine();
        }
        break;
      case 5:
        awi->ustawianiePrawidel();
        break;
    }
      
    delete menu1;
  } while (wybor1 != -1);
  
  delete awi;
}
//-----------------------------------------------------------------------
//=======================================================================
//--- to juz jest chyba zbedna klasa - mozna potem to przeniesc do jakiegos osobnego modulu ("trash" :) )
//-----------------------------------------------------------------------
// Klasa testowa - chyba nie bedzie juz potrzebna?
/*class AnalizaWstecznaTesty {
  private:
    AnalizaWsteczna *aw; 
  public:
    AnalizaWstecznaTesty(AnalizaWsteczna *aw_p);
    ~AnalizaWstecznaTesty();  
    void run();
};
//-----------------------------------------------------------------------
AnalizaWstecznaTesty::AnalizaWstecznaTesty(AnalizaWsteczna *aw_p) {
  aw = aw_p;
}
//-----------------------------------------------------------------------
AnalizaWstecznaTesty::~AnalizaWstecznaTesty() {
}
void AnalizaWstecznaTesty::run() {
  Stan st;
  int pomZnak;  
  
  if (!aw) {
    komunikat("Cos nie tak - nie jest zainicjowana klasa AnalizaWsteczna!");
    return;
  }
// ewentualnie sprawdzic czy analiza wsteczna nie ma pustej zawartosci!
  do {
    erase();
    mvaddstr(2, getmaxy(stdscr) / 4 + 1, "Teraz podaj stan...");
  
    if (!AnalizaWstecznaInterface::getStan(&st)) {
      return;
    }

    AnalizaWstecznaInterface::showStan(&st);
  
    mvaddstr(2, getmaxy(stdscr) / 4, "Oceny:\n");
    printw("%s %d", "Biale: ", aw->getOcena(&st, bialy)); 
    printw("%s %d", "\nCzarne: ", aw->getOcena(&st, czarny)); 

    mvaddstr(2, getmaxy(stdscr) / 4, "q - wyjscie, s - nowy stan");

    do {
      pomZnak = getch();  
    } while (pomZnak != 'q' && pomZnak != 's');
  } while (pomZnak != 'q');

  if (pomZnak == 'q') {
    return; // Dalsza czesc to pokazywanie ruchow, na razie ,,odcinamy'' 
  }

  ListaStanow *ls = aw->getMozliweRuchy(&st, czarny);                
  ListaStanow::iterator it;

  for (it = ls->begin(); it != ls->end(); it++) {
    Stan st_it = *it;
    AnalizaWstecznaInterface::showStan(&st_it);   
    mvaddstr(2, getmaxy(stdscr) / 4, "q - wyjscie, n - nastepny");

    do {
      pomZnak = getch();  
    } while (pomZnak != 'q' && pomZnak != 'n');

    if (pomZnak == 'q') {
      break;
    }
  }

  delete ls;
}
//-----------------------------------------------------------------------
        AnalizaWstecznaTesty *awt = new AnalizaWstecznaTesty(awi->aw);
        awt->run();
        delete awt;
//-----------------------------------------------------------------------
*/
