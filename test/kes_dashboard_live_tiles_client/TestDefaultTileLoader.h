/**
 * \file TestDefaultTileLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_KES_DASHBOARD_LIVE_TILES_CLIENT_TESTDEFAULTTILELOADER_H_
#define TEST_KES_DASHBOARD_LIVE_TILES_CLIENT_TESTDEFAULTTILELOADER_H_


#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "kes_dashboard_live_tiles_client/internal/DefaultTileLoader.h"

#include "test/mocks/kes_dlt_cli/MockTile.h"
#include "test/mocks/kes_dlt_cli/MockTileFactory.h"


namespace KESDLTC {
namespace test {

/**
 * Check that DefaultTileLoader.getTiles() calls TileFactory.create() for each
 * of the default tiles it returns.
 */
TEST(TestDefaultTileLoader, GetTilesCallsTileFactoryCreate) {
    auto mockTileFactory = std::make_shared<MockTileFactory>();
    auto mockTile = std::make_shared<MockTile>();

    KESDLTC::internal::DefaultTileLoader defaultTileLoader(mockTileFactory);

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(::testing::Return(mockTile));

    EXPECT_CALL(*mockTileFactory, create_impl)
        .Times(4);

    defaultTileLoader.getTiles();
}

}  // namespace test
}  // namespace KESDLTC

#endif  // TEST_KES_DASHBOARD_LIVE_TILES_CLIENT_TESTDEFAULTTILELOADER_H_
