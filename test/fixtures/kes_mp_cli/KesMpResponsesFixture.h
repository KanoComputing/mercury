/**
 * \file KesMpResponsesFixture.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef TEST_FIXTURES_KES_MP_CLI_KESMPRESPONSESFIXTURE_H_
#define TEST_FIXTURES_KES_MP_CLI_KESMPRESPONSESFIXTURE_H_


#include <gtest/gtest.h>
#include <parson.h>

#include <fstream>
#include <map>
#include <memory>
#include <string>

#include "mercury/config.h"


namespace KESMPC {
namespace test {

class KesMpResponsesFixture : public ::testing::Test {
 public:
    static void SetUpTestCase() {
        rawResponses["empty_feed1"] = loadData("empty_feed1.json");
        rawResponses["feed1"] = loadData("feed1.json");
        rawResponses["feed2"] = loadData("feed2.json");
        rawResponses["feed3"] = loadData("feed3.json");
        rawResponses["invalid_feed1"] = loadData("invalid_feed1.json");
        rawResponses["invalid_feed2"] = loadData("invalid_feed2.json");
        rawResponses["malformed_feed1"] = loadData("malformed_feed1.json");

        for (const auto &keyValue : rawResponses) {
            responses[keyValue.first] = parseJson(keyValue.second);
            paintingCounts[keyValue.first] = getPaintingCount(responses[keyValue.first]);  // NOLINT
        }

        rawCaches["painting_cache1"] = loadData("painting_cache1.json");

        for (const auto &keyValue : rawCaches) {
            caches[keyValue.first] = parseJson(keyValue.second);
        }
    }

    static void TearDownTestCase() {}

    virtual void SetUp() {}
    virtual void TearDown() {}

 private:
    static std::string loadData(const std::string& filename) {
        const std::string path = dataDir + "/" + filename;

        // TODO: Add this to mercury/utils/filesystem.
        // Read raw data file in.
        std::ifstream file(path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        return buffer.str();
    }

    static std::shared_ptr<JSON_Value> parseJson(const std::string& data) {
        return std::shared_ptr<JSON_Value>(
            json_parse_string(data.c_str()),
            json_value_free);
    }

    static int getPaintingCount(std::shared_ptr<JSON_Value> response) {
        if (response == nullptr)
            return -1;

        JSON_Object* responseData = json_value_get_object(response.get());

        if (!json_object_has_value_of_type(responseData, "paintings", JSONArray))  // NOLINT
            return -1;

        return json_array_get_count(
            json_object_get_array(responseData, "paintings"));
    }

 protected:
    static std::string dataDir;
    static std::map<std::string, std::string> rawResponses;
    static std::map<std::string, std::shared_ptr<JSON_Value>> responses;
    static std::map<std::string, int> paintingCounts;
    static std::map<std::string, std::string> rawCaches;
    static std::map<std::string, std::shared_ptr<JSON_Value>> caches;
};

std::string KesMpResponsesFixture::dataDir =  // NOLINT
    std::string(CMAKE_PROJ_BASE_DIR) + "/test/fixtures/kes_mp_cli/data/";

std::map<std::string, std::string> KesMpResponsesFixture::rawResponses =
    std::map<std::string, std::string>();

std::map<std::string, std::shared_ptr<JSON_Value>> KesMpResponsesFixture::responses =  // NOLINT
    std::map<std::string, std::shared_ptr<JSON_Value>>();

std::map<std::string, int> KesMpResponsesFixture::paintingCounts =
    std::map<std::string, int>();

std::map<std::string, std::string> KesMpResponsesFixture::rawCaches =
    std::map<std::string, std::string>();

std::map<std::string, std::shared_ptr<JSON_Value>> KesMpResponsesFixture::caches =  // NOLINT
    std::map<std::string, std::shared_ptr<JSON_Value>>();

}  // namespace test
}  // namespace KESMPC

#endif  // TEST_FIXTURES_KES_MP_CLI_KESMPRESPONSESFIXTURE_H_
