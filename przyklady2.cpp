#include "ncurses.h"
#include <iostream>
#include <list>
#include <string>

#include "przyklady2.h"
#include "biblioteczneFunkcje.h"
#include "menuClass.h"

using namespace std;
//--------------- Przeciazanie operatorow 

//----------------------------------------------------------------
void Przyklady2::lambdaFunkcje1() {
  endwin();  // Powrot do zwyklego trybu 'cooked' :)
  //cout << "W tej konfiguracji programu obsluga lambda funkcji nie zostala zaimplementowana." << endl;
  
  auto funkcja = [] (int a)->int {
    return a * a;
  };
  for (int i = 1; i <= 10; i++)
    cout << funkcja (i) << " ";
  cout << endl;
  cout << __cplusplus << endl;
  
  std::cout << "\nPodaj jakikolwiek JEDEN znak aby aby zakonczyc... (np 'w' <Enter>)";
  char cc;
  std::cin >> cc; 
    
  doupdate(); // Z powrotem do ncurses
  curs_set(false);
}
//-----------------------------------------------------------
//----------------------------------------------------------------
void Przyklady2::lambdaFunkcje() {
  int wybor1 = -1;

  do {
    erase();
    MenuClass *menu1 = new MenuClass();
    menu1->Opcja("Lambda funkcje 1");

    menu1->OpcjaWyjscia("Wyjscie");
  
    wybor1 = menu1->Run();

    switch (wybor1) {
      case 0:
        lambdaFunkcje1();
        break;
    } 
       
    delete menu1;
  } while (wybor1 != -1);
}
//-----------------------------------------------------------------}
