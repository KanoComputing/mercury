/**
 * \file TileManager.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <exception>
#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/DefaultTileLoader.h"
#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/OnlineLoader.h"
#include "kes_dashboard_live_tiles_client/TileCache.h"
#include "kes_dashboard_live_tiles_client/TileManager.h"
#include "mercury/utils/Time.h"

using std::cerr;
using std::endl;
using std::exception;
using std::list;
using std::make_shared;
using std::shared_ptr;
using std::string;

using KESDLTC::internal::DefaultTileLoader;
using KESDLTC::internal::IOnlineLoader;
using KESDLTC::internal::ITileCache;
using KESDLTC::internal::ITileLoader;
using KESDLTC::internal::OnlineLoader;
using KESDLTC::internal::TileCache;
using KESDLTC::ITile;
using KESDLTC::TileManager;


TileManager::TileManager(
    const string& cacheDir,
    const shared_ptr<IOnlineLoader> onlineLoader,
    const shared_ptr<ITileCache> tileCache,
    const shared_ptr<ITileLoader> defaultTileLoader):
    cacheDir(cacheDir),
    onlineLoader(onlineLoader),
    tileCache(tileCache),
    defaultTileLoader(defaultTileLoader) {
    // NOLINT
    if (this->cacheDir == "")
        this->cacheDir = string(getenv("HOME")) + "/" + this->CACHE_DIRNAME;
    if (this->onlineLoader == nullptr)
        this->onlineLoader = make_shared<OnlineLoader>(this->cacheDir);
    if (this->tileCache == nullptr)
        this->tileCache = make_shared<TileCache>(this->cacheDir);
    if (this->defaultTileLoader == nullptr)
        this->defaultTileLoader = make_shared<DefaultTileLoader>();
}


TileManager::~TileManager() {
    // Empty destructor.
}


list<shared_ptr<ITile>> TileManager::getTiles(bool cache) const {
    list<shared_ptr<ITile>> tiles;

    // Check that we're not spamming the server.
    if (!cache && !this->isCooldown()) {
        // Download the feed of tiles from the KES.
        try {
            tiles = this->onlineLoader->getTiles();
        } catch (const exception& e) {
            cerr << "TileManager: Caught: " << e.what() << endl;
        } catch (...) {
            cerr << "TileManager: Caught unexpected error" << endl;
        }

        // If it was successful, update the cache.
        if (!tiles.empty()) {
            this->tileCache->update(tiles);
            return tiles;
        }
    }

    // If tiles were not retrieved from the KES directly, grab the cached ones.
    try {
        tiles = this->tileCache->getTiles();
    } catch (const exception& e) {
        cerr << "TileManager: Caught: " << e.what() << endl;
    } catch (...) {
        cerr << "TileManager: Caught unexpected error" << endl;
    }

    // If everything else failed, return some defaults.
    if (tiles.empty()) {
        tiles = this->defaultTileLoader->getTiles();
    }

    return tiles;
}


bool TileManager::isCooldown() const {
    return (this->tileCache->getLastUpdated() +
            this->onlineLoader->getQueryCooldown())
           > getTimestamp();
}
