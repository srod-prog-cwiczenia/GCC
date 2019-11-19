#include <string>

using namespace std;
/* Wyrzuca na ekran zawartosc lancucha, znak po znaku, podaje tez kody ASCII */
void dumpLancuch(char* str); 

/* Wypisuje komunikat na ekranie. TODO: Obudowac to w jakas sensowna ramke, itp */
void komunikat(string txt);
void komunikat(int liczba);

/* Wyswietla info o pustej opcji. wykorzystywane w pustych opcjach. */
void dummy();

/* Pytanie postaci Tak lub Nie. */
bool pytanieNT(string txt);

/* Jak sama nazwa wskazuje, sprawdza czy 
istnieje zadany plik. Korzysta z funkcji stat, byc moze istnieje jednak prostszy sposob? */
bool istniejePlik (const char* nazwaPliku);

/* Uruchamia proces i zwraca jego wynik. */
string uruchomieniePolecenia(string polecenie);
