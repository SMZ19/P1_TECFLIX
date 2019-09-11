//
// Created by smz on 10/9/19.
//

#ifndef P1_TECFLIX_WINDOWGUI_H
#define P1_TECFLIX_WINDOWGUI_H



#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>

class windowGUI : public QWidget {

public:
    windowGUI(QWidget *parent = 0);





protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void drawLines(QPainter *qp);

private:
    QSlider *slider;
    QLabel *label;
    static const int filas = 15;
    static const int columnas = 15;
    bool mapMatrix[columnas][filas];

    static const int B_WIDTH = 800;
    static const int B_HEIGHT = 600;
    int dimX =0;
    int dimY=0;
    bool found = false;
    int maxDivX  = 0;
    int maxDivY  = 0;
    int squareSize = 50;
    static const int DELAY = 140;

    int timerId;


    void doDrawing();

    void getDimensions(int , int);
    void initGame();

};

#endif //P1_TECFLIX_WINDOWGUI_H
