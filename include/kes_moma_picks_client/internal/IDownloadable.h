/**
 * \file IDownloadable.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_IDOWNLOADABLE_H_
#define INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_IDOWNLOADABLE_H_


#include <string>


namespace KESMPC {
namespace internal {

class IDownloadable {
 public:  // Constructors & destructors.
    virtual ~IDownloadable() {}

 public:  // Methods.
    virtual bool download(const std::string& baseDir) = 0;
};

}  // namespace internal
}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_IDOWNLOADABLE_H_
