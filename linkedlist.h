//
// Created by Ashwi on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_LINKEDLIST_H
#define INC_20F_FLT_PLN_LINKEDLIST_H

#include <iostream>
#include <fstream>
#include "stringclass.h"
#include <sstream>

using namespace std;

template <class T>
class my_node{
    template <class t> friend class linkedlist;
public:
    my_node<T>():next(nullptr),prev(nullptr){}
    my_node<T>(T val):next(nullptr),prev(nullptr),data(val){}
    my_node<T>(const my_node<T>& data2){
        next = data2.next;
        prev = data2.prev;
        data = data2.data;
    }

    ~my_node(){
        delete next;
    }

//    my_node& operator = (const my_node &newThing){
//        this -> data = newThing.data;
//        this -> next = newThing.next;
//        this -> prev = newThing.prev;
//        return *this;
//    }

    T* get_data_pointer(){
        return data;
    }

    T &getData(){
        return data;
    }

    my_node* getNext(){
        return next;
    }

    void setNext(my_node<T> *thing){
        next = thing;
    }

    void setData(T thing){
        data = thing;
    }

    void setPrev(my_node<T> *thing){
        prev = thing;
    }

    my_node* getPrev(){
        return prev;
    }

private:
    my_node<T>* next;
    my_node<T>* prev;
    T data;
};

template <class T>
class linkedlist{
private:
    my_node<T>* front;
    my_node<T>* back;
    my_node<T>* current;
    int size;

public:
    linkedlist<T>(){
        front  = nullptr;
        back = nullptr;
        size = 0;
    }

    linkedlist<T>(const linkedlist& thing) {
        size = 0;
        front = nullptr;
        back = nullptr;
        for (int i = 0; i < thing.getSize(); i++) {
            push_back(thing[i]);
        }
    }

    ~linkedlist(){
        delete front;
    }

    void push_back(T pushBack){
        my_node<T>* toPush = nullptr;
        if(front == nullptr){ // linked list is empty
            front = new my_node<T> (pushBack);
            back = front;
        }
        else{ // linked list not empty
            toPush = new my_node<T> (pushBack); // new node with data of pushBack
            back->setNext(toPush); // back points to node that points to toPush
            toPush->setPrev(back); // back->getNext() = toPush
            back = toPush; // toPush is at end of list, back of list is toPush
        }
        size++;
    }

    int getSize() const{
//        my_node<T>* curr;
//        if(front == nullptr){ // no elements
//            return 0;
//        }
//        else if(front == back || front->next == nullptr){ // one element
//            return 1;
//        }
//        else{
//            curr = front;
//            int size = 1;
//            while(curr != back){
//                curr = curr->getNext();
//                size++;
//            }
        return size;
        //}
    }

    void sort_list(){
        int n = this->getSize();
        int i, j;
        for(i = 0; i < n-1; i++){
            for(j = 0; j < n-i-1; j++){
                if((*this)[j+1] < (*this)[j]){      // element in front of j
                    swapper(j, j+1);
                }
            }
        }
    }

    void swapper(int left, int right){
        int temp = indexNode(left)->getData();
        indexNode(left)->setData(indexNode(right)->getData());
        indexNode(right)->setData(temp);
    }

    my_node<T>* indexNode(int find){
        my_node<T>* current = front;
        int counter = 0;
        while(counter < find && current->getNext() != nullptr){
            current = current->next;
            counter++;
        }
        return current;
    }

    void remove_duplicates(){
        sort_list();
        if(this->getSize() == 0 || this->getSize() == 1){
            return;
        }
        for(int i =1; i < this->getSize(); i++){
            if((*this)[i] == (*this)[i-1]){
                remove(i);
                i--;
            }
        }
    }

    void remove(int deleteNode){
        if(deleteNode == 0){ // removing from the beginning
            if(this-> getSize () == 1){ // if there is only one element in list
                this-> front = this->back = nullptr;
            }
            else if(this-> getSize () > 2) { // if there are more than 2 elements in list
                this->front = this->front->getNext();
            }
            else if(this-> getSize () == 2) { // if there is 2 elements, start is set to the next one (what end originally was
                my_node<T>* tempo = this -> front;          // for segfaults
                this-> front = this-> front->getNext();
                delete tempo;
                this-> back = this -> front;
            }
        }

        else if(deleteNode > 0 && deleteNode < this->getSize ()-1){ // removes a node from the middle of list
            int counter = 0;
            my_node<T>* thisPointer;
            thisPointer = front;
            while (thisPointer != back && counter < deleteNode-1){
                thisPointer = thisPointer->getNext(); // set to the pointer before deletion
                counter++;
            }
            my_node<T>* one = thisPointer;
            my_node<T>* two = thisPointer -> getNext();
            my_node<T>* three = two -> getNext(); // 3 elements required in order to have a middle node
            one -> setNext(three);
            three->setPrev(one);
        }

        else if (deleteNode == this->getSize () -1){ // remove node at end of list
            my_node<T>* thisPointer;
            thisPointer = front;
            int i = 0;
            while (thisPointer != back && i < deleteNode-1){
                thisPointer = thisPointer->getNext();
                i++;
            }
            my_node<T>* removeNode = thisPointer -> getNext();
            back = thisPointer;
            back -> setNext(nullptr);
            delete removeNode;
        }
        size--;
    }

    // OPERATORS

    linkedlist<T>& operator = (const linkedlist<T>& thing){
        size = thing.size;
        if(thing.front == nullptr && thing.back == nullptr){
            front = back = nullptr;
            return *this;
        }
        else{
            delete front;
            int counter = 0;
            front = nullptr;
            current = front;
            while(counter < thing.getSize()){
                this->push_back(thing[counter]);
                counter++;
            }
            my_node<T> *curr = new my_node <T>(*front);
            while(curr->getNext() != nullptr) {
                curr = curr->getNext();
            }
            back = curr;
        }
        return *this;
    }

    T &operator [] (int index) const{
        my_node<T> *start = front;
        for(int i = 0; i < index; i++){
            if(start != back){
                start = start->getNext();
            }
        }
        return start->getData();
    }


};

#endif //INC_20F_FLT_PLN_LINKEDLIST_H