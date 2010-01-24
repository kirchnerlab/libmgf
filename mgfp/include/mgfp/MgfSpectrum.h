#ifndef __MGFSPECTRUM_H__
#define __MGFSPECTRUM_H__

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
class MgfSpectrum : public Collection<MassAbundancePair>
{
  public:
    MgfSpectrum();
    std::vector<int> getCHARGE(void) const;
    void setCHARGE(const std::vector<int>& charges);
    std::string getCOMP(void) const;
    void setCOMP(const std::string& comp);
    std::string getETAG(void) const;
    void setETAG(const std::string& etag);
    std::string getINSTRUMENT(void) const;
    void setINSTRUMENT(const std::string& instrument);
    void getIONS(std::vector<MassAbundancePair>& ions) const;
    void setIONS(const std::vector<MassAbundancePair>& ions);
    std::string getIT_MODS(void) const;
    void setIT_MODS(const std::string& it_mods);
    std::pair<double, double> getPEPMASS(void) const;
    void setPEPMASS(const std::pair<double, double> pepmass);
    double getRTINSECONDS(void) const;
    void setRTINSECONDS(const double rtinseconds);
    std::string getSCANS(void) const;
    void setSCANS(const std::string& scans);
    std::string getSEQ(void) const;
    void setSEQ(const std::string& seq);
    std::string getTAG(void) const;
    void setTAG(const std::string& tag);
    std::string getTITLE(void) const;
    void setTITLE(const std::string& title);
    double getTOL(void) const;
    void setTOL(const double tol);
    std::string getTOLU(void) const;
    void setTOLU(const std::string& tolu);
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

