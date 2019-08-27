/**
 * \file KesDltResponsesFixture.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_FIXTURES_APICONFIG_APICONFIGFIXTURE_H_
#define TEST_FIXTURES_APICONFIG_APICONFIGFIXTURE_H_

#include <gtest/gtest.h>
#include <string>

using ::testing::Test;

class APIConfigFixture : public Test {
 public:
    static std::string CONFIG_DIR;
    static std::string BASE_CONFIG;
    static std::string OVERRIDE_CONFIG;
    static std::string INVALID_CONFIG;
    static std::string MISSING_CONFIG;
};


std::string APIConfigFixture::CONFIG_DIR =  // NOLINT
    std::string(CMAKE_PROJ_BASE_DIR) + "/test/fixtures/apiconfig/data";
std::string APIConfigFixture::BASE_CONFIG =  // NOLINT
    APIConfigFixture::CONFIG_DIR + "/base.yaml";
std::string APIConfigFixture::OVERRIDE_CONFIG =  // NOLINT
    APIConfigFixture::CONFIG_DIR + "/override.yaml";
std::string APIConfigFixture::INVALID_CONFIG =  // NOLINT
    APIConfigFixture::CONFIG_DIR + "/invalid.yaml";
std::string APIConfigFixture::MISSING_CONFIG =  // NOLINT
    APIConfigFixture::CONFIG_DIR + "/file_doesnt_exist.yaml";


#endif  // TEST_FIXTURES_APICONFIG_APICONFIGFIXTURE_H_
