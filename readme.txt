                       GRP DECOMPILER 
                          
                       Version 2.0.9

            File extraction tools for GRP pseudo-archives by Popov Evgeniy Alekseyevich

System requirement

52 kilobytes free space on storage media. 

Description and usage

This program let you extract files from GRP pseudo-archives.
It is used in games that built on BUILD game engine.
This program takes a target file name and output path as command line arguments.
Always add directory separator(\ or /) at an end of output path.

Exit codes

0 - Operation successfully complete.
1 - Can't open input file.
2 - Can't create output file.
3 - Can't allocate memory.
4 - Invalid format.

License

This program distributed under GNU GENERAL PUBLIC LICENSE.

Compatibility

GRP DECOMPILER work with all BUILD engine games.

Source code

The program source code compiled under Open Watcom.
But you can do it under any modern C compiler.
Source code can be compiled for wide range operating systems, but you need to create makefile or build script by yourself.
I provide only two things: compiled the binary file for Windows and makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1.Extract content of source code archive.
2.Open terminal and go to source code directory.
3.
Run as root for installation: make install
Run as root for uninstall: make uninstall

Contact

You can send me a letter to tuzik87@inbox.ru.

Version history

0.1 - 0.9 - Internal unstable builds.
1.0 - 1.0.4 - Stable branch.
1.0.5 - 1.3 - Small changes in source code.
1.4 - Source code improved. Linux support added.
1.5 - Small changes in source code.
1.6 - Small bugs with output filenames fixed.
1.7 - 1.8 - Small changes in source code.
1.9 - Filename checking improved.
1.9.0.1 – Documentation updated.
1.9.1 - 1.9.6 - Small changes.
1.9.8 - 2.0.1 - Small bug with output file names fixed.
2.0.2 - 2.0.4 - Small changes.
2.0.4.1 - Makefile updated.
2.0.5 - 2.0.6 - Small changes.
2.0.7 - Small bug fixed.
2.0.7.1 - 2.0.7.2 - Makefile updated.
2.0.8 - 2.0.9 - Small changes.