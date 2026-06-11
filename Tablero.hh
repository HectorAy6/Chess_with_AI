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

        
    protected:
        mat tablero_piezas = mat(size_tablero);

        void print();

        //Funcion que juega una ronda del quipo seleccionado, en caso de matar el Rei devuelve True
        bool movimiento(bool equipo);

        void demanarPos(int &fila, int &columna);


};

#endif // MACRO


