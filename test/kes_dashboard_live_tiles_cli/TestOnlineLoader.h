/**
 * \file TestOnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTONLINELOADER_H_
#define TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTONLINELOADER_H_


#include <list>
#include <memory>

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <mercury/kes_dashboard_live_tiles_cli/ITile.h>
#include <mercury/kes_dashboard_live_tiles_cli/OnlineLoader.h>

using std::list;
using std::shared_ptr;


TEST(TestOnlineLoader, getTiles) {
    OnlineLoader onlineLoader("/tmp/kes-dlt-cli");
    list<shared_ptr<ITile>> tiles = onlineLoader.getTiles();

    EXPECT_FALSE(tiles.empty());
}

#endif  // TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTONLINELOADER_H_
