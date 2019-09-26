//
// Created by smz on 21/9/19.
//

#ifndef P1_TECFLIX_LINKEDLIST_H
#define P1_TECFLIX_LINKEDLIST_H


#define NULL 0
#include <stdio.h>
#include <QtWidgets/QPushButton>
#include "Page.h"

struct NodeList{
    int value;
    NodeList *next;
    QString title;
    QPushButton *ButtonList[9];
};
class linkedList {
public:
    void createPage();
    NodeList *list = NULL;
    void appendFirst( int);
    void deleteFirst( );
    void appendLast(int );
    void deleteLast();
    void menu();
    void showList(NodeList *);
    int find(int );
    void editList( int , int);
    NodeList* obtainNode(int );
};



#endif //P1_TECFLIX_LINKEDLIST_H
