/**
 * \file theme.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Tests for the Mercury::Theme functions
 *
 */

#ifndef TEST_UNIT_THEME_THEME_H_
#define TEST_UNIT_THEME_THEME_H_


#include <gtest/gtest.h>

#include "mercury/theme/theme.h"


namespace Mercury {
namespace Theme {
namespace test {

TEST(theme, SetWallpaper) {
    Mercury::Theme::Theme theme;
    EXPECT_EQ(theme.set_wallpaper("/test/path"), true);
}


TEST(theme, GetWallpaper) {
    Mercury::Theme::Theme theme;
    EXPECT_NE(theme.get_wallpaper(), "");
}

}  // namespace test
}  // namespace Theme
}  // namespace Mercury

#endif  // TEST_UNIT_THEME_THEME_H_
