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

#include "kes_dashboard_live_tiles_client/TestDefaultTileLoader.h"
#include "kes_dashboard_live_tiles_client/TestOnlineLoader.h"
#include "kes_dashboard_live_tiles_client/TestTile.h"
#include "kes_dashboard_live_tiles_client/TestTileCache.h"
#include "kes_dashboard_live_tiles_client/TestTileManager.h"

#include "kes_moma_picks_client/TestDefaultPaintingLoader.h"
#include "kes_moma_picks_client/TestOnlineLoader.h"
#include "kes_moma_picks_client/TestPainting.h"
#include "kes_moma_picks_client/TestPaintingCache.h"
#include "kes_moma_picks_client/TestPaintingManager.h"

#include "kw/apiconfig.h"
#include "kw/kw_apis.h"
#include "kw/kw_getters.h"
#include "kw/kw_server_data.h"

#include "theme/theme.h"

#include "unit/utils/TestEnvironment.h"

// --- Run integration tests ---

// #include "live/kes_dashboard_live_tiles_client/LiveTestTileManager.h"
// #include "live/kes_moma_picks_client/LiveTestPaintingManager.h"

// --- Run thread tests through the address sanitizer ---

#include "thread/TestKanoWorldRefresh.h"
#include "thread/TestKanoWorldSave.h"


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
