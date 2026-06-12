#if !defined(PEON_HH)
#define PEON_HH

#include "Pieza.hh"


class Peon: public Pieza{
    public:
        Peon (bool blanca, Tablero *t);
        Peon (Pieza *p2);
        Peon ();

        virtual int tipo_de_pieza(){return PEON;}
        virtual char print(){return 'p';}
        virtual void obtener_casillas_amenaza(std::set<Pos> &result, Pos p, Tablero *t);
        virtual void obtener_casillas_jaque(std::set<Pos> &result, Pos p, Tablero *t);
        
    private:
        bool primer_movimiento = true;
        virtual bool mover(Pos original, Pos nueva);
        std::set<Pos> movimientos_validos = {Pos(-1,0), Pos(-2,0), Pos(-1,1), Pos(1,-1)}; 
        Tablero *tab;
};

#endif // MACRO
