#include <ncurses.h>
#include <string>
#include <string.h>
#include <set>
#include "menuClass.h"
#include "biblioteczneEkran.h"
#include "biblioteczneFunkcje.h"
#include "generatorHasla.h"

#define MAX_DLUGOSC_GEN_HASLA 30

using namespace std;
/*
void zainicjowanie_terminala(void)
{
  biezace_okno = initscr();
  cbreak();
  noecho();
  nonl();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);
}*/
/*---------------------------------------------------------------*/
class ObslugaZbioruZnakow {
/* wrapper na zbior znakow */
  private:
    set<char> zbiorChar;
  public:
    ObslugaZbioruZnakow(int wersjaP) {
      switch (wersjaP) { //TODO: to zrobic jakos bardziej zrecznie!
        case 1:
          for (char ch = 'a'; ch <= 'z'; ch++)
            zbiorChar.insert(ch);
          for (char ch = 'A'; ch <= 'Z'; ch++)
            zbiorChar.insert(ch);
          for (char ch = '0'; ch <= '9'; ch++)
            zbiorChar.insert(ch);
          zbiorChar.insert('_');
          break;
        default:
          for (char ch = char(32); ch <= char(126); ch++)
            zbiorChar.insert(ch);
          break;
      }
    }
    int dobry_znak(char znak_p) {
      return zbiorChar.find(znak_p) != zbiorChar.end();
    };
    int liczba_dobrych_znakow() {
      return zbiorChar.size();
    };
    char n_ty_dobry_znak(int numer_p) {
      //TODO: byloby zapewne lepiej zrealizowac to przez iterator, tylko wczesniej wykonac sortowanie (potrzebne?)
      int licznik1 = 0, poz1 = 0;
      for(;;) {
        if (dobry_znak(poz1)) {
	    if (licznik1++ == numer_p)
	      return char(poz1);
        }
        poz1 = (poz1++ == 256) ? 0 : poz1;
      }
    };
};
/*---------------------------------------------------------------*/
class GeneratorHasla {
  public:
    GeneratorHasla(int wersjaP);
    ~GeneratorHasla();
  private:
    ObslugaZbioruZnakow ozz;
    int dobry_znak(int znak_p);
    int liczba_dobrych_znakow();
    char n_ty_dobry_znak(int numer_p);
    void zapisanieDoPliku(string haslo);
  public:
    void generatorHasla();
};
/*---------------------------------------------------------------*/
GeneratorHasla::GeneratorHasla(int wersjaP) : ozz(wersjaP) {
}
/*---------------------------------------------------------------*/
GeneratorHasla::~GeneratorHasla() {
}
/*---------------------------------------------------------------*/
int GeneratorHasla::dobry_znak(int znak_p) {
  //return znak_p >= 32 && znak_p <= 126;
  return ozz.dobry_znak(char(znak_p));
}
/*---------------------------------------------------------------*/
int GeneratorHasla::liczba_dobrych_znakow() {
  return ozz.liczba_dobrych_znakow();
  /*int licznik1, poz1;

  for (licznik1 = 0, poz1 = 0; poz1 <= 255; poz1++){
    licznik1 += dobry_znak(poz1);
  }

  return(licznik1);*/
}
/*---------------------------------------------------------------*/
char GeneratorHasla::n_ty_dobry_znak(int numer_p) {
  return ozz.n_ty_dobry_znak(numer_p);
  /*int licznik1, poz1;

  poz1 = licznik1 = 0;

  while (1) {
      if (dobry_znak(poz1)) {
	  if (licznik1++ == numer_p)
	    return char(poz1);
      }

      poz1 = (poz1++ == 256) ? 0 : poz1;
  }*/
}
/*---------------------------------------------------------------*/
/*
void zwolnienie_terminala(void)
{
  endwin();
}
*/
/*-----------------------------------------------------------*/

