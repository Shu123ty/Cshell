#include "shell.hpp"
#include "input.hpp"
#include "builtin.hpp"
#include "executor.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>

using namespace std;

void shell_loop(void){
    const char* home = getenv("HOME");

    if (home != nullptr)
    {
    chdir(home);
    }

    int running = 1;
   
    while (running){
        cout << "Cshell-> " << flush;
        
        string command = read_input();

        if(!cin){
            break;
        }

        vector<string> args = parse_input(command);

        if (args.empty()){
            continue;
        }
        
        if (args[0] == "exit"){
            running = 0;
        }
        else{
            if (args[0] == "cd"){
                execute_cd(args);
            }else if (args[0] == "help"){
                execute_help();
            }
            else{
                execute_command(args);
            }
        }
    }
}