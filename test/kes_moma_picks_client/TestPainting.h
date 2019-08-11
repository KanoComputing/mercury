/**
 * \file TestPainting.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_KES_MOMA_PICKS_CLIENT_TESTPAINTING_H_
#define TEST_KES_MOMA_PICKS_CLIENT_TESTPAINTING_H_


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <parson.h>

#include <iostream>
#include <memory>
#include <string>

#include "kes_moma_picks_client/Painting.h"

#include "test/fixtures/kes_mp_cli/KesMpResponsesFixture.h"
#include "test/fixtures/kes_mp_cli/PaintingCacheFixture.h"
#include "test/matchers/JsonMatchers.h"
#include "test/mocks/mock_http_client.h"


namespace KESMPC {
namespace test {

/**
 * Chech that Painting() constructor sets all members.
 */
TEST(TestPainting, EmptyConstructor) {
    KESMPC::Painting painting;

    EXPECT_EQ(painting.getId(), "");
    EXPECT_EQ(painting.getUsername(), "");
    EXPECT_EQ(painting.getTitle(), "");
    EXPECT_EQ(painting.getDateCreated(), "");
    EXPECT_EQ(painting.getCover(), "");
    EXPECT_EQ(painting.getOpenUrl(), "");
    EXPECT_EQ(painting.getFallbackUrl(), "");
    EXPECT_EQ(painting.getCoverPath(), "");
}

/**
 * Chech that Painting(args) constructor sets all members.
 */
TEST(TestPainting, FullConstructor) {
    KESMPC::Painting painting(
        "id", "cover", "title", "username", "dateCreated", "openUrl",
        "fallbackUrl", "coverPath");

    EXPECT_EQ(painting.getId(), "id");
    EXPECT_EQ(painting.getUsername(), "username");
    EXPECT_EQ(painting.getTitle(), "title");
    EXPECT_EQ(painting.getDateCreated(), "dateCreated");
    EXPECT_EQ(painting.getCover(), "cover");
    EXPECT_EQ(painting.getOpenUrl(), "openUrl");
    EXPECT_EQ(painting.getFallbackUrl(), "fallbackUrl");
    EXPECT_EQ(painting.getCoverPath(), "coverPath");
}

/**
 * Check that Painting.initialise() sets all members as received from a
 * valid KES response.
 */
TEST_F(KesMpResponsesFixture, InitialiseSetsAllKESContractMembers) {
    JSON_Value* paintingData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->responses["feed1"].get()),
                "paintings"),
            0);
    JSON_Object* data = json_value_get_object(paintingData);

    KESMPC::Painting painting;
    painting.initialise(paintingData);

    EXPECT_EQ(
        std::string(json_object_get_string(data, "id")),
        painting.getId());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "username")),
        painting.getUsername());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "title")),
        painting.getTitle());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "dateCreated")),
        painting.getDateCreated());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "cover")),
        painting.getCover());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "openUrl")),
        painting.getOpenUrl());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "fallbackUrl")),
        painting.getFallbackUrl());
    EXPECT_EQ("", painting.getCoverPath());
}

/**
 * Check that Painting.initialise() sets all members as received from a
 * valid KES response and also the optional coverPath member.
 */
TEST_F(KesMpResponsesFixture, InitialiseAlsoSetsCoverPath) {
    JSON_Value* paintingData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->caches["painting_cache1"].get()),
                "paintings"),
            0);
    JSON_Object* data = json_value_get_object(paintingData);

    KESMPC::Painting painting;
    painting.initialise(paintingData);

    EXPECT_EQ(
        std::string(json_object_get_string(data, "id")),
        painting.getId());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "username")),
        painting.getUsername());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "title")),
        painting.getTitle());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "dateCreated")),
        painting.getDateCreated());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "cover")),
        painting.getCover());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "openUrl")),
        painting.getOpenUrl());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "fallbackUrl")),
        painting.getFallbackUrl());
    EXPECT_EQ(
        std::string(json_object_get_string(data, "coverPath")),
        painting.getCoverPath());
}

/**
 * Check that Painting.initialise() fails when any data field from a
 * KES response does not match what is expected.
 */
TEST_F(KesMpResponsesFixture, InitialiseFailsForMissingKESContractMembers) {
    JSON_Value* paintingData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->responses["invalid_feed2"].get()),
                "paintings"),
            0);
    JSON_Object* data = json_value_get_object(paintingData);

    KESMPC::Painting painting;

    EXPECT_FALSE(painting.initialise(paintingData));
}

/**
 * Check that Painting.serialise() serialises all members pertinent to a valid
 * KES response.
 */
