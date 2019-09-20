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




    getDimensions(this->width(),this->height());
    initGame();
    for(int i = 0; i < 27 ; i++){

        movieList[i] = movie();
        movieList[i].setNum(i);
        movieList[i].setTitle("27");
    }



    firstBtn = new QPushButton(QString::number(movieList[counter1].getNum()),this);
    firstBtn->setGeometry(200,500,50,50);
    secondBtn = new QPushButton(QString::number(movieList[counter2].getNum()),this);
    secondBtn->setGeometry(250,500,50,50);
    thirdBtn = new QPushButton(QString::number(movieList[counter3].getNum()),this);
    thirdBtn->setGeometry(300,500,50,50);
    previousBtn = new QPushButton(this);
    previousBtn->setIcon(QIcon("/home/smz/CLionProjects/P1_TECFLIX/Images/previous.png"));
    previousBtn->setIconSize(QSize(50, 50));
    previousBtn->setGeometry(140,500,50,50);
    nextBtn = new QPushButton(this);
    nextBtn->setIcon(QIcon("/home/smz/CLionProjects/P1_TECFLIX/Images/next.png"));
    nextBtn->setIconSize(QSize(50, 50));
    nextBtn->setGeometry(360,500,50,50);



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

}
void windowGUI::setModePag() {
    nopagMode = false;
    pagMode = true;
    infiniteMode = false;

}
void windowGUI::setModeInfinite() {
    nopagMode = false;
    pagMode = false;
    infiniteMode = true;

}

void windowGUI::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    doDrawing();
    if((B_HEIGHT + zooming) < 650 && B_WIDTH+zooming > 400 && B_HEIGHT+zooming > 400) {
        this->resize(B_WIDTH + zooming, B_HEIGHT + zooming);
    }else{
        if((B_WIDTH+zooming < 450) && (B_HEIGHT+zooming) < 450){
            this->resize(449 , 449);

        }else{

            this->resize(B_WIDTH + zooming, B_HEIGHT);
        }
    }


    getDimensions(this->width(),this->height());
}

void windowGUI::doDrawing() {

    QPainter qp(this);


    if(nopagMode == true ) {
        firstBtn->hide();
        secondBtn->hide();
        thirdBtn->hide();
        nextBtn->hide();
        previousBtn->hide();
        QPen pen(Qt::black, 1, Qt::SolidLine);
        qp.setPen(pen);
        for (int c = 0; c < maxDivX; c++) {
            for (int f = 0; f < maxDivY; f++) {
                if(this->width() == 449 && this->height() == 449){
                    qp.drawRect(0, 0, 400, 400);
                }
                else {
                    qp.drawRect(c * squareSize, f * squareSize, squareSize - 20, squareSize - 10);
                }
            }
        }
    }else if(pagMode == true ){
        firstBtn->show();
        secondBtn->show();
        thirdBtn->show();
        nextBtn->show();
        previousBtn->show();
        /*
        QPen pen(Qt::cyan, 1, Qt::SolidLine);
        qp.setPen(pen);
        for (int c = 0; c < maxDivX; c++) {
            for (int f = 0; f < maxDivY; f++) {
                qp.drawRect(c * squareSize, f * squareSize, squareSize - 20, squareSize - 10);
            }
        }*/

    }else if(infiniteMode == true){
        QPen pen(Qt::red, 1, Qt::SolidLine);
        qp.setPen(pen);
        for (int c = 0; c < maxDivX; c++) {
            for (int f = 0; f < maxDivY; f++) {
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
