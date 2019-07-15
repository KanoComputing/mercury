/**
 * \file TileManager.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <list>

#include "mercury/kes_dashboard_live_tiles_cli/Tile.h"
#include "mercury/kes_dashboard_live_tiles_cli/TileManager.h"


TileManager::TileManager() {
    // Empty constructor.
}


TileManager::~TileManager() {
    // Empty destructor.
}


std::list<Tile> TileManager::getTiles(bool cache) {
    std::list<Tile> tiles;

    // if not cache and cooldown expired
    //   get with OnlineFeedLoader
    //   if successful:
    //     update LocalFeedLoader
    //     return

    // get with LocalFeedLoader

    return tiles;
}
