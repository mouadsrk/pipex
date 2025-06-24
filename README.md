# 🔗 Pipex

**Pipex** is a Unix pipeline recreation project developed in C as part of the 42 Network curriculum. The goal is to mimic the behavior of shell pipelines by executing multiple commands chained with pipes and handling file redirections.

---

## 🎯 Project Objectives

- Reproduce shell pipeline behavior using `pipe`, `fork`, `dup2`, and `execve` system calls  
- Handle multiple commands connected by pipes  
- Support input/output redirection from/to files  
- Manage child processes and proper file descriptor management  
- Handle errors gracefully

---

## 🛠️ Features

- Execute a sequence of commands separated by pipes (`|`)  
- Redirect standard input/output using files  
- Properly create child processes for each command  
- Close unused file descriptors to avoid leaks  
- Report errors with descriptive messages

---

## 🧪 How to Compile and Run

```bash
# Clone repo and compile
git clone git@github.com:mouadsrk/pipex.git
cd pipex
make

# Run the program:
# ./pipex infile "cmd1" "cmd2" outfile
./pipex input.txt "grep hello" "wc -l" output.txt
