
README.txt
==========

This folder contains the wxWidgets version of the Hexdump application. Right now a Code::Blocks
project file and a Visual Studio 2012 project file are provided.

The Visual Studio project file assumes an environment variable named WX_ROOT has been set to
point at the top of the wxWidgets installation folder. This environment variable is not a
requirement of wxWidgets itself. It is only used in the Visual Studio project file to make those
files independent of the precise location of wxWidgets on your system. Note that the
Code::Blocks project file uses a Code::Blocks global variable to locate wxWidgets. See the
Code::Blocks documentation for more information.

For some reason the Debug configuration of the Visual Studio project files does not entirely
work. I get the following somewhat baffling error:

fatal error CVT1100: duplicate resource. type:MANIFEST, name:1, language:0x0409 CVTRES wxHexdump

The Release configuration works fine, however, and the two configurations are very similar. I
don't have time right now to figure out the solution to this issue.
