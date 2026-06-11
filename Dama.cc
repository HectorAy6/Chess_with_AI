#include "Dama.hh"
#include "Tablero.hh"

Dama::Dama (bool blanca):Pieza(blanca){}
Dama::Dama (Pieza *p2):Pieza(p2){}
Dama::Dama ():Pieza(){}

void Dama::obtener_movimientos_posibles(std::set<Pos> &result, Pos p, Tablero *t){
    result.clear();
    Pos mov(0,1);

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


bool Dama::mover(Pos original, Pos nueva){
    Pos mov(nueva.x-original.x, nueva.y-original.y);
    return mov.x==0 || mov.y == 0 ||abs(mov.x)==abs(mov.y);
}