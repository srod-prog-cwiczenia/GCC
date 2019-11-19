#include <string>
#include <list>
#include <iostream>
#include "define.h"

using namespace std;

class MenuClass {
public:
  MenuClass();
  void Opcja(string opcja);
  ~MenuClass();
  int Run();  
  void OpcjaWyjscia(string opcja);
  void ustawienieWersji(WersjaMenu wersja);
private:
  typedef list<string> listaLancuchow;
  listaLancuchow *lista;

  int getMaxDlugoscOpcji();
  void ramkaWokolMenu();
  int wybranaOpcja(int znak);
  bool dobryZnak(int znak);
  void wyswietlenie();
  int liczbaOpcji;        // liczba opcji
  int nrOpcjiWyjscia; // Nr opcji ktora jest wyjsciem z menu - nie reaguje na liczby ale na literke 'w'
  WersjaMenu wersjaMenu; // Rozne rodzaje menu
};
