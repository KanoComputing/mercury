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

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/LocalLoader.h"
#include "mercury/kes_dashboard_live_tiles_cli/OnlineLoader.h"
#include "mercury/kes_dashboard_live_tiles_cli/TileManager.h"
#include "mercury/utils/Time.h"

using std::cerr;
using std::endl;
using std::exception;
using std::list;
using std::shared_ptr;
using std::string;


TileManager::TileManager() {
    this->cacheDir = string(getenv("HOME")) + "/" + this->CACHE_DIR;
}


TileManager::~TileManager() {
    // Empty destructor.
}


list<shared_ptr<ITile>> TileManager::getTiles(bool cache) const {
    OnlineLoader onlineLoader(this->cacheDir);
    LocalLoader localLoader(this->cacheDir);
    list<shared_ptr<ITile>> tiles;

    bool isCooldown =
        (localLoader.getLastUpdated() + onlineLoader.getQueryCooldown()) >
        getTimestamp();

    // Check that we're not spamming the server.
    if (!cache && !isCooldown) {
        // Download the feed of tiles from the KES.
        try {
            tiles = onlineLoader.getTiles();
        } catch (const exception& e) {
            cerr << "TileManager: Caught: " << e.what() << endl;
        } catch (...) {
            cerr << "TileManager: Caught unexpected error" << endl;
        }

        // If it was successful, update the cache.
        if (!tiles.empty()) {
            localLoader.update(tiles);
            return tiles;
        }
    }

    // If all else has failed, return the latest tiles from the cache.
    try {
        tiles = localLoader.getTiles();
    } catch (const exception& e) {
        cerr << "TileManager: Caught: " << e.what() << endl;
    } catch (...) {
        cerr << "TileManager: Caught unexpected error" << endl;
    }

    return tiles;
}
