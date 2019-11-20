#include <stdio.h>
#include <time.h>
#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include "ncurses.h"

using namespace std;

class Zegar {
public:
  Zegar();
  ~Zegar();
  void run();
private:
  void pokazCzas();
};

//-----------------------------------------
Zegar::Zegar() {
}
//----------------------------------------
void Zegar::pokazCzas() {
  erase();
  time_t czas = time(NULL);
  
  ostringstream strumien;
  strumien << czas;
  string tresc = "Sekundy od 1 stycznia 1970 ";
  tresc += strumien.str();
  mvaddstr(1, 10, tresc.c_str());

  tm *czasStrukt = localtime(&czas);
  mvprintw(2, 10, "Biezacy czas to %s", asctime(czasStrukt));
  
  mvprintw(3, 10, "seconds after the minute %d", czasStrukt->tm_sec);
  mvprintw(4, 10, "minutes after the hour %d", czasStrukt->tm_min);
  mvprintw(5, 10, "hours since midnight %d", czasStrukt->tm_hour);		
  mvprintw(6, 10, "day of the month %d", czasStrukt->tm_mday);		
  mvprintw(7, 10, "months since January %d", czasStrukt->tm_mon);		
  mvprintw(8, 10, "years sincce 1900 %d", czasStrukt->tm_year);		

  mvprintw(9, 10, "days since Sunday %d", czasStrukt->tm_wday);		
  mvprintw(10, 10, "days since January %d", czasStrukt->tm_yday);		
  mvprintw(11, 10, "Daylight Saving Time flag %d", czasStrukt->tm_isdst);		

  mvaddstr(17, 10, "Wcisnij dowolny klawisz aby wyjsc");
  refresh();
}
//----------------------------------------
void Zegar::run() {
  nodelay(stdscr, TRUE);

  while (getch() == ERR) {  
    pokazCzas();  
    sleep(1);  
  }

  while (getch() != ERR) {};

  nodelay(stdscr, FALSE);
}
//----------------------------------------
Zegar::~Zegar() {
}
//---------------------------------------
void wyswietlanieCzasu() {
  Zegar *sz = new Zegar();
  sz->run();
  delete sz;
}
//-----------------------------------------------------
