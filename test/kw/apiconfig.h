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

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <mercury/config.h>
#include <mercury/kw/APIConfig.h>
#include <mercury/kw/kw.h>
#include <test/fixtures/apiconfig/APIConfigFixture.h>

#include <string>


using Mercury::KanoWorld::APIConfig;
using Mercury::KanoWorld::KanoWorld;
using std::string;
using testing::Eq;


TEST_F(APIConfigFixture, NoOverrides)
{
    APIConfig config({BASE_CONFIG});

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
    APIConfig config({OVERRIDE_CONFIG, BASE_CONFIG});

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
    APIConfig config({OVERRIDE_CONFIG,
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
    APIConfig config;

    EXPECT_EQ(config.get_api_url(), "https://worldapi.kano.me");
}


/**
 * The config can be queried to see if a value is present
 */
TEST_F(APIConfigFixture, HasValues)
{
    APIConfig config({BASE_CONFIG});

    EXPECT_EQ(config.has("API_URL"), true);
    EXPECT_EQ(config.has("empty_key"), true);
    EXPECT_EQ(config.has("uknown_key"), false);
}


#endif  // TEST_KW_APICONFIG_H_
