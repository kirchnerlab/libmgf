/*!

\mainpage mgfp: Mascot Generic Format (MGF) Parser
\author Marc Kirchner <marc.kirchner@childrens.harvard.edu>

\section sec_intro Introduction
\c mgfp is a flex/bison-based C++ MGF parser library.

\section sec_install Installation

\subsection sec_install_bin Obtaining a Binary Package
Binary packages for Microsoft Windows, Linux (64 bit, built on Ubuntu 10.4) and
MacOS X (Snow Leopard) are available for download from the Steen Lab software
page at http://software.steenlab.org/mgfp .

\subsection sec_install_src Building from Source
Building \c mgfp from source is straightforward. However, it requires a working
CMake build system (available from http://cmake.org/) and CMake >= 2.6.

With cmake available, the building process is
 tar xvzf mgfp-xxxxxxx.tar.gz
 cd mgfp-xxxxxxx
 mkdir build
 cd build
 cmake ..
 make
 make test
 make install

Optionally, if you want to build your own precompiled packages, you can add
  [...]
  cmake ..
  make package


\section sec_examples Examples
Coding examples are in the \c applications/ subdirectory.

\section sec_appendix Appendix

\subsection sec_grammar The MGF Grammar
The following is the current MGF Grammar, extracted from Parser.ypp.
\verbinclude mgf_grammar.txt

\subsection sec_issues Known Issues
 - Parsing the TITLE tag. If the TITLE tag starts with a valid integer or double
   parsing will fail. There is no simple remedy for this as there are no
   official requirements for the string that follows the tag (e.g. enclosure in
   quotes or similar). For the time being, simply do not start search titles
   with integers or doubles.
*/

