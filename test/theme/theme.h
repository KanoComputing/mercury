/**
 * \file theme.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Tests for the Mercury::Theme functions
 *
 */

#ifndef TEST_THEME_THEME_H_
#define TEST_THEME_THEME_H_


#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <mercury/theme/theme.h>


using testing::Eq;


TEST(sample_tests, example_1)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
    Theme theme;
    theme.set_wallpaper("/test/path");
}

TEST(sample_tests, example_2)
{
    EXPECT_EQ(1, 0);
    ASSERT_THAT(0, Eq(0));
    Theme theme;
    theme.set_wallpaper("/test/path");
}


#endif  // TEST_THEME_THEME_H_
