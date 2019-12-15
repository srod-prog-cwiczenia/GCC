//--------------------------
class OknoAplikacji {
public:
    OknoAplikacji();
    ~OknoAplikacji();
  public:
    static void powrotDoTrybuTekstowego();
    static void powrotDoNCurses(bool zZatrzymaniemP = false);
    static void winieta();
    static void ramka(int x1, int  y1, int x2, int y2);
    static bool startTrybKolorowy();
    static void zainicjowanieEkranu();
    void zwolnienieEkranu();
};


