# Object file reader 

A CLI utility written in C++ which dumps all the relevant information about an object file (its sections and symbols)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)

## Introduction

Provide a more detailed introduction to the project. Include information about its background, motivation, and any relevant context.

## Features

- Read an object file and display the contents of it

## Installation

To compile the project all you have to do is run make like so:

```bash
make
```

If you are using an editor like me which requires the `compile_commands.json` in order for the intellisense to work properly you can compile the project with

```bash
make compile-commands
```

Note: You will need to install the `bear` CLI which is used to output the `compile_commands.json` from a `Makefile`.

## Usage

```bash
./object-reader <file name>
```

## License

Specify the project's license. Choose an appropriate open-source license that suits your project's needs.

