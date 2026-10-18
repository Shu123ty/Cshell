#include "executor.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void execute_command(vector<string>& args){
    
    if (args.empty()){
        return;
    }

    pid_t pid = fork(); // creates a child process

    if (pid < 0){
        perror("fork");
        return;
    }
    if(pid == 0){
        vector<char*> argv;
        for(string& arg: args){ 
            argv.push_back(arg.data());    
        }
        argv.push_back(nullptr);
        
        execvp(argv[0], argv.data());

        perror(args[0].c_str());
        _exit(127);
    }
    else{

        int status;
        pid_t result;

        do{
            result = waitpid(pid, &status,0);
        }while (result == -1 && errno == EINTR);

        if (result == -1){
            perror("waitpid");
        }
    }
}