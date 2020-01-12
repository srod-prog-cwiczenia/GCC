#ifndef OPIS_H
#define OPIS_H

#include <string>
#include <vector>

#define SEPARATOR_OPISU '|'
using namespace std;

class Opis
{
    public:
        Opis(const string &tresc);
        virtual ~Opis();
        void pokaz();
//opcje tesowe, TODO: dumpWektor przeniesc do osobnej klasy diagnostycznej!
        static void dumpWektorStringowNaEkran(const vector<string> &vv);
        void dumpWierszeNaEkran();
    protected:
    private:
        vector<string> vWiersze;
};

#endif // OPIS_H
