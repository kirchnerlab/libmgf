#ifndef __MGFHEADER_H__
#define __MGFHEADER_H__

#include <mgfp/config.h>

#include <map>
#include <ostream>
#include <string>
#include <vector>

#include <mgfp/utils.h> // for existsOrEmpty()

namespace mgf {

/** Mascot Generic Format file header (global parameters) information. MGF files
 * hold global and local parameters. Whereas local parameters are stored with
 * the respective MgfSpectrum, MgfHeader is where the global variables reside.
 * The description and values of the variables are taken from the official
 * MatrixScience format information page at
 * http://www.matrixscience.com/help/data_file_help.html#GEN..
 */
class MgfHeader
{
  public:
    
    /** Get the
     *  @return The.
     */
    std::string getCLE(void) const;

    /** Set the
     *  @param[in] cle The
     */
    void setCLE(const std::string& cle);
    
    /** Get the
     *  @return The.
     */
    std::string getCOM(void) const;

    /** Set the
     *  @param[in] com The
     */
    void setCOM(const std::string& com);
    
    /** Get the database name agains which Mascot should search.
     *  @return The database name.
     */
    std::string getDB(void) const;

    /** Set the sequence database name that specifies the database against which
     *  searches should be carreid out.
     *  @param[in] db The database name.
     */
    void setDB(const std::string& db);
    
    /** Get the
     *  @return The.
     */
    std::string getFORMAT(void) const;

    /** Set the
     *  @param[in] format The
     */
    void setFORMAT(const std::string& format);
    
    /** Get the 
     *  @return The.
     */
    std::string getINSTRUMENT(void) const;

    /** Set the
     *  @param[in] instrument The
     */
    void setINSTRUMENT(const std::string& instrument);
    
    /** Get the modification string. The modefication string specifies which
     *  post-translational modifications are searched in a Mascot query.
     *  @return The modification string.
     */
    std::string getIT_MODS(void) const;

    /** Set the modification string. The modfication string specifies whcih
     * post-otranslations modifications are searched in a Mascot query.
     *  @param[in] it_mods The modification string.
     */
    void setIT_MODS(const std::string& it_mods);
    
    /** Get the
     *  @return The.
     */
    std::string getITOLU(void) const;

    /** Set the
     *  @param[in] itolu The
     */
    void setITOLU(const std::string& itolu);
    
    /** Get the
     *  @return The.
     */
    std::string getMASS(void) const;

    /** Set the
     *  @param[in] mass The
     */
    void setMASS(const std::string& mass);
    
    /** Get the
     *  @return The.
     */
    std::string getMODS(void) const;

    /** Set the
     *  @param[in] mods The
     */
    void setMODS(const std::string& mods);
    
    /** Get the
     *  @return The.
     */
    std::string getQUANTITATION(void) const;

    /** Set the
     *  @param[in] quantitation The
     */
    void setQUANTITATION(const std::string& quantitation);
    
    /** Get the
     *  @return The.
     */
    std::string getREPORT(void) const;

    /** Set the
     *  @param[in] report The
     */
    void setREPORT(const std::string& report);
    
    /** Get the
     *  @return The.
     */
    std::string getREPTYPE(void) const;

    /** Set the
     *  @param[in] reptype The
     */
    void setREPTYPE(const std::string& reptype);
    
    /** Get the
     *  @return The.
     */
    std::string getSEARCH(void) const;

    /** Set the
     *  @param[in] search The
     */
    void setSEARCH(const std::string& search);
    
    /** Get the
     *  @return The.
     */
    std::string getTAXONOMY(void) const;

    /** Set the
     *  @param[in] taxonomy The
     */
    void setTAXONOMY(const std::string& taxonomy);
    
    /** Get the unit in which the tolerance is specified (\a ppm or \a Da).
     *  @return A string specifying the tolerance unit.
     */
    std::string getTOLU(void) const;

    /** Set the unit in which the tolerance is specified (\a ppm or \a Da).
     *  @param[in] tolu The tolerance unit.
     */
    void setTOLU(const std::string& tolu);
    
    /** Get the user email address.
     *  @return A user email address string.
     */
    std::string getUSEREMAIL(void) const;

    /** Set the user email address.
     *  @param[in] useremail The user email address as \a abc@example.org.
     */
    void setUSEREMAIL(const std::string& useremail);
    
