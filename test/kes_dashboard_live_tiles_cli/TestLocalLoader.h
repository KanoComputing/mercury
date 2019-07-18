/**
 * \file TestLocalLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTLOCALLOADER_H_
#define TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTLOCALLOADER_H_


#include <list>
#include <memory>

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <mercury/kes_dashboard_live_tiles_cli/ITile.h>
#include <mercury/kes_dashboard_live_tiles_cli/LocalLoader.h>

using std::list;
using std::shared_ptr;


TEST(TestLocalLoader, getTilesFromCache) {
    LocalLoader localLoader("/tmp/kes-dlt-cli/test");
    list<shared_ptr<ITile>> tiles = localLoader.getTiles();

    EXPECT_FALSE(tiles.empty());
}


TEST(TestLocalLoader, getTilesFromDefaults) {
}


TEST(TestLocalLoader, updateCache) {
}


TEST(TestLocalLoader, updateSetsLastUpdated) {
}


TEST(TestLocalLoader, getLastUpdatedNoCache) {
}


TEST(TestLocalLoader, getLastUpdatedFromCache) {
}


TEST(TestLocalLoader, isCacheEmpty) {
}

#endif  // TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTLOCALLOADER_H_
