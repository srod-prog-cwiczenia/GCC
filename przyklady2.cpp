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
  cout << "Funkcja lambda liczaca kwadraty:\n";
  auto funkcja = [] (int a)->int {
    return a * a;
  };
  for (int i = 1; i <= 10; i++)
    cout << funkcja (i) << " ";
  cout << endl;
  //+++++++
  int a = 7, b = 13;
  auto f1 = [ a, & b ]()->void
    {//a++; // tej zmiennej nie zmienimy jako parametr, bylby blad kompilacji
     b++;};
  f1();
  cout << a << ' ' << b << '\n';
  //++++ to samo ale mutable:  
  a = 7, b = 13;
  auto f2 = [ a, & b ]()mutable->void 
    {a++; // mutable wiec mozemy ja zwiekszyc ale to nadal kopia lokalna
     b++;};
  f2();
  cout << "teraz mutable: " << a << ' ' << b << '\n';

  std::cout << "\nPodaj jakikolwiek JEDEN znak aby aby zakonczyc... (np 'w' <Enter>)";
  char cc;
  std::cin >> cc; 
    
  doupdate(); // Z powrotem do ncurses
  curs_set(false);
}
//-----------------------------------------------------------
void Przyklady2::wbudowaneStale() {
  cout << "Stała __cplusplus: " << __cplusplus << endl;
}
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
