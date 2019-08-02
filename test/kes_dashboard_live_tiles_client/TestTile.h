/**
 * \file TestTile.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_KES_DASHBOARD_LIVE_TILES_CLIENT_TESTTILE_H_
#define TEST_KES_DASHBOARD_LIVE_TILES_CLIENT_TESTTILE_H_


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <parson.h>

#include <iostream>
#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/Tile.h"

#include "test/fixtures/kes_dlt_cli/KesDltResponsesFixture.h"
#include "test/fixtures/kes_dlt_cli/TileCacheFixture.h"
#include "test/matchers/JsonMatchers.h"
#include "test/mocks/mock_http_client.h"


namespace KESDLTC {
namespace test {

/**
 * Chech that Tile() constructor sets all members.
 */
TEST(TestTile, EmptyConstructor) {
    KESDLTC::Tile tile;

    EXPECT_EQ(tile.getId(), "");
    EXPECT_EQ(tile.getUsername(), "");
    EXPECT_EQ(tile.getTitle(), "");
    EXPECT_EQ(tile.getDescription(), "");
    EXPECT_EQ(tile.getApp(), "");
    EXPECT_EQ(tile.getCover(), "");
    EXPECT_EQ(tile.getOpenUrl(), "");
    EXPECT_EQ(tile.getFallbackUrl(), "");
    EXPECT_EQ(tile.getCoverPath(), "");
}

/**
 * Chech that Tile(args) constructor sets all members.
 */
TEST(TestTile, FullConstructor) {
    KESDLTC::Tile tile(
        "id", "cover", "title", "description", "username", "app", "openUrl",
        "fallbackUrl", "coverPath");

    EXPECT_EQ(tile.getId(), "id");
    EXPECT_EQ(tile.getUsername(), "username");
    EXPECT_EQ(tile.getTitle(), "title");
    EXPECT_EQ(tile.getDescription(), "description");
    EXPECT_EQ(tile.getApp(), "app");
    EXPECT_EQ(tile.getCover(), "cover");
    EXPECT_EQ(tile.getOpenUrl(), "openUrl");
    EXPECT_EQ(tile.getFallbackUrl(), "fallbackUrl");
    EXPECT_EQ(tile.getCoverPath(), "coverPath");
}

/**
 * Check that Tile.initialise() sets all members as received from a
 * valid KES response.
 */
TEST_F(KesDltResponsesFixture, InitialiseSetsAllKESContractMembers) {
    JSON_Value* tileData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->responses["feed1"].get()),
                "tiles"),
            0);
    JSON_Object* data = json_value_get_object(tileData);

    KESDLTC::Tile tile;
    tile.initialise(tileData);

    EXPECT_EQ(
        std::string(json_object_get_string(data, "id")),
        tile.getId());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "username")),
        tile.getUsername());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "title")),
        tile.getTitle());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "description")),
        tile.getDescription());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "app")),
        tile.getApp());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "cover")),
        tile.getCover());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "openUrl")),
        tile.getOpenUrl());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "fallbackUrl")),
        tile.getFallbackUrl());
    EXPECT_EQ("", tile.getCoverPath());
}

/**
 * Check that Tile.initialise() sets all members as received from a
 * valid KES response and also the optional coverPath member.
 */
TEST_F(KesDltResponsesFixture, InitialiseAlsoSetsCoverPath) {
    JSON_Value* tileData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->caches["tile_cache1"].get()),
                "tiles"),
            0);
    JSON_Object* data = json_value_get_object(tileData);

    KESDLTC::Tile tile;
    tile.initialise(tileData);

    EXPECT_EQ(
        std::string(json_object_get_string(data, "id")),
        tile.getId());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "username")),
        tile.getUsername());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "title")),
        tile.getTitle());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "description")),
        tile.getDescription());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "app")),
        tile.getApp());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "cover")),
        tile.getCover());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "openUrl")),
        tile.getOpenUrl());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "fallbackUrl")),
        tile.getFallbackUrl());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "coverPath")),
        tile.getCoverPath());
}

/**
 * Check that Tile.initialise() fails when any data field from a KES response
 * does not match what is expected.
 */
TEST_F(KesDltResponsesFixture, InitialiseFailsForMissingKESContractMembers) {
    JSON_Value* tileData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->responses["invalid_feed2"].get()),
                "tiles"),
            0);
    JSON_Object* data = json_value_get_object(tileData);

    KESDLTC::Tile tile;

    EXPECT_FALSE(tile.initialise(tileData));
}

/**
 * Check that Tile.serialise() serialises all members pertinent to a valid
 * KES response.
 */
