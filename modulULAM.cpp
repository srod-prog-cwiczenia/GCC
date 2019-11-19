#include <ncurses.h>
#include <string>
#include "modulULAM.h"

#define MaxX 79
#define MaxY 33

// Konfiguracja programu

struct KonfULAM {
  int DlugoscZycia1; // Gatunek +
  int DlugoscZycia2; // Gatunek -
  int ZawijanieEkranu;
  int KtoryWygrywaWStarciu; // + 1 lub - 1 lub tez 0
  bool PracaKrokowa;
};

static KonfULAM konfULAM = {
  5, 11,
  0,
  1, false};

int t[MaxX][MaxY];
int suma1, suma2;
int getMaxX, getMaxY;
//--------------------------------------
void pokazZnak(int znak, int xp, int yp, int para) {
  attron(COLOR_PAIR(para));
  mvaddch(yp, xp, znak);
  attroff(COLOR_PAIR(para));
}
//---------------------------------------
bool miesciSieNaEkranie(int xp, int yp) {
  return (xp >= 1 && yp >= 1 && xp <= getMaxX && yp <= getMaxY);
}
//---------------------------------------
void Pokazanie() {
  erase();

  for (int x = 0; x < MaxX; x++)
    for (int y = 0; y < MaxY; y++) {
      if (t[x][y] > 0) {
        if (miesciSieNaEkranie(x + 1, y + 1)) {
    	  pokazZnak(ACS_DIAMOND, x + 1, y + 1, 1);
        }
      } else if(t[x][y] < 0) {
        if (miesciSieNaEkranie(x + 1, y + 1)) {	
          pokazZnak('*', x + 1, y + 1, 2);
        }
      }
    }
}

//--------------------------------------
int signum1(int pp) {
 
  if (pp > 1) {
    return 1;
  }
  
  if (pp < - 1) {
    return - 1;
  }

  return 0;
}

//--------------------------------------

int tablica(int xp, int yp) {
  if (konfULAM.ZawijanieEkranu) {
    xp += MaxX;
    xp %= MaxX;

    yp += MaxY;
    yp %= MaxY;
  };

  if (xp < 0 || xp >= MaxX || yp < 0 || yp >= MaxY)
    return 0;

  return t[xp][yp];
}
//--------------------------------------

void Analiza(void)
  {
  for (int x = 0; x < MaxX; x++)
    for (int y = 0; y < MaxY; y++)
      if (t[x][y] > 0)
	t[x][y]++;
      else if(t[x][y] < 0)
	t[x][y]--;

  for (int x = 0; x < MaxX; x++)
    for (int y = 0; y < MaxY; y++)
      {
      if (t[x][y])
	continue;

      int suma1 = 0;
      int suma2 = 0;

      if(signum1(tablica(x - 1, y)) == 1)
	suma1++;

      if(signum1(tablica(x - 1, y)) == - 1)
	suma2++;

      if(signum1(tablica(x + 1, y)) == 1)
	suma1++;

      if(signum1(tablica(x + 1, y)) == - 1)
	suma2++;

      if(signum1(tablica(x, y - 1)) == 1)
	suma1++;

      if(signum1(tablica(x, y - 1)) == - 1)
	suma2++;

      if(signum1(tablica(x, y + 1)) == 1)
	suma1++;

      if(signum1(tablica(x, y + 1)) == - 1)
	suma2++;

      if(suma1 == 1 && suma2 == 0)
	t[x][y] = 1;

      if(suma1 == 0 && suma2 == 1)
	t[x][y] = - 1;

      if(suma1 == 1 && suma2 == 1)
	t[x][y] = konfULAM.KtoryWygrywaWStarciu;
      }

  for (int x = 0; x < MaxX; x++)
    for (int y = 0; y < MaxY; y++)
      {
      if(t[x][y] == konfULAM.DlugoscZycia1)
	t[x][y] = 0;

      if(t[x][y] == - konfULAM.DlugoscZycia2)
	t[x][y] = 0;
      }

  }

//--------------------------------------

void funkcjaUlam() {
//  _setcursortype(_NOCURSOR);
  erase();
  getMaxX = getmaxx(stdscr);
  getMaxY = getmaxy(stdscr);

  start_color(); // TODO: 
    //Oczywiscie, trzeba przedtem wykryc czy terminal obsluguje kolorki, najlepiej to zrobic we wspolnej bibliotece.
  
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);

  for (int x = 0; x < MaxX; x++)
    for (int y = 0; y < MaxY; y++)
      t[x][y] = 0;

  t[MaxX / 5 * 4][MaxY / 5 * 4] = 1;

  t[MaxX / 3 * 2][MaxY / 2] = - 1;
  t[MaxX / 2][MaxY / 3 * 2] = - 1;

  Pokazanie();

  int znak = 0;

 /* while (konf.ULAM.PracaKrokowa ?  znak != 27 : !kbhit()) {
    Analiza();
    Pokazanie();

    if (konfULAM.PracaKrokowa) {
      while(!kbhit());
      while(kbhit())
	znak = getch();
      }
    else {
      delay(50);
    }
  }*/ // Te partie programu trzebanapisac inaczej

  do {
    Analiza();
    Pokazanie();
    znak = getch();
  } while (znak != 'q');
}

