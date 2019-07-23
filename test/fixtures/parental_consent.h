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
#include <parson.h>
#include <test/fixtures/kw_api.h>

#include <memory>
#include <string>
#include <tuple>


class LoggedInKW : public ::testing::Test, public KWUtils {
 protected:
    void SetUp() override {
        this->login();
    }
};


class ParentalConsentCache : public LoggedInKW {};


class APIResponse : public ::testing::TestWithParam<
    std::tuple<bool, std::string>>, public KWUtils {
 public:
    virtual void SetUp() {
        this->login();

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
    public ::testing::TestWithParam<HTTPClientError>, public KWUtils {
 public:
    virtual void SetUp() {
        this->login();
    }
};


#endif  // TEST_FIXTURES_PARENTAL_CONSENT_H_
