#include "../Header/Alfil.hh"
#include "../Header/Tablero.hh"

Alfil::Alfil (bool blanca):Pieza(blanca){}
Alfil::Alfil (Pieza *p2):Pieza(p2){}
Alfil::Alfil ():Pieza(){}

void Alfil::obtener_casillas_amenaza(std::set<Pos> &result, Pos p, Tablero *t){
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

void Alfil::obtener_casillas_jaque(std::set<Pos> &result, Pos p, Tablero *t){
    result.clear();
    for(auto mov:vector_mov){
        Pos aux = p;
        bool posible = true;
        while(posible){
            aux=aux+mov;
            if(pos_aceptable(aux.x, aux.y) and !t->ocupado(aux)){if(!t->hay_jaque_mover_pieza(p, aux)) result.insert(aux);}
            else posible = false;
        }
        if(pos_aceptable(aux.x, aux.y) and t->ocupado_equipo(aux, !color) and !t->hay_jaque_mover_pieza(p,aux)) result.insert(aux);
    }
}