# Cshell

A simple Linux shell written in C++ to explore how command-line shells work internally, including process creation, command execution, and built-in commands.

## Features

- **Command execution** — Run external Linux commands.
- **Built-in commands** — Supports `cd`, `help`, and `exit`.
- **Process management** — Uses `fork()`, `execvp()`, and `waitpid()` to execute external programs.
- **Directory navigation** — Change directories using `cd`.
- **Dynamic prompt** — Displays the current directory in the shell prompt.
- **Input parsing** — Splits command input into arguments.
- **Modular architecture** — Separates input handling, built-ins, execution, and the main shell loop.

## Requirements

- Linux
- C++ compiler (`g++`)
- GNU Make (optional)

## Installation

Clone the repository:

```bash
git clone <YOUR_REPOSITORY_URL>
cd Cshell
```

Replace `<YOUR_REPOSITORY_URL>` with your GitHub repository URL.

## Build

Using Make:

```bash
make
```

Or compile manually:

```bash
g++ -Wall -Wextra -std=c++17 -Iinclude main.cpp src/*.cpp -o CSHELL
```

## Run

Start Cshell:

```bash
./CSHELL
```

## Built-in Commands

| Command | Description |
|---|---|
| `cd` | Change the current working directory |
| `help` | Display available commands and usage information |
| `exit` | Exit Cshell |

Cshell also supports external commands available through your system's `PATH`, such as:

```bash
ls
pwd
whoami
uname -a
```

## Project Structure

```text
Cshell/
├── main.cpp
├── Makefile
├── LICENSE
├── README.md
├── .gitignore
├── include/
│   ├── input.hpp
│   ├── builtins.hpp
│   ├── executor.hpp
│   └── shell.hpp
└── src/
    ├── input.cpp
    ├── builtins.cpp
    ├── executor.cpp
    └── shell.cpp
```

## How It Works

1. **Read input:** Accept a command from the user.
2. **Parse input:** Split the command into its program name and arguments.
3. **Check built-ins:** Handle commands such as `cd`, `help`, and `exit` inside Cshell.
4. **Create a process:** Use `fork()` to create a child process for external commands.
5. **Execute the command:** The child calls `execvp()` to run the requested program.
6. **Wait for completion:** The parent uses `waitpid()` to wait for the child process.

The `cd` command runs in the shell process itself so that directory changes persist between commands.

## Current Limitations

- Quoted arguments containing spaces are not supported.
- Pipes (`|`) are not supported.
- Input and output redirection (`<`, `>`, `>>`) are not supported.
- Background execution (`&`) is not supported.

## Learning Goals

Cshell is a learning project focused on understanding:

- Linux process management
- System calls and process execution
- Command parsing
- Built-in shell commands
- Modular C++ program design

## License

Copyright (c) 2026 Shubhayu Mukherjee.

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.