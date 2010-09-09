#include <mgfp/MgfSpectrum.h>

#include <cstdlib> // for std::abs(int)
#include <sstream>

namespace mgf {

MgfSpectrum::MgfSpectrum() : Collection<MassAbundancePair>() {
    this->clear();
}

std::vector<int> MgfSpectrum::getCHARGE(void) const {
    return charges_;
}
void MgfSpectrum::setCHARGE(const std::vector<int>& charges) {
    charges_ = charges;
}

std::string MgfSpectrum::getCOMP(void) const {
    return comp_;
}
void MgfSpectrum::setCOMP(const std::string& comp) {
    comp_ = comp;
}

std::string MgfSpectrum::getETAG(void) const {
    return etag_;
}
void MgfSpectrum::setETAG(const std::string& etag) {
    etag_ = etag_;
}

std::string MgfSpectrum::getINSTRUMENT(void) const {
    return instrument_;
}
void MgfSpectrum::setINSTRUMENT(const std::string& instrument) {
    instrument_ = instrument;
}

void MgfSpectrum::getIONS(std::vector<MassAbundancePair>& ions) const {
    ions = c_;
}
void MgfSpectrum::setIONS(const std::vector<MassAbundancePair>& ions) {
    c_ = ions;
}

std::string MgfSpectrum::getIT_MODS(void) const {
    return it_mods_;
}
void MgfSpectrum::setIT_MODS(const std::string& it_mods) {
    it_mods_ = it_mods;
}

std::pair<double, double> MgfSpectrum::getPEPMASS(void) const {
    return pepmass_;
}
void MgfSpectrum::setPEPMASS(const std::pair<double, double> pepmass) {
    pepmass_ = pepmass;
}

double MgfSpectrum::getRTINSECONDS(void) const {
    return rtinseconds_;
}
void MgfSpectrum::setRTINSECONDS(const double rtinseconds) {
    rtinseconds_ = rtinseconds;
}

std::string MgfSpectrum::getSCANS(void) const {
    return scans_;    // FIXME
}
void MgfSpectrum::setSCANS(const std::string& scans) {
    scans_ = scans;    //FIXME
}

void MgfSpectrum::setSCANS(const int scans) {
    std::ostringstream oss;
    oss << scans;
    scans_ = oss.str();    //FIXME
}

std::string MgfSpectrum::getSEQ(void) const {
    return seq_ ;
}
void MgfSpectrum::setSEQ(const std::string& seq) {
    seq_ = seq;
}

std::string MgfSpectrum::getTAG(void) const {
    return tag_;
}
void MgfSpectrum::setTAG(const std::string& tag) {
    tag_ = tag;
}

std::string MgfSpectrum::getTITLE(void) const {
    return title_;
}
void MgfSpectrum::setTITLE(const std::string& title) {
    title_ = title;
}

double MgfSpectrum::getTOL(void) const {
    return tol_;
}
void MgfSpectrum::setTOL(const double tol) {
    tol_ = tol;
}

std::string MgfSpectrum::getTOLU(void) const {
    return tolu_;
}
void MgfSpectrum::setTOLU(const std::string& tolu) {
    tolu_ = tolu;
}

void MgfSpectrum::clear() {
    charges_.clear();
    comp_ = etag_ = instrument_ = it_mods_ = scans_ = "";
    seq_ = tag_ = title_ = tolu_ = "";
    pepmass_ = std::make_pair(0.0, 0.0);
    rtinseconds_ = 0;
    tol_ = 0.0;
    Collection<MassAbundancePair>::clear();
}

std::ostream& operator<<(std::ostream& os, const MgfSpectrum& mgf) {
    // start with title, then A-Z
    os << "BEGIN IONS" << std::endl;
    if (!mgf.title_.empty())
        os << "TITLE=" << mgf.title_ << std::endl;
    if (!mgf.charges_.empty()) {
        os << "CHARGE=";
        typedef std::vector<int>::const_iterator VICI;
        for (VICI i = mgf.charges_.begin(); i != mgf.charges_.end(); ++i) {
            if (i != mgf.charges_.begin()) {
                os << ',';
            }
            os << std::abs(*i);
            if (*i > 0) {
                os << '+';
            } else {
                os << '-';
            }
        }
        os << std::endl;
    }
    if (!mgf.comp_.empty())
        os << "COMP=" << mgf.comp_ << std::endl;
    if (!mgf.etag_.empty())
        os << "ETAG=" << mgf.etag_ << std::endl;
    if (!mgf.instrument_.empty())
        os << "INSTRUMENT=" << mgf.instrument_ << std::endl;
    if (!mgf.it_mods_.empty())
        os << "IT_MODS=" << mgf.it_mods_ << std::endl;
    if (mgf.pepmass_.first > 0.0) {
        os << "PEPMASS=" << mgf.pepmass_.first;
        if (mgf.pepmass_.second > 0.0) {
            os << " " << mgf.pepmass_.second;
        }
        os << std::endl;
    }
    if (mgf.rtinseconds_ > 0)
        os << "RTINSECONDS=" << mgf.rtinseconds_ << std::endl;
    if (!mgf.scans_.empty())
        os << "SCANS=" << mgf.scans_ << std::endl;
    if (!mgf.seq_.empty())
        os << "SEQ=" << mgf.seq_ << std::endl;
    if (!mgf.tag_.empty())
        os << "TAG=" << mgf.tag_ << std::endl;
    if (mgf.tol_ > 0.0)
        os << "TOL=" << mgf.tol_ << std::endl;
    if (!mgf.tolu_.empty())
        os << "TOLU=" << mgf.tolu_ << std::endl;
    for (MgfSpectrum::const_iterator i = mgf.begin(); i != mgf.end(); ++i) {
        os << i->first << " " << i->second << std::endl;
    }
    os << "END IONS" << std::endl;
    return os;
}

} // namespace mgf

