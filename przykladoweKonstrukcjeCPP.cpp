#include "ncurses.h"
#include <iostream>
#include <list>
#include <string>

#include "przykladoweKonstrukcjeCPP.h"
#include "biblioteczneFunkcje.h"
#include "menuClass.h"
#include "przyklady2.h"

using namespace std;
//--------------- Przeciazanie operatorow 

class DwieDane {
  int nr;
  double liczba;

  public:
    DwieDane(int i = 0, double li = 0.0) {
      nr = i;
      liczba = li;
    };

  friend ostream & operator<< (ostream &wyjscie, const DwieDane &klasa);
};

//----------------- Przeciazenie operatora wyjscia

ostream & operator<< (ostream &wyjscie, const DwieDane &klasa) {
  wyjscie << "Liczba porzadkowa: " << klasa.nr << endl << 
    "Liczba rzeczywista: " << klasa.liczba << endl;
  return wyjscie;
}

//-------------------------- Przyklad na referancje w jezyku C++:

void nie_zwieksz(int i) {
   ++i; // tak naprawde funkcja nie robi nic, bo zmieniona zostaje tylko lokalna kopia
}
//-----------------------------
void zwieksz_c(int *i)
{
   ++(*i); // ta funkcja jest napisana w stylu C
}
//-------------------------------
void zwieksz_cpp(int& i)
{
   ++i; // ta funkcja wykorzystuje mozliwosci C++
}

//-------------------------- Obsluga list

typedef list<int> mojalista;

//--------------------------------------- A tu przyklad na szablony


template< class Typ > // definicja szablonu klasy
class MojaKlasa {
  public:
    MojaKlasa( Typ wartoscPoczatkowa ) {
      zawartosc = wartoscPoczatkowa;
    }
    Typ funkcja();
  void wydrukowanieCalkowite();
  void wydrukowanie();
  Typ zawartosc;
  int zwyklySkladnik; // zwykly skladnik zawsze typu int
};

template< class Typ >
Typ MojaKlasa<Typ>::funkcja(){
     Typ zmienna;
     return zmienna;   
 }


template< class Typ >
void MojaKlasa<Typ>::wydrukowanieCalkowite(){
  int dodruku;
  dodruku = int(zawartosc);
  printf("%d", dodruku);

}

template< class Typ >
void MojaKlasa<Typ>::wydrukowanie(){
  std::cout << zawartosc;
  
}

//--------------------------------------
void przykladyDzialanNaLancuchach() {
  endwin();
  //  Przyklady dotyczace lancuchow:
  string a("abcd efg");
  string b("xyz ijk");
  string c;

  cout << a << " " << b << endl;                        // Output: abcd efg xyz ijk

  cout << "String empty: "    << c.empty()    << endl;  // String empty: 1 
                                                         // Is string empty? Yes it is empty. (TRUE)
  c = a + b;                                            // concatenation
  cout << c << endl;                                    // abcd efgxyz ijk
  cout << "String length: "   << c.length()   << endl;  // String length: 15
  cout << "String size: "     << c.size()     << endl;  // String size: 15
  cout << "String capacity: " << c.capacity() << endl;  // String capacity: 15
  cout << "String empty: "    << c.empty()    << endl;  // String empty: 0 
                                                         // Is string empty? No it is NOT empty. (FALSE)
  string d = c;
  cout << d << endl;                                    // abcd efgxyz ijk

                                                         // First character: a
  cout << "First character: " << c[0] << endl;          // Strings start with index 0 just like C.

  string f("    Leading and trailing blanks      ");
  cout << "String f:" << f << endl;
  cout << "String length: " << f.length() << endl;      // String length: 37
  cout << "String f:" << f.append("ZZZ") << endl;       // String f:    Leading and trailing blanks      ZZZ
  cout << "String length: " << f.length() << endl;      // String length: 40

  string g("abc abc abd abc");
  cout << "String g: " << g << endl;                    // String g: abc abc abd abc
  cout << "Replace 12,1,\"xyz\",3: " << g.replace(12,1,"xyz",3) << endl;  // Replace 12,1,"xyz",3: abc abc abd xyzbc
  cout << g.replace(0,3,"xyz",3) << endl;               // xyz abc abd xyzbc
  cout << g.replace(4,3,"xyz",3) << endl;               // xyz xyz abd xyzbc
  cout << g.replace(4,3,"ijk",1) << endl;               // xyz i abd xyzbc
  cout << "Find: " << g.find("abd",1) << endl;          // Find: 6
  cout << g.find("qrs",1) << endl;

  string h("abc abc abd abc");
  cout << "String h: " << h << endl;
  cout << "Find \"abc\",0: " << h.find("abc",0) << endl; // Find "abc",0: 0
  cout << "Find \"abc\",1: " << h.find("abc",1) << endl; // Find "abc",1: 4
  cout << "Find_first_of \"abc\",0: " << h.find_first_of("abc",0) << endl; // Find_first_of "abc",0: 0
  cout << "Find_last_of \"abc\",0: " << h.find_last_of("abc",0) << endl;   // Find_last_of "abc",0: 0
  cout << "Find_first_not_of \"abc\",0: " << h.find_first_not_of("abc",0) << endl;  // Find_first_not_of "abc",0: 3
  cout << "Find_first_not_of \" \": " << h.find_first_not_of(" ") << endl;  // Find_first_not_of " ": 0
  cout << "Substr 5,9: " << h.substr(5,9) << endl;       // Substr 5,9: bc abd ab
  cout << "Compare 0,3,\"abc\": " << h.compare(0,3,"abc") << endl;  // Compare 0,3,"abc": 0
  cout << "Compare 0,3,\"abd\": " << h.compare(0,3,"abd") << endl;  // Compare 0,3,"abd": -1
  cout << h.assign("xyz",0,3) << endl;                   // xyz
  cout << "First character: " << h[0] << endl; // Strings start with 0 // First character: x

  std::cout << "\nPodaj jakikolwiek JEDEN znak aby aby zakonczyc... (np 'w' <Enter>)";
  char cc;
  std::cin >> cc; 

  doupdate();
  curs_set(false);
}
//----------------------------------------------------------------
void przykladyList() {
  endwin();  // Powrot do zwyklego trybu 'cooked' :)

  cout << "\nNastepny przyklad: obsluga list\n";
  mojalista *lista = new mojalista();

// dodawanie nowego elementu na koniec listy
  int nowy_element1 = 13;
  lista->push_back(nowy_element1);

// dodawanie nowego elementu na poczatku listy
  int nowy_element2 = 14;
  lista->push_front(nowy_element2);


  for (int jj = 1; jj <= 10; jj++) {
    lista->push_front(jj * jj);
  }
 
// przegladanie listy
  mojalista::iterator it;

  for (it = lista->begin() ; it != lista->end() ; ++it) {
    cout << *it;
    cout << " ";
  }

  cout << "\n";
// przegladanie listy wspak
  mojalista::reverse_iterator rit;

  for (rit = lista->rbegin() ; rit != lista->rend() ; ++rit) {
    cout << *rit;
    cout << " ";
  }

  delete lista;

  std::cout << "\nPodaj jakikolwiek JEDEN znak aby aby zakonczyc... (np 'w' <Enter>)";
  char cc;
  std::cin >> cc; 

  doupdate(); // Z powrotem do ncurses
  curs_set(false);
}
//-----------------------------------------------------------

