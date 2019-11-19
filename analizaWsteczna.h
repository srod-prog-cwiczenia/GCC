#include <list>

#define DUMMY -1
#define NAZWA_PLIKU_Z_ANALIZA "plikZAnaliza.dat"

using namespace std;

typedef enum {bialy, czarny} Kto;
typedef enum {b1, b2, c1} Figura;
typedef int Oceny[8][8][8][8][8][8];

typedef struct {  // Umowa: jesli w x lub y jest DUMMY to pole jest puste
  int x,y;
} Pole;

typedef struct {
  Pole b1;
  Pole b2;
  Pole c1;
} Stan;
typedef list<Stan> ListaStanow;
//-----------------------------------------------------------------------
#define SRODEK_PLANSZY 7
#define MAX_ROZ_PLANSZY_PRAWIDLA 15
//-----------------------------------------------------------------------
typedef int TPlanszaDlaPrawidelRuchu[MAX_ROZ_PLANSZY_PRAWIDLA][MAX_ROZ_PLANSZY_PRAWIDLA];
//pole SRODEK_PLANSZY,SRODEK_PLANSZY 
//jest srodkiem tej planszy; 1 oznacza ze mozna sie na nie przesunac
//-----------------------------------------------------------------------
class PrawidlaRuchu {
  public:
    TPlanszaDlaPrawidelRuchu b1Pla, b2Pla, c1Pla;
    PrawidlaRuchu();
    ~PrawidlaRuchu();
    bool isConnected(Pole *skad, Pole *dokad, Figura fig);
};
//-----------------------------------------------------------------------
class AnalizaWsteczna {
// ta klasa ma byc w zalozeniu warstwa ,,maszyny'' do analizy - czyli tutaj ma byc zero interface-u pomiedzy
// uzytkownikiem!
  friend class AnalizaWstecznaTesty; 
  private:
  public: // na razie public bo potrzeba to do zapisania w pliku i do ustawiania
    Oceny oB, oC;  
    PrawidlaRuchu *pra;
  public:
    AnalizaWsteczna();
    ~AnalizaWsteczna();

    void analiza();
    void clearOceny();

    int getOcena(Stan *st, Kto oso);
    ListaStanow *getMozliweRuchy(Stan *st, Kto oso);
    bool isOcena(); //sprawdza czy dokonano jakies analizy
//tutaj sa niektore pomocnicze statyczne metody, na razie tak to bedzie rozwiazane
    static bool isPustePole(Pole *po);
  private:
    bool isConnected(Pole *skad, Pole *dokad, Figura fig);
    bool isConnectedK(Pole *skad, Pole *dokad);
    bool isConnectedH(Pole *skad, Pole *dokad);

    bool isRoznePola(Pole *p1, Pole *p2);
    bool isValidStan(Stan *st);
    bool isZwycieskiRuch(Stan *st, Kto oso);

    void setOcena(Stan *st, Kto oso, int ocena);
    bool createStan(int xb1, int yb1, int xb2, int yb2, int xc1, int yc1, Stan *st);

};
//-----------------------------------------------------------------------

