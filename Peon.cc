#include "Peon.hh"
#include "Tablero.hh"

Peon::Peon (bool blanca, Tablero *t):Pieza(blanca){ tab = t;}
Peon::Peon (Pieza *p2):Pieza(p2){}
Peon::Peon ():Pieza(){}

void Peon::obtener_casillas_amenaza(std::set<Pos> &result, Pos p, Tablero *t){
    result.clear();
    int factor = color==NEGRA?-1:1;
    if(!t->ocupado(Pos(p.x-1*factor, p.y))) {
        result.insert(Pos(p.x-1*factor, p.y));
        if(primer_movimiento and !t->ocupado(Pos(p.x-2*factor, p.y)) )result.insert(Pos(p.x-2*factor, p.y));
    }
    
    if(p.y>0 and t->ocupado_equipo(Pos(p.x-1*factor, p.y-1), !color)){
        result.insert(Pos(p.x-1*factor, p.y-1));
    }

    if(p.y<size_tablero-1 and t->ocupado_equipo(Pos(p.x-1*factor, p.y+1), !color)){
        result.insert(Pos(p.x-1*factor, p.y+1));
    }
    if(result.size()>0) primer_movimiento = false;
}

void Peon::obtener_casillas_jaque(std::set<Pos> &result, Pos p, Tablero *t){
    result.clear();
    int factor = color==NEGRA?-1:1;
    if(!t->ocupado(Pos(p.x-1*factor, p.y))) {
        if(!t->hay_jaque_mover_pieza(p, Pos(p.x-1*factor, p.y)))result.insert(Pos(p.x-1*factor, p.y));
        if(primer_movimiento and !t->ocupado(Pos(p.x-2*factor, p.y)) and !t->hay_jaque_mover_pieza(p, Pos(p.x-2*factor, p.y)))result.insert(Pos(p.x-2*factor, p.y));
    }
    
    if(p.y>0 and t->ocupado_equipo(Pos(p.x-1*factor, p.y-1), !color) and !t->hay_jaque_mover_pieza(p, Pos(p.x-1*factor, p.y-1))){
        result.insert(Pos(p.x-1*factor, p.y-1));
    }

    if(p.y<size_tablero-1 and t->ocupado_equipo(Pos(p.x-1*factor, p.y+1), !color) and !t->hay_jaque_mover_pieza(p, Pos(p.x-1*factor, p.y+1))){
        result.insert(Pos(p.x-1*factor, p.y+1));
    }
    if(result.size()>0) primer_movimiento = false;
}

bool Peon::mover(Pos original, Pos nueva){
    Pos mov(nueva.x-original.x, nueva.y-original.y);
    /*if(color==NEGRA){
        mov.x=-mov.x;
    }
    if(movimientos_validos.find(mov)!= movimientos_validos.end()){
        if(mov.x==-2 and !primer_movimiento) return false;
        if(mov.y!=0 and tab->tablero_piezas[nueva.x][nueva.y]==nullptr) return false;
        primer_movimiento = false;
        return true;
    }
    primer_movimiento = false;
    */
    return false;
}