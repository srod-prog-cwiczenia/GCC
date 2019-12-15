#include <ncurses.h>
#include <iostream>
#include "biblioteczneEkran.h"

//--------------------------
OknoAplikacji::OknoAplikacji() {
  zainicjowanieEkranu();
  startTrybKolorowy();
  winieta();
}
//--------------------------
void OknoAplikacji::winieta() {
  for (int xx = 0; xx < getmaxx(stdscr); xx++) {
    mvaddch(0, xx, ACS_HLINE);
    int y2 = getmaxy(stdscr) - 1;
    mvaddch(y2, xx, ACS_HLINE);
  }
}
//--------------------------
OknoAplikacji::~OknoAplikacji() {
  zwolnienieEkranu();
}
//--------------------------
bool OknoAplikacji::startTrybKolorowy() {
  if (has_colors() == false) {	
    mvaddstr(1, 1, "Twoj terminal prawdopodobnie nie posiada kolorow. Nacisnij q aby przejsc dalej.\n");

    while (getch()!='q') {};

    return false;
  }

  start_color();
  return true;	
}
//---------------------------------------------------
void OknoAplikacji::zainicjowanieEkranu() {
  initscr(); /* inicjalizacja trybu ncurses */
  raw();/* Line buffering disabled */
  keypad(stdscr, true);/* We get F1, F2 etc..*/
  noecho(); /* nie bedzie widac wpisywanych znakow na przyklad przy getch */
  curs_set(false); /* nie pokazuj kursora */
  /* mozna by jeszcze uzywac m.in.:

	cbreak(); - wylacza buferowanie linii
	nonl(); - sterowanie wejsciem
	intrflush(stdscr, FALSE); - sterowanie wejsciem
	keypad(stdscr, TRUE); - sterowanie wejsciem

	*/
}
//--------------------------
void OknoAplikacji::zwolnienieEkranu() {
  curs_set(true); /* pokazuj normalnie kursor */
  endwin(); /* zakoncz */
}
//-----------------------------------------------
//--------------------------------
void OknoAplikacji::ramka(int x1, int  y1, int x2, int y2) {
  mvaddch(y1, x1, ACS_ULCORNER);
  mvaddch(y2, x1, ACS_LLCORNER);  
  mvaddch(y1, x2, ACS_URCORNER);
  mvaddch(y2, x2, ACS_LRCORNER);

  for (int xx = x1 + 1; xx < x2; xx++) {
    mvaddch(y1, xx, ACS_HLINE);
    mvaddch(y2, xx, ACS_HLINE);    
  }

  for (int yy = y1 + 1; yy < y2; yy++) {
    mvaddch(yy, x1, ACS_VLINE);
    mvaddch(yy, x2, ACS_VLINE);    
  }
}
//--------------------------------
void OknoAplikacji::powrotDoTrybuTekstowego() {
  endwin();
}
//--------------------------------
void OknoAplikacji::powrotDoNCurses(bool zZatrzymaniemP) {
  if (zZatrzymaniemP) {
    std::cout << "\nPodaj jakikolwiek JEDEN znak aby aby zakonczyc... (np 'w' <Enter>)";
    char cc;
    std::cin >> cc; 
  }
  doupdate(); // Z powrotem do ncurses
  curs_set(false);
}
//--------------------------------


