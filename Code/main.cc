#include <iostream>
#include "../Header/Tablero.hh"



int main(){
    char c;
    Tablero t;
    t.jugar_partida();
    std::cin >> c;
    while(c=='r'){
        t.reset();
        t.jugar_partida();
        std::cin >> c;
    }

}