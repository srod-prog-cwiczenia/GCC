#include <ncurses.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "menuClass.h"
#include "biblioteczneFunkcje.h"
#include "biblioteczneEkran.h"
#include "analizaWsteczna.h"

//=======================================================================
//-----------------------------------------------------------------------
AnalizaWsteczna::AnalizaWsteczna() {
  clearOceny();
  pra = new PrawidlaRuchu();
}
//-----------------------------------------------------------------------
AnalizaWsteczna::~AnalizaWsteczna() {
  delete pra;
}
//-----------------------------------------------------------------------
void AnalizaWsteczna::clearOceny() {
  for (int xb1 = 0; xb1 < 8; xb1++)
    for (int yb1 = 0; yb1 < 8; yb1++)
      for (int xb2 = 0; xb2 < 8; xb2++)
        for (int yb2 = 0; yb2 < 8; yb2++)
          for (int xc1 = 0; xc1 < 8; xc1++)
            for (int yc1 = 0; yc1 < 8; yc1++) {
              oB[xb1][yb1][xb2][yb2][xc1][yc1] = oC[xb1][yb1][xb2][yb2][xc1][yc1] = 0;
            }    
              
}
//-----------------------------------------------------------------------
bool AnalizaWsteczna::isOcena() {
  bool ken = false;
  for (int xb1 = 0; xb1 < 8; xb1++)
    for (int yb1 = 0; yb1 < 8; yb1++)
      for (int xb2 = 0; xb2 < 8; xb2++)
        for (int yb2 = 0; yb2 < 8; yb2++)
          for (int xc1 = 0; xc1 < 8; xc1++)
            for (int yc1 = 0; yc1 < 8; yc1++) {
              ken = ken || oB[xb1][yb1][xb2][yb2][xc1][yc1] || oC[xb1][yb1][xb2][yb2][xc1][yc1];
            }    
  return ken;            
}
//-----------------------------------------------------------------------
void AnalizaWsteczna::analiza() {
  Stan st;
  Kto oso;
  erase();

  printw("%s", "Zaczynam kasowanie...");
  clearOceny();
 
  printw("%s", "Skasowalem");

//tu ustawianie od razu zwycieskich
  for (int kto = 0; kto < 2; kto++) {
    switch (kto) {
      case 0:
        oso = bialy; break;
      case 1:
        oso = czarny; break;
    }
    
    for (int xb1 = 0; xb1 < 8; xb1++)
      for (int yb1 = 0; yb1 < 8; yb1++)
        for (int xb2 = 0; xb2 < 8; xb2++)
          for (int yb2 = 0; yb2 < 8; yb2++)
            for (int xc1 = 0; xc1 < 8; xc1++)
              for (int yc1 = 0; yc1 < 8; yc1++) {
                if (!createStan(xb1, yb1, xb2, yb2, xc1, yc1, &st)) // Nieprawidlowy stan, wiec dalej
                  continue;  

                if (isZwycieskiRuch(&st, oso)) {
                  setOcena(&st, oso, 1);
                }
              }
  }

  printw("%s", "Ustawienie poczatkowych"); //Dotad jak sie wydaje dziala OK.

// Hm, czemu tu jest 100? Pewnie jest wziete ,,z sufitu'' :)
//TODO: anyway trzeba to zmienic na wieksza liczbe. a moze na
// nieskonczonosc? - zmieniam na 200, jak sie sprawdzi to mozna to zapelic ,,w nieskoczonosc''
  for (int licznik = 1; licznik <= 200; licznik++) {
    printw("%d %s", licznik, ".\n");  
// Zasadniczy przebieg analizy
    bool bylaKorekta = false;

    for (int kto = 0; kto < 2; kto++) {
      switch (kto) {
        case 0:
          oso = bialy; break;
        case 1:
          oso = czarny; break;
      }
    
      for (int xb1 = 0; xb1 < 8; xb1++)
        for (int yb1 = 0; yb1 < 8; yb1++)
          for (int xb2 = 0; xb2 < 8; xb2++)
            for (int yb2 = 0; yb2 < 8; yb2++)
              for (int xc1 = 0; xc1 < 8; xc1++)
                for (int yc1 = 0; yc1 < 8; yc1++) {
                  if (!createStan(xb1, yb1, xb2, yb2, xc1, yc1, &st))
                    continue;//Nieprawidlowy stan, wiec dalej
                  
                  if (isZwycieskiRuch(&st, oso)) {
                    continue;  //Tego nie mam co oceniac bo i tak sie zmieni :)   
                  }
                          
                  int zastanaOcena = getOcena(&st, oso);
                  int wynikowaOcena = 0;
                  int najlepszaUjemna = 0;
                  int najlepszaDodatnia = 0;
                  bool bylaZerowa = false;
                  ListaStanow *ls = getMozliweRuchy(&st, oso);                
                  ListaStanow::iterator it;

                  for (it = ls->begin(); it != ls->end(); it++) {
                    Stan st_it = *it;
                    int pom = getOcena(&st_it, oso == bialy ? czarny : bialy);
                  
                    if (pom < 0) {
                      najlepszaUjemna = 
                        najlepszaUjemna ? (najlepszaUjemna < pom ? pom : najlepszaUjemna)
                          : pom;                  
                    }

                    if (pom > 0) {
                      najlepszaDodatnia = 
                        najlepszaDodatnia ? (najlepszaDodatnia < pom ? pom : najlepszaDodatnia)
                          : pom;                  
                    }
                  
                    bylaZerowa = bylaZerowa || !pom;
                  }

                  delete ls;

                  if (najlepszaUjemna) {
                    wynikowaOcena = - najlepszaUjemna + 1;
                  } else if (bylaZerowa) {
                    wynikowaOcena = 0;  
                  } else if (najlepszaDodatnia) {
                    wynikowaOcena = - najlepszaDodatnia - 1;
                  } else {
                  //Powazny blad!!
                  }

// Korekta do nowej oceny
                  if (zastanaOcena != wynikowaOcena) {
                    setOcena(&st, oso, wynikowaOcena);
                    bylaKorekta = true; 
                  }  
                }    
    }
    if (!bylaKorekta) {
      break;
    }
  }
}
//-----------------------------------------------------------------------
// Jesli stan wyjdzie nieprawidlowy to zwraca false!
bool AnalizaWsteczna::createStan(int xb1, int yb1, int xb2, int yb2, int xc1, int yc1, Stan *st) {
  if (xb1 == xb2 && yb1 == yb2)
    return false;

  st->c1.x = xc1;
  st->c1.y = yc1;

  if (xb1 == xc1 && yb1 == yc1) {
    st->b1.x = st->b1.y = DUMMY;  
  } else {
    st->b1.x = xb1; 
    st->b1.y = yb1; 
  }

  if (xb2 == xc1 && yb2 == yc1) {
    st->b2.x = st->b2.y = DUMMY;  
  } else {
    st->b2.x = xb2; 
    st->b2.y = yb2; 
  }
  
  return true;
}
//-----------------------------------------------------------------------
// Zakladamy ze stan jest poprawny!
// Jesli na przyklad nie ma b1 to jego wspolrzedne wybieramy jako takie same jak c1
// (ten ostatni musi istniec zawsze, o ile jest stan poprawny).
int AnalizaWsteczna::getOcena(Stan *st, Kto oso) {
  int xb1, yb1, xb2, yb2, xc1, yc1;

  xc1 = st->c1.x;
  yc1 = st->c1.y;  

  if (isPustePole(&st->b1)) {
    xb1 = xc1;
    yb1 = yc1;
  } else {
    xb1 = st->b1.x;
    yb1 = st->b1.y; 
  }

  if (isPustePole(&st->b2)) {
    xb2 = xc1;
    yb2 = yc1;
  } else {
    xb2 = st->b2.x;
    yb2 = st->b2.y; 
  }


  switch (oso) {
    case bialy:
      return oB[xb1][yb1][xb2][yb2][xc1][yc1];
//      break;
    case czarny:
      return oC[xb1][yb1][xb2][yb2][xc1][yc1];
//      break;
  }  
}
//-----------------------------------------------------------------------
void AnalizaWsteczna::setOcena(Stan *st, Kto oso, int ocena) {
  int xb1, yb1, xb2, yb2, xc1, yc1;

  xc1 = st->c1.x;
  yc1 = st->c1.y;  

  if (isPustePole(&st->b1)) {
    xb1 = xc1;
    yb1 = yc1;
  } else {
    xb1 = st->b1.x;
    yb1 = st->b1.y; 
  }

  if (isPustePole(&st->b2)) {
    xb2 = xc1;
    yb2 = yc1;
  } else {
    xb2 = st->b2.x;
    yb2 = st->b2.y; 
  }


  switch (oso) {
    case bialy:
      oB[xb1][yb1][xb2][yb2][xc1][yc1] = ocena;
      break;
    case czarny:
      oC[xb1][yb1][xb2][yb2][xc1][yc1] = ocena;
      break;
  }  
}
//-----------------------------------------------------------------------
bool AnalizaWsteczna::isPustePole(Pole *po) {
  return po->x == DUMMY || po->y == DUMMY;
}
//-----------------------------------------------------------------------
// Sprawdza czy istnieje zwycieski ruch od razu w tym posunieciu
bool AnalizaWsteczna::isZwycieskiRuch(Stan *st, Kto oso) {
  switch (oso) {
    case bialy:
      return !isPustePole(&st->b1) && isConnected(&st->b1, &st->c1, b1) || 
        !isPustePole(&st->b2) && isConnected(&st->b2, &st->c1, b2); 
    case czarny:  
      return isPustePole(&st->b2) && !isPustePole(&st->c1) && isConnected(&st->c1, &st->b1, c1) || 
        isPustePole(&st->b1) && !isPustePole(&st->c1) && isConnected(&st->c1, &st->b2, c1);
  }
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
/* Sprawdza czy pola sa rozne. Traktujemy puste pola jak NULLe czyli sa zawsze od siebie rozne
   i kazdy NULL jest rozny od not NULLa */
bool AnalizaWsteczna::isRoznePola(Pole *p1, Pole *p2) {
  return isPustePole(p1) || isPustePole(p2) || p1->x != p2->x || p1->y != p2->y;
}
//-----------------------------------------------------------------------
/* Sprawdzenie czy stan jest poprawny. */
bool AnalizaWsteczna::isValidStan(Stan *st) {
  bool ok = !isPustePole(&st->b1) || !isPustePole(&st->b2);
  ok = ok && !isPustePole(&st->c1);
  ok = ok && isRoznePola(&st->b1, &st->b2);
  ok = ok && isRoznePola(&st->b1, &st->c1);
  ok = ok && isRoznePola(&st->b2, &st->c1);
  return ok;
}
//-----------------------------------------------------------------------
bool AnalizaWsteczna::isConnected(Pole *skad, Pole *dokad, Figura fig) {
  /* To funkcja ktora podaje czy mozna sie przesunac z pola skad na pole dokad
     za pomoca figury fig. metoda ta ma byc wymienna, to znaczy powinna w sumie byc
     zapodawana podczas startu tej klasy. Na razie jdank cos tam zaszyjemy na poczatek...*/
/*  switch (fig) {
    case b1:
      isConnectedK(skad, dokad);
      break;
    case b2:
      isConnectedK(skad, dokad);
      break;
    case c1:
      isConnectedK(skad, dokad);
      break;
//TODO: dodac jakis internal error na wypadek nieoprogramowanej figury
  }*/
  pra->isConnected(skad, dokad, fig);
}
//-----------------------------------------------------------------------
bool AnalizaWsteczna::isConnectedK(Pole *skad, Pole *dokad) {
  if (skad->x == dokad->x && skad->y == dokad->y)
    return false;
  return abs(skad->x - dokad->x) <= 1 && abs(skad->y - dokad->y) <= 1;
}
//-----------------------------------------------------------------------
bool AnalizaWsteczna::isConnectedH(Pole *skad, Pole *dokad) {
  return (skad->x - dokad->x == 1 || skad->x - dokad->x == -1) &&
    (skad->y - dokad->y == 1 || skad->y - dokad->y == -1);
}
//-----------------------------------------------------------------------
/* Generuje liste mozliwych stanow ktore sa osiagalne z zadanego stanu.
Zakladamy naturalnie ze:
1. Stan jest poprawny;
2. Nie ma mozliwosci zwycieskiego ruchu. */
ListaStanow *AnalizaWsteczna::getMozliweRuchy(Stan *st, Kto oso) {
  ListaStanow *ls = new ListaStanow();
  Pole polePom;
  Stan stanPom;

  switch (oso) {
    case czarny: {
      for (int xx = 0; xx < 8; xx++)
        for (int yy = 0; yy < 8; yy++) {
          if (xx == st->c1.x && yy == st->c1.y)
            continue;
        
          polePom.x = xx;
          polePom.y = yy;

          if (!isConnected(&st->c1, &polePom, c1))
            continue;

          stanPom.c1.x = xx;  // miejsce docelowe
          stanPom.c1.y = yy;
          
          if (!isRoznePola(&polePom, &st->b1)) {
            stanPom.b1.x = DUMMY;  // zbijamy go
            stanPom.b1.y = DUMMY;
          } else {
            stanPom.b1.x = st->b1.x;
            stanPom.b1.y = st->b1.y;
          }
        
          if (!isRoznePola(&polePom, &st->b2)) {
            stanPom.b2.x = DUMMY;  // zbijamy go
            stanPom.b2.y = DUMMY;
          } else {
            stanPom.b2.x = st->b2.x;
            stanPom.b2.y = st->b2.y;
          }
        
          ls->push_back(stanPom); 
        }        
  
      break;
    }
    case bialy: {
      if (!isPustePole(&st->b1))
        for (int xx = 0; xx < 8; xx++)
          for (int yy = 0; yy < 8; yy++) {
            if (xx == st->b1.x && yy == st->b1.y)
              continue;

            if (xx == st->b2.x && yy == st->b2.y)
              continue;
        
            polePom.x = xx;
            polePom.y = yy;

            if (!isConnected(&st->b1, &polePom, b1))
              continue;

            stanPom.b1.x = xx;  // miejsce docelowe
            stanPom.b1.y = yy;
   
            stanPom.b2.x = st->b2.x;
            stanPom.b2.y = st->b2.y;
        
            stanPom.c1.x = st->c1.x;
            stanPom.c1.y = st->c1.y;
                  
            ls->push_back(stanPom); 
          }

      if (!isPustePole(&st->b2))        
        for (int xx = 0; xx < 8; xx++)
          for (int yy = 0; yy < 8; yy++) {
            if (xx == st->b1.x && yy == st->b1.y)
              continue;

            if (xx == st->b2.x && yy == st->b2.y)
              continue;
        
            polePom.x = xx;
            polePom.y = yy;

            if (!isConnected(&st->b2, &polePom, b2))
              continue;
  
            stanPom.b1.x = st->b1.x;
            stanPom.b1.y = st->b1.y;

            stanPom.b2.x = xx;  // miejsce docelowe
            stanPom.b2.y = yy;
        
            stanPom.c1.x = st->c1.x;
            stanPom.c1.y = st->c1.y;
                  
            ls->push_back(stanPom); 
          }        
     
      break;
    }
  }

  return ls;
}
//-----------------------------------------------------------------------
PrawidlaRuchu::PrawidlaRuchu() {
  for (int xx = 0; xx < MAX_ROZ_PLANSZY_PRAWIDLA; xx++) 
    for (int yy = 0; yy < MAX_ROZ_PLANSZY_PRAWIDLA; yy++) 
      b1Pla[xx][yy] = 0;
  for (int xx = 0; xx < MAX_ROZ_PLANSZY_PRAWIDLA; xx++) 
    for (int yy = 0; yy < MAX_ROZ_PLANSZY_PRAWIDLA; yy++) 
      b2Pla[xx][yy] = 0;
  for (int xx = 0; xx < MAX_ROZ_PLANSZY_PRAWIDLA; xx++) 
    for (int yy = 0; yy < MAX_ROZ_PLANSZY_PRAWIDLA; yy++) 
      c1Pla[xx][yy] = 0;
/*  b2Pla[SRODEK_PLANSZY - 1][SRODEK_PLANSZY - 1] = 1;
  b2Pla[SRODEK_PLANSZY + 1][SRODEK_PLANSZY - 1] = 1;
  b2Pla[SRODEK_PLANSZY - 1][SRODEK_PLANSZY + 1] = 1;
  b2Pla[SRODEK_PLANSZY + 1][SRODEK_PLANSZY + 1] = 1;*/
// ustawienie skoczka:
  for (int xx = 0; xx < MAX_ROZ_PLANSZY_PRAWIDLA; xx++) 
    for (int yy = 0; yy < MAX_ROZ_PLANSZY_PRAWIDLA; yy++)  
      if (abs(xx - SRODEK_PLANSZY) + abs(yy - SRODEK_PLANSZY) == 3 && xx != SRODEK_PLANSZY 
       && yy != SRODEK_PLANSZY)
        b2Pla[xx][yy] = 1;
  
  for (int xx = -1; xx <= 1 ; xx++) 
    for (int yy = -1; yy <= 1; yy++) 
      if (xx != 0 || yy != 0)
        b1Pla[SRODEK_PLANSZY + xx][SRODEK_PLANSZY + yy] = 1;
/*  for (int xx = -1; xx <= 1 ; xx++) 
    for (int yy = -1; yy <= 1; yy++) 
      if (xx != 0 || yy != 0)
        b2Pla[SRODEK_PLANSZY + xx][SRODEK_PLANSZY + yy] = 1;*/
  for (int xx = -1; xx <= 1 ; xx++) 
    for (int yy = -1; yy <= 1; yy++) 
      if (xx != 0 || yy != 0)
        c1Pla[SRODEK_PLANSZY + xx][SRODEK_PLANSZY + yy] = 1;
}
//-----------------------------------------------------------------------
PrawidlaRuchu::~PrawidlaRuchu() {
}
//-----------------------------------------------------------------------
bool PrawidlaRuchu::isConnected(Pole *skad, Pole *dokad, Figura fig) {
  int polozenieX = dokad->x - skad->x + SRODEK_PLANSZY;
  int polozenieY = dokad->y - skad->y + SRODEK_PLANSZY;
  if (polozenieX <= 0 || polozenieY <= 0 || MAX_ROZ_PLANSZY_PRAWIDLA <= polozenieX ||
   MAX_ROZ_PLANSZY_PRAWIDLA <= polozenieY)
    return false;
  
  switch (fig) {
    case b1:
      return b1Pla[polozenieX][polozenieY];
    case b2:
      return b2Pla[polozenieX][polozenieY];    
    case c1:
      return c1Pla[polozenieX][polozenieY];    
    default:
      assert(!"Niezdefiniowana figura w switch-u!");
  }
}
//-----------------------------------------------------------------------

