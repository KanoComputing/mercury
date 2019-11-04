/**
 * \file TestOnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_UNIT_KES_DASHBOARD_LIVE_TILES_CLIENT_TESTONLINELOADER_H_
#define TEST_UNIT_KES_DASHBOARD_LIVE_TILES_CLIENT_TESTONLINELOADER_H_


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <parson.h>

#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/internal/Exceptions.h"
#include "kes_dashboard_live_tiles_client/internal/IOnlineLoader.h"
#include "kes_dashboard_live_tiles_client/internal/ITileLoader.h"
#include "kes_dashboard_live_tiles_client/internal/OnlineLoader.h"

#include "mercury/http/exceptions.h"
#include "mercury/http/http_client_interface.h"

#include "test/fixtures/kes_dlt_cli/KesDltResponsesFixture.h"
#include "test/fixtures/kes_dlt_cli/KesDltValidResponsesFixture.h"
#include "test/helpers/TemplateTests.h"
#include "test/matchers/JsonMatchers.h"
#include "test/mocks/kes_dlt_cli/MockTile.h"
#include "test/mocks/kes_dlt_cli/MockTileFactory.h"
#include "test/mocks/mock_http_client.h"


namespace KESDLTC {
namespace test {


/**
 * Check that users of the class can use it through a pointer of the
 * IOnlineLoader interface.
 */
TEST(TestOnlineLoader, IsAnIOnlineLoader) {
    Mercury::test::testBaseIsAnInterface<
        KESDLTC::internal::OnlineLoader, KESDLTC::internal::IOnlineLoader>("");
}

/**
 * Check that users of the class can use it through a pointer of the
 * ITileLoader interface.
 */
TEST(TestOnlineLoader, IsAnITileLoader) {
    Mercury::test::testBaseIsAnInterface<
        KESDLTC::internal::OnlineLoader, KESDLTC::internal::ITileLoader>("");
}

INSTANTIATE_TEST_CASE_P(
    Parameterised,
    KesDltValidResponsesFixture,
    ::testing::Values("feed1", "feed2", "feed3"));

/**
 * Check that OnlineLoader.getTiles() calls HTTPClient.GET()
 */
