//
// Created by Ashwi on 10/31/2020.
//


// Created by Ashwi on 9/26/2020.

#include "catch.hpp"
#include "stringclass.h"
#include "linkedlist.h"
#include "city_node.h"
#include "stack.h"
#include "adjacency.h"

TEST_CASE("String Class can be utilized", "[stringclass]")
{
    my_string(a);
    char* test_temp = (char*)"hello world";
    my_string data_string = test_temp;

    SECTION("Test of default constructor (nothing passed into it)" )
    {
        my_string(test_string);
        REQUIRE(test_string.get_length() == 0);
    }
    SECTION("Test get_string and get_length")
    {
        REQUIRE(strcmp(data_string.get_string(), "hello world") == 0);
        REQUIRE(strcmp(data_string.get_string(), test_temp) == 0);
        REQUIRE(data_string.get_length() == 11);
        REQUIRE(a.get_length() == 0);
    }
    SECTION("Test get_words")
    {
        my_string raw_word;
        char* remove_punctuation_1 = (char*)"hello!";

        raw_word = remove_punctuation_1;
        REQUIRE(strcmp(raw_word.get_words(), "hello") == 0);
    }
    SECTION("Test extract_sub")
    {
        my_string subbed_word;
        char* extract_master = (char*)"word(extract me)";

        subbed_word = extract_master;
        REQUIRE(strcmp(subbed_word.extract_sub(), "extract me") == 0);
    }
    SECTION("Test get_first_char and ")
    {
        my_string test_me = (char*)"hello";
        REQUIRE(test_me.get_first_char() == 'h');
    }
    SECTION("Test toLower")
    {
        my_string upper_case = (char*)"HeLlO WOrLD";
        my_string lower_case = upper_case.toLower();
        REQUIRE(strcmp(lower_case.get_string(), "hello world") == 0);
        REQUIRE(lower_case.get_length() == 11);
    }
    SECTION("Test operators")
    {
        my_string test_me;
        char* test_array = (char*)"test123";
        test_me = test_array;
        REQUIRE(strcmp(test_me.get_string(), test_array) == 0);
        my_string test_two = test_me;
        REQUIRE(bool(test_two == test_me) == true);
        my_string test_three = (char*)"321test";
        REQUIRE(test_me != test_three);
        my_string test_four = test_me + test_three;
        REQUIRE(strcmp(test_four.get_string(), "test123321test") == 0);
        REQUIRE(test_me[1] == 'e');
    }
}

TEST_CASE("LinkedList can be Utilized", "[linkedlist]")
{
    /// LINKED LIST TESTS
    SECTION("Test push_back, [] operator and getSize") {
        linkedlist<int> test_list;
        test_list.push_back(1);
        test_list.push_back(7);
        test_list.push_back(5);

        REQUIRE(test_list[0] == 1);
        REQUIRE(test_list[1] == 7);
        REQUIRE(test_list[2] == 5);
        REQUIRE(test_list.getSize() == 3);
    }
    SECTION("Test remove_duplicates (which also tests swapper, sort_list and indexNode)")
    {
        linkedlist<int> test_list;
        test_list.push_back('c');
        test_list.push_back('b');
        test_list.push_back('a');
        test_list.push_back('c');
        test_list.push_back('d');
        test_list.push_back('a');

        test_list.remove_duplicates();
        REQUIRE(test_list.getSize() == 4);
        REQUIRE(test_list[0] == 'a');
        REQUIRE(test_list[1] == 'b');
        REQUIRE(test_list[2] == 'c');
        REQUIRE(test_list[3] == 'd');
    }
    SECTION("Test remove")
    {
        linkedlist<int> test_list;
        test_list.push_back('a');
        test_list.push_back('b');
        test_list.push_back('c');
        test_list.push_back('d');
        test_list.push_back('e');
        test_list.push_back('f');
        REQUIRE(test_list[0] == 'a');

        test_list.remove(0);
        REQUIRE(test_list[0] == 'b');
        REQUIRE(test_list[2] == 'd');
        REQUIRE(test_list.getSize() == 5);

        test_list.remove(2);
        REQUIRE(test_list.getSize() == 4);
        REQUIRE(test_list[0] == 'b');
        REQUIRE(test_list[1] == 'c');
        REQUIRE(test_list[2] == 'e');
        REQUIRE(test_list[3] == 'f');
        int last = test_list.getSize()-1;
        REQUIRE(test_list[last] == 'f');

        test_list.remove(last);
        REQUIRE(test_list.getSize() == 3);
        REQUIRE(test_list[0] == 'b');
        REQUIRE(test_list[1] == 'c');
        REQUIRE(test_list[2] == 'e');
    }
    SECTION("Test = operator")
    {
        linkedlist<int> test_list_one;
        test_list_one.push_back(1);
        test_list_one.push_back(2);
        test_list_one.push_back(3);
        test_list_one.push_back(4);
        test_list_one.push_back(5);
        test_list_one.push_back(6);
        linkedlist<int> test_list_two;
        test_list_two = test_list_one;

        bool is_equal = true;
        for(int i = 0; i < test_list_one.getSize(); i++){
            if(test_list_two[i] != test_list_one[i]){
                is_equal = false;
            }
        }
        REQUIRE(is_equal == true);
    }
    SECTION("Test = operator with copy constructor")
    {
        linkedlist<int> test_list_one;
        test_list_one.push_back(1);
        test_list_one.push_back(2);
        test_list_one.push_back(3);
        test_list_one.push_back(4);
        test_list_one.push_back(5);
        test_list_one.push_back(6);
        linkedlist<int> test_list_two = test_list_one;

        bool is_equal = true;
        for(int i = 0; i < test_list_one.getSize(); i++){
            if(test_list_two[i] != test_list_one[i]){
                is_equal = false;
            }
        }
        REQUIRE(is_equal == true);
    }
}

