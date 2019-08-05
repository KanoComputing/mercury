/**
 * \file IDownloadable.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_IDOWNLOADABLE_H_
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_IDOWNLOADABLE_H_


#include <string>


namespace KESDLTC {
namespace internal {

class IDownloadable {
 public:  // Constructors & destructors.
    virtual ~IDownloadable() {}

 public:  // Methods.
    virtual bool download(const std::string& baseDir) = 0;
};

}  // namespace internal
}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_IDOWNLOADABLE_H_
