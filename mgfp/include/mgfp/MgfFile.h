/* $Id$ */

#ifndef __MGFFILE_H__
#define __MGFFILE_H__

#include <mgfp/config.h>

#include <ostream>

#include <mgfp/Collection.h>
#include <mgfp/MgfHeader.h>
#include <mgfp/MgfSpectrum.h>

namespace mgf
{

class MgfFile : public Collection<MgfSpectrum>
{
  public:
    MgfFile();
    void getHeader(MgfHeader& header);
    MgfHeader& getHeaderRef();
    void setHeader(const MgfHeader& header);
    void clear();
  private:
    friend std::ostream& operator<<(std::ostream& os, const MgfFile& mgf);
    MgfHeader header_;
};

std::ostream& operator<<(std::ostream& os, const MgfFile& mgf);

}

#endif

