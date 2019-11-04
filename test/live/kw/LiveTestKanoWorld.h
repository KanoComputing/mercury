/**
 * \file LiveTestKanoWorld.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Tests for the Mercury::KW - Kano World - functions
 */


#ifndef TEST_LIVE_KW_LIVETESTKANOWORLD_H_
#define TEST_LIVE_KW_LIVETESTKANOWORLD_H_


#include <gtest/gtest.h>
#include <sys/stat.h>

#include <string>

#include "mercury/kw/kw.h"

#include "test/fixtures/kw_api.h"


namespace Mercury {
namespace KanoWorld {
namespace test {

TEST(kw, RenewTokenCorrect) {
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    std::string token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9." \
        "eyJleHAiOjE2MTk5MjMxNjIuMDE2LCJ1c2VyIjp7ImlkIjoiMDE3" \
        "MTA3Njg0NzQ4MTg5OTE0NzciLCJyb2xlcyI6W119fQ." \
        "Dhm3_2wDUyA5Tf3IANGfB8Y6DH2Nxzgl84fPSiURdJ8";

    EXPECT_EQ(kw.refresh_token(token, true), true);
}


TEST(kw, LoginCorrect) {
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    EXPECT_EQ(kw.login("testing_user", "kano12345experience", true), true);
}


TEST(kw, LoginCorrectAndLogout) {
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);
    EXPECT_EQ(kw.login("testing_user", "kano12345experience", true), true);
    EXPECT_EQ(kw.logout(true), true);
}


TEST(kw, LoginDataFilenameCreated) {
    KanoWorld kw(KanoWorldAPI::URL);
    struct stat st;

    EXPECT_GT(kw.data_filename.length(), 0);

    // Make sure the cache file is not here
    if (stat(kw.data_filename.c_str(), &st) != -1) {
        unlink(kw.data_filename.c_str());
    }

    EXPECT_EQ(stat(kw.data_filename.c_str(), &st), -1);
    EXPECT_EQ(kw.login("testing_user", "kano12345experience", true), true);
    EXPECT_NE(stat(kw.data_filename.c_str(), &st), -1);
}


TEST(kw, LoadCachedData) {
    KanoWorld kw(KanoWorldAPI::URL);
    struct stat st;

    EXPECT_NE(stat(kw.data_filename.c_str(), &st), -1);
    EXPECT_EQ(kw.load_data(), true);
    EXPECT_GT(kw.get_token().length(), 0);
    EXPECT_GT(kw.get_expiration_date().count(), 0);
}

TEST(kw, LoginGetCorrectData) {
    KanoWorld kw(KanoWorldAPI::URL);

    EXPECT_EQ(kw.login("testing_user", "kano12345experience", true), true);
    EXPECT_GT(kw.get_token().length(), 0);
    EXPECT_GT(kw.get_expiration_date().count(), 0);
}

}  // namespace test
}  // namespace KanoWorld
}  // namespace Mercury

#endif  // TEST_LIVE_KW_LIVETESTKANOWORLD_H_
