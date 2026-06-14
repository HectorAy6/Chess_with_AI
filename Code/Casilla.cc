#include "../Header/Casilla.hh"

Casilla::Casilla(QWidget *parent):QLabel(parent){
}

void Casilla::mouseReleaseEvent (QMouseEvent *event)
{

    QPixmap i(":/Images/Images/Rei_B.png");
    this->setPixmap(i);
    emit click(fi,co);
}