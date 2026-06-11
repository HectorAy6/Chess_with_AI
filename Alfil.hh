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
        virtual void obtener_movimientos_posibles(std::set<Pos> &result, Pos p, Tablero *t);

    private:
        virtual bool mover(Pos original, Pos nueva);
        std::vector<Pos> vector_mov={Pos(1,1), Pos(-1,1), Pos(1,-1), Pos(-1,-1)};

};

#endif // MACRO
