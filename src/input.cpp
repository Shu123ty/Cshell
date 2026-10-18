#include "input.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string read_input(){
    
    string buffer;

    if (!getline(cin, buffer)){ 
        return "";
    }

    return buffer; 
}


vector<string> parse_input(const string& input){
    
    vector<string> args;
    istringstream stream(input); 
    string token;
    
    while (stream >> token){ 
        args.push_back(token);
    }

    return args; 
}