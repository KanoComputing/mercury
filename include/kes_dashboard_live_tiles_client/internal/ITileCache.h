/**
 * \file ITileCache.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_ITILECACHE_H_
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_ITILECACHE_H_


#include <list>
#include <memory>

#include "kes_dashboard_live_tiles_client/internal/ITileLoader.h"
#include "kes_dashboard_live_tiles_client/ITile.h"


namespace KESDLTC {
namespace internal {

class ITileCache : public ITileLoader {
 public:  // Constructors & destructors.
    virtual ~ITileCache() {}

 public:  // Methods.
    virtual void update(const std::list<std::shared_ptr<ITile>>& tiles) = 0;
    virtual double getLastUpdated() const = 0;
    virtual bool isCacheEmpty() const = 0;
};

}  // namespace internal
}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_ITILECACHE_H_
