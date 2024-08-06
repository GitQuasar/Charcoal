# Charcoal Docs
## Introduction
* `Charcoal` is written in C++ (so it's pretty fast);
* `Charcoal` is written in a form of command line application with simple and intuitive CLI;
* `Charcoal` stores your tasks in JSON files (so it's pretty easy for me, as a developer, to work with them, and for you, as a user, to import and export them).

## Little side note:
> `Charcoal` is in his pretty early stage.

For now, that means:
* there is no usage of some fancy project building systems (such as CMake), instead, building of this project is pretty much hardcoded and is relying on aprroach with usage of Makefile (you need to install 'make' utility for this to work out on Windows);
* it is not expected to be worked on in some professional IDE (that's why there's no project or solution files present).

## Build
> For default, this project is compiled with `clang++` compiler, but you can change this by editing the `CC` variable in the Makefile itself from `clang++` to whatever the compiler is installed on `your` machine.

Steps:
1. Open your terminal in the project root directory, execute the following command and hope for the best:
`make build`
2. Run the resulted `Charcoal.exe`  in the `bin` folder.