//
// Created by Ashwi on 10/29/2020.
//

#include "process_flights.h"
#include "city_node.h"
#include "stringclass.h"
#include "vectorclass.h"
#include "adjacency.h"
#include "stack.h"

void parse_input(ifstream &input_file, adjacency &route_map){
    char temp[500];     // store line of input in here
    int counter = 0;    // keeps track of progress of parse
    int num_requests = 0;   // keeps track of request number
    my_string temp_origin;  // holds the origin
    my_string temp_destination;     // holds the destination
    int temp_cost;              // holds the cost
    int temp_duration;          // holds the time (min)
    my_string temp_airline;     // stores the airline

    input_file.getline(temp, 499);  // the first line will tell us how many flights there are (input)
    my_string num_elements = temp;      // number of input flights
    num_requests = atoi(temp);          // convert from char* to integer

    while(counter < num_requests){            // loop iterates over each line of input, populates adjacency list
        bool destination_exists = false;        // will store whether the destination already exists on list
        input_file.getline(temp, 499);       // put the entire input line into temp
        my_string parse_me = temp;              // put char* temp into a my_string
        my_vector<my_string> elements = parse_me.get_individual();  // call get_individual (returns a vector of "|" separated my_strings)

        temp_origin = elements[0];              // the first part of the input line is the origin city
        temp_destination = elements[1];         // the second part of the input line is the destination
        temp_cost = elements[2].get_index_number();     // the third part of the input line is the cost of the flight
        temp_duration = elements[3].get_index_number();     // the fourth part of the input line is the time (min) of the flight
        temp_airline = elements[4];         // the last part of the input line is the airline

        if(!route_map.find(temp_origin)){        // if this city node doesn't exists on adjacent list
            city_node new_origin;                   // create new city
            new_origin.set_city_name(temp_origin);  // set the origin city
            route_map.add_node(new_origin);         // add the city to the adjacency list
            route_map.get_node(route_map.get_size()-1).push_destination(temp_destination, temp_duration, temp_cost, temp_airline);  // push the destination to the adjacency list at the origin index
        }
        else{
            for(int j = 0; j < route_map.get_node(route_map.get_index_of_node(temp_origin)).get_size(); j++){   // parse through the destinations of the origin city stored on the adjacency list
                if(route_map.get_node(route_map.get_index_of_node(temp_origin)).get_destination(j) == temp_destination){        // if the destination already exists on the adjacent list for the city
                    destination_exists = true;      // set destination_exists to true, this means that we have inputted two flights that have the same route
                    int route_index = route_map.get_index_of_node(temp_origin);     // get index of origin city on adjacency list
                    route_map.get_node(route_index).push_same_destination(j, temp_duration, temp_cost, temp_airline);   // push new route parameters to destination of origin city
                }
            }
            if(destination_exists == false) {   // if the flight does not share the same route as another flight
                int route_index = route_map.get_index_of_node(temp_origin);     // get index of origin city on adjacency list
                route_map.get_node(route_index).push_destination(temp_destination, temp_duration, temp_cost, temp_airline);  //push new destination and new flight parameters
            }
            if(destination_exists == true){         // same route, different airline
                cout << endl;
            }
            destination_exists = false;     // set to false for next use
        }

        if(!route_map.find(temp_destination)){        // if this destination doesn't exist on adjacent list
            city_node new_origin;       // create new destination city (act as origin on adjacent list)
            new_origin.set_city_name(temp_destination);     // set the city name to the destination city name
            route_map.add_node(new_origin);         // add the city node to the adjacent list
            route_map.get_node(route_map.get_size()-1).push_destination(temp_origin, temp_duration, temp_cost, temp_airline);       // push the origin city parameters to the destination of the destination city node
        }
        else{       // if the destination already exists on the adjacent list
            for(int j = 0; j < route_map.get_node(route_map.get_index_of_node(temp_destination)).get_size(); j++){
                if(route_map.get_node(route_map.get_index_of_node(temp_destination)).get_destination(j) == temp_origin){
                    destination_exists = true;
                    int route_index = route_map.get_index_of_node(temp_destination);
                    route_map.get_node(route_index).push_same_destination(j, temp_duration, temp_cost, temp_airline);
                }
            }
            if(destination_exists == false) {
                int route_index = route_map.get_index_of_node(temp_destination);
                route_map.get_node(route_index).push_destination(temp_origin, temp_duration, temp_cost, temp_airline);
            }
            if(destination_exists == true){     // same route, different airline
                cout << endl;
            }
            destination_exists = false;     // set to false (just in case for next iteration)
        }
        counter++;      // increment counter
    }
    route_map.print_node_map();     // cout what our adjacency list looks like
}


