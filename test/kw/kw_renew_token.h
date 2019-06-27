/**
 * \file kw_renew_token.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Tests for the Mercury::KW - Kano World - functions
 *
 */

#ifndef TEST_KW
#define TEST_KW

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <mercury/kw/kw.h>

using testing::Eq;

TEST(kw, renew_token)
{
    KanoWorld kw;
    EXPECT_EQ(kw.renew_token("1234567890"), true);
}

TEST(kw, is_logged_in)
{
    KanoWorld kw;
    EXPECT_EQ(kw.is_user_logged_in("username"), true);
}

TEST(kw, whoami)
{
    KanoWorld kw;
    EXPECT_EQ(kw.who_am_i(), true);
}

#endif  // TEST_KW
