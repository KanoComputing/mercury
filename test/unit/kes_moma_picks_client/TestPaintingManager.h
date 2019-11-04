/**
 * \file TestPaintingManager.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_UNIT_KES_MOMA_PICKS_CLIENT_TESTPAINTINGMANAGER_H_
#define TEST_UNIT_KES_MOMA_PICKS_CLIENT_TESTPAINTINGMANAGER_H_


#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <list>
#include <memory>

#include "kes_moma_picks_client/IPainting.h"
#include "kes_moma_picks_client/IPaintingManager.h"
#include "kes_moma_picks_client/PaintingManager.h"

#include "mercury/utils/Time.h"

#include "test/helpers/TemplateTests.h"
#include "test/mocks/kes_mp_cli/MockDefaultPaintingLoader.h"
#include "test/mocks/kes_mp_cli/MockOnlineLoader.h"
#include "test/mocks/kes_mp_cli/MockPainting.h"
#include "test/mocks/kes_mp_cli/MockPaintingCache.h"
#include "test/mocks/MockEnvironment.h"


namespace KESMPC {
namespace test {


/**
 * Check that users of the class can use it through a pointer of the
 * IPaintingManager interface.
 */
TEST(TestPaintingManager, IsAnIPaintingManager) {
    Mercury::test::testBaseIsAnInterface<
        KESMPC::PaintingManager, KESMPC::IPaintingManager>();
}

/**
 * Check that PaintingManager constructor calls Environment.getenv("HOME").
 */
TEST(TestPaintingManager, ConstructorCallsEnvironmentGetEnvWithHome) {
    auto mockEnvironment = std::make_shared<Mercury::Utils::test::MockEnvironment>();  // NOLINT

    ON_CALL(*mockEnvironment, get)
        .WillByDefault(::testing::Return(""));

    EXPECT_CALL(*mockEnvironment, get("HOME"))
        .Times(1);

    KESMPC::PaintingManager paintingManager(
        "", nullptr, nullptr, nullptr, mockEnvironment);
}

/**
 * Check that PaintingManager.getPaintings(false) calls and returns
 * OnlineLoader.getPaintings() when PaintingManager.isCooldown() is false.
 */
TEST(
    TestPaintingManager,
    GetPaintingsCacheFalseNoCooldownRetrievesWithOnlineLoader) {
    // NOLINT
    auto mockOnlineLoader = std::make_shared<MockOnlineLoader>();
    auto mockPaintingCache = std::make_shared<MockPaintingCache>();
    auto mockDefaultPaintingLoader =
        std::make_shared<MockDefaultPaintingLoader>();
    auto mockPainting = std::make_shared<MockPainting>();

    std::list<std::shared_ptr<KESMPC::IPainting>> paintings, result;
    paintings.push_back(mockPainting);

    KESMPC::PaintingManager paintingManager(
        "", mockOnlineLoader, mockPaintingCache, mockDefaultPaintingLoader);

    ON_CALL(*mockPaintingCache, getPaintings)
        .WillByDefault(::testing::Return(paintings));

    EXPECT_CALL(*mockPaintingCache, getPaintings)
        .Times(1);

    result = paintingManager.getPaintings(false);

    EXPECT_EQ(result, paintings);
}

/**
 * Check that PaintingManager.getPaintings(false) does not call
 * OnlineLoader.getPaintings() when PaintingManager.isCooldown() is true.
 */
TEST(
    TestPaintingManager,
    GetPaintingsCacheFalseWithCooldownDoesNotSpamOnlineLoader) {
    // NOLINT
    auto mockOnlineLoader = std::make_shared<MockOnlineLoader>();
    auto mockPaintingCache = std::make_shared<MockPaintingCache>();
    auto mockDefaultPaintingLoader =
        std::make_shared<MockDefaultPaintingLoader>();
    auto mockPainting = std::make_shared<MockPainting>();

    std::list<std::shared_ptr<KESMPC::IPainting>> paintings;
    paintings.push_back(mockPainting);

    KESMPC::PaintingManager paintingManager(
        "", mockOnlineLoader, mockPaintingCache, mockDefaultPaintingLoader);

    ON_CALL(*mockPaintingCache, getLastUpdated)
        .WillByDefault(::testing::Return(getTimestamp()));

    ON_CALL(*mockOnlineLoader, getQueryCooldown)
        .WillByDefault(::testing::Return(getTimestamp()));

    EXPECT_CALL(*mockPaintingCache, getLastUpdated)
        .Times(1);

    EXPECT_CALL(*mockOnlineLoader, getQueryCooldown)
        .Times(1);

    EXPECT_CALL(*mockOnlineLoader, getPaintings)
        .Times(0);

    paintingManager.getPaintings(false);
}

