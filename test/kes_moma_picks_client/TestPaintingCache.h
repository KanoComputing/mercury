/**
 * \file TestPaintingCache.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_KES_MOMA_PICKS_CLIENT_TESTPAINTINGCACHE_H_
#define TEST_KES_MOMA_PICKS_CLIENT_TESTPAINTINGCACHE_H_


#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "kes_moma_picks_client/internal/Exceptions.h"
#include "kes_moma_picks_client/internal/PaintingCache.h"

#include "test/fixtures/kes_mp_cli/PaintingCacheFixture.h"
#include "test/matchers/JsonMatchers.h"
#include "test/mocks/kes_mp_cli/MockPainting.h"
#include "test/mocks/kes_mp_cli/MockPaintingFactory.h"


namespace KESMPC {
namespace test {

/**
 * Check that for a given cache data PaintingCache.getPaintings() calls
 * for each painting data PaintingFactory.create() to create a new Painting.
 */
TEST_F(PaintingCacheFixture, GetPaintingsCallsPaintingFactoryCreate) {
    auto mockPaintingFactory = std::make_shared<MockPaintingFactory>();
    auto mockPainting = std::make_shared<MockPainting>();

    this->clearCache();
    this->initialiseCache(this->rawResponses["feed1"]);

    KESMPC::internal::PaintingCache
        paintingCache(this->cacheDir, mockPaintingFactory);

    // Return the same mock Painting each for each painting data
    // from the response.
    ON_CALL(*mockPaintingFactory, create)
        .WillByDefault(::testing::Return(mockPainting));

    // Ignore the call to Painting.initialise().
    ON_CALL(*mockPainting, initialise)
        .WillByDefault(::testing::Return(true));

    EXPECT_CALL(*mockPaintingFactory, create)
        .Times(this->paintingCounts["feed1"]);

    paintingCache.getPaintings();
}

/**
 * Check that for a given cache data PaintingCache.getPaintings() calls
 * for each painting data Painting.initialise() with the expected JSON.
 */
TEST_F(PaintingCacheFixture, GetPaintingsCallsPaintingInitialise) {
    auto mockPaintingFactory = std::make_shared<MockPaintingFactory>();
    auto mockPainting = std::make_shared<MockPainting>();

    this->clearCache();
    this->initialiseCache(this->rawResponses["feed1"]);

    KESMPC::internal::PaintingCache
        paintingCache(this->cacheDir, mockPaintingFactory);

    // Return the same mock Painting each for each painting data
    // from the response.
    ON_CALL(*mockPaintingFactory, create)
        .WillByDefault(::testing::Return(mockPainting));

    // Ignore the call to Painting.initialise().
    ON_CALL(*mockPainting, initialise)
        .WillByDefault(::testing::Return(true));

    JSON_Array* paintingsData = json_object_get_array(
        json_value_get_object(this->responses["feed1"].get()), "paintings");

    JSON_Value* paintingData;

    // Expect that Painting.initialise() is called with each individual
    // paintingData from the cache.
    for (int i = 0; i < json_array_get_count(paintingsData); i++) {
        paintingData = json_array_get_value(paintingsData, i);

        EXPECT_CALL(*mockPainting, initialise(JsonEq(paintingData)))
            .Times(1);
    }

    paintingCache.getPaintings();
}

/**
 * Check that for a given cache data PaintingCache.getPaintings() throws a
 * CorruptedCacheException when cache data does not contain "paintings" array.
 */
TEST_F(
    PaintingCacheFixture,
    GetPaintingsThrowsCorruptedCacheExceptionWhenWhenMissingPaintingsField) {
    // NOLINT
    this->clearCache();
    this->initialiseCache(this->rawResponses["invalid_feed1"]);

    KESMPC::internal::PaintingCache paintingCache(this->cacheDir);

    ASSERT_THROW(
        paintingCache.getPaintings(),
        KESMPC::internal::CorruptedCacheException);
}

/**
 * Check that for a given cache data PaintingCache.getPaintings()
 * throws a CorruptedCacheException when Painting.initialise() fails.
 */
TEST_F(
    PaintingCacheFixture,
    GetPaintingsThrowsCorruptedCacheExceptionWhenPaintingInitialiseFails) {
    // NOLINT
    auto mockPaintingFactory = std::make_shared<MockPaintingFactory>();
    auto mockPainting = std::make_shared<MockPainting>();

    this->clearCache();
    this->initialiseCache(this->rawResponses["feed1"]);

    KESMPC::internal::PaintingCache
        paintingCache(this->cacheDir, mockPaintingFactory);

    // Return the same mock Painting each for each painting data
    // from the response.
    ON_CALL(*mockPaintingFactory, create)
        .WillByDefault(::testing::Return(mockPainting));

    // Set the mock Painting.initialise() to return false for failure.
    ON_CALL(*mockPainting, initialise)
        .WillByDefault(::testing::Return(false));

    ASSERT_THROW(
        paintingCache.getPaintings(),
        KESMPC::internal::CorruptedCacheException);
}

/**
 * Check that when cache is missing altogether PaintingCache.isCacheEmpty()
 * returns true.
 */
TEST_F(PaintingCacheFixture, IsCacheEmptyWithEmptyCache) {
    this->clearCache();

    KESMPC::internal::PaintingCache paintingCache(this->cacheDir);

    EXPECT_TRUE(paintingCache.isCacheEmpty());
}

/**
 * Check that when cache contains a malformed JSON PaintingCache.isCacheEmpty()
 * returns true to signal the cache not being usable.
 */
TEST_F(PaintingCacheFixture, IsCacheEmptyWithMalformedCache) {
    this->clearCache();
    this->initialiseCache(this->rawResponses["malformed_feed1"]);

    KESMPC::internal::PaintingCache paintingCache(this->cacheDir);

    EXPECT_TRUE(paintingCache.isCacheEmpty());
}

/**
 * Check that for a given cache data PaintingCache.isCacheEmpty() returns
 * false to signal the cache is usable.
 */
TEST_F(PaintingCacheFixture, IsCacheEmptyWithFullCache) {
    this->clearCache();
    this->initialiseCache(this->rawResponses["feed1"]);

    KESMPC::internal::PaintingCache paintingCache(this->cacheDir);

    EXPECT_FALSE(paintingCache.isCacheEmpty());
}

// TODO: Parameterised PaintingCache fixtures & parameterise tests above.
// TODO: Test PaintingCache.update()
// TODO: Test PaintingCache.getLastUpdated()

}  // namespace test
}  // namespace KESMPC

#endif  // TEST_KES_MOMA_PICKS_CLIENT_TESTPAINTINGCACHE_H_
