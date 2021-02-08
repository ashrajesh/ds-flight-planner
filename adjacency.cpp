//
// Created by Ashwi on 11/3/2020.
//

#include "adjacency.h"

adjacency::adjacency(){

}

adjacency::adjacency(const adjacency& x){      // remove const?
    size = x.size;
    listy = x.listy;
}

adjacency::~adjacency(){
    //auto
}

void adjacency::add_node(city_node new_city){
    listy.push_back(new_city);
    size++;
}

int adjacency::get_index_of_node(my_string origin_name){
    int return_index;
    for(int i = 0; i < listy.getSize(); i++){
        if(listy[i].get_city_name() == origin_name){
            return_index = i;
        }
    }
    return return_index;
}

city_node &adjacency::get_node(int index){
    return listy[index];
}

city_node &adjacency::get_node(my_string origin){
    for(int i = 0; i < listy.getSize(); i++){
        if(listy[i].get_city_name() == origin) {
            return listy[i];
        }
    }
}

int adjacency::get_destination_index(my_string origin, my_string destination){
    int origin_index = 0;
    for(int i = 0; i < listy.getSize(); i++){
        if(origin == listy[i].get_city_name()){
            for(int j = 0; j < listy[i].get_size(); j++){      //listy[i].return_destinations().getSize()
                if(destination == listy[i].get_destination(j)){
                    return j;
                }
            }
        }
    }
    return origin_index;
}

my_string adjacency::get_next_destination(my_string origin){
    my_string return_me;
    for(int i = 0; i < listy.getSize(); i++){
        if(origin == listy[i].get_city_name()) {
            //cout << "adjacent: " << listy[i].get_city_name();
            return_me = listy[i].get_destination_temp_index();
        }
    }
    return return_me;
}


bool adjacency::find(my_string city){      // used to return city_node
    bool return_me = false;
    for(int i = 0; i < listy.getSize(); i++) {
        if(city == listy[i].get_city_name()){
            return_me = true;
        }
    }
    return return_me;
}

int adjacency::get_size(){
    return size;
}

void adjacency::print_node_map(){
    for(int i = 0; i < listy.getSize(); i++){
        cout << listy[i].get_city_name() << " -> ";
        for(int h = 0; h < listy[i].get_size(); h++){
            if(h == listy[i].get_size()-1) {
                cout << " " << listy[i].get_destination(h);
            }
            else{
                cout << listy[i].get_destination(h)<< " -> ";
            }
        }
        if(i != listy.getSize()-1) {
            cout << endl << "|";
            cout << endl << "V" << endl;
        }
        else{
            cout << endl;
        }
    }
}