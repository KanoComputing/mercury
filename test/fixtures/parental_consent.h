/**
 * \file parental_consent.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Fixtures for parental consent
 *
 */


#ifndef TEST_FIXTURES_PARENTAL_CONSENT_H_
#define TEST_FIXTURES_PARENTAL_CONSENT_H_


#include <gtest/gtest.h>
#include <mercury/_http/exceptions.h>
#include <mercury/config.h>
#include <parson/parson.h>

#include <memory>
#include <string>
#include <tuple>


const char WORLDAPI_ME_ENDPOINT[] = "https://worldapi.kano.me/users/me";


std::shared_ptr<JSON_Value> load_response(const std::string& filename) {
    const std::string data_dir = std::string(CMAKE_PROJ_BASE_DIR) +
        "/test/fixtures/data/api_me_response/";
    return std::shared_ptr<JSON_Value>(
        json_parse_file((data_dir + filename).c_str()),
        json_value_free);
}


class APIResponse : public ::testing::TestWithParam<
    std::tuple<bool, std::string>> {
 public:
    virtual void SetUp() {
        auto params = GetParam();
        this->expected = std::get<0>(params);
        this->json_data = load_response(std::get<1>(params));
    }

    virtual void TearDown() {}
 protected:
    bool expected;
    std::shared_ptr<JSON_Value> json_data;
};


class ParentalConsentAPI : public APIResponse {};


class ParentalConsentException :
    public ::testing::TestWithParam<HTTPClientError> {};


#endif  // TEST_FIXTURES_PARENTAL_CONSENT_H_
