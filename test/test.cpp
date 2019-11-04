/**
 * \file test.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Main runner for all Google tests
 *
 */


#include <gtest/gtest.h>

//  --- Run all unit tests ---

#include "unit/kes_dashboard_live_tiles_client/TestDefaultTileLoader.h"
#include "unit/kes_dashboard_live_tiles_client/TestOnlineLoader.h"
#include "unit/kes_dashboard_live_tiles_client/TestTile.h"
#include "unit/kes_dashboard_live_tiles_client/TestTileCache.h"
#include "unit/kes_dashboard_live_tiles_client/TestTileManager.h"

#include "unit/kes_moma_picks_client/TestDefaultPaintingLoader.h"
#include "unit/kes_moma_picks_client/TestOnlineLoader.h"
#include "unit/kes_moma_picks_client/TestPainting.h"
#include "unit/kes_moma_picks_client/TestPaintingCache.h"
#include "unit/kes_moma_picks_client/TestPaintingManager.h"

#include "unit/kw/apiconfig.h"
#include "unit/kw/kw_apis.h"
#include "unit/kw/kw_getters.h"
#include "unit/kw/kw_server_data.h"

#include "unit/theme/theme.h"

#include "unit/utils/TestEnvironment.h"

// --- Run live integration tests ---

// #include "live/kes_dashboard_live_tiles_client/LiveTestTileManager.h"
// #include "live/kes_moma_picks_client/LiveTestPaintingManager.h"

// #include "live/kw/LiveTestKanoWorld.h"

// --- Run thread tests through the address sanitizer ---

#include "thread/TestKanoWorldRefresh.h"
#include "thread/TestKanoWorldSave.h"


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
