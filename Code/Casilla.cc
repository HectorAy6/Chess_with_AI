#include "../Header/Casilla.hh"

Casilla::Casilla(QWidget *parent):QLabel(parent){
}

void Casilla::mouseReleaseEvent (QMouseEvent *event)
{
    emit click(fi,co);
}

void Casilla::color_fondo(char f, int c, QColor col){
    if(f!=fi || c != co) return;
    QPalette p = palette();
    p.setColor(QPalette::Window, col);
    setPalette(p);

}

void Casilla::imagen_pieza(char f, int c, QPixmap &i){
    if(f!=fi || c != co) return;
    setPixmap(i);

}