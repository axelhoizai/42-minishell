[![minishell](https://github.com/ayogun/42-project-badges/blob/main/badges/minishelle.png)](https://github.com/ayogun/42-project-badges/blob/main/badges/minishelle.png)

#  42 Minishell - 110% ✅  

**Minishell** is a project that consists of creating a **simple Unix shell**.  
It allows you to explore the fundamentals of **process management, command parsing, signals, and system calls** by re-implementing basic shell behavior.  

### New skills unlocked  

- **Command Parsing** → Handling user input, tokenizing, and interpreting commands.  
- **Process Management** → Using `fork`, `execve`, and `wait` to execute programs.  
- **Pipes & Redirections** → Managing input/output redirections (`>`, `<`, `>>`) and pipelines (`|`).  
- **Environment Variables** → Expanding `$VARIABLES` and handling `env`, `export`, and `unset`.  
- **Signals Handling** → Managing `CTRL+C`, `CTRL+D`, `CTRL+\` for proper shell behavior.  
- **Error Handling & Memory Management** → Avoiding leaks and ensuring robust behavior.  

---

## 🏗️ Project Requirements  

### 🎯 Mandatory Features  
- Display a **prompt** and wait for user input.  
- Support **execution of binaries** found in the system `PATH`.  
- Implement the following built-in commands:  
  - `echo` with option `-n`  
  - `cd` with relative/absolute paths  
  - `pwd` to display current directory  
  - `export` and `unset` to manage environment variables  
  - `env` to print environment variables  
  - `exit` to close the shell  
- Handle **quotes** (`'`, `"`) and environment variable expansion (`$HOME`).  
- Implement **redirections** (`<`, `>`, `>>`) and **pipes** (`|`).  
- Correctly manage **signals** (`SIGINT`, `SIGQUIT`, `EOF`).  

---
## ⚙️ Setup
Clone the repository:
```
git clone git@github.com:axelhoizai/42-minishell.git && cd 42-minishell
```

Install dependencies:
```
make
```

## Usage
Run the executable with a valid map file:
```
./minishell
```