/**
 * Check that PaintingManager.getPaintings(false) returns
 * OnlineLoader.getPaintings() and calls PaintingCache.update(result)
 * when PaintingManager.isCooldown() is false and result is not empty.
 */
TEST(
    TestPaintingManager,
    GetPaintingsCacheFalseNoCooldownUpdatesPaintingCacheWhenThereAreResults) {
    // NOLINT
    auto mockOnlineLoader = std::make_shared<MockOnlineLoader>();
    auto mockPaintingCache = std::make_shared<MockPaintingCache>();
    auto mockDefaultPaintingLoader =
        std::make_shared<MockDefaultPaintingLoader>();
    auto mockPainting = std::make_shared<MockPainting>();

    std::list<std::shared_ptr<KESMPC::IPainting>> paintings, result;
    paintings.push_back(mockPainting);

    KESMPC::PaintingManager paintingManager(
        "", mockOnlineLoader, mockPaintingCache, mockDefaultPaintingLoader);

    ON_CALL(*mockOnlineLoader, getPaintings)
        .WillByDefault(::testing::Return(paintings));

    EXPECT_CALL(*mockOnlineLoader, getPaintings)
        .Times(1);

    EXPECT_CALL(*mockPaintingCache, update(::testing::Eq(paintings)))
        .Times(1);

    result = paintingManager.getPaintings(false);

    EXPECT_EQ(result, paintings);
}

/**
 * Check that PaintingManager.getPaintings(false) does not call
 * PaintingCache.update() when PaintingManager.isCooldown() is false and
 * OnlineLoader.getPaintings() result
 * is empty.
 */
TEST(
    TestPaintingManager,
    GetPaintingsCacheFalseNoCooldownDoesNotUpdateCacheWhenThereAreNoResults) {
    // NOLINT
    auto mockOnlineLoader = std::make_shared<MockOnlineLoader>();
    auto mockPaintingCache = std::make_shared<MockPaintingCache>();
    auto mockDefaultPaintingLoader =
        std::make_shared<MockDefaultPaintingLoader>();
    auto mockPainting = std::make_shared<MockPainting>();

    std::list<std::shared_ptr<KESMPC::IPainting>> paintings;
    paintings.push_back(mockPainting);

    KESMPC::PaintingManager paintingManager(
        "", mockOnlineLoader, mockPaintingCache, mockDefaultPaintingLoader);

    ON_CALL(*mockPaintingCache, getPaintings)
        .WillByDefault(::testing::Return(paintings));

    EXPECT_CALL(*mockOnlineLoader, getPaintings)
        .Times(1);

    EXPECT_CALL(*mockPaintingCache, update)
        .Times(0);

    paintingManager.getPaintings(false);
}

/**
 * Check that PaintingManager.getPaintings(false) returns
 * PaintingCache.getPaintings() when PaintingManager.isCooldown() is false and
 * OnlineLoader.getPaintings() result is empty.
 */
TEST(
    TestPaintingManager,
    GetPaintingsCacheFalseNoCooldownRetrievesFromPaintingCacheWhenThereAreNoResults) {  // NOLINT
    // NOLINT
    auto mockOnlineLoader = std::make_shared<MockOnlineLoader>();
    auto mockPaintingCache = std::make_shared<MockPaintingCache>();
    auto mockDefaultPaintingLoader =
        std::make_shared<MockDefaultPaintingLoader>();
    auto mockPainting = std::make_shared<MockPainting>();

    std::list<std::shared_ptr<KESMPC::IPainting>> paintings, result;
    paintings.push_back(mockPainting);

    KESMPC::PaintingManager paintingManager(
        "", mockOnlineLoader, mockPaintingCache, mockDefaultPaintingLoader);

    ON_CALL(*mockPaintingCache, getPaintings)
        .WillByDefault(::testing::Return(paintings));

    EXPECT_CALL(*mockOnlineLoader, getPaintings)
        .Times(1);

    EXPECT_CALL(*mockPaintingCache, getPaintings)
        .Times(1);

    result = paintingManager.getPaintings(false);

    EXPECT_EQ(result, paintings);
}

