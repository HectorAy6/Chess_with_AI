#include "../Header/Caballo.hh"
#include "../Header/Tablero.hh"

Caballo::Caballo (bool blanca):Pieza(blanca){
    if(blanca==BLANCA)imagen = QPixmap(":/Images/Images/Caballo_B.png");
    else imagen = QPixmap(":/Images/Images/Caballo_N.png");
}
Caballo::Caballo (Pieza *p2):Pieza(p2){}
Caballo::Caballo ():Pieza(){}

void Caballo::obtener_casillas_amenaza(std::set<Pos> &result, Pos p, Tablero *t){
    result.clear();
    for(auto it:movimientos_validos){
        Pos aux = p+it;
        if(pos_aceptable(aux.x, aux.y) and !t->ocupado_equipo(aux, color)){
            result.insert(aux);
        }
    }
}

void Caballo::obtener_casillas_jaque(std::set<Pos> &result, Pos p, Tablero *t){
    result.clear();
    for(auto it:movimientos_validos){
        Pos aux = p+it;
        if(pos_aceptable(aux.x, aux.y) and !t->ocupado_equipo(aux, color) and !t->hay_jaque_mover_pieza(p, aux)){
            result.insert(aux);
        }
    }
}