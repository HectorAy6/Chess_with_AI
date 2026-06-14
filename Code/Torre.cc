#include "../Header/Torre.hh"
#include "../Header/Tablero.hh"

Torre::Torre (bool blanca):Pieza(blanca){}
Torre::Torre (Pieza *p2):Pieza(p2){}
Torre::Torre ():Pieza(){}

void Torre::obtener_casillas_amenaza(std::set<Pos> &result, Pos p, Tablero *t){
    
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

void Torre::obtener_casillas_jaque(std::set<Pos> &result, Pos p, Tablero *t){
    
    result.clear();

    for(auto mov:vector_mov){
        Pos aux = p;
        bool posible = true;
        while(posible){
            aux=aux+mov;
            if(pos_aceptable(aux.x, aux.y) and !t->ocupado(aux)) {if(!t->hay_jaque_mover_pieza(p, aux))result.insert(aux);}
            else posible = false;
        }
        if(pos_aceptable(aux.x, aux.y) and t->ocupado_equipo(aux, !color) and !t->hay_jaque_mover_pieza(p, aux)) result.insert(aux);
    }
}