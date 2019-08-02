/**
 * \file ITileCache.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILECACHE_H_
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILECACHE_H_


#include <list>
#include <memory>

#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileLoader.h"

using std::list;
using std::shared_ptr;


class ITileCache : public ITileLoader {
 public:  // Constructors & destructors.
    virtual ~ITileCache() {}

 public:  // Methods.
    virtual void update(const list<shared_ptr<ITile>>& tiles) = 0;
    virtual double getLastUpdated() const = 0;
    virtual bool isCacheEmpty() const = 0;
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILECACHE_H_
