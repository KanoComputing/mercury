/**
 * \file kw_persistence.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Tests for the Mercury::KW - Kano World - functions
 *
 */

#ifndef TEST_KW_KW_PERSISTENCE_H_
#define TEST_KW_KW_PERSISTENCE_H_


#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <mercury/kw/kw.h>

#include <sys/stat.h>

using Mercury::KanoWorld::KanoWorld;
using testing::Eq;


TEST(kw, LoginDataFilenameCreated)
{
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

TEST(kw, LoadCachedData)
{
    KanoWorld kw(KanoWorldAPI::URL);
    struct stat st;

    EXPECT_NE(stat(kw.data_filename.c_str(), &st), -1);
    EXPECT_EQ(kw.load_data(), true);
    EXPECT_GT(kw.get_token().length(), 0);
    EXPECT_GT(kw.get_expiration_date().length(), 0);
}


#endif  // TEST_KW_KW_PERSISTENCE_H_
