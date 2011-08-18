--[ README ]------------------------------------------------

This is a flex/bison-C++ parser. The MGF grammar is located
in Parser.ypp, the scanner configuration in Scanner.l.
The code is based on the basic template provided by Timo 
Bingmann (http://idlebox.net/2007/flex-bison-cpp-example/).

Makefile.createParser holds the flex/bison commands that will
create the necessary .cpp, .h, and .h files. The whole
thing is wrapped as a static library which should ease the
independent distribution process. W.r.t. SVN versions, be aware
that in order to compile on any system (assuming a stable
MGF grammar but getting rid of depending on bison/flex availability),
the scanner and parser are pre-generated. This should in general not 
be a problem.

If you run into problems and manage to solve them, please send 
patches to
    Marc Kirchner <firstname.lastname@childrens.harvard.edu>

