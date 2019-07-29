/**
 * \file TestOnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTONLINELOADER_H_
#define TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTONLINELOADER_H_


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <parson.h>

#include <memory>
#include <string>

#include "mercury/_http/exceptions.h"
#include "mercury/_http/http_client_interface.h"
#include "mercury/kes_dashboard_live_tiles_cli/Exceptions.h"
#include "mercury/kes_dashboard_live_tiles_cli/OnlineLoader.h"

#include "test/fixtures/kes_dlt_cli/KesDltResponsesFixture.h"
#include "test/fixtures/kes_dlt_cli/KesDltValidResponsesFixture.h"
#include "test/mocks/kes_dlt_cli/MockTile.h"
#include "test/mocks/kes_dlt_cli/MockTileFactory.h"
#include "test/mocks/mock_http_client.h"

using std::shared_ptr;
using std::string;
using std::make_shared;

using ::testing::_;
using ::testing::StrEq;
using ::testing::Values;
using ::testing::Return;


INSTANTIATE_TEST_CASE_P(
    Parameterised,
    KesDltValidResponsesFixture,
    Values("feed1", "feed2", "feed3"));

/**
 * Check that OnlineLoader.getTiles() calls HTTPClient.GET()
 */
TEST_P(KesDltValidResponsesFixture, GetTilesCallsHTTPClientGET) {
    auto mockHttpClient = make_shared<MockHTTPClient>();
    auto mockTileFactory = make_shared<MockTileFactory>();
    auto mockTile = make_shared<MockTile>();

    OnlineLoader onlineLoader(
        "/tmp/kes-dlt-cli/test", mockHttpClient, mockTileFactory);

    // Ensuring the remainder of the function doesn't throw Exceptions by
    // returning a valid KES response from the HTTPClient.GET().
    ON_CALL(*mockHttpClient, GET_impl(OnlineLoader::KES_DLT_URL, _))
        .WillByDefault(Return(this->response));

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(Return(true));

    // Ignore the call to Tile.download().
    ON_CALL(*mockTile, download)
        .WillByDefault(Return(true));

    EXPECT_CALL(*mockHttpClient, GET_impl(OnlineLoader::KES_DLT_URL, _))
        .Times(1);

    onlineLoader.getTiles();
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getTiles()
 * calls for each tile data TileFactory.create().
 */
TEST_P(KesDltValidResponsesFixture, GetTilesCallsTileFactoryCreate) {
    auto mockHttpClient = make_shared<MockHTTPClient>();
    auto mockTileFactory = make_shared<MockTileFactory>();
    auto mockTile = make_shared<MockTile>();

    OnlineLoader onlineLoader(
        "/tmp/kes-dlt-cli/test", mockHttpClient, mockTileFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(*mockHttpClient, GET_impl(OnlineLoader::KES_DLT_URL, _))
        .WillByDefault(Return(this->response));

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(Return(true));

    // Ignore the call to Tile.download().
    ON_CALL(*mockTile, download)
        .WillByDefault(Return(true));

    EXPECT_CALL(*mockTileFactory, create)
        .Times(this->tileCount);

    onlineLoader.getTiles();
}


MATCHER_P(AnyInJsonArray, jsonArray, "") {
    for (int i = 0; i < json_array_get_count(jsonArray); i++)
        if (json_value_equals(json_array_get_value(jsonArray, i), arg))
            return true;
    return false;
}


/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getTiles()
 * calls for each tile data Tile.initialise() with the expected JSON.
 */
TEST_P(KesDltValidResponsesFixture, GetTilesCallsTileInitialise) {
    auto mockHttpClient = make_shared<MockHTTPClient>();
    auto mockTileFactory = make_shared<MockTileFactory>();
    auto mockTile = make_shared<MockTile>();

    OnlineLoader onlineLoader(
        "/tmp/kes-dlt-cli/test", mockHttpClient, mockTileFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(*mockHttpClient, GET_impl(OnlineLoader::KES_DLT_URL, _))
        .WillByDefault(Return(this->response));

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(Return(true));

    // Ignore the call to Tile.download().
    ON_CALL(*mockTile, download)
        .WillByDefault(Return(true));

    JSON_Array* tilesData = json_object_get_array(
        json_value_get_object(this->response.get()), "shares");

    // TODO: Should use AllInJsonArray to check that each item passed to
    // initialise is at a unique index in a given array. No clue how to atm.
    EXPECT_CALL(*mockTile, initialise(AnyInJsonArray(tilesData)))
        .Times(this->tileCount);

    onlineLoader.getTiles();
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getTiles()
 * calls for each tile data Tile.download() with the given cacheDir.
 */
TEST_P(KesDltValidResponsesFixture, GetTilesCallsTileDownload) {
    auto mockHttpClient = make_shared<MockHTTPClient>();
    auto mockTileFactory = make_shared<MockTileFactory>();
    auto mockTile = make_shared<MockTile>();

    const string cacheDir = "/tmp/kes-dlt-cli/test";
    OnlineLoader onlineLoader(cacheDir, mockHttpClient, mockTileFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(*mockHttpClient, GET_impl(OnlineLoader::KES_DLT_URL, _))
        .WillByDefault(Return(this->response));

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(Return(true));

    // Ignore the call to Tile.download().
    ON_CALL(*mockTile, download)
        .WillByDefault(Return(true));

    EXPECT_CALL(*mockTile, download(StrEq(cacheDir)))
        .Times(this->tileCount);

    onlineLoader.getTiles();
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getTiles()
 * throws a BrokenContractsException when JSON does not contain "shares" array.
 */
TEST_F(KesDltResponsesFixture,
       GetTilesThrowsBrokenContractsExceptionWhenMissingSharesField) {
    auto mockHttpClient = make_shared<MockHTTPClient>();

    const string cacheDir = "/tmp/kes-dlt-cli/test";
    OnlineLoader onlineLoader(cacheDir, mockHttpClient);

    // Set the HTTPClient.GET to return a given malformed KES response.
    ON_CALL(*mockHttpClient, GET_impl(OnlineLoader::KES_DLT_URL, _))
        .WillByDefault(Return(responses["malformed_feed1"]));

    ASSERT_THROW(onlineLoader.getTiles(), BrokenContractsException);
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getTiles()
 * throws a BrokenContractsException when Tile.initialise() fails.
 */
TEST_F(KesDltResponsesFixture,
       GetTilesThrowsBrokenContractsExceptionWhenTileInitialiseFails) {
    auto mockHttpClient = make_shared<MockHTTPClient>();
    auto mockTileFactory = make_shared<MockTileFactory>();
    auto mockTile = make_shared<MockTile>();

    const string cacheDir = "/tmp/kes-dlt-cli/test";
    OnlineLoader onlineLoader(cacheDir, mockHttpClient, mockTileFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(*mockHttpClient, GET_impl(OnlineLoader::KES_DLT_URL, _))
        .WillByDefault(Return(responses["feed1"]));

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(Return(mockTile));

    // Set the mock Tile.initialise() to return false for failure.
    ON_CALL(*mockTile, initialise)
        .WillByDefault(Return(false));

    ASSERT_THROW(onlineLoader.getTiles(), BrokenContractsException);
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getTiles()
 * throws a DownloadError when Tile.download() fails.
 */
TEST_F(KesDltResponsesFixture,
       GetTilesThrowsDownloadErrorWhenTileDownloadFails) {
    auto mockHttpClient = make_shared<MockHTTPClient>();
    auto mockTileFactory = make_shared<MockTileFactory>();
    auto mockTile = make_shared<MockTile>();

    const string cacheDir = "/tmp/kes-dlt-cli/test";
    OnlineLoader onlineLoader(cacheDir, mockHttpClient, mockTileFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(*mockHttpClient, GET_impl(OnlineLoader::KES_DLT_URL, _))
        .WillByDefault(Return(responses["feed1"]));

    // Return the same mock Tile each for each tile data from the response.
    ON_CALL(*mockTileFactory, create)
        .WillByDefault(Return(mockTile));

    // Ignore the call to Tile.initialise().
    ON_CALL(*mockTile, initialise)
        .WillByDefault(Return(true));

    // Set the mock Tile.download() to return false for failure.
    ON_CALL(*mockTile, download)
        .WillByDefault(Return(false));

    ASSERT_THROW(onlineLoader.getTiles(), DownloadError);
}

#endif  // TEST_KES_DASHBOARD_LIVE_TILES_CLI_TESTONLINELOADER_H_
