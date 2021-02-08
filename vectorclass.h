//
// Created by Ashwi on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_VECTORCLASS_H
#define INC_20F_FLT_PLN_VECTORCLASS_H

#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
class my_vector{
private:
    T* data;
    int cap;
    int size;
    void resize();

public:
    my_vector<T>(){
        data = new T[10];
        cap = 1;
        size = 0;
    }

    my_vector<T>(int){

    }

    my_vector<T>(const my_vector& vect){ // const my_vector& vect
        size = vect.size;
        cap = vect.cap;
        data = new T[cap];
        for(int i = 0; i < size; i++){
            data[i] = vect.data[i];
        }
    }

    ~my_vector(){if(size>0)delete[] data;};

    int get_vector_size() const{ // added const
        return size;
    }

    int get_vector_capacity(){
        return cap;
    }

    void print_vector(){
        for(int i = 0; i < size; i++){
            cout << data[i] << endl;
        }
    }

    void push_back(const T &thing){
        if(size == cap){
            T* temp = new T[2*cap];
            for(int i = 0; i < size; i++){
                temp[i] = data[i];
            }
            delete[] data;
            cap *= 2;
            data = temp;
        }
        data[size] = thing;
        size++;
    }

    void push_back(T thing, int index){
        if(index == cap){
            push_back(thing);
        }
        else{
            data[index] = thing;
        }
    }

    T vector_pop(){
        return data[size-- - 1];
    }

    void remove_at(int index){
        for(int i = index; i < size-1; ++i){
            data[i] = data[i+1];
        }
        size--;
    }

    int find_min(){
        int min = data[0];
        for(int i = 0; i < size; i++){
            if(data[i] < min){
                min = data[i];
            }
        }
        return min;
    }

    int search_index(T thing){
        for(int i = 0; i < size-1; i++){
            if(data[i] == thing){
                return i;
            }
        }
    }

    void replace(int index, T thing){
        data[index] = thing;
    }

    ///operators
    my_vector<T>& operator = (const my_vector<T>& thing){
        data = new T[thing.size];
        for(int i = 0; i < thing.size; i++){
            data[i] = thing.data[i];
        }
        cap = thing.cap;
        size = thing.size;
        return *this;
    }

    T operator [] (int index) const{
        return data[index];
    }
};

#endif //INC_20F_FLT_PLN_VECTORCLASS_H