/**
 * Check that PaintingManager.getPaintings(false) returns
 * PaintingCache.getPaintings() when PaintingManager.isCooldown() is true.
 */
TEST(
    TestPaintingManager,
    GetPaintingsCacheFalseWithCooldonwRetrievesFromPaintingCache) {
    // NOLINT
    auto mockOnlineLoader = std::make_shared<MockOnlineLoader>();
    auto mockPaintingCache = std::make_shared<MockPaintingCache>();
    auto mockDefaultPaintingLoader =
        std::make_shared<MockDefaultPaintingLoader>();
    auto mockPainting = std::make_shared<MockPainting>();

    std::list<std::shared_ptr<KESMPC::IPainting>> paintings, result;
    paintings.push_back(mockPainting);

    KESMPC::PaintingManager paintingManager(
        "", mockOnlineLoader, mockPaintingCache, mockDefaultPaintingLoader);

    ON_CALL(*mockPaintingCache, getLastUpdated)
        .WillByDefault(::testing::Return(getTimestamp()));

    ON_CALL(*mockOnlineLoader, getQueryCooldown)
        .WillByDefault(::testing::Return(getTimestamp()));

    EXPECT_CALL(*mockPaintingCache, getLastUpdated)
        .Times(1);

    EXPECT_CALL(*mockOnlineLoader, getQueryCooldown)
        .Times(1);

    ON_CALL(*mockPaintingCache, getPaintings)
        .WillByDefault(::testing::Return(paintings));

    EXPECT_CALL(*mockPaintingCache, getPaintings)
        .Times(1);

    result = paintingManager.getPaintings(false);

    EXPECT_EQ(result, paintings);
}

/**
 * Check that PaintingManager.getPaintings(true) returns
 * PaintingCache.getPaintings().
 */
TEST(TestPaintingManager, GetPaintingsCacheTrueRetrievesFromPaintingCache) {
    auto mockOnlineLoader = std::make_shared<MockOnlineLoader>();
    auto mockPaintingCache = std::make_shared<MockPaintingCache>();
    auto mockDefaultPaintingLoader =
        std::make_shared<MockDefaultPaintingLoader>();
    auto mockPainting = std::make_shared<MockPainting>();

    std::list<std::shared_ptr<KESMPC::IPainting>> paintings, result;
    paintings.push_back(mockPainting);

    KESMPC::PaintingManager paintingManager(
        "", mockOnlineLoader, mockPaintingCache, mockDefaultPaintingLoader);

    ON_CALL(*mockPaintingCache, getPaintings)
        .WillByDefault(::testing::Return(paintings));

    EXPECT_CALL(*mockPaintingCache, getPaintings)
        .Times(1);

    result = paintingManager.getPaintings(true);

    EXPECT_EQ(result, paintings);
}

/**
 * Check that PaintingManager.getPaintings(true) returns
 * DefaultPaintingLoader.getPaintings() when PaintingCache.getPaintings()
 * result is empty and calls PaintingCache.update().
 */
TEST(
    TestPaintingManager,
    GetPaintingsCacheTrueRetrievesDefaultPaintingsWhenCacheIsEmpty) {
    // NOLINT
    auto mockOnlineLoader = std::make_shared<MockOnlineLoader>();
    auto mockPaintingCache = std::make_shared<MockPaintingCache>();
    auto mockDefaultPaintingLoader =
        std::make_shared<MockDefaultPaintingLoader>();
    auto mockPainting = std::make_shared<MockPainting>();

    std::list<std::shared_ptr<KESMPC::IPainting>> paintings, result;
    paintings.push_back(mockPainting);

    KESMPC::PaintingManager paintingManager(
        "", mockOnlineLoader, mockPaintingCache, mockDefaultPaintingLoader);

    ON_CALL(*mockDefaultPaintingLoader, getPaintings)
        .WillByDefault(::testing::Return(paintings));

    EXPECT_CALL(*mockPaintingCache, getPaintings)
        .Times(1);

    EXPECT_CALL(*mockDefaultPaintingLoader, getPaintings)
        .Times(1);

    EXPECT_CALL(*mockPaintingCache, update(paintings))
        .Times(1);

    result = paintingManager.getPaintings(true);

    EXPECT_EQ(result, paintings);
}

}  // namespace test
}  // namespace KESMPC

#endif  // TEST_UNIT_KES_MOMA_PICKS_CLIENT_TESTPAINTINGMANAGER_H_
