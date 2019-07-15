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
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <mercury/_http/exceptions.h>
#include <mercury/_http/http_client.h>
#include <mercury/kw/kw.h>
#include <parson.h>
#include <test/fixtures/parental_consent.h>
#include <test/mocks/mock_http_client.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>


using testing::Eq;


TEST(kw, renew_token_malformed)
{
    KanoWorld kw;
    EXPECT_EQ(kw.refresh_token("1234567890", true), false);
}

TEST(kw, renew_token_empty)
{
    KanoWorld kw;
    EXPECT_EQ(kw.refresh_token("", true), false);
}

TEST(kw, renew_token_correct)
{
    KanoWorld kw;
    string token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9." \
        "eyJleHAiOjE2MTk5MjMxNjIuMDE2LCJ1c2VyIjp7ImlkIjoiMDE3" \
        "MTA3Njg0NzQ4MTg5OTE0NzciLCJyb2xlcyI6W119fQ." \
        "Dhm3_2wDUyA5Tf3IANGfB8Y6DH2Nxzgl84fPSiURdJ8";

    EXPECT_EQ(kw.refresh_token(token, true), true);
}

TEST(kw, login_correct)
{
    KanoWorld kw;
    EXPECT_EQ(kw.login("testing_user", "kano12345experience", true), true);
}

TEST(kw, login_correct_and_logout)
{
    KanoWorld kw;
    EXPECT_EQ(kw.login("testing_user", "kano12345experience", true), true);
    EXPECT_EQ(kw.logout(true), true);
}

TEST(kw, login_invalid_credentials)
{
    KanoWorld kw;
    EXPECT_EQ(kw.login("nonexisting", "nopassword", true), false);
}


TEST(kw, login_empty_username)
{
    KanoWorld kw;
    EXPECT_EQ(kw.login("", "nopassword", true), false);
}

TEST(kw, login_empty_password)
{
    KanoWorld kw;
    EXPECT_EQ(kw.login("yetanotherfakeuser", "", true), false);
}

TEST(kw, login_empty_credentials)
{
    KanoWorld kw;
    EXPECT_EQ(kw.login("", "", true), false);
}

TEST(kw, refresh_headers)
{
    KanoWorld kw;
    string header = kw.get_refresh_header("12345");
    EXPECT_EQ(header, "Authorization: Bearer 12345");
}

TEST(kw, get_hostname)
{
    // TODO: API not implemented yet
    KanoWorld kw;
    string hostname = kw.get_hostname("data/config_sample1.conf");
    EXPECT_EQ(hostname, "");
}

TEST(kw, is_logged_in)
{
    KanoWorld kw;
    EXPECT_EQ(kw.is_logged_in(false), false);
}

TEST(kw, whoami)
{
    KanoWorld kw;
    EXPECT_EQ(kw.whoami(), "");
}


INSTANTIATE_TEST_CASE_P(
    ParentalConsentAPIResponses,
    ParentalConsentAPI,
    ::testing::Values(
        std::make_tuple(true, "parental_consent.json"),
        std::make_tuple(false, "no_parental_consent.json"),
        std::make_tuple(false, "invalid_parental_consent.json")
    )
);


TEST_P(ParentalConsentAPI, test_account_verification)
{
    auto client = std::make_shared<MockHTTPClient>();
    KanoWorld kw(client);
    std::string auth_token = kw.get_token();

    EXPECT_CALL(
        *client,
        GET_impl(
            WORLDAPI_ME_ENDPOINT,
            std::map<std::string, std::string>{
                { "Authorization", "Bearer " + auth_token }
            }))
        .Times(1)
        .WillRepeatedly(testing::Return(this->json_data));

    kw.clear_account_verified_cache();
    EXPECT_EQ(kw.is_account_verified(), this->expected);
}


INSTANTIATE_TEST_CASE_P(
    ParentalConsentExceptions,
    ParentalConsentException,
    ::testing::Values(
        SessionInitError("Init error"),
        HTTPRequestFailedError(400, "Request error")
    )
);