void iterative_backtracking(ifstream &input_file, ofstream &output_file, adjacency &route_map){
    char temp[500];
    int counter = 0;
    input_file.getline(temp, 499);
    my_string num_elements = temp;

    int num_requests = 0;
    num_requests = atoi(temp);

    my_string desired_origin;       // stores the requested origin
    my_string desired_destination;  // stores the requested destination
    my_string request_metric;       // stores the requested metric (time or cost)
    my_string current_city;         // stores the current city

    stack<my_string> city_stack;    // initialize stack object

    while(counter < num_requests) {     // loop through each flight request
        input_file.getline(temp, 499);  // get the input line and store in temp
        my_string parse_me = temp;      // parse me will hold the line
        my_vector<my_string> elements = parse_me.get_individual();  // elements will get the returned vector from the parsed input line
        desired_origin = elements[0];       // first element holds origin
        desired_destination = elements[1];  // second element holds destination
        request_metric = elements[2];       // third element holds metric (time or cost)
        cout << endl;

        current_city = desired_origin;      // set the origin city to the current city
        city_stack.push_back(current_city); // push initial city to the stack

        my_vector<my_vector<my_string>> final_routes_two;   // holds vector of the final routes e.g Dallas,Austin,Houston
        my_vector<int> final_costs;     // holds final cost for each route
        my_vector<int> final_times;     // holds final time for each route
        my_vector<my_vector<my_string>> final_airlines;     // holds vector of airlines used on each route e.g. Spirit,American

        /// ITERATIVE BACKTRACKING STARTS HERE
        my_string current_top;          // stores the string at the top of the stack
        while(city_stack.isEmpty() == false){       // while the stack is not empty
            current_top = city_stack.get_top();     // set current top to whatever is at the top of the stack
            if(city_stack.check_top(desired_destination) == true){      // if the top of the stack is our desired destination
                linkedlist<my_string> temp_route = city_stack.get_cities(); // get the linked list of cities (route)
                my_vector<my_string> temp_route_two;        // will store vector of cities on route
                int total_cost = 0;     // will store total cost of route
                int total_time = 0;     // will store total time of route
                my_vector<my_string> airlines_used; // will store the airlines used throughout the rougte
                for(int q = 0; q < temp_route.getSize(); q++){  // iterate for the number of route elements
                    temp_route_two.push_back(temp_route[q]);    // push back the city at temp_route[q]
                    if(q != temp_route.getSize()-1) {           // if less than the size - 1 (only one airline,cost,time for each path (two cities))
                        total_cost += route_map.get_node(temp_route[q]).get_cost(route_map.get_node(temp_route[q]).get_destination_num(temp_route[q+1]));
                        total_time += route_map.get_node(temp_route[q]).get_duration(route_map.get_node(temp_route[q]).get_destination_num(temp_route[q+1]));
                        airlines_used.push_back(route_map.get_node(temp_route[q]).get_airline(route_map.get_node(temp_route[q]).get_destination_num(temp_route[q+1])));
                    }
                }
                final_costs.push_back(total_cost);      // push back the total cost
                final_times.push_back(total_time);      // push back the total time
                final_airlines.push_back(airlines_used);    // push back the vector of airlines used

                final_routes_two.push_back(temp_route_two); // push back the vector holding the final route
                city_stack.pop();       // pop the stack
            }
            else{
                bool is_problem = false;   // determines whether node is on adjacent list
                for(my_string curr = route_map.get_next_destination(current_top); curr != "NULL"; curr = route_map.get_next_destination(current_top)){   // get_next destination returns a destination to look at and shifts the pointer of the current destination index that the city node is looking at, so we will parse through each possible destination
                    if(route_map.find(curr) == false){is_problem = true; break;}    // if node doesn't exist on adjacency list

                    if(city_stack.is_on_stack(curr)){} // no need to visit the same city twice!
                    else{
                        city_stack.push_back(curr);     // if not on stack, push to stack
                        route_map.get_node(curr).reset_temp_index();    // reset the destinaation index for city
                        current_top = curr;     // ensure that the current top is set to whatever was pushed to the stack last
                    }
                }
                if(is_problem == true){break;}      // we don't need to do the rest of the loop if we know the node isn't on adjacent list
                if(city_stack.check_top(desired_destination) == true){      // this is pretty much the same as the last "if the destination is at the top of the stack", can reffer to those comments.
                    linkedlist<my_string> temp_route = city_stack.get_cities();
                    my_vector<my_string> temp_route_two;
                    int total_cost = 0;
                    int total_time = 0;
                    my_vector<my_string> airlines_used;
                    for(int q = 0; q < temp_route.getSize(); q++){
                        temp_route_two.push_back(temp_route[q]);
                        if(q != temp_route.getSize()-1) {
                            total_cost += route_map.get_node(temp_route[q]).get_cost(route_map.get_node(temp_route[q]).get_destination_num(temp_route[q+1]));
                            total_time += route_map.get_node(temp_route[q]).get_duration(route_map.get_node(temp_route[q]).get_destination_num(temp_route[q+1]));
                            airlines_used.push_back(route_map.get_node(temp_route[q]).get_airline(route_map.get_node(temp_route[q]).get_destination_num(temp_route[q+1])));
                        }
                    }
                    final_costs.push_back(total_cost);
                    final_times.push_back(total_time);
                    final_airlines.push_back(airlines_used);

                    final_routes_two.push_back(temp_route_two);
                    city_stack.pop();
                }
                city_stack.pop();   // pop the stack
                route_map.get_node(current_top).reset_temp_index();     // reset the destination index of whatever city was last at top.
            }
        }
        /// ITERATIVE BACKTRACKING ENDS HERE

        my_vector<my_vector<my_string>> finally_routes = final_routes_two;     // creating new copies of the vectors
        my_vector<int> finally_costs = final_costs;
        my_vector<int> finally_times = final_times;
        my_vector<my_vector<my_string>> finally_airlines = final_airlines;

        // Loop below will parse through each route and check if multiple airlines service it.
        for(int x = 0; x < final_routes_two.get_vector_size(); x++){            // for each route in vector
            for(int y = 0; y < final_routes_two[x].get_vector_size()-1; y++){   // for each path in route
                my_string temp_origin = final_routes_two[x][y];     // current origin set
                my_string temp_dest = final_routes_two[x][y+1];     // current destination set
                int dest_index = route_map.get_destination_index(temp_origin, temp_dest);   // index set at current destination
                int num_flights = route_map.get_node(temp_origin).get_many_size(dest_index); // get number of flights
                if(num_flights > 1){    // if there is more than one flight, there could be additional costs and time that we need to add
                    for(int z = 1; z < num_flights; z++){       // for num of airlines on route
                        my_vector<my_string> replace_airline = final_airlines[x];
                        my_string new_airline = route_map.get_node(temp_origin).get_many_airliney(dest_index, z);   // get airline at index z
                        replace_airline.replace(y, new_airline); // replace
                        finally_airlines.push_back(replace_airline); // push back

                        int new_cost = route_map.get_node(temp_origin).get_many_costy(dest_index, z);
                        int old_cost = route_map.get_node(temp_origin).get_many_costy(dest_index, z-1);
                        int push_back_cost = final_costs[x] - old_cost + new_cost;
                        finally_costs.push_back(push_back_cost);

                        int new_time = route_map.get_node(temp_origin).get_many_durationy(dest_index, z);
                        int old_time = route_map.get_node(temp_origin).get_many_durationy(dest_index, z-1);
                        int push_back_time = final_times[x] - old_time + new_time;
                        finally_times.push_back(push_back_time);

                        finally_routes.push_back(final_routes_two[x]);  // push back the route
                    }
                }
            }
        }

        // loop that totals time and cost based on route via find and replace
        for(int x = 0; x < finally_routes.get_vector_size(); x++) {            // for each route in vector
            for (int y = 0; y < finally_routes[x].get_vector_size() - 2; y++) {   // for each path
                if(finally_airlines[x][y] != finally_airlines[x][y+1]){     // if the airlines are different for a given path within a route, we have to accomodate for additional costs associated
                    int new_time = 43+22+finally_times[x];
                    finally_times.replace(x, new_time);
                    int new_cost = 19+finally_costs[x];
                    finally_costs.replace(x, new_cost);
                }
                else{                                       // if the airlines are the same, we give the path the standard layover costs and time delay
                    int new_time = 43+finally_times[x];
                    finally_times.replace(x, new_time);
                    int new_cost = 19+finally_costs[x];
                    finally_costs.replace(x, new_cost);
                }
            }
        }

        /// OUTPUT BASED ON METRICS REQUESTED

        bool path_exists = true;
        if(final_routes_two.get_vector_size() == 0){    // if a route does not exist
            cout << "Flight " << counter+1 << ":   ";
            output_file << "Flight " << counter+1 << ":   ";
            cout << "No flight paths from " << desired_origin << " to " << desired_destination << endl;
            output_file << "No flight paths from " << desired_origin << " to " << desired_destination << endl;
            path_exists = false;
            output_file << endl;
        }

        if(request_metric == "T" && path_exists == true) {      // requested metric is time
            cout << endl << "Flight " << counter+1 << ": " << desired_origin << ", " << desired_destination << " (Time)" << endl;
            output_file << "Flight " << counter+1 << ": " << desired_origin << ", " << desired_destination << " (Time)" << endl;
            my_vector<int> index_order;
            my_vector<int> final_times_two = finally_times;
            for(int v = 0; v < finally_routes.get_vector_size(); v++){
                int temp_index = final_times_two.search_index(final_times_two.find_min());
                index_order.push_back(temp_index);
                final_times_two.push_back(99999, temp_index);
            }
            for (int w = 0; w < finally_routes.get_vector_size(); w++) {        // iterate through each route and find optimal depending on request
                if(w == 3){
                    break;
                }
                cout << "Path " << w+1 << ": ";
                output_file <<  "Path " << w+1 << ": ";
                for(int x = 0; x < finally_routes[index_order[w]].get_vector_size(); x++){
                    if(x != finally_routes[index_order[w]].get_vector_size()-1){
                        cout << finally_routes[index_order[w]][x] << "(" << finally_airlines[index_order[w]][x] << ")";
                        cout << " -> ";
                        output_file << finally_routes[index_order[w]][x] << "(" << finally_airlines[index_order[w]][x] << ")";
                        output_file << " -> ";
                    }
                    else{
                        cout << finally_routes[index_order[w]][x] << ". ";
                        output_file << finally_routes[index_order[w]][x] << ". ";
                    }
                }
                cout << " Time: " << finally_times[index_order[w]] << "  ";
                output_file << " Time: " << finally_times[index_order[w]] << "  ";
                cout << "Cost: $" << finally_costs[index_order[w]]<< ".00  " << endl;
                output_file << "Cost: $" << finally_costs[index_order[w]] << ".00  " << endl;
            }
            output_file << endl;
        }

        else if(request_metric == "C" && path_exists == true){      // Does the same thing as previous if statement but with cost instead of time
            cout << endl << "Flight " << counter+1 << ": " << desired_origin << ", " << desired_destination << " (Cost)" << endl;
            output_file << "Flight " << counter+1 << ": " << desired_origin << ", " << desired_destination << " (Cost)" << endl;

            my_vector<int> index_order;
            my_vector<int> final_times_two = finally_costs;
            for(int v = 0; v < finally_routes.get_vector_size(); v++){
                int temp_index = final_times_two.search_index(final_times_two.find_min());
                index_order.push_back(temp_index);
                final_times_two.push_back(99999, temp_index);
            }
            for (int w = 0; w < finally_routes.get_vector_size(); w++) {        // iterate through each route and find optimal depending on request
                if(w == 3){
                    break;
                }
                cout << "Path " << w+1 << ": ";
                output_file <<  "Path " << w+1 << ": ";
                for(int x = 0; x < finally_routes[index_order[w]].get_vector_size(); x++){
                    if(x != finally_routes[index_order[w]].get_vector_size()-1){
                        cout << finally_routes[index_order[w]][x] << "(" << finally_airlines[index_order[w]][x] << ")";
                        cout << " -> ";
                        output_file << finally_routes[index_order[w]][x] << "(" << finally_airlines[index_order[w]][x] << ")";
                        output_file << " -> ";
                    }
                    else{
                        cout << finally_routes[index_order[w]][x] << ". ";
                        output_file << finally_routes[index_order[w]][x] << ". ";
                    }
                }
                cout << " Time: " << finally_times[index_order[w]]<< "  ";
                output_file << " Time: " << finally_times[index_order[w]]<< "  ";
                cout << "Cost: $" << finally_costs[index_order[w]]<< ".00  " << endl;
                output_file << "Cost: $" << finally_costs[index_order[w]]<< ".00  " << endl;
            }
            output_file << endl;
        }
        counter++;
    }
}