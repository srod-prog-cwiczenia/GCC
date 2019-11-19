#include "analizaWsteczna.h"
#include <string>

using namespace std;

typedef struct { // to jest strukturka wyciagana na liste stanow 
//podczas wywolania funkcji do pobierania listy stanow.
  Stan stan;
  int ocena;
  char klawisz;
} TOpcjaStanuStr;

typedef list<TOpcjaStanuStr> TListaMozliwychRuchow;

class AnalizaWstecznaInterface {
  public:
    AnalizaWsteczna *aw;
  AnalizaWstecznaInterface();
  ~AnalizaWstecznaInterface();
  void runOnLine();  
  void saveToFile();
  void loadFromFile();
  void ustawianiePrawidel();
  bool dialogDoPlanszy(Stan *st, Kto *kto, TListaMozliwychRuchow *lmr, ListaStanow *pamiec);
  bool getRuch(Stan *st, Kto oso); 
  Stan *getNajlepszyRuch(Stan *st, Kto oso); 
  char *getRuchFromStany(Stan *st1, Stan *st2, bool skroconyZapis = false);
// skroconyZapis = true oznacza ze stosujemy zapis skrocony, czyli zamiast a1a2 piszemy Ka2, etc.
  string getSpisMozliwychRuchow(Stan *st, Kto oso);
// to samo, alisci oparte na liscie
  TListaMozliwychRuchow *getListaMozliwychRuchow(Stan *st, Kto oso);
  
  static int getKodPola(char pole, int wersja);
  static bool getStan(Stan *st); // Pobierz stan od uzytkownika, 
//false oznacza rezygnacje z podawania stanu.
  static bool getStan(Stan *st, Kto *oso); // j.w. z tym ze pobiera jeszcze informacje kto zaczyna
//false oznacza rezygnacje z podawania stanu, oso to pobieranie osoby zaczynajacej ten stan
  static void showStan(Stan *st);
};
//---------------------------------------------------------------------
void analizaWsteczna();
//---------------------------------------------------------------------
