#include "Tablero.hh"

Tablero::Tablero(){

    for (auto& fila : tablero_piezas) {
        fila.resize(size_tablero); // Crea los unique_ptr apuntando a nullptr por defecto
    }

    reset();
    
}

void Tablero::print(){
    std::cout << "  A B C D E F G H" << std::endl;
    for(int i=0; i<size_tablero; i++){
        std::cout << 8-i;
        for(int j=0; j<size_tablero; j++){
            if(tablero_piezas[i][j]==nullptr){
                std::cout << " .";
            }else{
                std::cout << " " << tablero_piezas[i][j]->print_pieza() << "\033[0m";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  A B C D E F G H" << std::endl << std::endl;
}

int Tablero::movimiento(bool equipo){

    Pos pos_original, nueva_pos;
    bool acceptable = false;
    std::set<Pos> Movimientos_pos;
    
    while (!acceptable)
    {
        std::cout << "Elige pieza para mover:";
        
        demanarPos(pos_original.x, pos_original.y);

        if(pos_aceptable(pos_original.x, pos_original.y)){
            if(tablero_piezas[pos_original.x][pos_original.y]==nullptr) std::cout << "La posicion no esta ocupada" << std::endl;
            else if(tablero_piezas[pos_original.x][pos_original.y]->equipo()!=equipo) std::cout << "La posicion esta ocupada por pieza rival" << std::endl;
            else {
                tablero_piezas[pos_original.x][pos_original.y]->obtener_movimientos_posibles(Movimientos_pos, pos_original, this);
                if(Movimientos_pos.size()==0) std::cout << "La pieza no tiene movimientos validos" << std::endl;
                else acceptable = true;
            }
        }else std::cout << "La posicion no existeix" << std::endl;
        
    }
    
    acceptable = false;

    while (!acceptable)
    {
        std::cout << "Elige posicio a donde mover:";
        
        demanarPos(nueva_pos.x, nueva_pos.y);
        if(Movimientos_pos.find(nueva_pos)==Movimientos_pos.end()) std::cout << "La pieza no sepuede mover ahi" << std::endl;
        else acceptable = true;
        
    }

    if(pos_original==Rei_blanco) Rei_blanco = nueva_pos;
    else if (pos_original==Rei_negro) Rei_negro = nueva_pos;

    tablero_piezas[nueva_pos.x][nueva_pos.y] = tablero_piezas[pos_original.x][pos_original.y];;
    tablero_piezas[pos_original.x][pos_original.y] = nullptr;


    calculo_Jaque(!equipo);
    std::cout << "CaLCULO BIEN JAQUE MATE" << std:: endl;
    if(tiene_movimientos(!equipo)) return SIGUIENTE_RONDA;
    if(hay_jaque(!equipo)) return JAQUE_MATE;
    return TABLAS;

}

void Tablero::jugar_partida(){
    int acabado = SIGUIENTE_RONDA;
    bool equipo = BLANCA;
    
    print();

    while(acabado==SIGUIENTE_RONDA){
        acabado = movimiento(equipo);
        print();

        equipo= !equipo;
    }
    if(acabado==TABLAS) std::cout << "TABLAS";
    else if(equipo==BLANCA) std::cout << "JAQUE MATE GANADOR NEGRO";
    else std::cout << "JAQUE MATE GANADOR BLANCO";

    std::cout << std::endl;
}

void Tablero::reset(){

    for(int i=0; i<size_tablero; i++){
        for(int j=0; j<size_tablero; j++){
            tablero_piezas[i][j]=nullptr;
        }
    }
    //Piezas blancas
    tablero_piezas[7][1] = std::make_shared<Caballo>(BLANCA);
    tablero_piezas[7][6] = std::make_shared<Caballo>(BLANCA);
    tablero_piezas[7][4] = std::make_shared<Rei>(BLANCA);
    tablero_piezas[7][3] = std::make_shared<Dama>(BLANCA);
    tablero_piezas[7][0] = std::make_shared<Torre>(BLANCA);
    tablero_piezas[7][7] = std::make_shared<Torre>(BLANCA);
    tablero_piezas[7][2] = std::make_shared<Alfil>(BLANCA);
    tablero_piezas[7][5] = std::make_shared<Alfil>(BLANCA);
    for(int i = 0; i<size_tablero; i++){
        tablero_piezas[6][i] = std::make_shared<Peon>(BLANCA, this);
    }

    //Piezas Negras
    tablero_piezas[0][1] = std::make_shared<Caballo>(NEGRA);
    tablero_piezas[0][6] = std::make_shared<Caballo>(NEGRA);
    tablero_piezas[0][4] = std::make_shared<Rei>(NEGRA);
    tablero_piezas[0][3] = std::make_shared<Dama>(NEGRA);
    tablero_piezas[0][0] = std::make_shared<Torre>(NEGRA);
    tablero_piezas[0][7] = std::make_shared<Torre>(NEGRA);
    tablero_piezas[0][2] = std::make_shared<Alfil>(NEGRA);
    tablero_piezas[0][5] = std::make_shared<Alfil>(NEGRA);
    for(int i = 0; i<size_tablero; i++){
        tablero_piezas[1][i] = std::make_shared<Peon>(NEGRA, this);
    }

    Rei_blanco = Pos(7,4);
    Rei_negro = Pos(0,4);

    jaqueBlanco = false;
    jaqueNegro = false;
}

void Tablero::demanarPos(int &fila, int &columna){

    char columna_letra;

    while (!(std::cin >> columna_letra >> fila)) {
        std::cout << "Entrada invalida. Introduce una letra y un numero: " << std::endl;
        
        std::cin.clear(); 
        std::cin.ignore(1000, '\n');
    }

    if(columna_letra>'H') columna = columna_letra- 'a';
    else columna = columna_letra-'A';

    fila = 8-fila;
}

void Tablero::calculo_jaque(bool &Jaque,const bool equipo, const Pos rei){
    std::set<Pos> casillas_amenazadas, aux;
    for(int i=0; i<size_tablero; i++){
        for(int j=0; j<size_tablero; j++){
            if(tablero_piezas[i][j]!=nullptr and tablero_piezas[i][j]->equipo()!=equipo){
                tablero_piezas[i][j]->obtener_casillas_amenaza(aux,Pos(i,j), this);
                casillas_amenazadas.merge(aux);
            }
        }
    }

    Jaque = casillas_amenazadas.find(rei)!=casillas_amenazadas.end();
}

bool Tablero::hay_jaque_eliminar_pieza(Pos p){
    bool equipo = tablero_piezas[p.x][p.y]->equipo();
    bool result  = false;
    std::shared_ptr<Pieza> aux = tablero_piezas[p.x][p.y];
    tablero_piezas[p.x][p.y] = nullptr;
    calculo_Jaque(equipo);
    if(hay_jaque(equipo)){
        result = true;
    }
    tablero_piezas[p.x][p.y] = aux;
    calculo_Jaque(equipo);
    return result;
}

bool Tablero::hay_jaque_mover_pieza(Pos original, Pos nueva){
    bool equipo = tablero_piezas[original.x][original.y]->equipo();
    bool result  = false;
    if(original==Rei_blanco) Rei_blanco = nueva;
    else if(original == Rei_negro) Rei_negro = nueva;
    std::shared_ptr<Pieza> aux = tablero_piezas[nueva.x][nueva.y];
    tablero_piezas[nueva.x][nueva.y] = tablero_piezas[original.x][original.y];
    tablero_piezas[original.x][original.y] = nullptr;
    
    calculo_Jaque(equipo);
    if(hay_jaque(equipo)){
        result = true;
    }
    tablero_piezas[original.x][original.y] = tablero_piezas[nueva.x][nueva.y];
    tablero_piezas[nueva.x][nueva.y] = aux;

    if(nueva==Rei_blanco) Rei_blanco = original;
    else if(nueva == Rei_negro) Rei_negro = original;
    calculo_Jaque(equipo);
    return result;
}

bool Tablero::tiene_movimientos(bool equipo){
    std::set<Pos> result;
    for(int i=0; i<size_tablero; i++){
        for(int j=0; j<size_tablero; j++){
            if(tablero_piezas[i][j]!=nullptr and tablero_piezas[i][j]->equipo()==equipo){
                tablero_piezas[i][j]->obtener_movimientos_posibles(result,Pos(i,j), this);
                if(result.size()>0) return true;
            }
        }
    }
    return false;
}