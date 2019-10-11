/**
 * \file kw_apis.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Tests for the Mercury::KW - Kano World - functions
 *
 */

#ifndef TEST_KW_KW_APIS_H_
#define TEST_KW_KW_APIS_H_


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <parson.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "mercury/http/exceptions.h"
#include "mercury/http/http_client.h"
#include "mercury/kw/kw.h"

#include "test/fixtures/kw_api.h"
#include "test/fixtures/kw_utils_mixin.h"
#include "test/fixtures/parental_consent.h"
#include "test/mocks/mock_http_client.h"
#include "test/mocks/MockEnvironment.h"


namespace Mercury {
namespace KanoWorld {
namespace test {

/**
 * Ensure that the API url is correctly set when no argument is passed to the
 * constructor
 */
TEST(kw, DefaultConstructor) {
    Mercury::KanoWorld::KanoWorld kw;

    EXPECT_EQ(kw.api_url, "https://worldapi.kes.kano.me");
}

/**
 * Check that KanoWorld constructor calls Environment.getenv("HOME").
 */
TEST(kw, ConstructorCallsEnvironmentGetEnvWithHome) {
    auto mockEnvironment = std::make_shared<Mercury::Utils::test::MockEnvironment>();  // NOLINT

    ON_CALL(*mockEnvironment, get)
        .WillByDefault(::testing::Return(""));

    EXPECT_CALL(*mockEnvironment, get("HOME"))
        .Times(1);

    Mercury::KanoWorld::KanoWorld kw("", nullptr, mockEnvironment);
}

/**
 * Ensure that the API url is correctly set when an argument is passed to the
 * constructor
 */
TEST(kw, URLConstructor) {
    std::string url = "sometesturl";
    Mercury::KanoWorld::KanoWorld kw(url);

    EXPECT_EQ(kw.api_url, url);
}

TEST(kw, RenewTokenMalformed)
{
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    EXPECT_EQ(kw.refresh_token("1234567890", true), false);
}

TEST(kw, RenewTokenEmpty)
{
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    EXPECT_EQ(kw.refresh_token("", true), false);
}

TEST(kw, RenewTokenCorrect)
{
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    std::string token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9." \
        "eyJleHAiOjE2MTk5MjMxNjIuMDE2LCJ1c2VyIjp7ImlkIjoiMDE3" \
        "MTA3Njg0NzQ4MTg5OTE0NzciLCJyb2xlcyI6W119fQ." \
        "Dhm3_2wDUyA5Tf3IANGfB8Y6DH2Nxzgl84fPSiURdJ8";

    EXPECT_EQ(kw.refresh_token(token, true), true);
}

TEST(kw, LoginCorrect)
{
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    EXPECT_EQ(kw.login("testing_user", "kano12345experience", true), true);
}

TEST(kw, LoginCorrectAndLogout)
{
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    EXPECT_EQ(kw.login("testing_user", "kano12345experience", true), true);
    EXPECT_EQ(kw.logout(true), true);
}

TEST(kw, LoginInvalidCredentials)
{
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    EXPECT_EQ(kw.login("nonexisting", "nopassword", true), false);
}


TEST(kw, LoginEmptyUsername)
{
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    EXPECT_EQ(kw.login("", "nopassword", true), false);
}

TEST(kw, LoginEmptyPassword)
{
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    EXPECT_EQ(kw.login("yetanotherfakeuser", "", true), false);
}

TEST(kw, LoginEmptyCredentials)
{
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    EXPECT_EQ(kw.login("", "", true), false);
}

TEST(kw, RefreshHeaders)
{
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    std::string header = kw.get_refresh_header("12345");
    EXPECT_EQ(header, "Authorization: Bearer 12345");
}

TEST(kw, GetHostname)
{
    // TODO: API not implemented yet
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    std::string hostname = kw.get_hostname("data/config_sample1.conf");
    EXPECT_EQ(hostname, "");
}

TEST(kw, IsLoggedIn)
{
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    EXPECT_EQ(kw.is_logged_in(false), false);
}

TEST(kw, Whoami)
{
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    EXPECT_EQ(kw.whoami(), "");
}


/**
 * KanoWorld::refresh_account_verified() should hit the API to determine if the
 * account is verified and return the value returned by the API.
 */
INSTANTIATE_TEST_CASE_P(
    ParentalConsentAPIResponses,
    ParentalConsentAPI,
    ::testing::Values(
        std::make_tuple(true, "users/me/parental_consent.json"),
        std::make_tuple(false, "users/me/no_parental_consent.json"),
        std::make_tuple(false, "users/me/invalid_parental_consent.json")
    )
);
TEST_P(ParentalConsentAPI, TestAccountVerification)
{
    std::string auth_token = kw.get_token();

    EXPECT_CALL(
        *client,
        GET_impl(
            KanoWorldAPI::ME_ENDPOINT,
            std::map<std::string, std::string>{
                { "Authorization", "Bearer " + auth_token }
            }))
        .Times(1)
        .WillRepeatedly(testing::Return(this->json_data));

    kw.set_account_verified(false, true);;
    EXPECT_EQ(kw.refresh_account_verified(), this->expected);
}


/* TODO: Implement tests for HTTP class with a timeout */


/**
 * KanoWorld::refresh_account_verified() should return false when the
 * HTTPClient throws an exception (for example, when there is a server error)
 */
INSTANTIATE_TEST_CASE_P(
    ParentalConsentExceptions,
    ParentalConsentException,
    ::testing::Values(
        Mercury::HTTP::SessionInitError("Init error"),
        Mercury::HTTP::HTTPRequestFailedError(400, "Request error")
    )
);
TEST_P(ParentalConsentException, TestAccountVerificationException)
{
    std::string auth_token = kw.get_token();

    EXPECT_CALL(
        *client,
        GET_impl(
            KanoWorldAPI::ME_ENDPOINT,
            std::map<std::string, std::string>{
                { "Authorization", "Bearer " + auth_token }
            }))
        .Times(1)
        .WillRepeatedly(
            testing::Throw(this->GetParam()));

    kw.set_account_verified(false, true);;
    EXPECT_EQ(kw.refresh_account_verified(), false);
}


/**
 * KanoWorld::refresh_account_verified() should start to use the cache when it
 * has seen that the API has given it verification when the sticky parameter is
 * set.
 */
TEST_F(ParentalConsentCache, TestVerificationCache) {
    std::string auth_token = kw.get_token();

    std::shared_ptr<JSON_Value> fail = load_response(
        "users/me/no_parental_consent.json");
    std::shared_ptr<JSON_Value> success = load_response(
        "users/me/parental_consent.json");

    EXPECT_CALL(
        *this->client,
        GET_impl(
            KanoWorldAPI::ME_ENDPOINT,
            std::map<std::string, std::string>{
                { "Authorization", "Bearer " + auth_token }
            }))
        .Times(2)
        .WillOnce(testing::Return(fail))
        .WillOnce(testing::Return(success))
        .WillOnce(testing::Throw(Mercury::HTTP::SessionInitError("InitError")))
        .WillRepeatedly(testing::Return(success));

    kw.set_account_verified(false, true);;
    EXPECT_EQ(kw.refresh_account_verified(true), false);
    EXPECT_EQ(kw.refresh_account_verified(true), true);
    EXPECT_EQ(kw.refresh_account_verified(true), true);
    EXPECT_EQ(kw.refresh_account_verified(true), true);
}


/**
 * KanoWorld::refresh_account_verified() should never use the cache when the
 * sticky parameter is set.
 */
TEST_F(ParentalConsentCache, TestVerificationCacheDisabled) {
    std::string auth_token = kw.get_token();

    std::shared_ptr<JSON_Value> fail = load_response(
        "users/me/no_parental_consent.json");
    std::shared_ptr<JSON_Value> success = load_response(
        "users/me/parental_consent.json");

    EXPECT_CALL(
        *this->client,
        GET_impl(
            KanoWorldAPI::ME_ENDPOINT,
            std::map<std::string, std::string>{
                { "Authorization", "Bearer " + auth_token }
            }))
        .Times(5)
        .WillOnce(testing::Return(fail))
        .WillOnce(testing::Return(success))
        .WillOnce(testing::Throw(Mercury::HTTP::SessionInitError("InitError")))
        .WillRepeatedly(testing::Return(success));

    kw.set_account_verified(false, true);;

    EXPECT_EQ(kw.refresh_account_verified(false), false);
    EXPECT_EQ(kw.refresh_account_verified(false), true);
    EXPECT_EQ(kw.refresh_account_verified(false), false);
    EXPECT_EQ(kw.refresh_account_verified(false), true);
    EXPECT_EQ(kw.refresh_account_verified(false), true);
}


/**
 * KanoWorld::refresh_account_verified() should start to use the cache when it
 * has seen that the API has given it verification when the sticky parameter is
 * set but revert to querying the API directly when called after with this
 * value removed.
 */
TEST_F(ParentalConsentCache, TestVerificationMixCache) {
    std::shared_ptr<JSON_Value> fail = load_response(
        "users/me/no_parental_consent.json");
    std::shared_ptr<JSON_Value> success = load_response(
        "users/me/parental_consent.json");

    std::string auth_token = kw.get_token();

    EXPECT_CALL(
        *this->client,
        GET_impl(
            KanoWorldAPI::ME_ENDPOINT,
            std::map<std::string, std::string>{
                { "Authorization", "Bearer " + auth_token }
            }))
        .Times(3)
        .WillOnce(testing::Return(fail))
        .WillOnce(testing::Return(success))
        .WillOnce(testing::Throw(Mercury::HTTP::SessionInitError("InitError")))
        .WillOnce(testing::Return(success))
        .WillOnce(testing::Return(fail));

    kw.set_account_verified(false, true);;
    EXPECT_EQ(kw.refresh_account_verified(true), false);
    EXPECT_EQ(kw.refresh_account_verified(true), true);
    EXPECT_EQ(kw.refresh_account_verified(true), true);
    EXPECT_EQ(kw.refresh_account_verified(true), true);
    EXPECT_EQ(kw.refresh_account_verified(false), false);
}


}  // namespace test
}  // namespace KanoWorld
}  // namespace Mercury

#endif  // TEST_KW_KW_APIS_H_
