//
// Created by smz on 21/9/19.
//
#include "linkedList.h"
#include <iostream>

using  namespace std;

void linkedList ::appendFirst(int n) {

    NodeList *new_Node = new NodeList();
    new_Node->value = n;
    new_Node->next = list;

    list = new_Node;

    cout << "\tElement "<<n<< " has been appended correctly"<<endl;
}
void linkedList ::deleteFirst() {
    if(list == NULL){
        cout << "List is empty"<< endl;
    }else{
        NodeList *ptr = list;
        list = list->next;
        cout<<"Unfortunately, the node "<< ptr->value<<" has been deleted :(";
        free(ptr);
    }
}
void linkedList::appendLast(int n) {
    NodeList *current = new NodeList();
    current = list;

    while((current != NULL)){
        if(current->next == NULL){

            NodeList *new_Node = new NodeList();

            new_Node->value = n;
            current->next = new_Node;
            new_Node->next = NULL;
            break;


        }else {

            current = current->next;
        }
    }

}
void linkedList::deleteLast() {
    NodeList *current = new NodeList();
    current = list;

    while((current != NULL)){
        if(current->next->next == NULL){
            if(list == NULL){
                cout << "List is empty"<< endl;
            }else{
                cout<<"Unfortunately, the node "<< current->next->value<<" has been deleted :("<<endl;
                NodeList *ptr = current->next->next;
                current->next =NULL;
                free(ptr);
                break;

            }
            break;


        }else {

            current = current->next;
        }
    }

}
void linkedList ::showList(NodeList *list) {
    NodeList *current;
    current = list;
    cout<<"\nYour list: "<<endl;
    while(current !=  NULL){
        cout <<current->value<<" -> ";
        current = current->next;
    }
    cout<<"\n";
}
int linkedList :: find(int pos) {
    NodeList *current = new NodeList();
    current = list;
    int counter =1;

    while((current != NULL)){
        if(counter == pos){
            cout << "The value in positon: "<< pos<< " is: "<< current->value<<endl;

            return current->value;

        }
        counter++;
        current = current->next;
    }

}
NodeList* linkedList::obtainNode(int pos) {
    NodeList *current = new NodeList();
    current = list;
    int counter =1;

    while((current != NULL)){
        if(counter == pos){
            //cout << "The value in positon: "<< pos<< " is: "<< current->value;

            return current;

        }
        counter++;
        current = current->next;
    }
}
void linkedList::editList(int pos, int n) {
    NodeList *current = new NodeList();
    current = list;
    int counter =1;

    while((current != NULL)){
        if(counter == pos){
            cout << "The value in positon "<< pos<< " is "<< current->value<<" and has been replaced by: "<< n;
            current->value = n;

        }
        counter++;
        current = current->next;
    }
}


