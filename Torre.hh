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
        virtual void obtener_movimientos_posibles(std::set<Pos> &result, Pos p, Tablero *t);

    private:
        virtual bool mover(Pos original, Pos nueva);
        std::vector<Pos> vector_mov={Pos(1,0), Pos(0,1), Pos(-1,0), Pos(0,-1)};
};

#endif // MACRO
