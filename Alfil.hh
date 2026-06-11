#if !defined(ALFIL_HH)
#define ALFIL_HH

#include "Pieza.hh"

class Alfil: public Pieza{
    public:
        Alfil (bool blanca);
        Alfil (Pieza *p2);
        Alfil ();
        virtual int tipo_de_pieza(){return ALFIL;}
        virtual char print(){return 'a';}

    private:

};

#endif // MACRO
