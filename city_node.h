//
// Created by Ashwi on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_CITY_NODE_H
#define INC_20F_FLT_PLN_CITY_NODE_H
#include "stringclass.h"
#include "linkedlist.h"


class city_node {
private:
    my_string city_name;
    linkedlist<my_string> destinations;
    linkedlist<int> duration;
    linkedlist<int> cost;
    linkedlist<my_string> airline;
    int size;
    int temp_index;

    linkedlist<my_vector<int>> durationy;   // these linked lists take care of instances where there is more than one flight for a given route
    linkedlist<my_vector<int>> costy;
    linkedlist<my_vector<my_string>> airliney;

public:
    city_node();
    city_node(const city_node& x);

    void reset_temp_index();
    void set_city_name(my_string x);
    my_string get_city_name();

    void push_destination(my_string dest, int dura, int cos, my_string airline);
    void push_same_destination(int destination_index, int temp_duration, int temp_cost, my_string temp_airline);
    int get_size();

    my_string get_destination(int index);
    int get_destination_num(my_string destination);
    int get_duration(int index);
    int get_cost(int index);
    my_string get_airline(int index);
    my_string get_destination_temp_index();

    int get_many_size(int index);
    my_string get_many_airliney(int index, int second);
    int get_many_durationy(int index, int second);
    int get_many_costy(int index, int second);
};

#endif //INC_20F_FLT_PLN_CITY_NODE_H
