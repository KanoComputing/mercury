/**
 * \file kw_server_data.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Tests for the Mercury::KW - Kano World - functions
 *
 */

#ifndef TEST_UNIT_KW_KW_SERVER_DATA_H_
#define TEST_UNIT_KW_KW_SERVER_DATA_H_


#include <gtest/gtest.h>

#include "mercury/kw/kw.h"


namespace Mercury {
namespace KanoWorld {
namespace test {

TEST(kw, LoginGetNoData)
{
    Mercury::KanoWorld::KanoWorld kw(KanoWorldAPI::URL);

    EXPECT_EQ(kw.login("nonexisting", "badpassword", true), false);
    EXPECT_EQ(kw.get_token().length(), 0);
    EXPECT_EQ(kw.get_expiration_date().count(), 0);
}

}  // namespace test
}  // namespace KanoWorld
}  // namespace Mercury

#endif  // TEST_UNIT_KW_KW_SERVER_DATA_H_
