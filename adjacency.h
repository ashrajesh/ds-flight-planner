//
// Created by Ashwi on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_ADJACENCY_H
#define INC_20F_FLT_PLN_ADJACENCY_H
#include "stringclass.h"
#include "linkedlist.h"
#include "city_node.h"

class adjacency{
private:
    linkedlist<city_node> listy;
    int size = 0;
public:
    adjacency();

    adjacency(const adjacency& x);

    ~adjacency();

    void add_node(city_node new_city);

    int get_index_of_node(my_string origin_name);
    int get_destination_index(my_string origin, my_string destination);

    city_node &get_node(int index);

    city_node &get_node(my_string origin);

    bool find(my_string city);

    my_string get_next_destination(my_string origin);

    int get_size();

    void print_node_map();
};

#endif //INC_20F_FLT_PLN_ADJACENCY_H
