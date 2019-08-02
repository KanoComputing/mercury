/**
 * \file TestTileManager.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_KES_DASHBOARD_LIVE_TILES_CLIENT_LIVETESTTILEMANAGER_H_
#define TEST_KES_DASHBOARD_LIVE_TILES_CLIENT_LIVETESTTILEMANAGER_H_


#include <gtest/gtest.h>

#include <stdlib.h>

#include <list>
#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/TileManager.h"

#include "mercury/config.h"

using std::list;
using std::shared_ptr;
using std::string;


/**
 * This test actually runs live. It will perform an http request to the live
 * KES and write to the filesystem tiles. For debugging purposes only.
 */
TEST(TestTileManager, DoesSomethingOrOther) {
    const string cacheDir =
        string(CMAKE_PROJ_BASE_DIR) + "/build/test/tmp/.kes-dlt-cli";

    // Wipe cache.
    const string cmd = string("rm -rf ") + cacheDir;
    system(cmd.c_str());

    list<shared_ptr<ITile>> tiles;
    TileManager tileManager(cacheDir);

    // Download from KES.
    tiles = tileManager.getTiles(false);
    EXPECT_FALSE(tiles.empty());

    // Retrieve from cache (cooldown).
    tiles = tileManager.getTiles(false);
    EXPECT_FALSE(tiles.empty());

    // Retrieve from cache.
    tiles = tileManager.getTiles(true);
    EXPECT_FALSE(tiles.empty());

    // Wipe cache.
    system(cmd.c_str());

    // Get default tiles.
    tiles = tileManager.getTiles(true);
    EXPECT_FALSE(tiles.empty());

    // TODO: EXPECT_FALSE(exists(cacheDir + "/cache.json"));
}

#endif  // TEST_KES_DASHBOARD_LIVE_TILES_CLIENT_LIVETESTTILEMANAGER_H_
