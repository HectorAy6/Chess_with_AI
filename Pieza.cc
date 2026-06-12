#include "Pieza.hh"
#include "Tablero.hh"

Pieza::Pieza(bool blanca){
    color = blanca;
}

Pieza::Pieza(Pieza *p2){
    color = p2->color;
}

Pieza::Pieza(){
    color = true;
}

char Pieza::print_pieza(){
    if(color==BLANCA) std::cout<<"\033[7m";
    else std::cout<<"\033[34m";
    return print();
}

void Pieza::obtener_movimientos_posibles(std::set<Pos> &result, Pos p, Tablero *t){
    if(t->hay_jaque(color)){
        obtener_casillas_jaque(result,p,t);
    }else{
        if(t->hay_jaque_eliminar_pieza(p)){
            result.clear();
            
            return;
        }
        if(tipo_de_pieza()!=REI)obtener_casillas_amenaza(result,p,t);
        else obtener_casillas_amenaza(result,p,t);
    }
    
    return;
}
