/**
 * \file IOnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_IONLINELOADER_H_
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_IONLINELOADER_H_


#include "kes_dashboard_live_tiles_client/internal/ITileLoader.h"


namespace KESDLTC {
namespace internal {

class IOnlineLoader : public ITileLoader {
 public:  // Constructors & destructors.
    virtual ~IOnlineLoader() {}

 public:  // Methods.
    virtual double getQueryCooldown() const = 0;
};

}  // namespace internal
}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_IONLINELOADER_H_
