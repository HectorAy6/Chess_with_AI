#if !defined(PIEZA_HH)
#define PIEZA_HH

#include "Structs_y_Funciones.hh"
#include <set>
#include <vector>

class Tablero;

class Pieza {
    public:

        Pieza (bool blanca);
        Pieza (Pieza *p2);
        Pieza ();

        bool equipo(){return color;}

        virtual int tipo_de_pieza()=0;
        virtual char print_pieza();
        virtual char print()=0;
        virtual void obtener_movimientos_posibles(std::set<Pos> &result, Pos p, Tablero *t);
        virtual void obtener_casillas_amenaza(std::set<Pos> &result, Pos p, Tablero *t) = 0;
        virtual void obtener_casillas_jaque(std::set<Pos> &result, Pos p, Tablero *t) = 0;

        virtual void pieza_movida(){};

    protected:
        bool color;
        
    
};

#endif // MACRO

