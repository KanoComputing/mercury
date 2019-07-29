/**
 * \file TestTileManager.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTTILEMANAGER_H_
#define TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTTILEMANAGER_H_


#include <gtest/gtest.h>

#include <list>
#include <memory>

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/TileManager.h"

using std::list;
using std::shared_ptr;


/**
 * TODO
 */
TEST(TestTileManager, DoesSomethingOrOther) {
    TileManager tileManager;
    list<shared_ptr<ITile>> tiles = tileManager.getTiles(false);

    EXPECT_FALSE(tiles.empty());
}

#endif  // TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTTILEMANAGER_H_
