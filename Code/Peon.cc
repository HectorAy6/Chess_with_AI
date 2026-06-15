#include "../Header/Peon.hh"
#include "../Header/Tablero.hh"

Peon::Peon (bool blanca):Pieza(blanca){ 
    if(blanca==BLANCA)imagen = QPixmap(":/Images/Images/Peon_B.png");
    else imagen = QPixmap(":/Images/Images/Peon_N.png");
}
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

    if(p.y>0 and t->posiblePeonPasado(Pos(p.x, p.y-1), color)){
        result.insert(Pos(p.x-1*factor, p.y-1));
    }


    if(p.y<size_tablero-1 and t->ocupado_equipo(Pos(p.x-1*factor, p.y+1), !color)){
        result.insert(Pos(p.x-1*factor, p.y+1));
    }

    if(p.y<size_tablero-1 and t->posiblePeonPasado(Pos(p.x, p.y+1), color)){
        result.insert(Pos(p.x-1*factor, p.y+1));
    }
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

    if(p.y>0 and t->posiblePeonPasado(Pos(p.x, p.y-1), color) and !t->hay_jaque_mover_pieza(p, Pos(p.x-1*factor, p.y-1))){
        result.insert(Pos(p.x-1*factor, p.y-1));
    }

    if(p.y<size_tablero-1 and t->ocupado_equipo(Pos(p.x-1*factor, p.y+1), !color) and !t->hay_jaque_mover_pieza(p, Pos(p.x-1*factor, p.y+1))){
        result.insert(Pos(p.x-1*factor, p.y+1));
    }

    if(p.y<size_tablero-1 and t->posiblePeonPasado(Pos(p.x, p.y+1), color) and !t->hay_jaque_mover_pieza(p, Pos(p.x-1*factor, p.y+1))){
        result.insert(Pos(p.x-1*factor, p.y+1));
    }
}