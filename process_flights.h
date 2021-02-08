//
// Created by Ashwi on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_PROCESS_FLIGHTS_H
#define INC_20F_FLT_PLN_PROCESS_FLIGHTS_H
#include <fstream>
#include <iostream>
#include "adjacency.h"
#include "vectorclass.h"

using namespace std;

    void parse_input(ifstream &input_file, adjacency &route_map);
    void iterative_backtracking(ifstream &input_file, ofstream &output_file, adjacency &route_map);


#endif //INC_20F_FLT_PLN_PROCESS_FLIGHTS_H
