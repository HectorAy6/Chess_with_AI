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

bool Tablero::movimiento(bool equipo){

    Pos pos_original, nueva_pos;
    bool acceptable = false;
    
    while (!acceptable)
    {
        std::cout << "Elige pieza para mover:";
        
        demanarPos(pos_original.x, pos_original.y);

        if(pos_aceptable(pos_original.x, pos_original.y)){
            if(tablero_piezas[pos_original.x][pos_original.y]==nullptr) std::cout << "La posicion no esta ocupada" << std::endl;
            else if(tablero_piezas[pos_original.x][pos_original.y]->es_blanca()!=equipo) std::cout << "La posicion esta ocupada por pieza rival" << std::endl;
            else acceptable = true;
        }else std::cout << "La posicion no existeix" << std::endl;
        
    }
    
    acceptable = false;

    while (!acceptable)
    {
        std::cout << "Elige posicio a donde mover:";
  
        demanarPos(nueva_pos.x, nueva_pos.y);

        if(pos_aceptable(nueva_pos.x, nueva_pos.y)){
            if(!tablero_piezas[nueva_pos.x][nueva_pos.y]->mover(pos_original,nueva_pos))std::cout << "Esta pieza no se mueve asi" << std::endl;
            else if(tablero_piezas[nueva_pos.x][nueva_pos.y]->es_blanca()==equipo) std::cout << "La posicion esta ocupada por pieza de tu equipo" << std::endl;
            else acceptable = true;
        }else std::cout << "La posicion no existeix" << std::endl;
        
    }

    std::shared_ptr<Pieza> p = tablero_piezas[pos_original.x][pos_original.y];
    tablero_piezas[pos_original.x][pos_original.y] = nullptr;
    tablero_piezas[nueva_pos.x][nueva_pos.y] = p;
    return false;

}

void Tablero::jugar_partida(){
    bool acabado = false;
    bool equipo = BLANCA;
    
    print();

    while(!acabado){
        acabado = movimiento(equipo);
        print();

        equipo= !equipo;
    }
    if(equipo==BLANCA) std::cout << "GANADOR NEGRO";
    else std::cout << "GANADOR BLANCO";

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
        tablero_piezas[6][i] = std::make_shared<Peon>(BLANCA);
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
        tablero_piezas[1][i] = std::make_shared<Peon>(NEGRA);
    }
}

void Tablero::demanarPos(int &fila, int &columna){

    char columna_letra;

    std::cin >> columna_letra >> fila;
    if(columna_letra>'H') columna = columna_letra- 'a';
    else columna = columna_letra-'A';

    fila = 8-fila;
}