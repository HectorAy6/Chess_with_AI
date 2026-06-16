#if !defined(CABALLO_HH)
#define CABALLO_HH

#include "Pieza.hh"

class Caballo: public Pieza{
    public:
        Caballo (bool blanca);
        Caballo (Pieza *p2);
        Caballo ();
        virtual int tipo_de_pieza(){return CABALLO;}
        virtual char print(){return 'n';}
        virtual void obtener_casillas_amenaza(std::set<Pos> &result, Pos p, Tablero *t);
        virtual void obtener_casillas_jaque(std::set<Pos> &result, Pos p, Tablero *t);
        
    private:
        std::set<Pos> movimientos_validos = {Pos(-1,2), Pos(-1,-2), Pos(1,-2), Pos(1,2), Pos(2,1), Pos(-2,1), Pos(2,-1), Pos(-2,-1)};
};

#endif // MACRO
