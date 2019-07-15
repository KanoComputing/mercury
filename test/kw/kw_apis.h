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
#include <mercury/_http/http_client.h>
#include <mercury/kw/kw.h>
#include <parson/parson.h>
#include <test/mocks/mock_http_client.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>


using testing::Eq;

/* TODO:
class KanoWorldMock: public KanoWorld {
    MOCK_METHOD1(refresh_token, bool(...));
};
*/


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
        "eyJleHAiOjE2MTk5MjMxNjIuMDE2LCJ1c2VyIjp7ImlkIjoiMDE3MTA3Njg0NzQ4MTg5OTE0NzciLCJyb2xlcyI6W119fQ." \
        "Dhm3_2wDUyA5Tf3IANGfB8Y6DH2Nxzgl84fPSiURdJ8";

    EXPECT_EQ(kw.refresh_token(token, true), true);
}

TEST(kw, login_correct)
{
    KanoWorld kw;
    EXPECT_EQ(kw.login("testing_user", "kano12345experience", true), true);
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
    EXPECT_EQ(kw.am_i_logged_in(), false);
}

TEST(kw, whoami)
{
    KanoWorld kw;
    EXPECT_EQ(kw.whoami(), "");
}


#endif  // TEST_KW_KW_APIS_H_
