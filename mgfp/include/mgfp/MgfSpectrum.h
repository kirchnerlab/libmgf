#ifndef __MGFP_INCLUDE_MGFSPECTRUM_H__
#define __MGFP_INCLUDE_MGFSPECTRUM_H__

#include <mgfp/config.h>

#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include <mgfp/Collection.h>
#include <mgfp/MassAbundancePair.h>

namespace mgf {

/** An MgfSpectrum holds a fragment ion series and the corresponding (local)
 * search parameters. The parameter set, their values and syntax are taken from
 * the MatrixScience format help file at
 * http://www.matrixscience.com/help/data_file_help.html#GEN
 */
class MGFP_EXPORT MgfSpectrum : public Collection<MassAbundancePair>
{
  public:
    /** Default constructor. Constructs an empty MgfSpectrum.
     */
    MgfSpectrum();

    /** Get the precursor charges for which a search is requested.
     *  @see http://www.matrixscience.com/help/search_field_help.html#TWO
     *  @param[out] charges The charge vector.
     */
    std::vector<int> getCHARGE(void) const;

    /** Set the precursor charges for which a search is requested.
     *  @see http://www.matrixscience.com/help/search_field_help.html#TWO
     *  @param[in] charges The charge vector.
     */
    void setCHARGE(const std::vector<int>& charges);

    /** Get amino acid composition information.
     *  @see http://www.matrixscience.com/help/sq_help.html#COMP
     *  @return An amino acid composition string.
     */
    std::string getCOMP(void) const;

    /** Set the amino acid composition information.
     *  @see http://www.matrixscience.com/help/sq_help.html#COMP
     *  @param[in] An amino acid composition string.
     */
    void setCOMP(const std::string& comp);

    /** Get 
     *  @see 
     *  @return
     */
    std::string getETAG(void) const;

    /** Set 
     *  @see 
     *  @param[in] 
     */
    void setETAG(const std::string& etag);

    /** Get the instrument type/fragmentation rules. Based on the definitions in
     * the Mascot \c fragmentation_rules configuration files, this defines the
     * type of instrument Mascot expects and the fragmentation scheme used to
     * derive the theoretical fragementation spectra.
     *  @return The.
     */
    std::string getINSTRUMENT(void) const;

    /** Set the instrument type/fragementation rules. Valid values are defined
     * in the Mascot \c fragmentation_rules configuration file. There is no way
     * for \a mgfp to validate the user input, hence the responsibility lies
     * with the user.
     *  @param[in] instrument The
     */
    void setINSTRUMENT(const std::string& instrument);

    /** Get 
     *  @see 
     *  @return
     */
    void getIONS(std::vector<MassAbundancePair>& ions) const;

    /** Set 
     *  @see 
     *  @param[in] 
     */
    void setIONS(const std::vector<MassAbundancePair>& ions);

    /** Get the string representation of the variable modifications. The
     * modification string specifies which variable post-translational
     * modifications are searched in the Mascot query associated with the
     * current MgfSpectrum..
     *  @return A string of variable modifications.
     */
    std::string getIT_MODS(void) const;

    /** Set the variable modification string. The modfication string specifies which
     * variable post-translational modifications are searched in the Mascot
     * query associated with the current MgfSpectrum.
     * Strings should conform to UniMod standards.
     *  @param[in] it_mods The modification string.
     */
    void setIT_MODS(const std::string& it_mods);

    /** Get the peptide mass and (optionally) the abundance of the precursor.
     *  The \c .first part of the return value holds the precursor mass, in \a
     *  m/z. To determine relative (i.e. uncharged) mass, consult the precursor
     *  charges, available via getCHARGES(). If specified in the MGF file, the
     *  \c .second element of the return value holds the precursor abundance. If
     *  no precursor abundance was specified, then <tt> .second == 0</tt>.
     *  @return A pair of precursor mass and (optionally) abundance.
     */
    std::pair<double, double> getPEPMASS(void) const;

