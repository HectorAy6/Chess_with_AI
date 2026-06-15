#if !defined(PIEZA_HH)
#define PIEZA_HH

#include "Structs_y_Funciones.hh"
#include <set>
#include <vector>
#include <QWidget>

class Tablero;

class Pieza {
    public:

        Pieza (bool blanca);
        Pieza (Pieza *p2);
        Pieza ();

        bool equipo(){return color;}

        virtual int tipo_de_pieza()=0;
        char print_pieza();
        char print_pieza_seleccionada();
        virtual char print()=0;
        virtual void obtener_movimientos_posibles(std::set<Pos> &result, Pos p, Tablero *t);
        virtual void obtener_casillas_amenaza(std::set<Pos> &result, Pos p, Tablero *t) = 0;
        virtual void obtener_casillas_jaque(std::set<Pos> &result, Pos p, Tablero *t) = 0;

        virtual void pieza_movida(){};
        virtual void activar_doble_movimiento(){}
        virtual void desactivar_doble_movimiento(){}
        virtual bool se_ha_movido(){ return true;}
        virtual bool tiene_doble_movimiento(){ return false;}
        QPixmap& image(){ return imagen;}

    protected:
        bool color;
        QPixmap imagen;
        
    
};

#endif // MACRO

