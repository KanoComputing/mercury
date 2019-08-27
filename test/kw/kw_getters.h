/**
 * \file kw_getters.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Tests for the Mercury::KW getters
 *
 */

#ifndef TEST_KW_KW_GETTERS_H_
#define TEST_KW_KW_GETTERS_H_

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <mercury/kw/kw.h>

#include <limits>
#include <random>
#include <string>


using Mercury::KanoWorld::KanoWorld;
using testing::Eq;



int get_random_number(int max = std::numeric_limits<int>::max()) {
    static std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(0, max);

    return distribution(generator);
}


TEST(kw, SetUsernameWithSave)
{
    const std::string username = std::string("some-test-username-")
        + std::to_string(get_random_number());

    KanoWorld kw1;

    // Sanity check
    EXPECT_NE(kw1.get_username(), username);

    kw1.set_username(username, true);

    EXPECT_EQ(kw1.get_username(), username);

    // Refresh object

    KanoWorld kw2;
    EXPECT_EQ(kw2.get_username(), username);
}


#endif  // TEST_KW_KW_GETTERS_H_
