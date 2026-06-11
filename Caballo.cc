#include "Caballo.hh"
#include "Tablero.hh"

Caballo::Caballo (bool blanca):Pieza(blanca){}
Caballo::Caballo (Pieza *p2):Pieza(p2){}
Caballo::Caballo ():Pieza(){}

void Caballo::obtener_movimientos_posibles(std::set<Pos> &result, Pos p, Tablero *t){
    result.clear();
    for(auto it:movimientos_validos){
        Pos aux = p+it;
        if(pos_aceptable(aux.x, aux.y) and !t->ocupado_equipo(aux, color)){
            result.insert(aux);
        }
    }
}

bool Caballo::mover(Pos original, Pos nueva){
    Pos mov(nueva.x-original.x, nueva.y-original.y);
    if(movimientos_validos.find(mov)!= movimientos_validos.end()){
        return true;
    }
    return false;
}