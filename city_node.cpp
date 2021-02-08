//
// Created by Ashwi on 10/29/2020.
//

#include "city_node.h"

using namespace std;

city_node::city_node(){ // default
    city_name = "";
    size = 0;
    temp_index = 0;
}

city_node::city_node(const city_node& x){       //const added
    city_name = x.city_name;
    destinations = x.destinations;
    duration = x.duration;
    cost = x.cost;
    airline = x.airline;
    size = x.size;
    temp_index = x.temp_index;

    durationy = x.durationy;
    costy = x.costy;
    airliney = x.airliney;
}

void city_node::reset_temp_index(){
    temp_index = 0;
}

my_string city_node::get_destination_temp_index(){
    my_string return_me;
    if(temp_index == destinations.getSize()){
        return_me = "NULL";
    }
    else {
        return_me = destinations[temp_index];
        temp_index++;
    }
    return return_me;
};

my_string city_node::get_city_name() {
    return city_name;
}

void city_node::set_city_name(my_string x){
    city_name = x;
}

void city_node::push_destination(my_string dest, int dura, int cos, my_string air){
    destinations.push_back(dest);
    duration.push_back(dura);
    cost.push_back(cos);
    airline.push_back(air);

    my_vector<int> temp_duration;
    temp_duration.push_back(dura);
    my_vector<int> temp_cost;
    temp_cost.push_back(cos);
    my_vector<my_string> temp_airline;
    temp_airline.push_back(air);
    durationy.push_back(temp_duration);
    costy.push_back(temp_cost);
    airliney.push_back(temp_airline);
    size++;
}

void city_node::push_same_destination(int destination_index, int temp_duration, int temp_cost, my_string temp_airline){
    durationy[destination_index].push_back(temp_duration);
    costy[destination_index].push_back(temp_cost);
    airliney[destination_index].push_back(temp_airline);
}

int city_node::get_size(){
    return size;
}

my_string city_node::get_destination(int index){
    if(destinations.getSize() > 0){
        return destinations[index];
    }
    else{
        cout << "destination linkedlist is empty" << endl;
        return destinations[index];
    }
}

int city_node::get_destination_num(my_string destination){
    int return_me;
    for(int i = 0; i < destinations.getSize(); i++){
        if(destinations[i] == destination){
            return_me = i;
        }
    }
    return return_me;
}

int city_node::get_duration(int index){
    if(duration.getSize() > 0){
        return duration[index];
    }
    else{
        cout << "duration linkedlist is empty" << endl;
        return duration[index];
    }
}

int city_node::get_cost(int index){
    if(cost.getSize() > 0){
        return cost[index];
    }
    else{
        cout << "cost linkedlist is empty" << endl;
        return cost[index];
    }
}

my_string city_node::get_airline(int index){
    if(airline.getSize() > 0){
        return airline[index];
    }
    else{
        cout << "airline linkedlist is empty" << endl;
        return airline[index];
    }
}

int city_node::get_many_size(int index){
    int return_me = airliney[index].get_vector_size();
    return_me;
}

my_string city_node::get_many_airliney(int index, int second){
    my_string return_airlines = airliney[index][second];
    return return_airlines;
}
int city_node::get_many_durationy(int index, int second){
    int return_durations = durationy[index][second];
    return return_durations;
}
int city_node::get_many_costy(int index, int second){
    int return_costs = costy[index][second];
    return return_costs;
}

