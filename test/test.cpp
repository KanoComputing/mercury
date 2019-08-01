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

// #include "kes_dashboard_live_tiles_cli/LiveTestTileManager.h"
#include "kes_dashboard_live_tiles_cli/TestDefaultTileLoader.h"
#include "kes_dashboard_live_tiles_cli/TestOnlineLoader.h"
#include "kes_dashboard_live_tiles_cli/TestTile.h"
#include "kes_dashboard_live_tiles_cli/TestTileCache.h"
#include "kes_dashboard_live_tiles_cli/TestTileManager.h"

#include "kw/kw_apis.h"
#include "kw/kw_persistence.h"
#include "kw/kw_server_data.h"

#include "theme/theme.h"


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
