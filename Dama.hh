#if !defined(DAMA_HH)
#define DAMA_HH

#include "Pieza.hh"

class Dama: public Pieza{
    public:
        Dama (bool blanca);
        Dama (Pieza *p2);
        Dama ();
                
        virtual int tipo_de_pieza(){return DAMA;}
        virtual char print(){return 'd';}

        virtual void obtener_casillas_amenaza(std::set<Pos> &result, Pos p, Tablero *t);
        virtual void obtener_casillas_jaque(std::set<Pos> &result, Pos p, Tablero *t);

    private:
        std::vector<Pos> vector_mov={Pos(1,1), Pos(-1,1), Pos(1,-1), Pos(-1,-1), Pos(1,0), Pos(0,1), Pos(-1,0), Pos(0,-1)};
};

#endif // MACRO
