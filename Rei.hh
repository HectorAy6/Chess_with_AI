#if !defined(REI_HH)
#define REI_HH

#include "Pieza.hh"

class Rei: public Pieza{
    public:
        Rei (bool blanca);
        Rei (Pieza *p2);
        Rei ();

        virtual int tipo_de_pieza(){return REI;}
        virtual char print(){return 'r';}

        virtual void obtener_movimientos_posibles(std::set<Pos> &result, Pos p, Tablero *t);
        
    private:
        virtual bool mover(Pos original, Pos nueva);

        std::set<Pos> movimientos = {Pos(1,1), Pos(-1,1), Pos(1,-1), Pos(-1,-1), Pos(1,0), Pos(0,1), Pos(-1,0), Pos(0,-1)};
};

#endif // MACRO
