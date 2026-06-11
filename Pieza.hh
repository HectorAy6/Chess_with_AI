#if !defined(PIEZA_HH)
#define PIEZA_HH

#include "Structs_y_Funciones.hh"

class Pieza {
    public:

        Pieza (bool blanca);
        Pieza (Pieza *p2);
        Pieza ();

        bool es_blanca(){return pieza_blanca;}

        virtual bool mover(Pos original, Pos nueva){return true;};
        virtual int tipo_de_pieza()=0;
        virtual char print_pieza();
        virtual char print()=0;

    protected:
        bool pieza_blanca;
        
    
};

#endif // MACRO

