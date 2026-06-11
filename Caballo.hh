#if !defined(CABALLO_HH)
#define CABALLO_HH

#include "Pieza.hh"

class Caballo: public Pieza{
    public:
        Caballo (bool blanca);
        Caballo (Pieza *p2);
        Caballo ();
        virtual int tipo_de_pieza(){return CABALLO;}
        virtual char print(){return 'c';}
    private:
};

#endif // MACRO
