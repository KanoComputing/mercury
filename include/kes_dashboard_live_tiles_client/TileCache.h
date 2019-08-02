/**
 * \file TileCache.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_TILECACHE_H_
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_TILECACHE_H_


#include <list>
#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileCache.h"
#include "kes_dashboard_live_tiles_client/ITileFactory.h"
#include "kes_dashboard_live_tiles_client/TileFactory.h"

using std::list;
using std::make_shared;
using std::shared_ptr;
using std::string;


class TileCache : public ITileCache {
 public:  // Constructors & destructors.
    explicit TileCache(
        const string& cacheDir,
        const shared_ptr<ITileFactory> tileFactory = make_shared<TileFactory>());  // NOLINT
    ~TileCache();

 public:  // ITileLoader Methods.
    list<shared_ptr<ITile>> getTiles() override;

 public:  // ITileCache Methods.
    void update(const list<shared_ptr<ITile>>& tiles) override;
    double getLastUpdated() const override;
    bool isCacheEmpty() const override;

 private:  // Helper methods.
    void load();
    void setCacheData();

 private:  // Members.
    string cacheDir;
    string cachePath;
    shared_ptr<JSON_Value> cacheDataRoot;
    JSON_Object* cacheData;

 private:  // Constants.
    const shared_ptr<ITileFactory> tileFactory;
    const string CACHE_FILE = "cache.json";
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_TILECACHE_H_
