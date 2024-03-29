//
// Created by smz on 10/9/19.
//

#include "windowGUI.h"
#include "cURLParser.h"
#include "ImgDownloader.h"

#include <QPainter>
#include <QTime>
#include <iostream>
#include <QMenu>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
#include <QDebug>


std::vector<std::string> csv_read_row(std::istream &in, char delimiter);




cURLParser urlParser;
ImgDownloader downloader;
linkedList linkedL;
int filmsNotDisplayable = 0;
QPushButton *ButtonListNoPagMode[5043];
QPushButton *ButtonListInfMode[27];



windowGUI::windowGUI(QWidget *parent) : QMainWindow(parent) {


    //setStyleSheet("background-color:black;");

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





    firstBtn = new QPushButton(QString::number(counter1),this);
    firstBtn->setGeometry(100,B_HEIGHT-60,50,50);
    secondBtn = new QPushButton(QString::number(counter2),this);
    secondBtn->setGeometry(150,B_HEIGHT-60,50,50);
    thirdBtn = new QPushButton(QString::number(counter3),this);
    thirdBtn->setGeometry(200,B_HEIGHT-60,50,50);
    previousBtn = new QPushButton(this);
    previousBtn->setIcon(QIcon("/home/smz/CLionProjects/P1_TECFLIX/Images/previous.png"));
    previousBtn->setIconSize(QSize(50, 50));
    previousBtn->setGeometry(50,B_HEIGHT-60,50,50);
    nextBtn = new QPushButton(this);
    nextBtn->setIcon(QIcon("/home/smz/CLionProjects/P1_TECFLIX/Images/next.png"));
    nextBtn->setIconSize(QSize(50, 50));
    nextBtn->setGeometry(250,B_HEIGHT-60,50,50);

    connect(nextBtn, &QPushButton::clicked, this, &windowGUI::changePagesNext);
    connect(previousBtn, &QPushButton::clicked, this, &windowGUI::changePagesPrevious);
    connect(firstBtn, &QPushButton::clicked,this, &windowGUI::loadImagesP1);
    connect(secondBtn, &QPushButton::clicked,this, &windowGUI::loadImagesP2);
    connect(thirdBtn, &QPushButton::clicked,this, &windowGUI::loadImagesP3);
    for(int i = 0; i<5044; i++){
        QPushButton *button = new QPushButton(this);
        ButtonListNoPagMode[i] = button;
        ButtonListNoPagMode[i]->hide();
    }
    for(int i = 0; i<27; i++){
        QPushButton *button = new QPushButton(this);
        ButtonListInfMode[i] = button;
        ButtonListInfMode[i]->hide();
    }
    linkedL.appendFirst(1);
    linkedL.appendFirst(2);
    linkedL.appendFirst(3);

    getMoviesInfo(0,0);
    //getImagesURL(0,0);
    //reorganizeAndDelete(0,0);
    loadImagesP1();


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
void windowGUI::getMoviesInfo(int num, int mode) {
    std::ifstream in("/home/smz/CLionProjects/P1_TECFLIX/dataset/movie_metadata.csv");
    if (in.fail()){
        cout << "File not found" << endl;
    }
    else if(in.good()) {

        if(num == 0) {
            for (int i = 0; i < 27; i++) {
                std::vector<std::string> row = csv_read_row(in, ',');
                movieList[i] = movie();
                movieList[i].setNum(i);
                movieList[i].setTitle(QString::fromStdString(row[11]));



            }
            reorganizeAndDelete(mode,num);

        }else{


            for (int i = 0; i < 27+num; i++) {
                std::vector<std::string> row = csv_read_row(in, ',');
                if(i >= num) {
                    //cout<<row[11]<<endl;
                    movieList[i-num].setTitle(QString::fromStdString(row[11]));


                }else{

                }

            }

            reorganizeAndDelete(mode,num);


        }
    }

    in.close();

}
void windowGUI::reorganizeAndDelete(int mode, int notVisible) {
    if(mode == 0) {
        for (int i = 1; i < 4; i++) {
            for (int n = 0; n < 9; n++) {
                if (i == 1) {
                    linkedL.obtainNode(i)->ButtonList[n] = new QPushButton(this);
                    std::string str = "/home/smz/CLionProjects/P1_TECFLIX/moviesIMG/img";
                    str += std::to_string(n);
                    str += ".jpg";
                    QPixmap pixmap(str.data());

                    QIcon ButtonIcon(pixmap);
                    linkedL.obtainNode(i)->ButtonList[n]->setIcon(ButtonIcon);
                    linkedL.obtainNode(i)->ButtonList[n]->setIconSize(QSize(182, 268));
                    linkedL.obtainNode(i)->ButtonList[n]->hide();
                    linkedL.obtainNode(i)->LabelList[n] = new QLabel(this);
                    linkedL.obtainNode(i)->LabelList[n]->hide();
                } else if (i == 2) {
                    linkedL.obtainNode(i)->ButtonList[n] = new QPushButton(this);
                    std::string str = "/home/smz/CLionProjects/P1_TECFLIX/moviesIMG/img";
                    str += std::to_string(n + 9);
                    str += ".jpg";
                    QPixmap pixmap(str.data());
                    QIcon ButtonIcon(pixmap);
                    linkedL.obtainNode(i)->ButtonList[n]->setIcon(ButtonIcon);
                    linkedL.obtainNode(i)->ButtonList[n]->setIconSize(QSize(182, 268));
                    linkedL.obtainNode(i)->ButtonList[n]->hide();
                    linkedL.obtainNode(i)->LabelList[n] = new QLabel(this);
                    linkedL.obtainNode(i)->LabelList[n]->hide();

                } else if (i == 3) {
                    linkedL.obtainNode(i)->ButtonList[n] = new QPushButton(this);
                    std::string str = "/home/smz/CLionProjects/P1_TECFLIX/moviesIMG/img";
                    str += std::to_string(n + 18);
                    str += ".jpg";
                    QPixmap pixmap(str.data());
                    pixmap.scaledToWidth(100);
                    pixmap.scaledToHeight(100);
                    QIcon ButtonIcon(pixmap);
                    linkedL.obtainNode(i)->ButtonList[n]->setIcon(ButtonIcon);
                    linkedL.obtainNode(i)->ButtonList[n]->setIconSize(QSize(182, 268));
                    linkedL.obtainNode(i)->ButtonList[n]->hide();
                    linkedL.obtainNode(i)->LabelList[n] = new QLabel(this);
                    linkedL.obtainNode(i)->LabelList[n]->hide();

                }

            }

        }
    }else if(mode == 1){

        for (int i = 1; i < 4; i++) {
            for (int n = 0; n < 9; n++) {
                if (i == 1) {

                    std::string str = "/home/smz/CLionProjects/P1_TECFLIX/moviesIMG/img";
                    str += std::to_string(notVisible+n);
                    str += ".jpg";
                    QPixmap pixmap(str.data());

                    QIcon ButtonIcon(pixmap);
                    linkedL.obtainNode(i)->ButtonList[n]->setIcon(ButtonIcon);
                    linkedL.obtainNode(i)->ButtonList[n]->setIconSize(QSize(182, 268));

                } else if (i == 2) {

                    std::string str = "/home/smz/CLionProjects/P1_TECFLIX/moviesIMG/img";
                    str += std::to_string(n + 9+notVisible);
                    str += ".jpg";
                    QPixmap pixmap(str.data());
                    QIcon ButtonIcon(pixmap);
                    linkedL.obtainNode(i)->ButtonList[n]->setIcon(ButtonIcon);
                    linkedL.obtainNode(i)->ButtonList[n]->setIconSize(QSize(182, 268));


                } else if (i == 3) {

                    std::string str = "/home/smz/CLionProjects/P1_TECFLIX/moviesIMG/img";
                    str += std::to_string(n + 18+notVisible);
                    str += ".jpg";
                    QPixmap pixmap(str.data());
                    pixmap.scaledToWidth(100);
                    pixmap.scaledToHeight(100);
                    QIcon ButtonIcon(pixmap);
                    linkedL.obtainNode(i)->ButtonList[n]->setIcon(ButtonIcon);
                    linkedL.obtainNode(i)->ButtonList[n]->setIconSize(QSize(182, 268));

                }

            }

        }


    }else if(mode == 2){
        cout<<"Not Visible: "<<notVisible<<endl;
        for (int i = 1; i < 4; i++) {
            for (int n = 0; n < 9; n++) {
                if (i == 1) {

                    std::string str = "/home/smz/CLionProjects/P1_TECFLIX/moviesIMG/img";
                    str += std::to_string(notVisible+n);
                    str += ".jpg";
                    QPixmap pixmap(str.data());

                    QIcon ButtonIcon(pixmap);
                    linkedL.obtainNode(i)->ButtonList[n]->setIcon(ButtonIcon);
                    linkedL.obtainNode(i)->ButtonList[n]->setIconSize(QSize(182, 268));

                } else if (i == 2) {

                    std::string str = "/home/smz/CLionProjects/P1_TECFLIX/moviesIMG/img";
                    str += std::to_string(n + 9+notVisible);
                    str += ".jpg";
                    QPixmap pixmap(str.data());
                    QIcon ButtonIcon(pixmap);
                    linkedL.obtainNode(i)->ButtonList[n]->setIcon(ButtonIcon);
                    linkedL.obtainNode(i)->ButtonList[n]->setIconSize(QSize(182, 268));


                } else if (i == 3) {

                    std::string str = "/home/smz/CLionProjects/P1_TECFLIX/moviesIMG/img";
                    str += std::to_string(n + 18+notVisible);
                    str += ".jpg";
                    QPixmap pixmap(str.data());
                    pixmap.scaledToWidth(100);
                    pixmap.scaledToHeight(100);
                    QIcon ButtonIcon(pixmap);
                    linkedL.obtainNode(i)->ButtonList[n]->setIcon(ButtonIcon);
                    linkedL.obtainNode(i)->ButtonList[n]->setIconSize(QSize(182, 268));

                }

            }

        }


    }

}
/*
void windowGUI::getImagesURL(int mode , int NotVisible){
    int counting = 0;
    for(std::list<std::string>::const_iterator i = moviesHTMLList.begin(); i != moviesHTMLList.end(); ++i)
    {
        //cout<<"link: "<< urlParser.getURL(i->c_str())<<endl;
        if(mode == 0) {
            downloader.download(urlParser.getURL(i->c_str()), counting);
        }else if(mode == 1){
            if(counting > 17){
                downloader.download(urlParser.getURL(i->c_str()), counting+NotVisible);
            }
        }else if(mode == 2){
            if(counting < 9){
                downloader.download(urlParser.getURL(i->c_str()), counting);
            }
        }
        counting++;
    }


}
*/

void windowGUI::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);
    doDrawing();
    if(nopagMode || pagMode) {
        if ((B_HEIGHT + zooming) < 650 && B_WIDTH + zooming > 400 && B_HEIGHT + zooming > 400) {
            this->resize(B_WIDTH + zooming, B_HEIGHT + zooming);
        } else {
            if ((B_WIDTH + zooming < 450) && (B_HEIGHT + zooming) < 450) {
                this->resize(449, 449);

            } else {

                this->resize(B_WIDTH + zooming, B_HEIGHT);
            }
        }


        getDimensions(this->width(), this->height());
    }
}

