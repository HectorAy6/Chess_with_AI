#if !defined(REI_HH)
#define REI_HH

#include "Pieza.hh"

class Rei: public Pieza{
    public:
        Rei (bool blanca);
        Rei (Pieza *p2);
        Rei ();

        virtual int tipo_de_pieza(){return REI;}
        virtual char print(){return 'r';}
    private:
};

#endif // MACRO
