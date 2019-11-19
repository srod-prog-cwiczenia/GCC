#include <string>
#include <list>
#include <iostream>

using namespace std;

class WyswietlanieUptime {
public:
  WyswietlanieUptime();
  ~WyswietlanieUptime();
  void run();
private:
};

//-----------------------------------------
WyswietlanieUptime::WyswietlanieUptime() {
}
//----------------------------------------
void WyswietlanieUptime::run() {


}
//----------------------------------------
WyswietlanieUptime::~WyswietlanieUptime() {
}
//---------------------------------------
void wyswietlanieUptime() {
  WyswietlanieUptime *wu = new WyswietlanieUptime();
  wu->run();
  delete wu;
}

//-----------------------------------------------------
