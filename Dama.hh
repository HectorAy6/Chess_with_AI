#if !defined(DAMA_HH)
#define DAMA_HH

#include "Pieza.hh"

class Dama: public Pieza{
    public:
        Dama (bool blanca);
        Dama (Pieza *p2);
        Dama ();
                
        virtual int tipo_de_pieza(){return DAMA;}
        virtual char print(){return 'd';}
    private:
};

#endif // MACRO
