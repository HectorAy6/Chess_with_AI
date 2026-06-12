#if !defined(TABLERO_HH)
#define TABLERO_HH

#include "Peon.hh"
#include "Torre.hh"
#include "Caballo.hh"
#include "Alfil.hh"
#include "Dama.hh"
#include "Rei.hh"
#include <vector>
#include <memory>


typedef std::vector<std::vector<std::shared_ptr<Pieza>>> mat;

class Tablero {
    public:
        Tablero();

        void jugar_partida();
        void reset();

        bool ocupado(Pos p){
            if(tablero_piezas[p.x][p.y]==nullptr) return false;
            return true;
        }

        bool ocupado_equipo(Pos p, bool equipo){
            if(tablero_piezas[p.x][p.y]==nullptr) return false;
            if(tablero_piezas[p.x][p.y]->equipo()==equipo) return true;
            return false;
        }

        
        bool hay_jaque(bool equipo){
            if(equipo==BLANCA) return jaqueBlanco;
            else return jaqueNegro;
        }

        bool hay_jaque_eliminar_pieza(Pos p);

        bool hay_jaque_mover_pieza(Pos original, Pos nueva);

        
    protected:

        #define SIGUIENTE_RONDA 0
        #define TABLAS 1
        #define JAQUE_MATE 2  

        mat tablero_piezas = mat(size_tablero);
        std::set<Pos> Movimientos_pieza_seleccionada;
        Pos Rei_blanco, Rei_negro, posicion_pieza_actual;
        bool jaqueBlanco, jaqueNegro;

        void print();

        void calculo_Jaque(bool equipo){
            if(equipo==BLANCA) return calculo_jaque(jaqueBlanco, BLANCA, Rei_blanco);
            else return calculo_jaque(jaqueNegro, NEGRA, Rei_negro);

        }

        void calculo_jaque(bool &Jaque,const bool equipo ,const Pos rei);

        //Funcion que juega una ronda del quipo seleccionado, en caso de matar el Rei devuelve True
        int movimiento(bool equipo);

        void demanarPos(int &fila, int &columna);

        bool tiene_movimientos(bool equipo);


};

#endif // MACRO


