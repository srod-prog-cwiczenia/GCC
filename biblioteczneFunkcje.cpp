#include <ncurses.h>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <sstream>
#include "biblioteczneFunkcje.h"
//---------------------------------------------------------
void dumpLancuch(char* str) { // Nie chcial tu przyjac const char
  printw("%s", "\nLancuch:\n");
  char *qq = str;

  while (*qq) {
    printw("%s%d%c", "#", *qq, *qq >= 32 && 126 >= *qq ? *qq : '?');
    qq++;
    printw("%s", " ");
  }    

  printw("%s", "\nDlugosc lancucha: ");
  printw("%d %s", strlen(str), " q - wyjscie z dump.");
 
  int pomZnak;  

  do {
    pomZnak = getch();  
  } while (pomZnak != 'q');
}
//---------------------------------------------------------
void komunikat(string txt) {
  printw("%s", "\n");
  printw("%s", txt.c_str());
  printw("%s", "\nWcisnij d aby przejsc dalej...");
  int pomZnak;

  do {
    pomZnak = getch();  
  } while (pomZnak != 'd');
}
//---------------------------------------------------------
void komunikat(int liczba) {
  string txt;
  ostringstream strumien;
  strumien << liczba;
  txt.append(strumien.str());
  komunikat(txt);
}
//---------------------------------------------------------
void dummy() {
   // TODO: Zrobic jakas ramke wokol tego komunikatu...
  printw("%s", "\nOpcja jest pusta.\nWcisnij d aby przejsc dalej...");
  int pomZnak;

  do {
    pomZnak = getch();  
  } while (pomZnak != 'd');
}
//---------------------------------------------------------
bool pytanieNT(string txt) {
  printw("%s", "\n");
  printw("%s", txt.c_str());
  printw("%s", "\n");
  printw("%s", "t - tak");
  printw("%s", "\n"); 
  printw("%s", "n - nie\n");
  
  int pomZnak;

  do {
    pomZnak = getch();  
  } while (pomZnak != 'n' && pomZnak != 't' && pomZnak != 'N' && pomZnak != 'T');

  return pomZnak == 't' || pomZnak == 'T';
}
//---------------------------------------------------------
string uruchomieniePolecenia(string polecenie) {
  string result; 
  char tmp[1024]; 
  FILE *term = popen(polecenie.c_str(), "r"); 
      
  while ((fgets(tmp, 1024, term)) != 0) { 
    result += string(tmp); 
    tmp[0] = '\0'; 
  /* Ta instrukcja wyzej to pewnie dlatego ze jesli fgets 
     przeczyta cos to zwraca tmp, jesli nie to po prostu zwraca NULL */
  } 

  return result;      
}
//----------------------------------------------------
//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/stat.h>

bool istniejePlik (const char* nazwaPliku) {
  struct stat buf;
        /* Odczytywanie statystyk pliku */
  return  stat(nazwaPliku, &buf) ? false : true;
}
//-------------------------------------------------------
vector<string> lancuch2Vector(const string &lancuch, char separator) {
  vector<string> kawalkiV;
  string kawalek;
  istringstream strumienLancuchowy(kawalek);
  while (getline(strumienLancuchowy, kawalek, separator)) {
    kawalkiV.push_back(kawalek);
  }
  return kawalkiV;
}
//-------------------------------------------------------
