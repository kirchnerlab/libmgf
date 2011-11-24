/*!

\mainpage libmgf: Mascot Generic Format (MGF) Parser

\section sec_intro Introduction
\c libmgf (formerly mgfp) is a flex/bison-based C++ MGF parser library.<br>
It includes the library code as well as the following set of 
MGF processing tools:

\li mgfvalidate -- validates a given MGF file 
\li rix -- reporter ion extractor for iTRAQ4 and TMT
\li ms2preproc -- MGF preprocessing tool (see below)

The <a href="http://steenlab.org">Steen \& Steen Lab</a> provides
the library under the terms of a MIT license for use in academic and 
non-academic environments.

\section sec_citation Citation

If you make use of \c libmgf in your own projects, please cite the
following article:<br>

\li Kirchner M, Steen JAJ, Hamprecht FA, Steen H (2010).
MGFp: An open Mascot Generic Format parser library implementation.
<i>Journal of Proteome Research, 9(5):2762-2763 (2010)</i>.
[<a href="http://www.ncbi.nlm.nih.gov/pubmed/20334363">PubMed entry</a>]

If you use \c ms2preproc in your data analysis pipeline, please cite<br>

\li Renard BY, Kirchner M, Monigatti F, Invanov AR, Rappsilber J, 
Winter D, Steen JAJ, Hamprecht FA, Steen H, When Less
Can Yield More - Computational Preprocessing of MS/MS Spectra for
Peptide Identification, <i>Proteomics 9(21):4978-4984 (2009)</i>.
[<a href="http://www.ncbi.nlm.nih.gov/pubmed/19743429">PubMed entry</a>]

\section sec_install Installation

\subsection sec_install_bin Obtaining the Software
Binary packages for Microsoft Windows are available here: 
\li https://github.com/kirchnerlab/libmgf/downloads

Linux and Mac users, please build from source.

\subsection sec_install_src Building from Source
Building \c libmgf from source is straightforward. It requires a working
CMake build system (available from http://cmake.org/) and CMake >= 2.6.

With cmake available, the build process is
\verbatim
 git clone git://github.com/kirchnerlab/libmgf.git
 mkdir libmgf-build
 cd libmgf-build
 cmake ../libmgf
 make
 make test
 make install
 make package (optional, generates binary packages for your platform)
\endverbatim

For Mac users: if you are using MacPorts, then linking errors with \c
boost::program_options seem common; alas, this is not a \c libmgf issue but
indicates a compiler/library incompatibility on your system.

\section Usage

\subsection cmdline Using the command line applications
All command line applications come with a \c --help switch that
describes their usage.

\subsection lib Using the libmgf library
To use the parser, one must first create a parser driver instance:
\code
    #include <mgf/mgf.h>
    ...
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
\li the MGF format has been misused many times; although MatrixScience provides
    a format description, there is no official formal grammar. As such, libmgf
    may sometimes refuse to accept a specific MGF dialect. Please contact the
    developers if that seems to be the case for you and we will see what we can 
    do. Note that libmgf provides comprehensive error messages; please include
    this information in bug reports or enhancement requests.
\li Multiple USERxx entries; the current implementation ignores USER entries.
\li General PMF support: most libmgf testing has been done on MS/MS ion search
    data. Hence, it is possible that valid PMF constructs are not
    recognized. If that is the case, please contact the developers and we will
    attempt to fix issues as quickly as possible.

\subsection sec_grammar The MGF Grammar
The following is the current MGF Grammar, extracted from Parser.ypp.
\verbinclude mgf_grammar.txt

*/

