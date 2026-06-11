#include "Alfil.hh"
#include "Tablero.hh"

Alfil::Alfil (bool blanca):Pieza(blanca){}
Alfil::Alfil (Pieza *p2):Pieza(p2){}
Alfil::Alfil ():Pieza(){}

void Alfil::obtener_movimientos_posibles(std::set<Pos> &result, Pos p, Tablero *t){
    result.clear();
    for(auto mov:vector_mov){
        Pos aux = p;
        bool posible = true;
        while(posible){
            aux=aux+mov;
            if(pos_aceptable(aux.x, aux.y) and !t->ocupado(aux)) result.insert(aux);
            else posible = false;
        }
        if(pos_aceptable(aux.x, aux.y) and t->ocupado_equipo(aux, !color)) result.insert(aux);
    }
}

bool Alfil::mover(Pos original, Pos nueva){
    Pos mov(nueva.x-original.x, nueva.y-original.y);
    return abs(mov.x)==abs(mov.y);
}