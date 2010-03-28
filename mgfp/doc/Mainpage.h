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
\verbatim
 tar xvzf mgfp-xxxxxxx.tar.gz
 cd mgfp-xxxxxxx
 mkdir build
 cd build
 cmake ..
 make
 make test
 make install
\endverbatim

Optionally, if you want to build your own precompiled packages, you can add
\verbatim
  cmake ..
  make package
\endverbatim

\section Usage
To use the parser, one must first create a parser driver instance:
\code
    mgf::MgfFile mgfFile;
    mgf::Driver driver(mgfFile);
\endcode
Then set the verbosity flage (defaulting to off/false)
\code
    driver.trace_parsing = true;
    driver.trace_scanning = true;
\endcode
and parse the input. The input is a stream (like \c std::cin in the
example here or \c std::fstream).
\code
    bool result = driver.parse_stream(std::cin);
\endcode
One should always check if the parsing was successful and only continue if so.
\code
    if (!result) {
        std::cerr << std::endl
          << "Error parsing data stream (use -v for details)." << std::endl;
        return -1;
    }
\endcode
If the parsing was successful, the contents of the MGF file are available in 
terms of an MgfFile object; it is possible to iterate over the MS/MS spectra
and to read/modify/otherwise process the contents. The example here attempts
to extract TMT reporter ion intensities from centroid mode MS/MS spectra:

\code
    typedef mgf::MgfFile::iterator MFI;
    for (MFI i = mgfFile.begin(); i != mgfFile.end(); ++i) {
        // sort the MS/MS spectrum by m/z
        std::sort(i->begin(), i->end(), mgf::LessThanMz());
        typedef mgf::MgfSpectrum::iterator MSI;
        // extract TMT reporter ion intensities
        std::tr1::array<double, 6> obsTmtAbundances;
        for (size_t n = 0; n < 6; ++n) {
            MSI closestIt = findClosestMz(i->begin(), i->end(), tmtMasses[n]);
            // check if the closest centroid is close enough
            if (std::abs(closestIt->first - tmtMasses[n]) < 0.5) {
                obsTmtAbundances[n] = closestIt->second;
            } else {
                obsTmtAbundances[n] = 0.0;
            }
            tmts.push_back(obsTmtAbundances);
        }
    }
\endcode


\section sec_examples Examples
Coding examples are in the \c applications/ subdirectory

\section sec_appendix Appendix

\subsection sec_issues Known Issues
\li Parsing the TITLE tag. If the TITLE tag starts with a valid integer or double
    parsing will fail. There is no simple grammar-based remedy for this as there
    are no official requirements for the string that follows the tag (e.g.
    enclosure in quotes or similar). The solution is to modify the scanner to
    read full TITLE lines and to process the line prior to returning it to the
    parser. This will be implemented asap.
\li Multiple USERxx entries; the current implementation ignores USER entries.
\li General PMF support: most MGFp testing has been done on MS/MS ion search
    data. Hence, it is possible that valid PMF constructs are not
    recognized. If that is the case, please contact the developers and we will
    attempt to fix issues as quickly as possible.

\subsection sec_grammar The MGF Grammar
The following is the current MGF Grammar, extracted from Parser.ypp.
\verbinclude mgf_grammar.txt

*/

