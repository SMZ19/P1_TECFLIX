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
#include <QWheelEvent>
#include <qt5/QtWidgets/QPushButton>
#include <QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <string>
#pragma once



class windowGUI : public QMainWindow {

public:
    windowGUI(QWidget *parent = 0);




protected:

    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void wheelEvent(QWheelEvent *);
    void drawLines(QPainter *qp);

private:
    QSlider *slider;
    QLabel *label;
    bool nopagMode = false;
    bool pagMode = true;
    bool infiniteMode = false;
    static const int filas = 15;
    static const int columnas = 15;
    bool mapMatrix[columnas][filas];
    int zooming;
    static const int B_WIDTH = 600;
    static const int B_HEIGHT = 600;
    int dimX =0;
    int dimY=0;
    int maxDivX  = 0;
    int maxDivY  = 0;
    int squareSize = 50;
    static const int DELAY = 140;
    char mode;
    int timerId;

    void setModeNoPag();
    void setModePag();
    void setModeInfinite();

    void doDrawing();

    void getDimensions(int , int);
    void initGame();

};

#endif //P1_TECFLIX_WINDOWGUI_H
