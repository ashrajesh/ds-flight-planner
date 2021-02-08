//
// Created by Ashwi on 9/1/2020.
//
#include <cstring>
#include "stringclass.h"
#include <iostream>
#include <sstream>
#include "vectorclass.h"

using namespace std;

my_string::my_string(){ // default
    data = new char[1];
    data[0] = '\0';
    master_index = new char[1]; /// might need to delete
    master_index[0]  = '\0';
}

my_string::my_string(char *x) { // creates my_string object given char*
    if (x == nullptr) { // just in case
        cout << "empty" << endl;
        data = new char[1];
        data[0] = '\0';
        master_index = new char[1];
        master_index[0] ='\0';
    }
    else {
        data = new char[strlen(x) + 1]; // includes space for null terminator
        strcpy(data, x);
        data[strlen(x)] = '\0';
        master_index = new char[1]; // includes space for null terminator
        master_index[0] = '\0';
    }
    num_positive = 0;
    num_negative = 0;
}

my_string::my_string(const my_string& x){ // Copy Constructor
    data = new char[strlen(x.data)+1];
    strcpy(data, x.data);
    data[strlen(x.data)] = '\0';
    master_index = new char[strlen(x.master_index)+1];               /// might need to delete
    strcpy(master_index, x.master_index);     /// might need to delete
    master_index[strlen(x.master_index)] = '\0';
    num_negative = x.num_negative;
    num_positive = x.num_positive;
    length = x.length;
}

char my_string::get_first_char(){
    return data[0];
}

char* my_string::get_string() {
    return data;
}

int my_string::get_index_number() {
//    char temp = this->data[0];
//    return (int) temp;
    return stoi(this->data);
}

char* my_string::get_words() { // removes "useless" characters from my_string objects
    int counter = 0;
    while(data[counter] != '\0'){
        if(data[counter] == '.' || data[counter] == ',' || data [counter] == '!' || data[counter] == '?' || data[counter] == ';' || data[counter] == '"' || data[counter] == '/'){
            data[counter] = '\0';
        }
        counter++;
    }
    return data;
}

char* my_string::extract_sub(){             //takes [phrase](extract_me) or word(extract_me)
    char* extract_me = new char[50];
    for(int i = 0; i < this->get_length(); i++){
        if(data[i] == '('){
            int counter_1 = 0;
            int counter_2 = i+1;    // +1 to get past of first '('
            while(data[counter_2] != ')'){
                extract_me[counter_1] = data[counter_2];
                counter_1++;
                counter_2++;
            }
            extract_me[counter_1] = '\0';
        }
    }
    return extract_me;
}

char* my_string::get_master(){
    return master_index;
}

my_vector<my_string> my_string::get_individual(){ // pair mystring, group name '(' (mystring pointer) if(!= nullptr) make a group map
    stringstream full_line(data);           // take in full line of data
    my_vector<my_string> individual_words;      // vector that will store all the individual words
    my_string this_word;                        // this_word stores each word to be pushed back to the vector
    char* temp_string = new char[101];           // parse data into char*
    while(full_line.getline(temp_string, 101, '\0')){ // input data until null terminator reached
        stringstream streamer(temp_string); // new stringstream
        while(streamer.getline(temp_string, 101, '|') || streamer.getline(temp_string, 51, '\n')){  // delimit words via space
            this_word = temp_string;        // set this_word to the delimited char*
            individual_words.push_back(this_word);
//            if(this_word.data[0] == '['){   // if the string starts with '['
//                my_string start_string = temp_string;
//                streamer.getline(temp_string, 51, ']');     // parse chars into the char* until delimiter ']'
//                char* space_char = (char*)" ";
//                my_string space_string = space_char;
//                this_word = start_string + space_string + temp_string;        // entire phrase will be equal to this_word
//                this_word = this_word.delete_first_char();
//                if(streamer.peek() == '('){
//                    char* subby = new char[51];
//                    my_string curr_thing;
//                    streamer.getline(subby, 51, ')');
//                    char* curr_subby = subby +1;
//                    strcpy(this_word.master_index, curr_subby);
//                }
//                individual_words.push_back(this_word);      // push back phrase to vector of my_strings
//            }
//            else{       // otherwise it is a regular, single word
//                char* subby = new char[51];
//                for(int a = 0; a < this_word.get_length(); a++) {   // iterate through chars in the word to find '('
//                    if (this_word.data[a] == '(') {
//                        cout << "single word master index" << endl;
//                        subby = this_word.extract_sub();
//                        strcpy(this_word.master_index, subby);
//                        this_word.data[a] = '\0';
//                    }
//                }
//                this_word = this_word.get_words(); /// removes redundant characters from words such as "." or "!"
//                individual_words.push_back(this_word);  // push back word to vector of my_strings
//            }
        }
    }
    return individual_words;        // return vector of parsed words
}

