#include "../Header/Rei.hh"
#include "../Header/Tablero.hh"

Rei::Rei (bool blanca):Pieza(blanca){
    if(blanca==BLANCA)imagen = QPixmap(":/Images/Images/Rei_B.png");
    else imagen = QPixmap(":/Images/Images/Rei_N.png");
}
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
    if(primer_movimiento){
        if(t->enroque_derecha(p)) result.insert(p+Pos(0,2));
        if(t->enroque_izquierda(p)) result.insert(p+Pos(0,-2));
    }
}
