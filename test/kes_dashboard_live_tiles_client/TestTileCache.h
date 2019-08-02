/**
 * \file TestTileCache.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_KES_DASHBOARD_LIVE_TILES_CLIENT_TESTTILECACHE_H_
#define TEST_KES_DASHBOARD_LIVE_TILES_CLIENT_TESTTILECACHE_H_


#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "kes_dashboard_live_tiles_client/Exceptions.h"
#include "kes_dashboard_live_tiles_client/TileCache.h"

#include "test/fixtures/kes_dlt_cli/TileCacheFixture.h"
#include "test/matchers/JsonMatchers.h"
#include "test/mocks/kes_dlt_cli/MockTile.h"
#include "test/mocks/kes_dlt_cli/MockTileFactory.h"


namespace KESDLTC {
namespace test {

/**
 * Check that for a given cache data TileCache.getTiles() calls
 * for each tile data TileFactory.create() to create a new Tile.
 */
TEST_F(TileCacheFixture, GetTilesCallsTileFactoryCreate) {
    auto mockTileFactory = std::make_shared<MockTileFactory>();
    auto mockTile = std::make_shared<MockTile>();

    this->clearCache();
    this->initialiseCache(this->rawResponses["feed1"]);

    KESDLTC::internal::TileCache tileCache(this->cacheDir, mockTileFactory);

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(::testing::Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(::testing::Return(true));

    EXPECT_CALL(*mockTileFactory, create)
        .Times(this->tileCounts["feed1"]);

    tileCache.getTiles();
}

/**
 * Check that for a given cache data TileCache.getTiles() calls
 * for each tile data Tile.initialise() with the expected JSON.
 */
TEST_F(TileCacheFixture, GetTilesCallsTileInitialise) {
    auto mockTileFactory = std::make_shared<MockTileFactory>();
    auto mockTile = std::make_shared<MockTile>();

    this->clearCache();
    this->initialiseCache(this->rawResponses["feed1"]);

    KESDLTC::internal::TileCache tileCache(this->cacheDir, mockTileFactory);

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(::testing::Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(::testing::Return(true));

    JSON_Array* tilesData = json_object_get_array(
        json_value_get_object(this->responses["feed1"].get()), "tiles");

    JSON_Value* tileData;

    // Expect that Tile.initialise() is called with each individual
    // tileData from the cache.
    for (int i = 0; i < json_array_get_count(tilesData); i++) {
        tileData = json_array_get_value(tilesData, i);

        EXPECT_CALL(*mockTile, initialise(JsonEq(tileData)))
            .Times(1);
    }

    tileCache.getTiles();
}

/**
 * Check that for a given cache data TileCache.getTiles() throws a
 * CorruptedCacheException when cache data does not contain "tiles" array.
 */
TEST_F(
    TileCacheFixture,
    GetTilesThrowsCorruptedCacheExceptionWhenWhenMissingTilesField) {
    // NOLINT
    this->clearCache();
    this->initialiseCache(this->rawResponses["invalid_feed1"]);

    KESDLTC::internal::TileCache tileCache(this->cacheDir);

    ASSERT_THROW(
        tileCache.getTiles(),
        KESDLTC::internal::CorruptedCacheException);
}

/**
 * Check that for a given cache data TileCache.getTiles()
 * throws a CorruptedCacheException when Tile.initialise() fails.
 */
TEST_F(
    TileCacheFixture,
    GetTilesThrowsCorruptedCacheExceptionWhenTileInitialiseFails) {
    // NOLINT
    auto mockTileFactory = std::make_shared<MockTileFactory>();
    auto mockTile = std::make_shared<MockTile>();

    this->clearCache();
    this->initialiseCache(this->rawResponses["feed1"]);

    KESDLTC::internal::TileCache tileCache(this->cacheDir, mockTileFactory);

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(::testing::Return(mockTile));

    // Set the mock Tile.initialise() to return false for failure.
    ON_CALL(*mockTile, initialise)
        .WillByDefault(::testing::Return(false));

    ASSERT_THROW(
        tileCache.getTiles(),
        KESDLTC::internal::CorruptedCacheException);
}

/**
 * Check that when cache is missing altogether TileCache.isCacheEmpty()
 * returns true.
 */
TEST_F(TileCacheFixture, IsCacheEmptyWithEmptyCache) {
    this->clearCache();

    KESDLTC::internal::TileCache tileCache(this->cacheDir);

    EXPECT_TRUE(tileCache.isCacheEmpty());
}

/**
 * Check that when cache contains a malformed JSON TileCache.isCacheEmpty()
 * returns true to signal the cache not being usable.
 */
TEST_F(TileCacheFixture, IsCacheEmptyWithMalformedCache) {
    this->clearCache();
    this->initialiseCache(this->rawResponses["malformed_feed1"]);

    KESDLTC::internal::TileCache tileCache(this->cacheDir);

    EXPECT_TRUE(tileCache.isCacheEmpty());
}

/**
 * Check that for a given cache data TileCache.isCacheEmpty() returns
 * false to signal the cache is usable.
 */
TEST_F(TileCacheFixture, IsCacheEmptyWithFullCache) {
    this->clearCache();
    this->initialiseCache(this->rawResponses["feed1"]);

    KESDLTC::internal::TileCache tileCache(this->cacheDir);

    EXPECT_FALSE(tileCache.isCacheEmpty());
}

// TODO: Parameterised TileCache fixtures & parameterise tests above.
// TODO: Test TileCache.update()
// TODO: Test TileCache.getLastUpdated()

}  // namespace test
}  // namespace KESDLTC

#endif  // TEST_KES_DASHBOARD_LIVE_TILES_CLIENT_TESTTILECACHE_H_