TEST_CASE("Vector can be Utilized", "[vectorclass]")
{
    my_vector<int> num_vect;
    my_vector<char> alpha_vect;
    REQUIRE(alpha_vect.get_vector_size() == 0);

    SECTION("Test [] operator and get_vector_size") {
        alpha_vect.push_back('h');
        alpha_vect.push_back('i');
        REQUIRE(alpha_vect[0] == 'h');
        REQUIRE(alpha_vect[1] == 'i');
        REQUIRE(alpha_vect.get_vector_size() == 2);
    }
    SECTION("Test push_back functions") {
        num_vect.push_back(3);
        num_vect.push_back(1);
        num_vect.push_back(2);
        int vector_sum = 0;
        for (int i = 0; i < num_vect.get_vector_size(); i++) {
            vector_sum += num_vect[i];
        }
        REQUIRE(vector_sum == 6);
        REQUIRE(num_vect.get_vector_size() == 3);

        num_vect.push_back(4, 1);
        REQUIRE(num_vect[0] == 3);
        REQUIRE(num_vect[1] == 4);
        REQUIRE(num_vect[2] == 2);
    }
    SECTION("Test = operator")
    {
        my_vector<char> new_vect;
        new_vect.push_back('x');
        new_vect.push_back('y');
        new_vect.push_back('z');
        new_vect.push_back('h');
        new_vect.push_back('i');

        alpha_vect = new_vect;
        bool is_equal = true;
        for(int i = 0; i < alpha_vect.get_vector_size(); i++){
            if(alpha_vect[i] != new_vect[i]){
                is_equal = false;
            }
        }
        REQUIRE(is_equal == true);
    }
    SECTION("Test pop")
    {
        int last_element;
        num_vect.push_back(0);
        num_vect.push_back(1);
        num_vect.push_back(2);
        num_vect.push_back(3);

        last_element = num_vect.get_vector_size()-1;
        REQUIRE(num_vect.get_vector_size() == 4);
        REQUIRE(num_vect[last_element] == 3);

        num_vect.vector_pop();

        last_element = num_vect.get_vector_size()-1;
        REQUIRE(num_vect.get_vector_size() == 3);
        REQUIRE(num_vect[last_element] == 2);
    }
    SECTION("Test remove_at")
    {
        my_vector<int> remove_vect;
        remove_vect.push_back(0);
        remove_vect.push_back(1);
        remove_vect.push_back(2);
        remove_vect.push_back(3);

        REQUIRE(remove_vect.get_vector_size() == 4);
        remove_vect.remove_at(1);
        REQUIRE(remove_vect.get_vector_size() == 3);
        REQUIRE(remove_vect[0] == 0);
        REQUIRE(remove_vect[1] == 2);
    }
}

TEST_CASE("Stack can be Utilized", "[stack]")
{
    stack<int> nums;
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(1);

    SECTION("Test peek")
    {
        REQUIRE(nums.peek() == 1);
    }

    SECTION("Test isEmpty")
    {
        stack<int> nums_two;
        REQUIRE(nums_two.isEmpty() == true);
        nums_two.push_back(0);
        REQUIRE(nums_two.isEmpty() == false);
    }

    SECTION("Test Pop")
    {
        nums.pop();
        REQUIRE(nums.peek() == 2);
        nums.pop();
        REQUIRE(nums.peek() == 3);
        nums.pop();
        REQUIRE(nums.isEmpty() == true);
    }
}