TEST_F(KesMpResponsesFixture, SerialiseWritesAllKESContractMembers) {
    JSON_Value* paintingData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->responses["feed1"].get()),
                "paintings"),
            0);
    JSON_Object* data = json_value_get_object(paintingData);

    KESMPC::Painting painting;
    painting.initialise(paintingData);

    std::shared_ptr<JSON_Value> result(
        painting.serialise(), json_value_free);

    std::shared_ptr<char> resultStr(
        json_serialize_to_string_pretty(result.get()),
        json_free_serialized_string);
    std::shared_ptr<char> paintingDataStr(
        json_serialize_to_string_pretty(paintingData),
        json_free_serialized_string);

    EXPECT_THAT(result.get(), JsonEq(paintingData))
        << "paintingData was: " << std::string(paintingDataStr.get()) << std::endl  // NOLINT
        << "result was: " << std::string(resultStr.get()) << std::endl;
}

/**
 * Check that Painting.serialise() serialises all members pertinent to a valid
 * KES response and also coverPath when it's set.
 */
TEST_F(KesMpResponsesFixture, SerialiseAlsoWritesCoverPath) {
    JSON_Value* paintingData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->caches["painting_cache1"].get()),
                "paintings"),
            0);
    JSON_Object* data = json_value_get_object(paintingData);

    KESMPC::Painting painting;
    painting.initialise(paintingData);

    std::shared_ptr<JSON_Value> result(
        painting.serialise(), json_value_free);

    std::shared_ptr<char> resultStr(
        json_serialize_to_string_pretty(result.get()),
        json_free_serialized_string);
    std::shared_ptr<char> paintingDataStr(
        json_serialize_to_string_pretty(paintingData),
        json_free_serialized_string);

    EXPECT_THAT(result.get(), JsonEq(paintingData))
        << "paintingData was: " << std::string(paintingDataStr.get()) << std::endl  // NOLINT
        << "result was: " << std::string(resultStr.get()) << std::endl;
}

/**
 * TODO
 */
/*TEST(TestPainting, DownloadCreatesPaintingDirDirectories) {
    // TODO
    EXPECT_TRUE(false);
}*/

/**
 * Check that Painting.download() calls HTTPClient.DL method with the intended
 * arguments.
 */
TEST_F(PaintingCacheFixture, DownloadCallsDL) {
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();

    JSON_Value* paintingData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->responses["feed1"].get()),
                "paintings"),
            0);

    KESMPC::Painting painting(mockHttpClient);
    painting.initialise(paintingData);

    ON_CALL(*mockHttpClient, DL)
        .WillByDefault(::testing::Return(true));

    EXPECT_CALL(
        *mockHttpClient,
        DL(painting.getCover(), ::testing::StartsWith(this->cacheDir)))
        .Times(1);

    painting.download(this->cacheDir);
}

/**
 * Check that Painting.download() sets its internal coverPath member to the
 * expected value.
 */
TEST_F(PaintingCacheFixture, DownloadSetsCoverPath) {
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();

    JSON_Value* paintingData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->caches["painting_cache1"].get()),
                "paintings"),
            0);

    KESMPC::Painting painting(mockHttpClient);
    painting.initialise(paintingData);

    ON_CALL(*mockHttpClient, DL)
        .WillByDefault(::testing::Return(true));

    EXPECT_EQ(
        painting.getCoverPath(),
        std::string(json_object_get_string(
            json_value_get_object(paintingData), "coverPath")));

    painting.download(this->cacheDir);

    const std::string expectedCoverPath =
        this->cacheDir + "/" +
        std::string(json_object_get_string(
            json_value_get_object(paintingData), "coverPath"));

    EXPECT_EQ(painting.getCoverPath(), expectedCoverPath);
}

/**
 * TODO
 */
/*TEST(TestPainting, DownloadFailsWhenCannotCreateDirs) {
    // TODO
    EXPECT_TRUE(false);
}*/

/**
 * Check that Painting.download() returns false when HTTPClient.DL also does so
 */
TEST_F(PaintingCacheFixture, DownloadFailsWhenDLFails) {
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();

    JSON_Value* paintingData =
        json_array_get_value(
            json_object_get_array(
                json_value_get_object(
                    this->caches["painting_cache1"].get()),
                "paintings"),
            0);

    KESMPC::Painting painting(mockHttpClient);
    painting.initialise(paintingData);

    ON_CALL(*mockHttpClient, DL)
        .WillByDefault(::testing::Return(false));

    EXPECT_FALSE(painting.download(this->cacheDir));
}

}  // namespace test
}  // namespace KESMPC

#endif  // TEST_KES_MOMA_PICKS_CLIENT_TESTPAINTING_H_
