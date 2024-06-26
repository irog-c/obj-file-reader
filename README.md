# Object file reader 

A CLI utility written in C++ which dumps all the relevant information about an object file (its sections and symbols)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)

## Introduction

I wrote this utility to learn more about the ELF relocatable object file format, how it works, and wanted to write a potentially useful utility for people who want to inspect such files. There is plenty of work left to do on this project and this is far from done, I will be adding features to it as I see fit.

Todo:
 - Add a more advanced argument handling with flags and such
 - Add support for printing out the disassembled function symbol
 - Add support to list all symbols per section
 - Possibly think about adding a way to edit the object file

Some resources I used for this project:
 - https://docs.oracle.com/cd/E19120-01/open.solaris/819-0690/6n33n7fcb/index.html
 - https://ftp.gnu.org/old-gnu/Manuals/bfd-2.9.1/html_node/bfd_toc.html
 - http://www.skyfree.org/linux/references/ELF_Format.pdf
 - https://sourceware.org/binutils/binutils-porting-guide.txt
 - https://github.com/CyberGrandChallenge/binutils/blob/master/binutils/objdump.c

## Features

- Read an object file and display the contents of it

## Installation

Prerequisites:

You might need to install `binutils`
```bash
sudo apt-get install binutils-dev
```

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

