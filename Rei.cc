#include "Rei.hh"
#include "Tablero.hh"

Rei::Rei (bool blanca):Pieza(blanca){}
Rei::Rei (Pieza *p2):Pieza(p2){}
Rei::Rei ():Pieza(){}

void Rei::obtener_casillas_amenaza(std::set<Pos> &result, Pos p, Tablero *t){
    result.clear();
    Pos mov(1,1);
    for(auto mov:movimientos){
        Pos aux = p+mov;
        if(pos_aceptable(aux.x, aux.y) and !t->ocupado_equipo(aux, color)) result.insert(aux);
    }
}

void Rei::obtener_casillas_jaque(std::set<Pos> &result, Pos p, Tablero *t){
    result.clear();
    Pos mov(1,1);
    for(auto mov:movimientos){
        Pos aux = p+mov;
        if(pos_aceptable(aux.x, aux.y) and !t->ocupado_equipo(aux, color) and !t->hay_jaque_mover_pieza(p, aux)) result.insert(aux);
    }
}


bool Rei::mover(Pos original, Pos nueva){
    Pos mov(nueva.x-original.x, nueva.y-original.y);
    return abs(mov.x)<2 and abs(mov.y)<2;
    
}