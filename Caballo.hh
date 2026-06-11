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
        virtual void obtener_movimientos_posibles(std::set<Pos> &result, Pos p, Tablero *t);
        
    private:
        virtual bool mover(Pos original, Pos nueva);
        std::set<Pos> movimientos_validos = {Pos(-1,2), Pos(-1,-2), Pos(1,-2), Pos(1,2), Pos(2,1), Pos(-2,1), Pos(2,-1), Pos(-2,-1)};
};

#endif // MACRO
