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
        virtual void obtener_casillas_amenaza(std::set<Pos> &result, Pos p, Tablero *t);
        virtual void obtener_casillas_jaque(std::set<Pos> &result, Pos p, Tablero *t);

    private:
        std::vector<Pos> vector_mov={Pos(1,1), Pos(-1,1), Pos(1,-1), Pos(-1,-1)};

};

#endif // MACRO
