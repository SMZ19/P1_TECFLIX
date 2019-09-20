//
// Created by smz on 10/9/19.
//

#include "windowGUI.h"


#include <QPainter>
#include <QTime>
#include <iostream>
#include <QMenu>


using namespace std;

windowGUI::windowGUI(QWidget *parent) : QMainWindow(parent) {

    //setStyleSheet("background-color:white;");

    QPixmap noPagModepix("/home/smz/CLionProjects/P1_TECFLIX/Images/nopagmode.png");
    QPixmap pagModepix("/home/smz/CLionProjects/P1_TECFLIX/Images/pagmode.png");
    QPixmap infiniteModepix("/home/smz/CLionProjects/P1_TECFLIX/Images/infinite.png");
    QPixmap quitpix("/home/smz/CLionProjects/P1_TECFLIX/Images/exit.png");

    QAction *noPagMode = new QAction(noPagModepix, "&Sin paginación", this);
    QAction *pagMode = new QAction(pagModepix, "&Con paginación", this);
    QAction *infiniteMode = new QAction(infiniteModepix, "&Scroll infinito", this);
    QAction *quit = new QAction(quitpix, "&Quit", this);
    quit->setShortcut(tr("CTRL+Q"));

    QMenu *mode;
    mode = menuBar()->addMenu("&Visualization mode ");
    mode->addAction(noPagMode);
    mode->addAction(pagMode);
    mode->addAction(infiniteMode);
    mode->addSeparator();
    mode->addAction(quit);

    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

    connect(quit, &QAction::triggered, qApp, &QApplication::quit);

    connect(noPagMode, &QAction::triggered, this, &windowGUI::setModeNoPag);
    connect(pagMode, &QAction::triggered, this, &windowGUI::setModePag);
    connect(infiniteMode, &QAction::triggered, this, &windowGUI::setModeInfinite);

    resize(B_WIDTH, B_HEIGHT);
    getDimensions(this->width(),this->height());
    initGame();
}

void windowGUI::initGame() {

    timerId = startTimer(DELAY);
}
void windowGUI::getDimensions(int dimX, int dimY) {

    maxDivX = dimX / squareSize;
    maxDivY = dimY / squareSize;


}

void windowGUI::setModeNoPag() {
    nopagMode = true;
    pagMode = false;
    infiniteMode = false;
    cout<<nopagMode<<endl;
    cout<<pagMode<<endl;
    cout<<infiniteMode<<endl;
}
void windowGUI::setModePag() {
    nopagMode = false;
    pagMode = true;
    infiniteMode = false;
    cout<<nopagMode<<endl;
    cout<<pagMode<<endl;
    cout<<infiniteMode<<endl;
}
void windowGUI::setModeInfinite() {
    nopagMode = false;
    pagMode = false;
    infiniteMode = true;
    cout<<nopagMode<<endl;
    cout<<pagMode<<endl;
    cout<<infiniteMode<<endl;
}

void windowGUI::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    doDrawing();

    this->resize(B_WIDTH+zooming,B_HEIGHT+zooming);

    getDimensions(this->width(),this->height());
}

void windowGUI::doDrawing() {

    QPainter qp(this);


    if(nopagMode == true) {
        QPen pen(Qt::black, 1, Qt::SolidLine);
        qp.setPen(pen);
        for (int c = 1; c < maxDivX; c++) {
            for (int f = 1; f < maxDivY; f++) {
                qp.drawRect(c * squareSize, f * squareSize, squareSize - 20, squareSize - 10);
            }
        }
    }else if(pagMode == true){
        QPen pen(Qt::cyan, 1, Qt::SolidLine);
        qp.setPen(pen);
        for (int c = 1; c < maxDivX; c++) {
            for (int f = 1; f < maxDivY; f++) {
                qp.drawRect(c * squareSize, f * squareSize, squareSize - 20, squareSize - 10);
            }
        }
    }else if(infiniteMode == true){
        QPen pen(Qt::red, 1, Qt::SolidLine);
        qp.setPen(pen);
        for (int c = 1; c < maxDivX; c++) {
            for (int f = 1; f < maxDivY; f++) {
                qp.drawRect(c * squareSize, f * squareSize, squareSize - 20, squareSize - 10);
            }
        }
    }



}


void windowGUI::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);


    repaint();
}
void windowGUI::wheelEvent(QWheelEvent *event) {
    if(event->delta() == 120){
        zooming-=10;
        squareSize += 5;
    }else{
        zooming+=10;
        squareSize -= 5;

    }

    QWidget::wheelEvent(event);
}