void GeneratorHasla::generatorHasla() {
  int dlugosc;
  int znak;
  long int ll;
  int l;
//  char ciag[MAX_DLUGOSC_GEN_HASLA + 1]; // Do wywalenia
  int pozycja;
  WINDOW *biezace_okno = stdscr;

  /*  printf("%d", liczba_dobrych_znakow());
      printf("%s", "-------------\n");

    for(l = 0; l <= 256; l++)
      {
      printf("%d", n_ty_dobry_znak(l));
      printf("%s", " ");
      }

  return(0); */
  //---------------------
//  zainicjowanie_terminala();

  erase();

  string haslo;
//  int xcent = getmaxx(biezace_okno) / 2; - zbedne w dalszym kontekscie
  int ycent = getmaxy(biezace_okno) / 2;

  mvaddstr(ycent, 5, "Prosze podac dlugosc generowanego ciagu\n");

  echo();
  scanw("%d", &dlugosc);
  noecho();

  if (dlugosc > MAX_DLUGOSC_GEN_HASLA || dlugosc <= 0) {
      printw("%s", "Bledna liczba, koncze dzialanie\n");
      printw("%s", "Nacisnij dowolny klawisz\n");
      getch();

 //     zwolnienie_terminala();
      return;
    }

  mvaddstr(ycent + 2, 5, "Prosze naciskac klawiature celem wygenerowania hasla...\n");
  nodelay(biezace_okno, TRUE);

    // Zasadnicza czesc generowania
  pozycja = 0;
  ll = 0;

  do {
    while((znak = getch()) == - 1) {
      ll++;
    }

    l = ll % liczba_dobrych_znakow();

    char pom[2];
    pom[1] = char(0);
    pom[0] = n_ty_dobry_znak(l);
    haslo.append(pom);
  } while (++pozycja < dlugosc);

//  ciag[pozycja] = 0;

  printw("%s", haslo.c_str());
  printw("%s", "\n");
  printw("%s", "w - zapisz do pliku");
  printw("%s", "\n");
  printw("%s", "q - Wyjscie\n");

  int pomZnak;

  do {
    pomZnak = getch();
  } while (pomZnak != 'q' && pomZnak != 'w');


    /*zwolnienie_terminala();*/
  nodelay(biezace_okno, FALSE); // Standardowo, czyli w obslugaEkranu nodelay
                                // byl ustawiony na false wiec przywracamy ten stan :)


  if (pomZnak == 'w') {
    zapisanieDoPliku(haslo);
  }
}
/*------------------------------------------------------------------------------*/
void GeneratorHasla::zapisanieDoPliku(string haslo) {
  printw("Na razie tylko pobieram nazwe pliku\n");
  printw("%s", "Prosze podac nazwe pliku:\n");
  printw("%s", "Pusta oznacza rezygnacje z zapisu do pliku. ");
/*  Trick z lancuchem dlugosci zerowej ktory konczy dzialanie procedury
  poczatkowo nie wychodzil a to dlatego ze po prostu nie jest w ogole
  wczytywany pusty lancuch przez scanw. Dopiero teraz dziala po ustawianiu str na lancuch pusty */

  char str[100];  // Jakas tam dlugosc, nie za krotka.

  echo();           // Aby wprowadzana nazwa pliku pojawiala sie na ekranie

  while (true) {
    *str = 0; // A to po to ze scanw po podaniu enter (lancuch pusty) str w ogole nie jest zmieniany!
    scanw("%99s", str);
//    dumpLancuch(str);

    if (!strlen(str)) {
      break;
    }

    if (istniejePlik(str)) {
      printw("%s", "Plik ");
      printw("%s", str);
      printw("%s", " juz istnieje, prosze podac inna nazwe (pusta oznacza rezygnacje z zapisu do pliku): ");
    } else {
      break;
    }
    //printw("%s", "\nq - wyjscie");
  }

  if (strlen(str)) {
    FILE *ff = fopen(str, "wb");

    if (ff) {
      fputs(haslo.c_str(), ff);
      fclose(ff);

      printw("%s%s%s", "\nHaslo zostalo zostalo zapisane do pliku ", str, ". d - dalej");

      int pomZnak;

      do {
        pomZnak = getch();
      } while (pomZnak != 'd');
    }
  }

  noecho();
}
/*------------------------------------------------------------------------------*/
void generatorHasla() {
  int wybor1 = -1;
  erase();
  MenuClass *menu1 = new MenuClass();
  menu1->Opcja("Haslo utworzone z wszystkich znakow ASCII (od char(32) do char(126)");
  menu1->Opcja("Tylko znaki [a-zA-z0-9] i _");
  menu1->OpcjaWyjscia("Wyjscie");
  wybor1 = menu1->Run();
  delete menu1;
  if (wybor1 == -1) return;

  GeneratorHasla *gh= new GeneratorHasla(wybor1);
  gh->generatorHasla();
  delete gh;
}
/*------------------------------------------------------------------------------*/