TEST_CASE("Adjacency List can be Utilized", "[adjacency]")
{
    my_string first_city = "Dallas";
    city_node city_one;
    city_one.set_city_name(first_city);

    my_string second_city = "Austin";
    city_node city_two;
    city_two.set_city_name(second_city);

    my_string third_city = "San Antonio";
    city_node city_three;
    city_three.set_city_name(third_city);

    city_one.push_destination("New York", 55, 72, "jetBlue");
    city_one.push_destination("Los Angles", 50, 70, "American");

    adjacency routes;
    routes.add_node(city_one);
    routes.add_node(city_two);
    routes.add_node(city_three);

    REQUIRE(routes.get_size() == 3);

    SECTION("Test Index of Cities")
    {
        REQUIRE(routes.get_index_of_node("Dallas") == 0);
        REQUIRE(routes.get_index_of_node("Austin") == 1);
        REQUIRE(routes.get_index_of_node("San Antonio") == 2);

        REQUIRE(routes.find("San Antonio") == true);
        REQUIRE(routes.find("Vegas") == false);
    }


    SECTION("Test destination stuff")
    {   my_string test_1 = routes.get_next_destination("Dallas").get_string();
        REQUIRE(strcmp(test_1.get_string(), "New York") == 0);
        my_string test_2 = routes.get_next_destination("Dallas").get_string();
        REQUIRE(strcmp(test_2.get_string(), "Los Angles") == 0);
        routes.get_node("Dallas").reset_temp_index();
        my_string test_3 = routes.get_next_destination("Dallas").get_string();
        REQUIRE(strcmp(test_3.get_string(), "New York") == 0);

        REQUIRE(routes.get_destination_index("Dallas", "New York") == 0);
        REQUIRE(routes.get_destination_index("Dallas", "Los Angles") == 1);
    }

}

TEST_CASE("City Nodes can be Utilized", "[city_node]")
{
    SECTION("City Naming / Identifying Test")
    {
        my_string cityName = "Dallas";
        city_node Dallas;
        Dallas.set_city_name(cityName);
        REQUIRE(strcmp(Dallas.get_city_name().get_string(), "Dallas") == 0);

        my_string cityNametwo = "New York City";
        city_node NYC;
        NYC.set_city_name(cityNametwo);
        REQUIRE(strcmp(NYC.get_city_name().get_string(), "New York City") == 0);
    }

    SECTION("Destination (simple) Properties Test") {
        my_string cityName = "Dallas";
        city_node Dallas;
        Dallas.set_city_name(cityName);

        my_string destination = "Austin";
        int cost = 98;
        int duration = 47;
        my_string airline = "Spirit";

        my_string destination_two = "San Antonio";
        int cost_two = 53;
        int duration_two = 124;
        my_string airline_two = "Southwest";

        Dallas.push_destination(destination, duration, cost, airline);
        Dallas.push_destination(destination_two, duration_two, cost_two, airline_two);

        REQUIRE(strcmp(Dallas.get_destination(0).get_string(), "Austin") == 0);
        REQUIRE(Dallas.get_cost(0) == 98);
        REQUIRE(Dallas.get_duration(0) == 47);
        REQUIRE(strcmp(Dallas.get_airline(0).get_string(), "Spirit") == 0);

        REQUIRE(strcmp(Dallas.get_destination(1).get_string(), "San Antonio") == 0);
        REQUIRE(Dallas.get_cost(1) == 53);
        REQUIRE(Dallas.get_duration(1) == 124);
        REQUIRE(strcmp(Dallas.get_airline(1).get_string(), "Southwest") == 0);
    }

    SECTION("Destination (multiple flights for same route) Properties Test")
    {
        my_string cityName = "Dallas";
        city_node Dallas;
        Dallas.set_city_name(cityName);

        my_vector<my_string> destinations;
        my_vector<int> costs;
        my_vector<int> durations;
        my_vector<my_string> airlines;

        destinations.push_back("Austin");
        costs.push_back(98);
        durations.push_back(47);
        airlines.push_back("Spirit");

        destinations.push_back("Austin");
        costs.push_back(53);
        durations.push_back(124);
        airlines.push_back("Southwest");

        Dallas.push_destination(destinations[0], durations[0], costs[0], airlines[0]);
        Dallas.push_same_destination(0, durations[1], costs[1], airlines[1]);

        REQUIRE(Dallas.get_many_size(0) == 2);
        Dallas.push_destination("New York", 55, 72, "jetBlue");
        REQUIRE(Dallas.get_many_size(1) == 1);

        REQUIRE(strcmp(Dallas.get_many_airliney(0,0).get_string(), "Spirit") == 0);
        REQUIRE(strcmp(Dallas.get_many_airliney(0,1).get_string(), "Southwest") == 0);
        REQUIRE(strcmp(Dallas.get_many_airliney(1,0).get_string(), "jetBlue") == 0);

        REQUIRE(Dallas.get_many_costy(0,0) == 98);
        REQUIRE(Dallas.get_many_costy(0,1) == 53);
        REQUIRE(Dallas.get_many_costy(1,0) == 72);

        REQUIRE(Dallas.get_many_durationy(0,0) == 47);
        REQUIRE(Dallas.get_many_durationy(0,1) == 124);
        REQUIRE(Dallas.get_many_durationy(1,0) == 55);
    }
}