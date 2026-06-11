#if !defined(PEON_HH)
#define PEON_HH

#include "Pieza.hh"

class Peon: public Pieza{
    public:
        Peon (bool blanca);
        Peon (Pieza *p2);
        Peon ();

        virtual int tipo_de_pieza(){return PEON;}
        virtual char print(){return 'p';}
    private:
};

#endif // MACRO
