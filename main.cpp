
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>

using namespace std;

string read_input(){
    
    string buffer;

    if (!getline(cin, buffer)){ // checks if input taken
        return "";
    }

    return buffer; // returns input command
}

// vector<string> work similar to pointer of pointer-> array where each is a string.
vector<string> parse_input(const string& input){
    
    vector<string> args;
    istringstream stream(input); // reads input piece by piece
    string token;
    
    while (stream >> token){ // removes every kind of whitespace
        args.push_back(token);
    }

    return args; // returns the vector
}

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

void execute_help(void){
    
    cout << "Cshell - Built-in Commands\n";
    cout << "  cd [directory]  Change the working directory\n";
    cout << "  help            Display this help message\n";
    cout << "  exit            Exit the shell\n";
    cout << "\n";
    cout << "Other commands are searched for in PATH.\n";

}

void shell_loop(void){

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

int main(){
    
    shell_loop();
    return 0;
}