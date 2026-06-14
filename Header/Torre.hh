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
        virtual void obtener_casillas_amenaza(std::set<Pos> &result, Pos p, Tablero *t);
        virtual void obtener_casillas_jaque(std::set<Pos> &result, Pos p, Tablero *t);
        virtual bool se_ha_movido(){ return !primer_movimiento;}
        virtual void pieza_movida() override{ primer_movimiento = false;}

    private:
        std::vector<Pos> vector_mov={Pos(1,0), Pos(0,1), Pos(-1,0), Pos(0,-1)};
        bool primer_movimiento = true;
};

#endif // MACRO
