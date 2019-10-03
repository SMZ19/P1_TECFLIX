//
// Created by smz on 20/9/19.
//

#ifndef P1_TECFLIX_MOVIE_H
#define P1_TECFLIX_MOVIE_H

#include <string>
#include <QtCore/QString>

using namespace std;

class movie {

    public:
        movie(){

        }


        int num;
        QString title;



        void setNum(int );
        int getNum();
        void setTitle( QString );
        QString getTitle();



};


#endif //P1_TECFLIX_MOVIE_H
