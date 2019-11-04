/**
 * \file apiconfig.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Tests for the Mercury::KW - APIConfig - functions
 *
 */


#ifndef TEST_KW_APICONFIG_H_
#define TEST_KW_APICONFIG_H_

#include <gtest/gtest.h>

#include <string>

#include "mercury/config.h"
#include "mercury/kw/APIConfig.h"
#include "mercury/kw/kw.h"
#include "test/fixtures/apiconfig/APIConfigFixture.h"


namespace Mercury {
namespace KanoWorld {
namespace test {

TEST_F(APIConfigFixture, NoOverrides)
{
    Mercury::KanoWorld::APIConfig config({BASE_CONFIG});

    EXPECT_EQ(config.get_api_url(), "test_url");
    EXPECT_EQ(config.get_value<string>("no_override"),
              "base no_override value");
    EXPECT_EQ(config.get_value<string>("override"),
              "base override value");
    EXPECT_EQ(config.get_value<string>("missing_key"),
              "");
}


TEST_F(APIConfigFixture, OverrideValues)
{
    Mercury::KanoWorld::APIConfig config({OVERRIDE_CONFIG, BASE_CONFIG});

    EXPECT_EQ(config.get_api_url(), "test_url");
    EXPECT_EQ(config.get_value<string>("no_override"),
              "base no_override value");
    EXPECT_EQ(config.get_value<string>("override"),
              "overriden override value");
    EXPECT_EQ(config.get_value<string>("missing_key"),
              "");
}


TEST_F(APIConfigFixture, MalformedConfig)
{
    Mercury::KanoWorld::APIConfig config({OVERRIDE_CONFIG,
                      INVALID_CONFIG,
                      MISSING_CONFIG,
                      BASE_CONFIG});

    EXPECT_EQ(config.get_api_url(), "test_url");
    EXPECT_EQ(config.get_value<string>("no_override"),
              "base no_override value");
    EXPECT_EQ(config.get_value<string>("override"),
              "overriden override value");
    EXPECT_EQ(config.get_value<string>("missing_key"),
              "");
}


/**
 * The config should pull from the repo when building for debug
 */
TEST_F(APIConfigFixture, NoArgsConfig)
{
    Mercury::KanoWorld::APIConfig config;

    EXPECT_EQ(config.get_api_url(), "https://worldapi.kes.kano.me");
}


/**
 * The config can be queried to see if a value is present
 */
TEST_F(APIConfigFixture, HasValues)
{
    Mercury::KanoWorld::APIConfig config({BASE_CONFIG});

    EXPECT_EQ(config.has("API_URL"), true);
    EXPECT_EQ(config.has("empty_key"), true);
    EXPECT_EQ(config.has("uknown_key"), false);
}

}  // namespace test
}  // namespace KanoWorld
}  // namespace Mercury

#endif  // TEST_KW_APICONFIG_H_
