/**
 * \file TestOnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_KES_MOMA_PICKS_CLIENT_TESTONLINELOADER_H_
#define TEST_KES_MOMA_PICKS_CLIENT_TESTONLINELOADER_H_


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <parson.h>

#include <memory>
#include <string>

#include "kes_moma_picks_client/internal/Exceptions.h"
#include "kes_moma_picks_client/internal/IOnlineLoader.h"
#include "kes_moma_picks_client/internal/IPaintingLoader.h"
#include "kes_moma_picks_client/internal/OnlineLoader.h"

#include "mercury/http/exceptions.h"
#include "mercury/http/http_client_interface.h"

#include "test/fixtures/kes_mp_cli/KesMpResponsesFixture.h"
#include "test/fixtures/kes_mp_cli/KesMpValidResponsesFixture.h"
#include "test/helpers/TemplateTests.h"
#include "test/matchers/JsonMatchers.h"
#include "test/mocks/kes_mp_cli/MockPainting.h"
#include "test/mocks/kes_mp_cli/MockPaintingFactory.h"
#include "test/mocks/mock_http_client.h"


namespace KESMPC {
namespace test {


/**
 * Check that users of the class can use it through a pointer of the
 * IOnlineLoader interface.
 */
TEST(TestOnlineLoader, IsAnIOnlineLoader) {
    Mercury::test::testBaseIsAnInterface<
        KESMPC::internal::OnlineLoader, KESMPC::internal::IOnlineLoader>("");
}

/**
 * Check that users of the class can use it through a pointer of the
 * IPaintingLoader interface.
 */
TEST(TestOnlineLoader, IsAnIPaintingLoader) {
    Mercury::test::testBaseIsAnInterface<
        KESMPC::internal::OnlineLoader, KESMPC::internal::IPaintingLoader>("");
}

INSTANTIATE_TEST_CASE_P(
    Parameterised,
    KesMpValidResponsesFixture,
    ::testing::Values("feed1", "feed2", "feed3"));

/**
 * Check that OnlineLoader.getPaintings() calls HTTPClient.GET()
 */
TEST_P(KesMpValidResponsesFixture, GetPaintingsCallsHTTPClientGET) {
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();
    auto mockPaintingFactory = std::make_shared<MockPaintingFactory>();
    auto mockPainting = std::make_shared<MockPainting>();

    KESMPC::internal::OnlineLoader onlineLoader(
        "/tmp/kes-mp-cli/test", mockHttpClient, mockPaintingFactory);

    // Ensuring the remainder of the function doesn't throw Exceptions by
    // returning a valid KES response from the HTTPClient.GET().
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESMPC::internal::OnlineLoader::KES_MP_URL, ::testing::_))
        .WillByDefault(::testing::Return(this->response));

    // Return the same mock Painting each for each painting data
    // from the response.
    ON_CALL(*mockPaintingFactory, create)
        .WillByDefault(::testing::Return(mockPainting));

    // Ignore the call to Painting.initialise().
    ON_CALL(*mockPainting, initialise)
        .WillByDefault(::testing::Return(true));

    // Ignore the call to Painting.download().
    ON_CALL(*mockPainting, download)
        .WillByDefault(::testing::Return(true));

    EXPECT_CALL(
        *mockHttpClient,
        GET_impl(KESMPC::internal::OnlineLoader::KES_MP_URL, ::testing::_))
        .Times(1);

    onlineLoader.getPaintings();
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getPaintings()
 * calls for each painting data PaintingFactory.create().
 */
TEST_P(KesMpValidResponsesFixture, GetPaintingsCallsPaintingFactoryCreate) {
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();
    auto mockPaintingFactory = std::make_shared<MockPaintingFactory>();
    auto mockPainting = std::make_shared<MockPainting>();

    KESMPC::internal::OnlineLoader onlineLoader(
        "/tmp/kes-mp-cli/test", mockHttpClient, mockPaintingFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESMPC::internal::OnlineLoader::KES_MP_URL, ::testing::_))
        .WillByDefault(::testing::Return(this->response));

    // Return the same mock Painting each for each painting data
    // from the response.
    ON_CALL(*mockPaintingFactory, create)
        .WillByDefault(::testing::Return(mockPainting));

    // Ignore the call to Painting.initialise().
    ON_CALL(*mockPainting, initialise)
        .WillByDefault(::testing::Return(true));

    // Ignore the call to Painting.download().
    ON_CALL(*mockPainting, download)
        .WillByDefault(::testing::Return(true));

    EXPECT_CALL(*mockPaintingFactory, create)
        .Times(this->paintingCount);

    onlineLoader.getPaintings();
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getPaintings()
 * calls for each painting data Painting.initialise() with the expected JSON.
 */
TEST_P(KesMpValidResponsesFixture, GetPaintingsCallsPaintingInitialise) {
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();
    auto mockPaintingFactory = std::make_shared<MockPaintingFactory>();
    auto mockPainting = std::make_shared<MockPainting>();

    KESMPC::internal::OnlineLoader onlineLoader(
        "/tmp/kes-mp-cli/test", mockHttpClient, mockPaintingFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESMPC::internal::OnlineLoader::KES_MP_URL, ::testing::_))
        .WillByDefault(::testing::Return(this->response));

    // Return the same mock Painting each for each painting data
    // from the response.
    ON_CALL(*mockPaintingFactory, create)
        .WillByDefault(::testing::Return(mockPainting));

    // Ignore the call to Painting.initialise().
    ON_CALL(*mockPainting, initialise)
        .WillByDefault(::testing::Return(true));

    // Ignore the call to Painting.download().
    ON_CALL(*mockPainting, download)
        .WillByDefault(::testing::Return(true));

    JSON_Array* paintingsData = json_object_get_array(
        json_value_get_object(this->response.get()), "paintings");

    JSON_Value* paintingData;

    // Expect that Painting.initialise() is called with each individual
    // paintingData from the KES response.
    for (int i = 0; i < json_array_get_count(paintingsData); i++) {
        paintingData = json_array_get_value(paintingsData, i);

        EXPECT_CALL(*mockPainting, initialise(JsonEq(paintingData)))
            .Times(1);
    }

    onlineLoader.getPaintings();
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getPaintings()
 * calls for each painting data Painting.download() with the given cacheDir.
 */
