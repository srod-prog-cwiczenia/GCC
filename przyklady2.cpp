#include "ncurses.h"
#include <iostream>
#include <list>
#include <string>

#include "przyklady2.h"
#include "biblioteczneFunkcje.h"
#include "menuClass.h"

using namespace std;
//--------------- Klasa z rozwiazaniami zadan ze wskaznikow (napisana w stylu `a la Java :) ):
class WskaznikiPrzyklady2 {
    public:
        static string format(string txt) {
	   return txt + ".";
        }; 
	static void zadanieZeWskaznikow() {
                endwin();  // Powrot do zwyklego trybu 'cooked' :)

		int tab[] = { 1,2,3,10 };
		//przesumować zawartosc tej tablicy za pomoca wskaznikow
		int suma = 0;
		int *wi = tab;
		for (int i : tab) {
			suma += *wi++;
		}
		cout << "Suma: " << suma << endl;
// zdefiniowac tablice wskaznikow : int *tabP[10],
		//utworzyć je w pętli i potem użyć delete w pętli;
		int *tabP[10];//tablica wskaników na liczby całkowite
		for (int i = 0; i < 10; i++) {
			tabP[i] = new int;
			*tabP[i] = i * i;
		}
		for (int i = 0; i < 10; i++)
			cout << *tabP[i] << " ";
		cout << endl;
		for (int i = 0; i < 10; i++)
			delete tabP[i];
// za pomoca wskaznikow wypelnic tablice
		// int tM[10][10]; 
		// iloczynami indeksow
		int tM[10][10];
		int *wI = (int *)tM;
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++) {
				*wI = i * j;
				wI++;
			}
		cout << "tabliczka mnożenia: \n";
		for (int i = 0; i < 10; i++,cout<<endl) {
			for (int j = 0; j < 10; j++) {
				cout << tM[i][j] << " ";
			}	
		}
                std::cout << "\nPodaj jakikolwiek JEDEN znak aby aby zakonczyc... (np 'w' <Enter>)";
                char cc;
                std::cin >> cc; 
                doupdate(); // Z powrotem do ncurses
                curs_set(false);
	}
	static void wskaznikiNaFunkcje() {
                endwin();  // Powrot do zwyklego trybu 'cooked' :)

		string (*formatZ)(string);
		string(*formatZ2)(string);
		formatZ = format;
		formatZ2 = formatZ;
		cout << formatZ2("Ala");
//TODO: z obslugi zwiazanej z ncurses najlepiej zrobic jakas warstwe,
// tymczasem mozna przeniesc te powtarzajace sie sekwencje do jednej metody (w zasadzie dwoch, patrz 
// poczatek tej metody :) 
		std::cout << "\nPodaj jakikolwiek JEDEN znak aby aby zakonczyc... (np 'w' <Enter>)";
                char cc;
                std::cin >> cc; 
                doupdate(); // Z powrotem do ncurses
                curs_set(false);

	}
};

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
  int aa = 7, bb = 13;
  auto f1 = [ aa, & bb ]()->void
    {//aa++; // tej zmiennej nie zmienimy jako parametr, bylby blad kompilacji
     bb++;};
  f1();
  cout << "Po wyjsciu z funkcji f1: " << aa << ' ' << bb << endl;
  //++++ to samo ale mutable:  
  aa = 7, bb = 13;
  auto f2 = [ aa, & bb ]()mutable->void 
    {aa++; // mutable wiec mozemy ja zwiekszyc ale to nadal kopia lokalna
     bb++;
     cout << "W funkcji f2 (teraz uzyto modyfikator mutable): " << aa << ' ' << bb << endl;
     };
  f2();
  cout << "Po wyjsciu z funkcji f2 (teraz uzyto modyfikator mutable): " << aa << ' ' << bb << endl;

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
//TODO: stworzyc oddzielne menu na zadania ze wskaznikow:
    menu1->Opcja("Zadania ze wskaznikow - suma i tabliczka mnozenia przez wskazniki");
    menu1->Opcja("Zadania ze wskaznikow - test wskaznikow na funkcje");
    menu1->OpcjaWyjscia("Wyjscie");
    menu1->ustawienieWersji(wmDrabinka);  
    wybor1 = menu1->Run();

    switch (wybor1) {
      case 0:
        lambdaFunkcje1();
        break;
      case 1: 
        WskaznikiPrzyklady2::zadanieZeWskaznikow(); 
        break;
      case 2: 
        WskaznikiPrzyklady2::wskaznikiNaFunkcje(); 
        break;
    } 
       
    delete menu1;
  } while (wybor1 != -1);
}
//-----------------------------------------------------------------}
