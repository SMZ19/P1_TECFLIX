#include <QApplication>
#include "windowGUI.h"

#include <iostream>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);



    windowGUI window;
    window.setWindowTitle("TECFLIX");
    window.setGeometry(10,10,1150,700);
    window.adjustSize();
    window.show();


    return app.exec();
}