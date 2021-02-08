//
// Created by Ashwi on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_STRINGCLASS_H
#define INC_20F_FLT_PLN_STRINGCLASS_H

#include<cstring>
#include<iostream>
//#include<vector>
#include "vectorclass.h"

using namespace std;

class my_string{
private:
    char *data = nullptr;
    unsigned int length = 0;
    int num_positive; // holds total number of positive instances
    int num_negative; // holds total number of negative instances
    char* master_index = nullptr;

public:
    my_string();
    my_string(char *x);
    my_string(const my_string& x); // copy constructor
    ~my_string(){if(length>0)delete[] data;}; // destructor
    char get_first_char();
    unsigned int get_length();
    int get_index_number();
    char *get_string();
    char *get_words();
    char *get_master();
    char *toLower();
    char *extract_sub();
    char* delete_first_char();
    my_vector<my_string> get_individual();
    my_string substring(int start, int numChars);

    //Operators
    my_string& operator= (const my_string& string_ref);
    my_string& operator= (my_string *string_ref);
    my_string& operator= (char* string_ref);

    my_string operator+ (const my_string& string_ref);
    friend ostream& operator << (ostream& output, const my_string& string_ref);

    bool operator== (const char* string_ref);
    bool operator== (const my_string& string_ref);

    char& operator[] (const int);
    friend bool operator <(const my_string& left, const my_string& right);

    bool operator!= (const my_string& string_ref) const; // for useless words (find by comparing)
    bool operator!= (const my_string* string_ref);

};

#endif //INC_20F_FLT_PLN_STRINGCLASS_H
