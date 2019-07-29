/**
 * \file TestTileCache.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTTILECACHE_H_
#define TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTTILECACHE_H_


#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "mercury/kes_dashboard_live_tiles_cli/Exceptions.h"
#include "mercury/kes_dashboard_live_tiles_cli/TileCache.h"

#include "test/fixtures/kes_dlt_cli/TileCacheFixture.h"
#include "test/matchers/JsonMatchers.h"

using std::make_shared;

/**
 * Check that for a given cache data TileCache.getTiles() calls
 * for each tile data TileFactory.create() to create a new Tile.
 */
TEST_F(TileCacheFixture, GetTilesCallsTileFactoryCreate) {
    auto mockTileFactory = make_shared<MockTileFactory>();
    auto mockTile = make_shared<MockTile>();

    this->clearCache();
    this->initialiseCache(this->rawResponses["feed1"]);

    TileCache tileCache(this->cacheDir, mockTileFactory);

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(Return(true));

    EXPECT_CALL(*mockTileFactory, create)
        .Times(this->tileCounts["feed1"]);

    tileCache.getTiles();
}

/**
 * Check that for a given cache data TileCache.getTiles() calls
 * for each tile data Tile.initialise() with the expected JSON.
 */
TEST_F(TileCacheFixture, GetTilesCallsTileInitialise) {
    auto mockTileFactory = make_shared<MockTileFactory>();
    auto mockTile = make_shared<MockTile>();

    this->clearCache();
    this->initialiseCache(this->rawResponses["feed1"]);

    TileCache tileCache(this->cacheDir, mockTileFactory);

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(Return(true));

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
TEST_F(TileCacheFixture,
       GetTilesThrowsCorruptedCacheExceptionWhenWhenMissingTilesField) {
    // NOLINT
    this->clearCache();
    this->initialiseCache(this->rawResponses["invalid_feed1"]);

    TileCache tileCache(this->cacheDir);

    ASSERT_THROW(tileCache.getTiles(), CorruptedCacheException);
}

/**
 * Check that for a given cache data TileCache.getTiles()
 * throws a CorruptedCacheException when Tile.initialise() fails.
 */
TEST_F(TileCacheFixture,
       GetTilesThrowsCorruptedCacheExceptionWhenTileInitialiseFails) {
    // NOLINT
    auto mockTileFactory = make_shared<MockTileFactory>();
    auto mockTile = make_shared<MockTile>();

    this->clearCache();
    this->initialiseCache(this->rawResponses["feed1"]);

    TileCache tileCache(this->cacheDir, mockTileFactory);

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(Return(mockTile));

    // Set the mock Tile.initialise() to return false for failure.
    ON_CALL(*mockTile, initialise)
        .WillByDefault(Return(false));

    ASSERT_THROW(tileCache.getTiles(), CorruptedCacheException);
}

/**
 * Check that when cache is missing altogether TileCache.isCacheEmpty()
 * returns true.
 */
TEST_F(TileCacheFixture, IsCacheEmptyWithEmptyCache) {
    // NOLINT
    this->clearCache();

    TileCache tileCache(this->cacheDir);

    EXPECT_TRUE(tileCache.isCacheEmpty());
}

/**
 * Check that when cache contains a malformed JSON TileCache.isCacheEmpty()
 * returns true to signal the cache not being usable.
 */
TEST_F(TileCacheFixture, IsCacheEmptyWithMalformedCache) {
    // NOLINT
    this->clearCache();
    this->initialiseCache(this->rawResponses["malformed_feed1"]);

    TileCache tileCache(this->cacheDir);

    EXPECT_TRUE(tileCache.isCacheEmpty());
}

/**
 * Check that for a given cache data TileCache.isCacheEmpty() returns
 * false to signal the cache is usable.
 */
TEST_F(TileCacheFixture, IsCacheEmptyWithFullCache) {
    // NOLINT
    this->clearCache();
    this->initialiseCache(this->rawResponses["feed1"]);

    TileCache tileCache(this->cacheDir);

    EXPECT_FALSE(tileCache.isCacheEmpty());
}

// TODO: Parameterised TileCache fixtures & parameterise tests above.
// TODO: Test TileCache.update()
// TODO: Test TileCache.getLastUpdated()

#endif  // TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTTILECACHE_H_