TEST_P(KesMpValidResponsesFixture, GetPaintingsCallsPaintingDownload) {
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();
    auto mockPaintingFactory = std::make_shared<MockPaintingFactory>();
    auto mockPainting = std::make_shared<MockPainting>();

    const std::string cacheDir = "/tmp/kes-mp-cli/test";
    KESMPC::internal::OnlineLoader onlineLoader(
        cacheDir, mockHttpClient, mockPaintingFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESMPC::internal::OnlineLoader::KES_MP_URL, ::testing::_))
        .WillByDefault(::testing::Return(this->response));

    // Return the same mock Painting each for each painting data
    // from the response.
    ON_CALL(*mockPaintingFactory, create)
        .WillByDefault(::testing::Return(mockPainting));

    // Ignore the call to Painting.initialise().
    ON_CALL(*mockPainting, initialise)
        .WillByDefault(::testing::Return(true));

    // Ignore the call to Painting.download().
    ON_CALL(*mockPainting, download)
        .WillByDefault(::testing::Return(true));

    EXPECT_CALL(*mockPainting, download(::testing::StrEq(cacheDir)))
        .Times(this->paintingCount);

    onlineLoader.getPaintings();
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getPaintings()
 * throws a BrokenContractsException when JSON does not contain "paintings"
 * array.
 */
TEST_F(
    KesMpResponsesFixture,
    GetPaintingsThrowsBrokenContractsExceptionWhenMissingPaintingsField) {
    // NOLINT
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();

    const std::string cacheDir = "/tmp/kes-mp-cli/test";
    KESMPC::internal::OnlineLoader onlineLoader(cacheDir, mockHttpClient);

    // Set the HTTPClient.GET to return a given malformed KES response.
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESMPC::internal::OnlineLoader::KES_MP_URL, ::testing::_))
        .WillByDefault(::testing::Return(responses["invalid_feed1"]));

    ASSERT_THROW(
        onlineLoader.getPaintings(),
        KESMPC::internal::BrokenContractsException);
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getPaintings()
 * throws a BrokenContractsException when Painting.initialise() fails.
 */
TEST_F(
    KesMpResponsesFixture,
    GetPaintingsThrowsBrokenContractsExceptionWhenPaintingInitialiseFails) {
    // NOLINT
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();
    auto mockPaintingFactory = std::make_shared<MockPaintingFactory>();
    auto mockPainting = std::make_shared<MockPainting>();

    const std::string cacheDir = "/tmp/kes-mp-cli/test";
    KESMPC::internal::OnlineLoader onlineLoader(
        cacheDir, mockHttpClient, mockPaintingFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESMPC::internal::OnlineLoader::KES_MP_URL, ::testing::_))
        .WillByDefault(::testing::Return(responses["feed1"]));

    // Return the same mock Painting each for each painting data
    // from the response.
    ON_CALL(*mockPaintingFactory, create)
        .WillByDefault(::testing::Return(mockPainting));

    // Set the mock Painting.initialise() to return false for failure.
    ON_CALL(*mockPainting, initialise)
        .WillByDefault(::testing::Return(false));

    ASSERT_THROW(
        onlineLoader.getPaintings(),
        KESMPC::internal::BrokenContractsException);
}

/**
 * Check that for a given HTTPClient.GET() response OnlineLoader.getPaintings()
 * throws a DownloadError when Painting.download() fails.
 */
TEST_F(
    KesMpResponsesFixture,
    GetPaintingsThrowsDownloadErrorWhenPaintingDownloadFails) {
    // NOLINT
    auto mockHttpClient =
        std::make_shared<Mercury::HTTP::test::MockHTTPClient>();
    auto mockPaintingFactory = std::make_shared<MockPaintingFactory>();
    auto mockPainting = std::make_shared<MockPainting>();

    const std::string cacheDir = "/tmp/kes-mp-cli/test";
    KESMPC::internal::OnlineLoader onlineLoader(
        cacheDir, mockHttpClient, mockPaintingFactory);

    // Set the HTTPClient.GET to return a given valid KES response.
    ON_CALL(
        *mockHttpClient,
        GET_impl(KESMPC::internal::OnlineLoader::KES_MP_URL, ::testing::_))
        .WillByDefault(::testing::Return(responses["feed1"]));

    // Return the same mock Painting each for each painting data
    // from the response.
    ON_CALL(*mockPaintingFactory, create)
        .WillByDefault(::testing::Return(mockPainting));

    // Ignore the call to Painting.initialise().
    ON_CALL(*mockPainting, initialise)
        .WillByDefault(::testing::Return(true));

    // Set the mock Painting.download() to return false for failure.
    ON_CALL(*mockPainting, download)
        .WillByDefault(::testing::Return(false));

    ASSERT_THROW(onlineLoader.getPaintings(), Mercury::HTTP::DownloadError);
}


}  // namespace test
}  // namespace KESMPC


#endif  // TEST_KES_MOMA_PICKS_CLIENT_TESTONLINELOADER_H_
