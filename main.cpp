#include <QApplication>
#include "windowGUI.h"


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    windowGUI window;
    window.setWindowTitle("TECFLIX");
    window.show();

    return app.exec();
}