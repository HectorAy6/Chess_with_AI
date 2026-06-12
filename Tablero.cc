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

    while (!pedirComanda(equipo));
    
    if(!piezaSeleccionada) return RENDIRSE;

    if(posicion_pieza_actual==Rei_blanco) Rei_blanco = nueva_posicion_pieza;
    else if (posicion_pieza_actual==Rei_negro) Rei_negro = nueva_posicion_pieza;

    tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]->pieza_movida();

    tablero_piezas[nueva_posicion_pieza.x][nueva_posicion_pieza.y] = tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y];
    tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y] = nullptr;


    calculo_Jaque(!equipo);
    if(tiene_movimientos(!equipo)) return SIGUIENTE_RONDA;
    if(hay_jaque(!equipo)) return JAQUE_MATE;
    return TABLAS;

}

void Tablero::jugar_partida(){
    int acabado = SIGUIENTE_RONDA;
    bool equipo = NEGRA;
    
    print();

    while(acabado==SIGUIENTE_RONDA){
        equipo= !equipo;
        acabado = movimiento(equipo);
        print();
    }
    if(acabado==TABLAS) std::cout << "TABLAS";
    else if(acabado==RENDIRSE && equipo==BLANCA) std::cout << "BLANCO SE RINDE, GANA NEGRO";
    else if(acabado==RENDIRSE && equipo==NEGRA) std::cout << "NEGRO SE RINDE, GANA BLANCO";
    else if(acabado==JAQUE_MATE && equipo==BLANCA) std::cout << "JAQUE MATE GANADOR BLANCO";
    else if(acabado==JAQUE_MATE && equipo==NEGRA) std::cout << "JAQUE MATE GANADOR NEGRO";

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

bool Tablero::pedirComanda(bool equipo){

    char comando;

    std::cout << "Introducir comando:" << std::endl;
    while (!(std::cin >> comando) || comandos_validos.find(comando)==comandos_validos.end()) {
        std::cout << "Entrada invalida. Introduce una letra para indicar que hacer: " << std::endl;
        std::cout << " 's/S' : seleccionar pieza " << std::endl;
        std::cout << " 'm/M' : mover seleccionada pieza " << std::endl;
        std::cout << " 'd/D' : quitar seleccion pieza " << std::endl;
        std::cout << " 'e/E' : acabar partida " << std::endl;
        
        std::cin.clear(); 
        std::cin.ignore(1000, '\n');
    }

    if(comando=='S' || comando == 's'){
        pedirPos(posicion_pieza_actual);
        piezaSeleccionada = false;
        if(pos_aceptable(posicion_pieza_actual.x, posicion_pieza_actual.y)){
            if(tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]==nullptr) std::cout << "La posicion no esta ocupada" << std::endl;
            else if(tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]->equipo()!=equipo) std::cout << "La posicion esta ocupada por pieza rival" << std::endl;
            else {
                tablero_piezas[posicion_pieza_actual.x][posicion_pieza_actual.y]->obtener_movimientos_posibles(Movimientos_pieza_seleccionada, posicion_pieza_actual, this);
                if(Movimientos_pieza_seleccionada.size()==0) std::cout << "La pieza no tiene movimientos validos" << std::endl;
                else {
                    std::cout << "Pieza seleccionada con exito" << std::endl;
                    piezaSeleccionada = true;
                }
            }
        }else std::cout << "La posicion no existe" << std::endl;
    }else if(comando=='m' || comando == 'M'){
        if(!piezaSeleccionada) {
            std::cout << "No hay ninguna pieza seleccionada" << std::endl;
            return false;
        }
        pedirPos(nueva_posicion_pieza);
        if(Movimientos_pieza_seleccionada.find(nueva_posicion_pieza)==Movimientos_pieza_seleccionada.end()) std::cout << "La pieza no sepuede mover ahi" << std::endl;
        else return true;
    }else if(comando=='d'||comando=='D'){
        piezaSeleccionada = false;
    }else if(comando=='e'|| comando == 'E'){
        piezaSeleccionada = false;
        return true;
    }
    return false;

    
}

void Tablero::pedirPos(Pos &p){
    char columna_letra;
    while (!(std::cin >> columna_letra >> p.x) ) {
        std::cout << "Entrada invalida. Introduce una letra y un numero para indicar posicion pieza" << std::endl;        
        std::cin.clear(); 
        std::cin.ignore(1000, '\n');
    }
    if(columna_letra>'H') p.y = columna_letra- 'a';
    else p.y = columna_letra-'A';

    p.x = 8-p.x;
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