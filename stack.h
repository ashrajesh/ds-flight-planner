//
// Created by Ashwi on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_STACK_H
#define INC_20F_FLT_PLN_STACK_H
#include "linkedlist.h"

using namespace std;

template <class T>
class stack{            // stack should be LIFO data structure
private:
    linkedlist<T> cities;

public:                 //overloaded assignment operator, a copy constructor, and a destructor.
    stack<T>(){

    }

    stack<T>(stack& x){
        cities = x.cities;
    }

    ~stack(){
        //auto
    }

    my_string get_top(){
        return cities[cities.getSize()-1];
    }

    void push_back(T pushMe){
        cities.push_back(pushMe);
    }

    void pop(){
        cities.remove(cities.getSize()-1);
    }

    T peek(){
        return cities[cities.getSize()-1];
    }

    bool check_top(my_string desiredCity){      // test case if works
        if(this->peek() == desiredCity){
            return true;
        }
        else{
            return false;
        }
    }

    bool isEmpty(){
        if(cities.getSize() == 0){
            return true;
        }
        else{
            return false;
        }
    }

    linkedlist<T> get_cities(){
        linkedlist<T> return_me;
        for(int i = 0; i < cities.getSize(); i++){
            return_me.push_back(cities[i]);
        }
        return return_me;
    }

    bool is_on_stack(my_string test){
        bool return_me = false;
        for(int i = 0; i < cities.getSize(); i++){
            if(cities[i] == test){
                return_me = true;
            }
        }
        return return_me;
    }

};

#endif //INC_20F_FLT_PLN_STACK_H
