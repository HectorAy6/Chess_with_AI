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
        virtual void obtener_casillas_amenaza(std::set<Pos> &result, Pos p, Tablero *t);
        virtual void obtener_casillas_jaque(std::set<Pos> &result, Pos p, Tablero *t);

        virtual void pieza_movida() override{ primer_movimiento = false;}

        virtual void activar_doble_movimiento() override{ doble_movimiento = true;}
        virtual void desactivar_doble_movimiento() override{ doble_movimiento = false;}
        virtual bool tiene_doble_movimiento()override{return doble_movimiento;}
    private:
        bool primer_movimiento = true, doble_movimiento=false;;
        std::set<Pos> movimientos_validos = {Pos(-1,0), Pos(-2,0), Pos(-1,1), Pos(1,-1)}; 
};

#endif // MACRO