void windowGUI::doDrawing() {

    QPainter qp(this);


    if(nopagMode == true ) {

        hideItems(1);
        hideItems(2);
        hideItems(3);
        firstBtn->hide();
        secondBtn->hide();
        thirdBtn->hide();
        nextBtn->hide();
        previousBtn->hide();
        QPen pen(Qt::black, 1, Qt::SolidLine);
        qp.setPen(pen);

        int counter1 = 0;
        for (int c = 0; c < maxDivX; c++) {
            for (int f = 0; f < maxDivY; f++) {
                if (this->width() == 449 && this->height() == 449) {
                    qp.drawRect(0, 0, 400, 400);
                } else {




                    std::string str = "/home/smz/CLionProjects/P1_TECFLIX/moviesIMG/img";
                    str += std::to_string(counter1);
                    str += ".jpg";
                    QPixmap pixmap(str.data());

                    QIcon ButtonIcon(pixmap);
                    ButtonListNoPagMode[counter1]->setIcon(ButtonIcon);
                    ButtonListNoPagMode[counter1]->setIconSize(QSize(squareSize - 20, squareSize - 10));


                    ButtonListNoPagMode[counter1]->setGeometry(c * squareSize, (f * squareSize)+20, squareSize - 20,squareSize - 10);
                    ButtonListNoPagMode[counter1]->show();

                    //qp.drawRect(c * squareSize, (f * squareSize)+20, squareSize - 20, squareSize - 10);
                    counter1++;
                }

            }
        }



    }else if(pagMode == true ){
        for(int i = 0; i<5044; i++){
            ButtonListNoPagMode[i]->hide();
        }


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
        for(int i = 0; i<5044; i++){
            ButtonListNoPagMode[i]->hide();
        }
        hideItems(1);
        hideItems(2);
        hideItems(3);
        firstBtn->hide();
        secondBtn->hide();
        thirdBtn->hide();
        nextBtn->hide();
        previousBtn->hide();
        QPen pen(Qt::red, 1, Qt::SolidLine);
        qp.setPen(pen);

        int itemsCounter = 0;
        int counterX = 0;
        int rowsToBeAdded = 9;
        for (int c = 0; c < 3; c++) {
            for (int f = 0; f < 9; f++) {
                std::string str = "/home/smz/CLionProjects/P1_TECFLIX/moviesIMG/img";
                str += std::to_string(itemsCounter);
                str += ".jpg";
                QPixmap pixmap(str.data());

                QIcon ButtonIcon(pixmap);
                ButtonListInfMode[itemsCounter]->setIcon(ButtonIcon);
                ButtonListInfMode[itemsCounter]->setIconSize(QSize(168, 200));


                ButtonListInfMode[itemsCounter]->setGeometry((c*200) +300, (f*210)  +30+zooming, 168, 200);
                ButtonListInfMode[itemsCounter]->show();



                if (ButtonListInfMode[itemsCounter]->y() <= 0) {

                    ButtonListInfMode[itemsCounter]->setGeometry((counterX * 200) + 300, (rowsToBeAdded * 210) + 30 + zooming, 168, 200);
                    ButtonListInfMode[itemsCounter]->show();
                    counterX++;
                    if(counterX == 3){
                        counterX = 0;
                        rowsToBeAdded++;
                    }


                }


                //cout<<"Filas: "<<rowsToBeAdded<<endl;
                //qp.drawRect((c*200) +300, (f*210)  +30+zooming, 168, 200);
                itemsCounter++;
            }
        }
    }



}
void windowGUI::loadImagesP1() {

    for(int n = 0; n < 9; n+=5){

        if(n!=5) {

            linkedL.obtainNode(1)->ButtonList[n]->setGeometry((previousBtn->x()-25), (n * 10) + 20, 168,268);
            linkedL.obtainNode(1)->ButtonList[n]->show();
            linkedL.obtainNode(1)->ButtonList[n+1]->setGeometry((previousBtn->x()-25)+200, (n * 10) + 20, 168,268);
            linkedL.obtainNode(1)->ButtonList[n+1]->show();
            linkedL.obtainNode(1)->ButtonList[n+2]->setGeometry((previousBtn->x()-25)+400, (n * 10) + 20, 168,268);
            linkedL.obtainNode(1)->ButtonList[n+2]->show();
            linkedL.obtainNode(1)->ButtonList[n+3]->setGeometry((previousBtn->x()-25)+600, (n * 10) + 20, 168,268);
            linkedL.obtainNode(1)->ButtonList[n+3]->show();


            linkedL.obtainNode(1)->LabelList[n]->setGeometry((previousBtn->x()-25), linkedL.obtainNode(1)->ButtonList[n]->y()+230, 168, 100);
            linkedL.obtainNode(1)->LabelList[n]->setText(movieList[n].getTitle());
            linkedL.obtainNode(1)->LabelList[n]->show();

            linkedL.obtainNode(1)->LabelList[n+1]->setGeometry((previousBtn->x()-25)+200, linkedL.obtainNode(1)->ButtonList[n+1]->y()+230, 168, 100);

            linkedL.obtainNode(1)->LabelList[n+1]->setText(movieList[n+1].getTitle());
            linkedL.obtainNode(1)->LabelList[n+1]->show();

            linkedL.obtainNode(1)->LabelList[n+2]->setGeometry((previousBtn->x()-25)+400, linkedL.obtainNode(1)->ButtonList[n+2]->y()+230 , 168, 100);
            linkedL.obtainNode(1)->LabelList[n+2]->setText(movieList[n+2].getTitle());
            linkedL.obtainNode(1)->LabelList[n+2]->show();

            linkedL.obtainNode(1)->LabelList[n+3]->setGeometry((previousBtn->x()-25)+600, linkedL.obtainNode(1)->ButtonList[n+3]->y()+230 , 168, 100);
            linkedL.obtainNode(1)->LabelList[n+3]->setText(movieList[n+3].getTitle());
            linkedL.obtainNode(1)->LabelList[n+3]->show();
            linkedL.obtainNode(1)->ButtonList[n + 4]->setGeometry((previousBtn->x() - 25) + 800, (n * 10) + 20, 168,268);
            linkedL.obtainNode(1)->ButtonList[n + 4]->show();
            linkedL.obtainNode(1)->LabelList[n+4]->setGeometry((previousBtn->x()-25)+800, linkedL.obtainNode(1)->ButtonList[n+4]->y()+230 , 168, 100);
            linkedL.obtainNode(1)->LabelList[n+4]->setText(movieList[n+4].getTitle());
            linkedL.obtainNode(1)->LabelList[n+4]->show();
        }else{

            linkedL.obtainNode(1)->ButtonList[n]->setGeometry((previousBtn->x()-25), (n * 60) + 30, 168,268);
            linkedL.obtainNode(1)->ButtonList[n]->show();
            linkedL.obtainNode(1)->ButtonList[n+1]->setGeometry((previousBtn->x()-25)+200, (n * 60) + 30, 168,268);
            linkedL.obtainNode(1)->ButtonList[n+1]->show();
            linkedL.obtainNode(1)->ButtonList[n+2]->setGeometry((previousBtn->x()-25)+400, (n * 60) + 30, 168,268);
            linkedL.obtainNode(1)->ButtonList[n+2]->show();
            linkedL.obtainNode(1)->ButtonList[n+3]->setGeometry((previousBtn->x()-25)+600, (n * 60) + 30, 168,268);
            linkedL.obtainNode(1)->ButtonList[n+3]->show();


            linkedL.obtainNode(1)->LabelList[n]->setGeometry((previousBtn->x()-25), linkedL.obtainNode(1)->ButtonList[n]->y()+230, 168, 100);
            linkedL.obtainNode(1)->LabelList[n]->setText(movieList[n].getTitle());

            linkedL.obtainNode(1)->LabelList[n]->show();

            linkedL.obtainNode(1)->LabelList[n+1]->setGeometry((previousBtn->x()-25)+200, linkedL.obtainNode(1)->ButtonList[n+1]->y()+230, 168, 100);
            linkedL.obtainNode(1)->LabelList[n+1]->setText(movieList[n+1].getTitle());

            linkedL.obtainNode(1)->LabelList[n+1]->show();

            linkedL.obtainNode(1)->LabelList[n+2]->setGeometry((previousBtn->x()-25)+400, linkedL.obtainNode(1)->ButtonList[n+2]->y()+230 , 168, 100);
            linkedL.obtainNode(1)->LabelList[n+2]->setText(movieList[n+2].getTitle());
            linkedL.obtainNode(1)->LabelList[n+2]->show();

            linkedL.obtainNode(1)->LabelList[n+3]->setGeometry((previousBtn->x()-25)+600, linkedL.obtainNode(1)->ButtonList[n+3]->y()+230 , 168, 100);
            linkedL.obtainNode(1)->LabelList[n+3]->setText(movieList[n+3].getTitle());
            linkedL.obtainNode(1)->LabelList[n+3]->show();

        }

        hideItems(2);
        hideItems(3);
        update();
    }

}
void windowGUI::loadImagesP2() {

    for(int n = 0; n < 9; n+=5){

        if(n!=5) {

            linkedL.obtainNode(2)->ButtonList[n]->setGeometry((previousBtn->x()-25), (n * 10) + 20, 168,268);
            linkedL.obtainNode(2)->ButtonList[n]->show();
            linkedL.obtainNode(2)->ButtonList[n+1]->setGeometry((previousBtn->x()-25)+200, (n * 10) + 20, 168,268);
            linkedL.obtainNode(2)->ButtonList[n+1]->show();
            linkedL.obtainNode(2)->ButtonList[n+2]->setGeometry((previousBtn->x()-25)+400, (n * 10) + 20, 168,268);
            linkedL.obtainNode(2)->ButtonList[n+2]->show();
            linkedL.obtainNode(2)->ButtonList[n+3]->setGeometry((previousBtn->x()-25)+600, (n * 10) + 20, 168,268);
            linkedL.obtainNode(2)->ButtonList[n+3]->show();


            linkedL.obtainNode(2)->LabelList[n]->setGeometry((previousBtn->x()-25), linkedL.obtainNode(2)->ButtonList[n]->y()+230, 168, 100);
            linkedL.obtainNode(2)->LabelList[n]->setText(movieList[n+9].getTitle());
            linkedL.obtainNode(2)->LabelList[n]->show();

            linkedL.obtainNode(2)->LabelList[n+1]->setGeometry((previousBtn->x()-25)+200, linkedL.obtainNode(2)->ButtonList[n+1]->y()+230, 168, 100);

            linkedL.obtainNode(2)->LabelList[n+1]->setText(movieList[n+10].getTitle());
            linkedL.obtainNode(2)->LabelList[n+1]->show();

            linkedL.obtainNode(2)->LabelList[n+2]->setGeometry((previousBtn->x()-25)+400, linkedL.obtainNode(2)->ButtonList[n+2]->y()+230 , 168, 100);
            linkedL.obtainNode(2)->LabelList[n+2]->setText(movieList[n+11].getTitle());
            linkedL.obtainNode(2)->LabelList[n+2]->show();

            linkedL.obtainNode(2)->LabelList[n+3]->setGeometry((previousBtn->x()-25)+600, linkedL.obtainNode(2)->ButtonList[n+3]->y()+230 , 168, 100);
            linkedL.obtainNode(2)->LabelList[n+3]->setText(movieList[n+12].getTitle());
            linkedL.obtainNode(2)->LabelList[n+3]->show();
            linkedL.obtainNode(2)->ButtonList[n + 4]->setGeometry((previousBtn->x() - 25) + 800, (n * 10) + 20, 168,268);
            linkedL.obtainNode(2)->ButtonList[n + 4]->show();
            linkedL.obtainNode(2)->LabelList[n+4]->setGeometry((previousBtn->x()-25)+800, linkedL.obtainNode(2)->ButtonList[n+4]->y()+230 , 168, 100);
            linkedL.obtainNode(2)->LabelList[n+4]->setText(movieList[n+13].getTitle());
            linkedL.obtainNode(2)->LabelList[n+4]->show();
        }else{

            linkedL.obtainNode(2)->ButtonList[n]->setGeometry((previousBtn->x()-25), (n * 60) + 30, 168,268);
            linkedL.obtainNode(2)->ButtonList[n]->show();
            linkedL.obtainNode(2)->ButtonList[n+1]->setGeometry((previousBtn->x()-25)+200, (n * 60) + 30, 168,268);
            linkedL.obtainNode(2)->ButtonList[n+1]->show();
            linkedL.obtainNode(2)->ButtonList[n+2]->setGeometry((previousBtn->x()-25)+400, (n * 60) + 30, 168,268);
            linkedL.obtainNode(2)->ButtonList[n+2]->show();
            linkedL.obtainNode(2)->ButtonList[n+3]->setGeometry((previousBtn->x()-25)+600, (n * 60) + 30, 168,268);
            linkedL.obtainNode(2)->ButtonList[n+3]->show();


            linkedL.obtainNode(2)->LabelList[n]->setGeometry((previousBtn->x()-25), linkedL.obtainNode(2)->ButtonList[n]->y()+230, 168, 100);
            linkedL.obtainNode(2)->LabelList[n]->setText(movieList[n+9].getTitle());

            linkedL.obtainNode(2)->LabelList[n]->show();

            linkedL.obtainNode(2)->LabelList[n+1]->setGeometry((previousBtn->x()-25)+200, linkedL.obtainNode(2)->ButtonList[n+1]->y()+230, 168, 100);
            linkedL.obtainNode(2)->LabelList[n+1]->setText(movieList[n+10].getTitle());

            linkedL.obtainNode(2)->LabelList[n+1]->show();

            linkedL.obtainNode(2)->LabelList[n+2]->setGeometry((previousBtn->x()-25)+400, linkedL.obtainNode(2)->ButtonList[n+2]->y()+230 , 168, 100);
            linkedL.obtainNode(2)->LabelList[n+2]->setText(movieList[n+11].getTitle());
            linkedL.obtainNode(2)->LabelList[n+2]->show();

            linkedL.obtainNode(2)->LabelList[n+3]->setGeometry((previousBtn->x()-25)+600, linkedL.obtainNode(2)->ButtonList[n+3]->y()+230 , 168, 100);
            linkedL.obtainNode(2)->LabelList[n+3]->setText(movieList[n+12].getTitle());
            linkedL.obtainNode(2)->LabelList[n+3]->show();

        }


        hideItems(1);
        hideItems(3);
        update();
    }
}
void windowGUI::loadImagesP3() {

    for(int n = 0; n < 9; n+=5){

        if(n!=5) {

            linkedL.obtainNode(3)->ButtonList[n]->setGeometry((previousBtn->x()-25), (n * 10) + 20, 168,268);
            linkedL.obtainNode(3)->ButtonList[n]->show();
            linkedL.obtainNode(3)->ButtonList[n+1]->setGeometry((previousBtn->x()-25)+200, (n * 10) + 20, 168,268);
            linkedL.obtainNode(3)->ButtonList[n+1]->show();
            linkedL.obtainNode(3)->ButtonList[n+2]->setGeometry((previousBtn->x()-25)+400, (n * 10) + 20, 168,268);
            linkedL.obtainNode(3)->ButtonList[n+2]->show();
            linkedL.obtainNode(3)->ButtonList[n+3]->setGeometry((previousBtn->x()-25)+600, (n * 10) + 20, 168,268);
            linkedL.obtainNode(3)->ButtonList[n+3]->show();


            linkedL.obtainNode(3)->LabelList[n]->setGeometry((previousBtn->x()-25), linkedL.obtainNode(3)->ButtonList[n]->y()+230, 168, 100);
            linkedL.obtainNode(3)->LabelList[n]->setText(movieList[n+18].getTitle());
            linkedL.obtainNode(3)->LabelList[n]->show();

            linkedL.obtainNode(3)->LabelList[n+1]->setGeometry((previousBtn->x()-25)+200, linkedL.obtainNode(3)->ButtonList[n+1]->y()+230, 168, 100);

            linkedL.obtainNode(3)->LabelList[n+1]->setText(movieList[n+19].getTitle());
            linkedL.obtainNode(3)->LabelList[n+1]->show();

            linkedL.obtainNode(3)->LabelList[n+2]->setGeometry((previousBtn->x()-25)+400, linkedL.obtainNode(3)->ButtonList[n+2]->y()+230 , 168, 100);
            linkedL.obtainNode(3)->LabelList[n+2]->setText(movieList[n+20].getTitle());
            linkedL.obtainNode(3)->LabelList[n+2]->show();

            linkedL.obtainNode(3)->LabelList[n+3]->setGeometry((previousBtn->x()-25)+600, linkedL.obtainNode(3)->ButtonList[n+3]->y()+230 , 168, 100);
            linkedL.obtainNode(3)->LabelList[n+3]->setText(movieList[n+21].getTitle());
            linkedL.obtainNode(3)->LabelList[n+3]->show();
            linkedL.obtainNode(3)->ButtonList[n + 4]->setGeometry((previousBtn->x() - 25) + 800, (n * 10) + 20, 168,268);
            linkedL.obtainNode(3)->ButtonList[n + 4]->show();
            linkedL.obtainNode(3)->LabelList[n+4]->setGeometry((previousBtn->x()-25)+800, linkedL.obtainNode(3)->ButtonList[n+4]->y()+230 , 168, 100);
            linkedL.obtainNode(3)->LabelList[n+4]->setText(movieList[n+22].getTitle());
            linkedL.obtainNode(3)->LabelList[n+4]->show();
        }else{

            linkedL.obtainNode(3)->ButtonList[n]->setGeometry((previousBtn->x()-25), (n * 60) + 30, 168,268);
            linkedL.obtainNode(3)->ButtonList[n]->show();
            linkedL.obtainNode(3)->ButtonList[n+1]->setGeometry((previousBtn->x()-25)+200, (n * 60) + 30, 168,268);
            linkedL.obtainNode(3)->ButtonList[n+1]->show();
            linkedL.obtainNode(3)->ButtonList[n+2]->setGeometry((previousBtn->x()-25)+400, (n * 60) + 30, 168,268);
            linkedL.obtainNode(3)->ButtonList[n+2]->show();
            linkedL.obtainNode(3)->ButtonList[n+3]->setGeometry((previousBtn->x()-25)+600, (n * 60) + 30, 168,268);
            linkedL.obtainNode(3)->ButtonList[n+3]->show();


            linkedL.obtainNode(3)->LabelList[n]->setGeometry((previousBtn->x()-25), linkedL.obtainNode(3)->ButtonList[n]->y()+230, 168, 100);
            linkedL.obtainNode(3)->LabelList[n]->setText(movieList[n+18].getTitle());

            linkedL.obtainNode(3)->LabelList[n]->show();

            linkedL.obtainNode(3)->LabelList[n+1]->setGeometry((previousBtn->x()-25)+200, linkedL.obtainNode(3)->ButtonList[n+1]->y()+230, 168, 100);
            linkedL.obtainNode(3)->LabelList[n+1]->setText(movieList[n+19].getTitle());

            linkedL.obtainNode(3)->LabelList[n+1]->show();

            linkedL.obtainNode(3)->LabelList[n+2]->setGeometry((previousBtn->x()-25)+400, linkedL.obtainNode(3)->ButtonList[n+2]->y()+230 , 168, 100);
            linkedL.obtainNode(3)->LabelList[n+2]->setText(movieList[n+20].getTitle());
            linkedL.obtainNode(3)->LabelList[n+2]->show();

            linkedL.obtainNode(3)->LabelList[n+3]->setGeometry((previousBtn->x()-25)+600, linkedL.obtainNode(3)->ButtonList[n+3]->y()+230 , 168, 100);
            linkedL.obtainNode(3)->LabelList[n+3]->setText(movieList[n+21].getTitle());
            linkedL.obtainNode(3)->LabelList[n+3]->show();

        }
        hideItems(2);
        hideItems(1);
        update();
    }
}
void windowGUI::hideItems(int num) {
    for (int n = 0; n < 9; n++) {
        linkedL.obtainNode(num)->ButtonList[n]->hide();
        linkedL.obtainNode(num)->LabelList[n]->hide();
    }

}
void windowGUI::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);

    repaint();
}
void windowGUI::wheelEvent(QWheelEvent *event) {
    if(nopagMode) {
        if (event->delta() == 120) {
            zooming -= 10;
            squareSize += 5;
        } else {
            zooming += 10;
            squareSize -= 5;

        }
        for (int i = 0; i < 5044; i++) {
            ButtonListNoPagMode[i]->hide();
        }
    }else if(infiniteMode){
        if (event->delta() == 120) {
            zooming -= 10;

        } else {
            zooming += 10;


        }
    }

    QWidget::wheelEvent(event);
}
void windowGUI::changePagesNext() {
    hideItems(1);
    hideItems(2);
    hideItems(3);

    counter1+=1;
    counter2+=1;
    counter3+=1;


    linkedL.obtainNode(1)->value = counter1;
    linkedL.obtainNode(2)->value = counter2;
    linkedL.obtainNode(3)->value = counter3;

    //cout<<"Me lleva: " << linkedL.obtainNode(2)->value << endl;
    firstBtn->setText(QString::number(linkedL.obtainNode(1)->value));
    secondBtn->setText(QString::number(linkedL.obtainNode(2)->value));
    thirdBtn->setText(QString::number(linkedL.obtainNode(3)->value));

    filmsNotDisplayable +=9;
    getMoviesInfo(filmsNotDisplayable,1);
    loadImagesP1();


}
void windowGUI::changePagesPrevious() {

    if(firstBtn->text() >= "1") {
        hideItems(1);
        hideItems(2);
        hideItems(3);
        counter1 -= 1;
        counter2 -= 1;
        counter3 -= 1;

        linkedL.obtainNode(1)->value = counter1;
        linkedL.obtainNode(2)->value = counter2;
        linkedL.obtainNode(3)->value = counter3;

        firstBtn->setText(QString::number(linkedL.obtainNode(1)->value));
        secondBtn->setText(QString::number(linkedL.obtainNode(2)->value));
        thirdBtn->setText(QString::number(linkedL.obtainNode(3)->value));
        filmsNotDisplayable -= 9;
        getMoviesInfo(filmsNotDisplayable,2);

        loadImagesP1();

    }


}
std::vector<std::string> csv_read_row(std::istream &in, char delimiter)
{
    std::stringstream ss;
    bool inquotes = false;
    std::vector<std::string> row;//relying on RVO
    while(in.good())
    {
        char c = in.get();
        if (!inquotes && c=='"') //beginquotechar
        {
            inquotes=true;
        }
        else if (inquotes && c=='"') //quotechar
        {
            if ( in.peek() == '"')//2 consecutive quotes resolve to 1
            {
                ss << (char)in.get();
            }
            else //endquotechar
            {
                inquotes=false;
            }
        }
        else if (!inquotes && c==delimiter) //end of field
        {
            row.push_back( ss.str() );
            ss.str("");
        }
        else if (!inquotes && (c=='\r' || c=='\n') )
        {
            if(in.peek()=='\n') { in.get(); }
            row.push_back( ss.str() );
            return row;
        }
        else
        {
            ss << c;
        }
    }
}
