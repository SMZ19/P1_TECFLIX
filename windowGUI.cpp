//
// Created by smz on 10/9/19.
//

#include "windowGUI.h"


#include <QPainter>
#include <QTime>
#include <iostream>

using namespace std;

windowGUI::windowGUI(QWidget *parent) : QWidget(parent) {

    setStyleSheet("background-color:white;");
    slider = new QSlider(Qt::Horizontal , this);
    slider->setGeometry(810,100,100,20);
    slider->setValue(10);
    label = new QLabel("0", this);
    label->setGeometry(920,100,100,20);
    connect(slider, &QSlider::valueChanged, label,static_cast<void (QLabel::*)(int)>(&QLabel::setNum));

    resize(B_WIDTH, B_HEIGHT);
    getDimensions(B_WIDTH,B_HEIGHT);
    initGame();
}

void windowGUI::initGame() {

    timerId = startTimer(DELAY);
}
void windowGUI::getDimensions(int dimX, int dimY) {

    maxDivX = dimX / squareSize;
    maxDivY = dimY / squareSize;
    cout<<"MAX en X:"<<maxDivX<<endl;
    cout<<"MAX en Y:"<<maxDivY<<endl;

}

void windowGUI::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    doDrawing();
    squareSize = slider->value();
}

void windowGUI::doDrawing() {

    QPainter qp(this);

    QPen pen(Qt::black, 1, Qt::SolidLine);
    qp.setPen(pen);
    for(int c = 0; c < maxDivX;c++){
        for(int f = 0; f< maxDivY;f++){
            qp.drawRect(c*squareSize,f*squareSize,squareSize,squareSize);
        }
    }



}

void windowGUI::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);


    repaint();
}