TEST_F(KesDltResponsesFixture, SerialiseWritesAllKESContractMembers) {
    JSON_Value* tileData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->responses["feed1"].get()),
                "tiles"),
            0);
    JSON_Object* data = json_value_get_object(tileData);

    KESDLTC::Tile tile;
    tile.initialise(tileData);

    std::shared_ptr<JSON_Value> result(
        tile.serialise(), json_value_free);

    std::shared_ptr<char> resultStr(
        json_serialize_to_string_pretty(result.get()),
        json_free_serialized_string);
    std::shared_ptr<char> tileDataStr(
        json_serialize_to_string_pretty(tileData),
        json_free_serialized_string);

    EXPECT_THAT(result.get(), JsonEq(tileData))
        << "tileData was: " << std::string(tileDataStr.get()) << std::endl
        << "result was: " << std::string(resultStr.get()) << std::endl;
}

/**
 * Check that Tile.serialise() serialises all members pertinent to a valid
 * KES response and also coverPath when it's set.
 */
TEST_F(KesDltResponsesFixture, SerialiseAlsoWritesCoverPath) {
    JSON_Value* tileData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->caches["tile_cache1"].get()),
                "tiles"),
            0);
    JSON_Object* data = json_value_get_object(tileData);

    KESDLTC::Tile tile;
    tile.initialise(tileData);

    std::shared_ptr<JSON_Value> result(
        tile.serialise(), json_value_free);

    std::shared_ptr<char> resultStr(
        json_serialize_to_string_pretty(result.get()),
        json_free_serialized_string);
    std::shared_ptr<char> tileDataStr(
        json_serialize_to_string_pretty(tileData),
        json_free_serialized_string);

    EXPECT_THAT(result.get(), JsonEq(tileData))
        << "tileData was: " << std::string(tileDataStr.get()) << std::endl
        << "result was: " << std::string(resultStr.get()) << std::endl;
}

/**
 * TODO
 */
/*TEST(TestTile, DownloadCreatesTileDirDirectories) {
    // TODO
    EXPECT_TRUE(false);
}*/

/**
 * Check that Tile.download() calls HTTPClient.DL method with the intended
 * arguments.
 */
TEST_F(TileCacheFixture, DownloadCallsDL) {
    auto mockHttpClient = std::make_shared<MockHTTPClient>();

    JSON_Value* tileData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->responses["feed1"].get()),
                "tiles"),
            0);

    KESDLTC::Tile tile(mockHttpClient);
    tile.initialise(tileData);

    ON_CALL(*mockHttpClient, DL)
        .WillByDefault(::testing::Return(true));

    EXPECT_CALL(
        *mockHttpClient,
        DL(tile.getCover(), ::testing::StartsWith(this->cacheDir)))
        .Times(1);

    tile.download(this->cacheDir);
}

/**
 * Check that Tile.download() sets its internal coverPath member to the
 * expected value.
 */
TEST_F(TileCacheFixture, DownloadSetsCoverPath) {
    auto mockHttpClient = std::make_shared<MockHTTPClient>();

    JSON_Value* tileData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->caches["tile_cache1"].get()),
                "tiles"),
            0);

    KESDLTC::Tile tile(mockHttpClient);
    tile.initialise(tileData);

    ON_CALL(*mockHttpClient, DL)
        .WillByDefault(::testing::Return(true));

    EXPECT_EQ(
        tile.getCoverPath(),
        std::string(json_object_get_string(
            json_value_get_object(tileData), "coverPath")));

    tile.download(this->cacheDir);

    const std::string expectedCoverPath =
        this->cacheDir + "/" +
        std::string(json_object_get_string(
            json_value_get_object(tileData), "coverPath"));

    EXPECT_EQ(tile.getCoverPath(), expectedCoverPath);
}

/**
 * TODO
 */
/*TEST(TestTile, DownloadFailsWhenCannotCreateDirs) {
    // TODO
    EXPECT_TRUE(false);
}*/

/**
 * Check that Tile.download() returns false when HTTPClient.DL also does so.
 */
TEST_F(TileCacheFixture, DownloadFailsWhenDLFails) {
    auto mockHttpClient = std::make_shared<MockHTTPClient>();

    JSON_Value* tileData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->caches["tile_cache1"].get()),
                "tiles"),
            0);

    KESDLTC::Tile tile(mockHttpClient);
    tile.initialise(tileData);

    ON_CALL(*mockHttpClient, DL)
        .WillByDefault(::testing::Return(false));

    EXPECT_FALSE(tile.download(this->cacheDir));
}

}  // namespace test
}  // namespace KESDLTC

#endif  // TEST_KES_DASHBOARD_LIVE_TILES_CLIENT_TESTTILE_H_