TEST_P(KesDltValidResponsesFixture, GetTilesCallsHTTPClientGET) {
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();
    auto mockTileFactory = std::make_shared<MockTileFactory>();
    auto mockTile = std::make_shared<MockTile>();

    KESDLTC::internal::OnlineLoader onlineLoader(
        "/tmp/kes-dlt-cli/test", mockHttpClient, mockTileFactory);

    // Ensuring the remainder of the function doesn't throw Exceptions by
    // returning a valid KES response from the HTTPClient.GET().
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESDLTC::internal::OnlineLoader::KES_DLT_URL, ::testing::_))
        .WillByDefault(::testing::Return(this->response));

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(::testing::Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(::testing::Return(true));

    // Ignore the call to Tile.download().
    ON_CALL(*mockTile, download)
        .WillByDefault(::testing::Return(true));

    EXPECT_CALL(
        *mockHttpClient,
        GET_impl(KESDLTC::internal::OnlineLoader::KES_DLT_URL, ::testing::_))
        .Times(1);

    onlineLoader.getTiles();
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getTiles()
 * calls for each tile data TileFactory.create().
 */
TEST_P(KesDltValidResponsesFixture, GetTilesCallsTileFactoryCreate) {
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();
    auto mockTileFactory = std::make_shared<MockTileFactory>();
    auto mockTile = std::make_shared<MockTile>();

    KESDLTC::internal::OnlineLoader onlineLoader(
        "/tmp/kes-dlt-cli/test", mockHttpClient, mockTileFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESDLTC::internal::OnlineLoader::KES_DLT_URL, ::testing::_))
        .WillByDefault(::testing::Return(this->response));

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(::testing::Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(::testing::Return(true));

    // Ignore the call to Tile.download().
    ON_CALL(*mockTile, download)
        .WillByDefault(::testing::Return(true));

    EXPECT_CALL(*mockTileFactory, create)
        .Times(this->tileCount);

    onlineLoader.getTiles();
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getTiles()
 * calls for each tile data Tile.initialise() with the expected JSON.
 */
TEST_P(KesDltValidResponsesFixture, GetTilesCallsTileInitialise) {
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();
    auto mockTileFactory = std::make_shared<MockTileFactory>();
    auto mockTile = std::make_shared<MockTile>();

    KESDLTC::internal::OnlineLoader onlineLoader(
        "/tmp/kes-dlt-cli/test", mockHttpClient, mockTileFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESDLTC::internal::OnlineLoader::KES_DLT_URL, ::testing::_))
        .WillByDefault(::testing::Return(this->response));

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(::testing::Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(::testing::Return(true));

    // Ignore the call to Tile.download().
    ON_CALL(*mockTile, download)
        .WillByDefault(::testing::Return(true));

    JSON_Array* tilesData = json_object_get_array(
        json_value_get_object(this->response.get()), "tiles");

    JSON_Value* tileData;

    // Expect that Tile.initialise() is called with each individual
    // tileData from the KES response.
    for (int i = 0; i < json_array_get_count(tilesData); i++) {
        tileData = json_array_get_value(tilesData, i);

        EXPECT_CALL(*mockTile, initialise(JsonEq(tileData)))
            .Times(1);
    }

    onlineLoader.getTiles();
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getTiles()
 * calls for each tile data Tile.download() with the given cacheDir.
 */
TEST_P(KesDltValidResponsesFixture, GetTilesCallsTileDownload) {
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();
    auto mockTileFactory = std::make_shared<MockTileFactory>();
    auto mockTile = std::make_shared<MockTile>();

    const std::string cacheDir = "/tmp/kes-dlt-cli/test";
    KESDLTC::internal::OnlineLoader onlineLoader(
        cacheDir, mockHttpClient, mockTileFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESDLTC::internal::OnlineLoader::KES_DLT_URL, ::testing::_))
        .WillByDefault(::testing::Return(this->response));

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(::testing::Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(::testing::Return(true));

    // Ignore the call to Tile.download().
    ON_CALL(*mockTile, download)
        .WillByDefault(::testing::Return(true));

    EXPECT_CALL(*mockTile, download(::testing::StrEq(cacheDir)))
        .Times(this->tileCount);

    onlineLoader.getTiles();
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getTiles()
 * throws a BrokenContractsException when JSON does not contain "tiles" array.
 */
TEST_F(
    KesDltResponsesFixture,
    GetTilesThrowsBrokenContractsExceptionWhenMissingTilesField) {
    // NOLINT
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();

    const std::string cacheDir = "/tmp/kes-dlt-cli/test";
    KESDLTC::internal::OnlineLoader onlineLoader(cacheDir, mockHttpClient);

    // Set the HTTPClient.GET to return a given malformed KES response.
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESDLTC::internal::OnlineLoader::KES_DLT_URL, ::testing::_))
        .WillByDefault(::testing::Return(responses["invalid_feed1"]));

    ASSERT_THROW(
        onlineLoader.getTiles(),
        KESDLTC::internal::BrokenContractsException);
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getTiles()
 * throws a BrokenContractsException when Tile.initialise() fails.
 */
TEST_F(
    KesDltResponsesFixture,
    GetTilesThrowsBrokenContractsExceptionWhenTileInitialiseFails) {
    // NOLINT
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();
    auto mockTileFactory = std::make_shared<MockTileFactory>();
    auto mockTile = std::make_shared<MockTile>();

    const std::string cacheDir = "/tmp/kes-dlt-cli/test";
    KESDLTC::internal::OnlineLoader onlineLoader(
        cacheDir, mockHttpClient, mockTileFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESDLTC::internal::OnlineLoader::KES_DLT_URL, ::testing::_))
        .WillByDefault(::testing::Return(responses["feed1"]));

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(::testing::Return(mockTile));

    // Set the mock Tile.initialise() to return false for failure.
    ON_CALL(*mockTile, initialise)
        .WillByDefault(::testing::Return(false));

    ASSERT_THROW(
        onlineLoader.getTiles(),
        KESDLTC::internal::BrokenContractsException);
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getTiles()
 * throws a DownloadError when Tile.download() fails.
 */
TEST_F(
    KesDltResponsesFixture,
    GetTilesThrowsDownloadErrorWhenTileDownloadFails) {
    // NOLINT
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();
    auto mockTileFactory = std::make_shared<MockTileFactory>();
    auto mockTile = std::make_shared<MockTile>();

    const std::string cacheDir = "/tmp/kes-dlt-cli/test";
    KESDLTC::internal::OnlineLoader onlineLoader(
        cacheDir, mockHttpClient, mockTileFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESDLTC::internal::OnlineLoader::KES_DLT_URL, ::testing::_))
        .WillByDefault(::testing::Return(responses["feed1"]));

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(::testing::Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(::testing::Return(true));

    // Set the mock Tile.download() to return false for failure.
    ON_CALL(*mockTile, download)
        .WillByDefault(::testing::Return(false));

    ASSERT_THROW(onlineLoader.getTiles(), Mercury::HTTP::DownloadError);
}


}  // namespace test
}  // namespace KESDLTC


#endif  // TEST_UNIT_KES_DASHBOARD_LIVE_TILES_CLIENT_TESTONLINELOADER_H_