void przykladoweInneKonstrukcje() {
  endwin();

  cout << "To przyklad na przeciazanie operatorow wyjscia:\n";
  DwieDane pusta, pelna(3, 4.5);
  cout << pusta;
  cout << pelna;

  cout << "\n Nastepny przyklad dotyczy referencji:\n";
  int a=0,b=0,c=0;
  nie_zwieksz(a);
  zwieksz_c(&b);
  zwieksz_cpp(c);
  cout << a << " " << b << " " << c; /* wypisze "0 1 1" */
  cout << "\nObjasnienie: pierwsze 0 to znaczy ze nie zwiekszyl liczby\n" <<
    "\nNastepne dwie jedynki to znacyz kolejno: sposob z ANSI C i referencja z C++\n";

  // Obsluga szablonow
  cout << "\nObsluga szablonow:\n";

  MojaKlasa< int > t_a( 3 );
  t_a.zawartosc = 5;
  t_a.wydrukowanieCalkowite();

  std::cout << "Linia ponizej\n";

  MojaKlasa< float > t_b( 5.6 );
  t_b.zawartosc = 12.345;
  t_b.wydrukowanieCalkowite();

  std::cout << "------------\n";
  t_a.wydrukowanie();
  std::cout << " ";
  t_b.wydrukowanie();

  std::cout << "\nPodaj jakikolwiek JEDEN znak aby aby zakonczyc... (np 'w' <Enter>)";
  char cc;
  std::cin >> cc; 

  doupdate();
  curs_set(false);
}

//---------------------------------------------------------------------
//using namespace std; To juz jest wlaczone w module :-)

void uruchomieniePoleceniaPrzyklad() {
  endwin();

  string result = uruchomieniePolecenia("ls -la");
  
  std::cout << result << endl; 
      
  std::cout << "\nPodaj jakikolwiek JEDEN znak aby aby zakonczyc... (np 'w' <Enter>)";
  char cc;
  std::cin >> cc; 

  doupdate();
  curs_set(false);
}

//----------------------------------------------------------------
void przykladoweKonstrukcjeCPP() {
  int wybor1 = -1;

  do {
    erase();
    MenuClass *menu1 = new MenuClass();
    menu1->Opcja("Przyklady dzialan na lancuchach");
    menu1->Opcja("Obsluga list");
    menu1->Opcja("Szablony, przeciazanie operatorow, et cetera");
    menu1->Opcja("Uruchomienie polecenie (ls -la) i przechwycenie jego odpowiedzi");
//    menu1->Opcja("Rozwiazania zadan i przyklady do C++ wersja >= 11 (Lambda funkcje, auto, PTM, itd)"); //TODO: czasami na niektorych ekranach to jest za dlugi napis, jak z tym sobie poradzic?
//pewnie trzeba podzielic opis na wiecej linijek
    menu1->Opcja("Rozwiazania zadan i przyklady do C++ wersja >= 11");

    menu1->OpcjaWyjscia("Wyjscie");
    menu1->ustawienieWersji(wmDrabinka);  
    wybor1 = menu1->Run();

    switch (wybor1) {
      case 0:
        przykladyDzialanNaLancuchach();
        break;
      case 1:
        przykladyList();
        break;
      case 2:
        przykladoweInneKonstrukcje();
        break;
      case 3:
        uruchomieniePoleceniaPrzyklad(); 
        break;
      case 4:
        Przyklady2::przykladyNaPracownie();
	break;
    } 
       
    delete menu1;
  } while (wybor1 != -1);
}
//-----------------------------------------------------------------}
