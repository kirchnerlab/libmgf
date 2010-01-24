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

/** MGF file representation.
 */
class MgfFile : public Collection<MgfSpectrum>
{
  public:
    /** Default constructor.
     * Creates an empty MgfFile object.
     */
    MgfFile();
    
    /** Returns the file header information.
     * @param[out] header mgf::MgfHeader object.
     */
    void getHeader(MgfHeader& header);
    
    /** Returns a reference to the file header information.
     * @return Returns a non-const reference to the mgf::MgfHeader object.
     */
    MgfHeader& getHeaderRef();

    /** Set the MGF file header information.
     * @param[in] header mgf::MgfHeader object.
     */
    void setHeader(const MgfHeader& header);

    /** Clear all data from the current MgfFile object.
     */
    void clear();

  private:
    friend std::ostream& operator<<(std::ostream& os, const MgfFile& mgf);
    MgfHeader header_;
};

std::ostream& operator<<(std::ostream& os, const MgfFile& mgf);

}

#endif

