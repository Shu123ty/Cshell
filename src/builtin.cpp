#include "builtin.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

using namespace std;

void execute_cd(vector<string>& args){

    string directory = args[1];

    if(directory.empty()){
        directory = getenv("HOME");
        if (directory.empty()){
            cerr << "cd: HOME is not set\n";
            return;
        }
    }

    if (chdir(directory.c_str()) != 0){
    perror("cd");
    }
}

void execute_help(void){
    
    cout << "Cshell - Built-in Commands\n";
    cout << "  cd [directory]  Change the working directory\n";
    cout << "  help            Display this help message\n";
    cout << "  exit            Exit the shell\n";
    cout << "\n";
    cout << "Other commands are searched for in PATH.\n";

}