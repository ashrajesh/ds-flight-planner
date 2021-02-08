#include <fstream>
#include <iostream>
#include "stringclass.h"
#include "vectorclass.h"
#include "linkedlist.h"
#include "process_flights.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <map>

using namespace std;

int main(int argc, char** argv) {
    if(argc==1){Catch::Session().run(); return 0;}
    else{cout<< "catch session not run" << endl << endl;}

    adjacency route_map;

    ifstream input_file;
    input_file.open(argv[1]);
    parse_input(input_file, route_map);

    ofstream output_file;
    output_file.open(argv[3]);
    ifstream input_file_two;
    input_file_two.open(argv[2]);
    iterative_backtracking(input_file_two, output_file, route_map);

    output_file.close();
    input_file_two.close();
    input_file.close();
    return 0;
}