#ifndef TESTY_H
#define TESTY_H


class Testy
{
    public:
        Testy();
        virtual ~Testy();
        static void dodajWieleOpcji(int ile, char *p...);
        static void dodajWieleOpcji2(int ile, char *p...);
        static void probaMenuZWielokrotnymiOpcjami();
        static void opcjaTestowa();
    protected:

    private:
};

#endif // TESTY_H