TEST_P(ParentalConsentException, test_account_verification_exception)
{
    auto client = std::make_shared<MockHTTPClient>();
    KanoWorld kw(client);
    std::string auth_token = kw.get_token();

    EXPECT_CALL(
        *client,
        GET_impl(
            WORLDAPI_ME_ENDPOINT,
            std::map<std::string, std::string>{
                { "Authorization", "Bearer " + auth_token }
            }))
        .Times(1)
        .WillRepeatedly(
            testing::Throw(this->GetParam()));

    kw.clear_account_verified_cache();
    EXPECT_EQ(kw.is_account_verified(), false);
}


TEST(ParentalConsentCache, test_verification_cache) {
    auto client = std::make_shared<MockHTTPClient>();
    KanoWorld kw(client);
    std::string auth_token = kw.get_token();

    std::shared_ptr<JSON_Value> fail = load_response(
        "no_parental_consent.json");
    std::shared_ptr<JSON_Value> success = load_response(
        "parental_consent.json");

    EXPECT_CALL(
        *client,
        GET_impl(
            WORLDAPI_ME_ENDPOINT,
            std::map<std::string, std::string>{
                { "Authorization", "Bearer " + auth_token }
            }))
        .Times(2)
        .WillOnce(testing::Return(fail))
        .WillOnce(testing::Return(success))
        .WillOnce(testing::Throw(SessionInitError("InitError")))
        .WillRepeatedly(testing::Return(success));

    kw.clear_account_verified_cache();
    EXPECT_EQ(kw.is_account_verified(), false);
    EXPECT_EQ(kw.is_account_verified(), true);
    EXPECT_EQ(kw.is_account_verified(), true);
    EXPECT_EQ(kw.is_account_verified(), true);
}


TEST(ParentalConsentCache, test_verification_cache_disabled) {
    auto client = std::make_shared<MockHTTPClient>();
    KanoWorld kw(client);
    std::string auth_token = kw.get_token();

    std::shared_ptr<JSON_Value> fail = load_response(
        "no_parental_consent.json");
    std::shared_ptr<JSON_Value> success = load_response(
        "parental_consent.json");

    EXPECT_CALL(
        *client,
        GET_impl(
            WORLDAPI_ME_ENDPOINT,
            std::map<std::string, std::string>{
                { "Authorization", "Bearer " + auth_token }
            }))
        .Times(5)
        .WillOnce(testing::Return(fail))
        .WillOnce(testing::Return(success))
        .WillOnce(testing::Throw(SessionInitError("InitError")))
        .WillRepeatedly(testing::Return(success));

    kw.clear_account_verified_cache();

    EXPECT_EQ(kw.is_account_verified(false), false);
    EXPECT_EQ(kw.is_account_verified(false), true);
    EXPECT_EQ(kw.is_account_verified(false), false);
    EXPECT_EQ(kw.is_account_verified(false), true);
    EXPECT_EQ(kw.is_account_verified(false), true);
}


TEST(ParentalConsentCache, test_verification_mix_cache) {
    auto client = std::make_shared<MockHTTPClient>();
    KanoWorld kw(client);
    std::string auth_token = kw.get_token();

    std::shared_ptr<JSON_Value> fail = load_response(
        "no_parental_consent.json");
    std::shared_ptr<JSON_Value> success = load_response(
        "parental_consent.json");

    EXPECT_CALL(
        *client,
        GET_impl(
            WORLDAPI_ME_ENDPOINT,
            std::map<std::string, std::string>{
                { "Authorization", "Bearer " + auth_token }
            }))
        .Times(3)
        .WillOnce(testing::Return(fail))
        .WillOnce(testing::Return(success))
        .WillOnce(testing::Throw(SessionInitError("InitError")))
        .WillOnce(testing::Return(success))
        .WillOnce(testing::Return(fail));

    kw.clear_account_verified_cache();
    EXPECT_EQ(kw.is_account_verified(true), false);
    EXPECT_EQ(kw.is_account_verified(true), true);
    EXPECT_EQ(kw.is_account_verified(true), true);
    EXPECT_EQ(kw.is_account_verified(true), true);
    EXPECT_EQ(kw.is_account_verified(false), false);
}


#endif  // TEST_KW_KW_APIS_H_