    /** Get the name of the user submitting the search.
     *  @return The.username.
     */
    std::string getUSERNAME(void) const;

    /** Set the name of the user submitting the search.
     *  @param[in] username The username.
     */
    void setUSERNAME(const std::string& username);
    
    /** Get the
     *  @return The.
     */
    int getPFA(void) const;

    /** Set the
     *  @param[in] pfa The
     */
    void setPFA(const int pfa);
    
    /** Get the
     *  @return The.
     */
    int getDECOY(void) const;

    /** Set the
     *  @param[in] decoy The
     */
    void setDECOY(const int decoy);
    
    /** Get the status of the error-tolerant search flag.
     *  @return The flag value (0=no error-tolerant search, 1=error-tolerant
     *          search)
     */
    int getERRORTOLERANT(void) const;

    /** Set the status of the error-tolerant search flag.
     *  @param[in] errortolerant The desired value of the error-tolerant search
     *                           flag (0=off, 1=on). 
     */
    void setERRORTOLERANT(const int errortolerant);
    
    /** Get the status of the isotope error correction flag. The flag controls
     *  whether Mascot also attempts to find peptide-spectral matches for a
     *  precursor mass -1m/z. This counters situations in which the instrument
     *  picks the second isotope as parent mass.
     *  @return The.isotope error correction flag value (0=off, 1=on)
     */
    double getPEP_ISOTOPE_ERROR(void) const;

    /** Set/unset the peptide isotope error correction flag. The flag controls
     *  whether Mascot also attempts to find peptide-spectral matches for a
     *  precursor mass -1m/z. This counters situations in which the instrument
     *  picks the second isotope as parent mass.
     *  @param[in] pep_isotope_error The desired value of the peptide isotope
     *                               error flag.
     */
    void setPEP_ISOTOPE_ERROR(const double pep_isotope_error);
    
    /** Get the
     *  @return The.
     */
    double getITOL(void) const;

    /** Set the
     *  @param[in] itol The
     */
    void setITOL(const double itol);
    
    /** Get the scan precursor mass (in m/z).
     *  @return The.mass of the precursor.
     */
    double getPRECURSOR(void) const;

    /** Set the precursor mass (in m/z)
     *  @param[in] precursor The mass value of the precursor (in m/z).
     */
    void setPRECURSOR(const double precursor);
    
    /** Get the
     *  @return The.
     */
    double getSEG(void) const;

    /** Set the
     *  @param[in] seg The
     */
    void setSEG(const double seg);
    
    /** Get the search tolerance. The return value has a unit that is specified
     *  by \a getTOLU.
     *  @return The.search tolerance.
     */
    double getTOL(void) const;

    /** Set the
     *  @param[in] tol The
     */
    void setTOL(const double tol);
    
    /** Get the precursor charges for which a search is requested.
     *  @param[out] charges The charge vector.
     */
    void getCHARGE(std::vector<int>& charges) const;

    /** Set the precursor charges for which a search is requested.
     *  @param[in] charges The charge vector.
     */
    void setCHARGE(const std::vector<int>& charges);
    
    /** Get the
     *  @return The.
     */
    void getFRAMES(std::vector<int>& frames) const;

    /** Set the
     *  @param[in] frames The
     */
    void setFRAMES(const std::vector<int>& frames);

    /** Clear all information from the current MgfHeader object.
     */
    void clear();

  private:
    /** Keep the header elements accessible for the stream operator. This allows
     * us to iterate over the elemtents instead of calling the \c get function
     * for each entry and checking the return value.
     */
    friend std::ostream& operator<<(std::ostream& os, const MgfHeader& mgf);

    /** Container for all string elements.
     */
    std::map<std::string, std::string> strings;
    
    /** Container for all integer elements.
     */
    std::map<std::string, int> ints;
    
    /** Container for all double elements.
     */
    std::map<std::string, double> doubles;

    /** Charge vector.
     */
    std::vector<int> charges_;
    
    /** Frame vector.
     */
    std::vector<int> frames_;
};

/** An stream operator to output the header information in MGF.
 */
std::ostream& operator<<(std::ostream& os, const MgfHeader& mgf);

} //namespace mgf

#endif

