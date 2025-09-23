                       GRP DECOMPILER 
                          
                       Version 2.2.3

            The file extraction tool for GRP pseudo-archives by Popov Evgeniy Alekseyevich

The program description.

This program lets you extract files from GRP pseudo-archives. It is used in games that are built on the BUILD game engine.
This program works with all BUILD engine games.
This program takes a target file name and an output path as the command-line arguments.
Always add a directory separator (\ or /) at the end of the output path.

Exit codes.

0: The operation was successfully completed.
1: Can't open the input file.
2: Can't create the output file.
3: Can't allocate memory.
4: The invalid format.

License.

This program is distributed under the GNU GENERAL PUBLIC LICENSE.

The source code.

The code was compiled under Open Watcom.
But you can compile it with any modern C compiler.
The source code can be compiled for a wide range of operating systems, but you need to create a makefile or a build script by yourself.
I provide only two things: the binary file for Windows and the makefile for Linux.

Install and uninstall under Linux.

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to install: make install
Run as root to uninstall: make uninstall

Version history.

0.1-0.9: The internal unstable builds.
1.0-1.0.4: The stable branch.
1.0.5-1.3: The small changes in the source code.
1.4: The source code has improved. Linux support has been added.
1.5: The small changes in the source code.
1.6: The small bug with the output file names has been fixed.
1.7-1.8: The small changes in the source code.
1.9: The filename checking has improved.
1.9.0.1: The documentation has been updated.
1.9.1-1.9.6: The small changes.
1.9.8-2.0.1: The small bug with the output file names has been fixed.
2.0.2-2.0.4: The small changes.
2.0.4.1: The makefile has been updated.
2.0.5-2.0.6: The small changes.
2.0.7: A small bug has been fixed.
2.0.7.1-2.0.7.2: The makefile has been updated.
2.0.8: 2.1.3: The small changes.
2.1.4: Visual C++ support has improved.
2.1.4.1: The documentation has been updated.
2.1.5: The small changes.
2.1.5.1-2.1.5.2: The documentation has been updated.
2.1.6: The source code was recompiled under Tiny C Compiler.
2.1.7: The small changes.
2.1.7.1: The makefile has been updated.
2.1.7.2: The documentation has been updated.
2.1.8: The small changes.
2.1.8.1: The documentation has been updated.
2.1.9: The extraction process has improved.
2.2: A small bug has been fixed.
2.2.1-2.2.3: The small changes.