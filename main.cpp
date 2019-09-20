#include <QApplication>
#include "windowGUI.h"
#include "linkedlist.cpp"

#include <iostream>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    LinkedList<std::string> list;
    list.add("Hello");
    list.add("Another message");
    list.add("Third message!");
    std::cout << list[2] << std::endl;


    windowGUI window;
    window.setWindowTitle("TECFLIX");
    window.show();



    return app.exec();
}