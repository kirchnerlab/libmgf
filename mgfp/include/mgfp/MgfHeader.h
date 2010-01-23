#ifndef __MGFHEADER_H__
#define __MGFHEADER_H__

#include <mgfp/config.h>

#include <map>
#include <ostream>
#include <string>
#include <vector>

#include <mgfp/utils.h> // for existsOrEmpty()

namespace mgf {

class MgfHeader
{
  public:
    std::string getCLE(void) const;
    void setCLE(const std::string& cle);
    std::string getCOM(void) const;
    void setCOM(const std::string& com);
    std::string getDB(void) const;
    void setDB(const std::string& db);
    std::string getFORMAT(void) const;
    void setFORMAT(const std::string& format);
    std::string getINSTRUMENT(void) const;
    void setINSTRUMENT(const std::string& instrument);
    std::string getIT_MODS(void) const;
    void setIT_MODS(const std::string& it_mods);
    std::string getITOLU(void) const;
    void setITOLU(const std::string& itolu);
    std::string getMASS(void) const;
    void setMASS(const std::string& mass);
    std::string getMODS(void) const;
    void setMODS(const std::string& mods);
    std::string getQUANTITATION(void) const;
    void setQUANTITATION(const std::string& quantitation);
    std::string getREPORT(void) const;
    void setREPORT(const std::string& report);
    std::string getREPTYPE(void) const;
    void setREPTYPE(const std::string& reptype);
    std::string getSEARCH(void) const;
    void setSEARCH(const std::string& search);
    std::string getTAXONOMY(void) const;
    void setTAXONOMY(const std::string& taxonomy);
    std::string getTOLU(void) const;
    void setTOLU(const std::string& tolu);
    std::string getUSEREMAIL(void) const;
    void setUSEREMAIL(const std::string& useremail);
    std::string getUSERNAME(void) const;
    void setUSERNAME(const std::string& username);
    int getPFA(void) const;
    void setPFA(const int pfa);
    int getDECOY(void) const;
    void setDECOY(const int decoy);
    int getERRORTOLERANT(void) const;
    void setERRORTOLERANT(const int errortolerant);
    double getPEP_ISOTOPE_ERROR(void) const;
    void setPEP_ISOTOPE_ERROR(const double pep_isotope_error);
    double getITOL(void) const;
    void setITOL(const double itol);
    double getPRECURSOR(void) const;
    void setPRECURSOR(const double precursor);
    double getSEG(void) const;
    void setSEG(const double seg);
    double getTOL(void) const;
    void setTOL(const double tol);
    void getCHARGE(std::vector<int>& charges) const;
    void setCHARGE(const std::vector<int>& charges);
    void getFRAMES(std::vector<int>& frames) const;
    void setFRAMES(const std::vector<int>& frames);
    void clear();

  private:
    friend std::ostream& operator<<(std::ostream& os, const MgfHeader& mgf);
    std::map<std::string, std::string> strings;
    std::map<std::string, int> ints;
    std::map<std::string, double> doubles;
    std::vector<int> charges_, frames_;
};

std::ostream& operator<<(std::ostream& os, const MgfHeader& mgf);

} //namespace mgf

#endif

