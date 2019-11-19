#include <ncurses.h>
#include <math.h>
#include <string.h>
#include <list>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "menuClass.h"
#include "biblioteczneFunkcje.h"
#include "biblioteczneEkran.h"

#include "showTablica.h"
//-----------------------------------------------------------------------
void ShowTablica::show(int xpocz, int ypocz, int rozmiar, int ziarnistosc, 
  int **tab, bool kratownica) {
  if (kratownica) {
    assert(!"Na razie nie jest zaimplementowana opcja z kratownica!");
  }
  int xrog = xpocz + 1; // na wiersz ze wspolrzednymi liczbowymi
  int yrog = ypocz;

  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  
  OknoAplikacji::ramka(xrog - 1, yrog - 1, xrog - 1 + ziarnistosc * rozmiar + 1, 
    yrog - 1 + ziarnistosc * rozmiar + 1);
    
  for (int xx = 0; xx < rozmiar; xx++)
    for (int yy = 0; yy < rozmiar; yy++) {
      if (tab[xx][yy]) {
        attron(COLOR_PAIR(1));
        for (int deltax = 0; deltax < ziarnistosc; deltax++)
          for (int deltay = 0; deltay < ziarnistosc; deltay++)
            mvaddch(ziarnistosc * (rozmiar - yy) - 1 - deltay + yrog, ziarnistosc * xx + deltax + xrog, ACS_DIAMOND);
        
        attroff(COLOR_PAIR(1));
        continue;      
      }
      for (int deltax = 0; deltax < ziarnistosc; deltax++)
        for (int deltay = 0; deltay < ziarnistosc; deltay++)
          mvaddch(ziarnistosc * (rozmiar - yy) - 1 - deltay + yrog, ziarnistosc * xx + deltax + xrog, '.');      
    }  

  for (int xx = 0; xx < rozmiar; xx++) {
    mvaddch(rozmiar * ziarnistosc + 1 + yrog, xrog + ziarnistosc * xx, 'A' + xx);
  }

  for (int yy = 0; yy < rozmiar; yy++) {
    mvaddch(yrog + ziarnistosc * (rozmiar - yy) - 1, xrog - 2, yy < 9 ? '1' + yy : 'A' + (yy - 9));
  }
}
//-----------------------------------------------------------------------
void ShowTablica::test() {
  erase(); 
  int tabL[20][20];
  for (int qx = 0; qx < 20; qx++) 
    for (int qy = 0; qy < 20; qy++) 
      tabL[qx][qy] = (qx + qy) % 6 == 2; 
  
  int *ptab[20];
  for (int qx = 0; qx < 20; qx++)
    ptab[qx] = tabL[qx];

  show(1, 1, 8, 1, ptab);
  move(getmaxy(stdscr) / 2 + 10, 2);
  dummy();

  erase();
  show(1, 1, 15, 1, ptab);
  move(getmaxy(stdscr) / 2 + 10, 2);
  dummy();

  erase();
  show(1, 1, 8, 2, ptab);
  move(getmaxy(stdscr) / 2 + 10, 2);
  dummy();

}
//-----------------------------------------------------------------------
void ShowTablica::test1() {
  // to przyklad na tablice 2D, do przeniesienia gdzies indziej no i do wnikliwego przeanalizowania :-)
  erase(); 
  int tabL[5][10];
  for (int qx = 0; qx < 5; qx++) 
    for (int qy = 0; qy < 10; qy++) {
//      if ((qx + qy) % 6 == 2) {
        tabL[qx][qy] = 100 * qx + qy;
//      }
    }
  //TODO: to koniecznie do dokonczenia, tudziez to i wyzej!!!
  int (*pt)[10] = tabL;
  for (int qq = 0; qq < 5; qq++) {
    int *ptt = *(pt++);
    for (int qqq = 0; qqq < 10; qqq++)
      printw("%d %s", *(ptt++), " ");
  }
  dummy();
}
//----------------------------------------------------------------------- 
