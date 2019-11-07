/**
 * \file live_tests.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Main runner for all Google live integration tests
 */


#include <gtest/gtest.h>

#include "live/kes_dashboard_live_tiles_client/LiveTestTileManager.h"
#include "live/kes_moma_picks_client/LiveTestPaintingManager.h"

#include "live/kw/LiveTestKanoWorld.h"


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