    /** Set the peptide mass and (optionally) the abundance of the precursor.
     *  \c pepmass.first must hold the precursor mass, in \a
     *  m/z. Optionally, \c pepmass.second may hold the precursor abundance. If
     *  no abundance value is available, \c pepmass.second must be set to zero.
     *  @param[in] pepmass A pair of precursor mass and (optionally) abundance.
     */
    void setPEPMASS(const std::pair<double, double> pepmass);

    /** Get the retention time of the precursor. 
     *  @return The retention time of the precursor, in seconds.
     */
    double getRTINSECONDS(void) const;

    /** Set the retention time of the precursor. 
     *  @param[in] rtinseconds The retention time of the precursor, in seconds.
     */
    void setRTINSECONDS(const double rtinseconds);

    /** Get 
     *  @see 
     *  @return
     */
    std::string getSCANS(void) const;

    /** Set 
     *  @see 
     *  @param[in] 
     */
    void setSCANS(const std::string& scans);

    /** Get the amino acid sequence. Please consult the detailed description in
     * the Mascot documentation (see link).
     *  @see http://www.matrixscience.com/help/sq_help.html#SEQ
     *  @return The amino acid sequence.
     */
    std::string getSEQ(void) const;

    /** Get the amino acid sequence. Please consult the detailed description in
     * the Mascot documentation (see link).
     *  @see http://www.matrixscience.com/help/sq_help.html#SEQ
     *  @param[in] seq The amino acid sequence.
     */
    void setSEQ(const std::string& seq);

    /** Get the sequence tag. Please consult the detailed description in the
     *  Mascot documentation (see link).
     *  @see http://www.matrixscience.com/help/sq_help.html#TAG
     *  @return The sequence tag.
     */
    std::string getTAG(void) const;

    /** Set the sequence tag. Please consult the detailed description in the
     *  Mascot documentation (see link).
     *  @see http://www.matrixscience.com/help/sq_help.html#TAG
     *  @param[in] tag A sequence tag string.
     */
    void setTAG(const std::string& tag);

    /** Get the query title. This returns the title of the query that
     *  corresponds to the spectrum at hand.
     *  @see http://www.matrixscience.com/help/data_file_help.html
     *  @return The query title.
     */
    std::string getTITLE(void) const;

    /** Set the query title. Set the title of the query that corresponds to the
     * spectrum at hand.
     *  @see http://www.matrixscience.com/help/data_file_help.html
     *  @param[in] title The query title.
     */
    void setTITLE(const std::string& title);

    /** Get the search tolerance. The return value is unit-dependent.  The unit
     *  is available via getTOLU().
     *  @see http://www.matrixscience.com/help/search_field_help.html#TOL
     *  @return The search tolerance.
     */
    double getTOL(void) const;

    /** Set the search tolerance. The tolerance value depends on the tolerance
     *  unit which can be set using setTOLU().
     *  @see http://www.matrixscience.com/help/search_field_help.html#TOL
     *  @param[in] tol The
     */
    void setTOL(const double tol);

    /** Get the unit in which the tolerance is specified. Valid values are \a %,
     * \a ppm, \a mmu and \a Da).
     *  @return A string specifying the tolerance unit.
     */
    std::string getTOLU(void) const;

    /** Set the unit in which the tolerance is specified. Valid values are \a %,
     * \a ppm, \a mmu and \a Da).
     *  @param[in] tolu The tolerance unit.
     */
    void setTOLU(const std::string& tolu);

    /** Clear all data from the MgfSpectrum.
     */
    void clear();

  private:
    friend std::ostream& operator<<(std::ostream& os, const MgfSpectrum& mgf);
    std::vector<int> charges_;
    std::string comp_, etag_, instrument_, it_mods_;
    std::pair<double, double> pepmass_;
    double rtinseconds_;
    std::string scans_, seq_, tag_, title_; // FIXME: scans_ should be a vector of ranges
    double tol_;
    std::string tolu_;
};

/** An stream operator to output the fragment ion spectrum in MGF. This includes
 * all entries between <tt>BEGIN IONS</tt> and <tt>END IONS</tt> as well as all
 * local parameter key/value-pairs.
 */
std::ostream& operator<<(std::ostream& os, const MgfSpectrum& mgf);

} // namespace mgf

#endif

