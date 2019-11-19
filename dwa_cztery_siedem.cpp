#include <ncurses.h>
#include <string>
#include "menuClass.h"
#include "teoriaLiczb.h"

using namespace std;

#define DUZA_LICZBA 1000000000

int tab[10];
int *przegroda;
int *tu; 
int *koniec;
int kandydat;

typedef struct {
  long int liczba1;
  long int liczba2;
  long int roznica;
} Znalezione; 

Znalezione znalezione;
Znalezione *odp;

/*---------------------------------------------*/
int poprawny_fragment(int *g1, int *g2){
  int tak;
  tak = 1;
 
  int *p1, *p2;

  for(p2 = g1 + 1; p2 <= g2; p2++){
    for(p1 = g1; p1 < p2; p1++){
      tak = tak && (*p1 != *p2);
    }
  }

return(tak);  
}
/*--------------------------------------------------------*/
int akcja(int *g1, int *g2){
  int *pp;  
  for(pp = g1; pp <= g2; pp++)
    printf("%d", *pp);
    
    printf("%s", "\n");
  return(0);
}
/*--------------------------------------------------------*/
long int odczytanie_liczby(int *g1, int *g2){
  long int liczba;
  long int mnoznik;
  int *pp;

  liczba = 0;
  mnoznik = 1;
  for(pp = g2; pp >= g1; pp--){
    liczba += mnoznik * *pp;
    mnoznik *= 10;
  }
  return(liczba);
}
/*--------------------------------------------------------*/
long int przeszukanie_mozliwych_liczb(int *g1, int *g2, 
 Znalezione *odp1){
  int *pp;
  long int odstep, liczba1, liczba2;

  for(pp = g1; pp < g2; pp++){
    liczba1 = odczytanie_liczby(g1, pp);
    liczba2 = odczytanie_liczby(pp + 1, g2); 

    odstep = liczba1 > liczba2 ? liczba1 - liczba2 : liczba2 - liczba1;
//To oczywiscie abs ale na niektorych wersjach C++ nie chce sie to cholerstow zlinkowac - no i jak sobie z tym poradzic?
//TODO: Wyjasnic dlaczego tak jest?
    if(odp1->roznica > odstep){
      odp1->liczba1 = liczba1;
      odp1->liczba2 = liczba2;
      odp1->roznica = odstep; 
    }
  }
}

/*--------------------------------------------------------*/

int szukanie_kandydata(int *g1, int *g2){
  int k;
  int *pp;
  int ok;
  kandydat = -1;
  
  for(k = *g2 + 1; k < 10; k++){
    ok = 1;

    for(pp = g1; pp < g2; pp++){
      if(*pp == k){
	ok = 0;
	break;
      }
    }
    if(ok)
      return(k);

  }

  return(-1);
}

/*=========================================================*/

void dwa_cztery_siedem() {
  odp = &znalezione;
  odp->liczba1 = 0;
  odp->liczba2 = 0;
  odp->roznica = DUZA_LICZBA; 
  koniec = tab + 9;
  tu = tab;
  *tu = -1;

  while(tu >= tab){
    while((tu >= tab) && (kandydat = szukanie_kandydata(tab, tu)) == -1)
      tu--;
  
    if(tu >= tab){
      *tu = kandydat;
      if(tu < koniec)
	*(++tu) = -1; 
      else{
	/*akcja(tab, koniec);*/
	przeszukanie_mozliwych_liczb(tab, koniec, odp);
      }
    }
  }

  erase();

  printw("%s", "\nLiczba 1:\t");
  printw("%ld", odp->liczba1);

  printw("%s", "\nLiczba 2:\t");
  printw("%ld", odp->liczba2);

  printw("%s", "\nRoznica:\t");
  printw("%ld", odp->roznica);

  printw("%s", "\n");
  printw("%s", "q - Wyjscie\n");
  
  while(getch() != 'q'){
  }
}
  
