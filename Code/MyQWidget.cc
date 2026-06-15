#include "../Header/MyQWidget.hh"

MyQWidget::MyQWidget(QWidget *parent):QWidget(parent){
    t.reset();
}

void MyQWidget::recivir_Pos(char f, int c){
    if(partida_acabada) return;
    int res = t.enviar_pos(f, c);
    if(res == POS_NO_VALIDA) return;
    if(res == TABLAS or res == JAQUE_MATE_B or res == JAQUE_MATE_N){
        partida_acabada = true;
        pintar_tablero();
        return;
    }
    if(res == SIGUIENTE_RONDA){
        t.cambio_equipo();
    }
    if(res==CORONACION){
        Pos p;
        if(f>'H') p.y = f- 'a';
        else p.y = f-'A';

        p.x = 8-c;
        pintar_coronacion(p);
    }else {
        pintar_tablero();
    }

}

void MyQWidget::pintar_tablero(){
    std::set<Pos> movimientos_pos; 
    t.get_movimientos_pos(movimientos_pos);
    Pos pieza_sel = t.get_pieza_sel();
    bool hay_pieza_sel = t.get_hay_pieza_sel();

    for(int i=0; i<size_tablero; i++){
        for(int j=0; j<size_tablero; j++){
            QColor col;
            if(i%2==j%2) {
                col = QColor(91, 57, 13);
            }else{
                col = QColor(238, 212, 114);
            }
            if(movimientos_pos.find(Pos(i,j))!=movimientos_pos.end()){
                col = QColor(255,0,0);
            }else if(Pos(i,j)==pieza_sel and hay_pieza_sel){
                col = QColor(0,0,255);
            }
            emit enviar_color(char('a'+j), 8-i, col);
            emit enviar_imatge(char('a'+j), 8-i, t.get_image(i,j));
        }
    }
}

void MyQWidget::pintar_coronacion(Pos p){
    std::set<Pos> movimientos_pos; 
    t.get_movimientos_pos(movimientos_pos);
    Pos pieza_sel = t.get_pieza_sel();

    for(int i=0; i<size_tablero; i++){
        for(int j=0; j<size_tablero; j++){
            QColor col;
            if(i%2==j%2) {
                col = QColor(91, 57, 13);
            }else{
                col = QColor(238, 212, 114);
            }

            if(j==p.y and abs(i-p.x)<4){
                col = QColor(255,255,255);
                QPixmap ima(":");
                bool e = t.get_equipo();
                if(abs(i-p.x)==0){
                    if(e==BLANCA)ima = QPixmap(":Images/Images/Dama_B.png");
                    else ima = QPixmap(":Images/Images/Dama_N.png");
                }
                else if(abs(i-p.x)==1){
                    if(e==BLANCA)ima = QPixmap(":Images/Images/Torre_B.png");
                    else ima = QPixmap(":Images/Images/Torre_N.png");
                }else if(abs(i-p.x)==2){
                    if(e==BLANCA)ima = QPixmap(":Images/Images/Caballo_B.png");
                    else ima = QPixmap(":Images/Images/Caballo_N.png");
                }else if(abs(i-p.x)==3){
                    if(e==BLANCA)ima = QPixmap(":Images/Images/Alfil_B.png");
                    else ima = QPixmap(":Images/Images/Alfil_N.png");
                }
                emit enviar_imatge(char('a'+j), 8-i, ima);
            }else if (Pos(i,j)!=pieza_sel){
                emit enviar_imatge(char('a'+j), 8-i, t.get_image(i,j));
            }else {
                emit enviar_imatge(char('a'+j), 8-i, t.get_image(-1,j));
            }
            emit enviar_color(char('a'+j), 8-i, col);
            
        }
    }
}