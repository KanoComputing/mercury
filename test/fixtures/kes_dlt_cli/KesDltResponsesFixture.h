/**
 * \file KesDltResponsesFixture.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_FIXTURES_KES_DLT_CLI_KESDLTRESPONSESFIXTURE_H_
#define TEST_FIXTURES_KES_DLT_CLI_KESDLTRESPONSESFIXTURE_H_


#include <gtest/gtest.h>
#include <parson.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "mercury/config.h"

using std::cerr;
using std::endl;
using std::map;
using std::shared_ptr;
using std::string;

using ::testing::Test;


class KesDltResponsesFixture : public Test {
 public:
    static void SetUpTestCase() {
        responses["feed1"] =
            KesDltResponsesFixture::loadResponse("feed1.json");
        responses["feed2"] =
            KesDltResponsesFixture::loadResponse("feed2.json");
        responses["feed3"] =
            KesDltResponsesFixture::loadResponse("feed3.json");

        responses["malformed_feed1"] =
            KesDltResponsesFixture::loadResponse("malformed_feed1.json");
        responses["malformed_feed2"] =
            KesDltResponsesFixture::loadResponse("malformed_feed2.json");
        responses["malformed_feed3"] =
            KesDltResponsesFixture::loadResponse("malformed_feed3.json");

        responses["empty_feed1"] =
            KesDltResponsesFixture::loadResponse("empty_feed1.json");

        for (const auto &keyValue : responses) {
            if (keyValue.second == nullptr) {
                cerr << "KesDltResponsesFixture: FAILED TO LOAD DATA FOR "
                     << keyValue.first << endl;
            }
            tileCounts[keyValue.first] =
                KesDltResponsesFixture::getTileCount(keyValue.second);
        }
    }

    static void TearDownTestCase() {}

    virtual void SetUp() {}
    virtual void TearDown() {}

 private:
    static shared_ptr<JSON_Value> loadResponse(const string& filename) {
        const string data_dir = string(CMAKE_PROJ_BASE_DIR) +
            "/test/fixtures/kes_dlt_cli/data/";

        return shared_ptr<JSON_Value>(
            json_parse_file((data_dir + filename).c_str()),
            json_value_free);
    }

    static int getTileCount(shared_ptr<JSON_Value> response) {
        if (response == nullptr)
            return -1;

        JSON_Object* responseData = json_value_get_object(response.get());

        if (!json_object_has_value_of_type(responseData, "shares", JSONArray))
            return -1;

        return json_array_get_count(
            json_object_get_array(responseData, "shares"));
    }

 protected:
    static map<string, shared_ptr<JSON_Value>> responses;
    static map<string, int> tileCounts;
};

map<string, shared_ptr<JSON_Value>> KesDltResponsesFixture::responses =
    map<string, shared_ptr<JSON_Value>>();

map<string, int> KesDltResponsesFixture::tileCounts = map<string, int>();


#endif  // TEST_FIXTURES_KES_DLT_CLI_KESDLTRESPONSESFIXTURE_H_
