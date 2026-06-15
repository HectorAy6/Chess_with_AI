#include <iostream>
#include <QApplication>
#include <QWidget>
#include "../Header/Tablero.hh"
#include "../Header/MyQWidget.hh"
#include "ui_chess.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Creamos una ventana base
    MyQWidget *ventana = new MyQWidget(nullptr);

    // Instanciamos la interfaz generada por el .ui
    Ui::Window ui; // Nota: "Form" es el nombre del objeto principal en Qt Designer (puede ser MainWindow)
    ui.setupUi(ventana);

    QList<Casilla*> casi = ventana->findChildren<Casilla*>();
    for(auto i: casi){
        i->setControl(ventana);
    }
    ventana->pintar_tablero();
    ventana->show();
    return app.exec();
}