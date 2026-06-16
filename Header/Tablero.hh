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
#include <map>


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

        bool enroque_izquierda(Pos rei);

        bool enroque_derecha(Pos rei);

        bool posiblePeonPasado(Pos p, bool equipo);

        int enviar_pos(char c, int f);

        void actualizar_posiciones(){
            antigua_pos_a = posicion_pieza_actual;
            antigua_pos_n = nueva_posicion_pieza;
        }

        void cambio_equipo(){equipo_jugando = !equipo_jugando;}

        void get_movimientos_pos(std::set<Pos> &s){s = Movimientos_pieza_seleccionada;}
        void get_antiguasPos(std::set<Pos> &s){s = std::set<Pos>{antigua_pos_a, antigua_pos_n};}
        
        Pos get_pieza_sel(){return posicion_pieza_actual;}
        Pos get_pieza_nueva(){return nueva_posicion_pieza;}
        bool get_hay_pieza_sel() {return piezaSeleccionada;}
        bool get_equipo(){return equipo_jugando;}

        char print_pieza(int x, int y){return tablero_piezas[x][y]->print();}

        QPixmap& get_image(int i, int j);

        
    protected:

        #define SIGUIENTE_RONDA 0
        #define TABLAS 1
        #define JAQUE_MATE 2  
        #define RENDIRSE 3
        #define POS_NO_VALIDA 4
        #define JAQUE_MATE_B 5
        #define JAQUE_MATE_N 6
        #define PIEZA_SELECCIONADA 7
        #define CORONACION 8


        mat tablero_piezas = mat(size_tablero);
        std::set<Pos> Movimientos_pieza_seleccionada;
        std::set<char> comandos_validos = {'s', 'e', 'm', 'd', 'S', 'E', 'M', 'D'};
        std::set<char> piezas_validas = {'t', 'c', 'a', 'd', 'T', 'C', 'A', 'D'};
        Pos Rei_blanco, Rei_negro, posicion_pieza_actual, nueva_posicion_pieza, antigua_pos_a, antigua_pos_n;
        std::map<mat,int> contador_posiciones;
        bool jaqueBlanco, jaqueNegro, piezaSeleccionada, equipo_jugando, coronando;
        QPixmap imagen_vacia;

        int movimientos_sin_accion;

        void print();

        void calculo_Jaque(bool equipo){
            if(equipo==BLANCA) return calculo_jaque(jaqueBlanco, BLANCA, Rei_blanco);
            else return calculo_jaque(jaqueNegro, NEGRA, Rei_negro);

        }

        void calculo_jaque(bool &Jaque,const bool equipo ,const Pos rei);

        //Funcion que juega una ronda del quipo seleccionado, en caso de matar el Rei devuelve True
        int movimiento(bool equipo);

        bool pedirComanda(bool equipo);

        void pedirPos(Pos &p);

        bool tiene_movimientos(bool equipo);

        void coronacion();

        bool demasiadas_pocas_piezas();


};

#endif // MACRO


