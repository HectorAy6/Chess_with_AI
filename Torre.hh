#if !defined(TORRE_HH)
#define TORRE_HH

#include "Pieza.hh"

class Torre: public Pieza{
    public:
        Torre (bool blanca);
        Torre (Pieza *p2);
        Torre ();

        virtual int tipo_de_pieza(){return TORRE;}
        virtual char print(){return 't';}
    private:
};

#endif // MACRO
