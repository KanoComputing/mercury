/**
 * \file TestOnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef __KES_DASHBOARD_LIVE_TILES_CLI_TEST_ONLINE_LOADER_H__
#define __KES_DASHBOARD_LIVE_TILES_CLI_TEST_ONLINE_LOADER_H__


#include <list>

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <mercury/kes_dashboard_live_tiles_cli/OnlineLoader.h>


using testing::Eq;


TEST(TestOnlineLoader, DoesSomethingOrOther) {
    OnlineLoader onlineLoader;
    std::list<Tile> tiles = onlineLoader.getTiles();

    EXPECT_FALSE(tiles.empty());
}

#endif  // __KES_DASHBOARD_LIVE_TILES_CLI_TEST_ONLINE_LOADER_H__
