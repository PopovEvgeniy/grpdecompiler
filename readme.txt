                       GRP DECOMPILER 
                          
                       Version 2.1.5

            File extraction tools for GRP pseudo-archives by Popov Evgeniy Alekseyevich

System requirements

68 kilobytes of free space on storage media. 

Description and usage

This program lets you extract files from GRP pseudo-archives.
It is used in games that are built on the BUILD game engine.
This program takes a target file name and an output path as the command-line arguments.
Always add a directory separator (\ or /) at the end of the output path.

Exit codes

0 - Operation was successfully completed.
1 - Can't open the input file.
2 - Can't create the output file.
3 - Can't allocate memory.
4 - Invalid format.

License

This program is distributed under GNU GENERAL PUBLIC LICENSE.

Compatibility

GRP DECOMPILER works with all BUILD engine games.

Source code

The code was compiled under Open Watcom.
But you can compile it under any modern C compiler.
Source code can be compiled for a wide range of operating systems, but you need to create a makefile or build script by yourself.
I provide only two things: the binary file for Windows and the makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to installation: make install
Run as root to uninstall: make uninstall

Contact

You can send me a letter at tuzik87@inbox.ru.

Version history

0.1 – 0.9 – Internal unstable builds.
1.0 – 1.0.4 – Stable branch.
1.0.5 – 1.3 – Small changes in source code.
1.4 – Source code improved. Linux support has been added.
1.5 – Small changes in source code.
1.6 – Small bugs with the output filenames fixed.
1.7 – 1.8 – Small changes in source code.
1.9 – Filename checking improved.
1.9.0.1 – Documentation updated.
1.9.1 – 1.9.6 – Small changes.
1.9.8 – 2.0.1 – Small bug with the output file names fixed.
2.0.2 – 2.0.4 – Small changes.
2.0.4.1 – Makefile updated.
2.0.5 – 2.0.6 – Small changes.
2.0.7 – Small bug fixed.
2.0.7.1 – 2.0.7.2 – Makefile updated.
2.0.8 – 2.1.3 – Small changes.
2.1.4 – Visual C++ support improved.
2.1.4.1 – Documentation updated.
2.1.5 – Small changes.