char* my_string::toLower(){         // converts my_string to lower case
    int counter = 0;
    while(data[counter] != '\0'){
        data[counter] = tolower(data[counter]);
        counter++;
    }
    return data;
}

unsigned int my_string::get_length() {      // returns length of my_string
    length = strlen(data);
    return length;
}

char* my_string::delete_first_char(){
    for(int i =0; i < this->get_length()-1; i++){
        data[i] = data[i+1];
    }
    data[this->get_length()-1] = '\0';
    return data;
}

my_string my_string::substring(int start, int numChars){
    char* temp = new char[numChars+1];
    int j = 0;
    for(int i =start; i < numChars; i++){
        temp[j] = this->data[i];
    }
    temp[numChars] = '\0';
    my_string words = temp;
    return words;
}


/// -*-*-*-*-*-*-*-*-*-*-*-* OPERATORS *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

my_string& my_string::operator=(const my_string& string_ref){
    if(this == &string_ref){
        return *this;
    }
    delete[] this -> data;
    data = new char[strlen(string_ref.data)+1];
    strcpy(data, string_ref.data);
    data[strlen(string_ref.data)] = '\0';
    master_index = new char[strlen(string_ref.master_index)+1];
    strcpy(master_index, string_ref.master_index);
    master_index[strlen(string_ref.master_index)] = '\0';

    return* this;
}

my_string& my_string::operator=(char* string_ref){
    if(this->data == string_ref){
        return *this;
    }
    delete[] this-> data;
    data = new char[strlen(string_ref)+1];
    strcpy(data, string_ref);
    data[strlen(string_ref)] = '\0';

    master_index = new char[1];
    master_index[0]  = '\0';

    return *this;
}

my_string my_string::operator+ (const my_string& string_one){
    int new_length = strlen(string_one.data)+strlen(data);
    char *temp = new char[new_length + 1];
    strcpy(temp, data);
    strcat(temp, string_one.data);
    my_string tempo(temp);
    delete[] temp;
    return tempo;
}

ostream& operator << (ostream& output, const my_string& string_ref){
    output << string_ref.data;
    return output;
}


bool my_string::operator== (const my_string& string_ref){
    if(strcmp(data, string_ref.data)==0){
        return true;
    }
    else{
        return false;
    }
}

bool my_string::operator== (const char* string_ref){
    if(strcmp(data, string_ref) == 0){
        return true;
    }
    else{
        return false;
    }
}

bool my_string::operator!= (const my_string& string_ref) const {
    if(strcmp(data, string_ref.data)==0){
        return false;
    }
    else{
        return true;
    }
}

bool my_string::operator!= (const my_string* string_ref){
    if(strcmp(data, string_ref->data)==0){
        return false;
    }
    else{
        return true;
    }
}

char& my_string::operator[] (const int character){
    return data[character];
}

bool operator<(const my_string &left, const my_string &right) {
    return strcmp(left.data, right.data)<0;

}