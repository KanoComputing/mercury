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

#include <fstream>
#include <map>
#include <memory>
#include <string>

#include "mercury/config.h"

using std::ifstream;
using std::make_shared;
using std::map;
using std::shared_ptr;
using std::string;
using std::stringstream;

using ::testing::Test;


class KesDltResponsesFixture : public Test {
 public:
    static void SetUpTestCase() {
        rawResponses["empty_feed1"] =
            KesDltResponsesFixture::loadRawResponse("empty_feed1.json");
        rawResponses["feed1"] =
            KesDltResponsesFixture::loadRawResponse("feed1.json");
        rawResponses["feed2"] =
            KesDltResponsesFixture::loadRawResponse("feed2.json");
        rawResponses["feed3"] =
            KesDltResponsesFixture::loadRawResponse("feed3.json");
        rawResponses["invalid_feed1"] =
            KesDltResponsesFixture::loadRawResponse("invalid_feed1.json");
        rawResponses["invalid_feed2"] =
            KesDltResponsesFixture::loadRawResponse("invalid_feed2.json");
        rawResponses["malformed_feed1"] =
            KesDltResponsesFixture::loadRawResponse("malformed_feed1.json");

        for (const auto &keyValue : rawResponses) {
            responses[keyValue.first] =
                KesDltResponsesFixture::getResponse(keyValue.second);
            tileCounts[keyValue.first] =
                KesDltResponsesFixture::getTileCount(responses[keyValue.first]);
        }
    }

    static void TearDownTestCase() {}

    virtual void SetUp() {}
    virtual void TearDown() {}

 private:
    static string loadRawResponse(const string& filename) {
        const string path = string(CMAKE_PROJ_BASE_DIR) +
            "/test/fixtures/kes_dlt_cli/data/" + filename;

        // TODO: Add this to mercury/utils/filesystem.
        // Read raw data file in.
        ifstream file(path);
        stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        return buffer.str();
    }

    static shared_ptr<JSON_Value> getResponse(const string& data) {
        return shared_ptr<JSON_Value>(
            json_parse_string(data.c_str()),
            json_value_free);
    }

    static int getTileCount(shared_ptr<JSON_Value> response) {
        if (response == nullptr)
            return -1;

        JSON_Object* responseData = json_value_get_object(response.get());

        if (!json_object_has_value_of_type(responseData, "tiles", JSONArray))
            return -1;

        return json_array_get_count(
            json_object_get_array(responseData, "tiles"));
    }

 protected:
    static map<string, string> rawResponses;
    static map<string, shared_ptr<JSON_Value>> responses;
    static map<string, int> tileCounts;
};

map<string, string> KesDltResponsesFixture::rawResponses =
    map<string, string>();

map<string, shared_ptr<JSON_Value>> KesDltResponsesFixture::responses =
    map<string, shared_ptr<JSON_Value>>();

map<string, int> KesDltResponsesFixture::tileCounts =
    map<string, int>();


#endif  // TEST_FIXTURES_KES_DLT_CLI_KESDLTRESPONSESFIXTURE_H_
