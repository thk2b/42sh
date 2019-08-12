# 42sh

A complete UNIX shell implementation

![screenshot](https://raw.githubusercontent.com/thk2b/42sh/master/media/screenshot.png)

Features
- command execution by searching the `PATH` environment variable
- line edition and history
- `;` for mutiple commands, `|` pipes, `>` and `N>` redirections
- logical operators `&&` and `||`
- backtics for command substitution
- `echo`, `cd`, `env` builtins


## Build

To build an executable, clone and run
```sh
make
```

## Usage

To launch the shell, run
```sh
./42sh
```
