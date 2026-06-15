#include "../Header/MyQWidget.hh"

MyQWidget::MyQWidget(QWidget *parent):QWidget(parent){}

void MyQWidget::recivir_Pos(char f, int c){
    int res = t.enviar_pos(f, c);
    if(res == POS_NO_VALIDA) return;
    if(res == SIGUIENTE_RONDA){
        t.cambio_equipo();
    }
    pintar_tablero();

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