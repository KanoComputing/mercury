/**
 * \file kw_api.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Constants and functions to contact the Kano World API and retrieve
 *        responses.
 *
 */


#ifndef TEST_FIXTURES_KW_API_H_
#define TEST_FIXTURES_KW_API_H_

#include <mercury/config.h>

#include <memory>
#include <string>


// TODO: Change this to https://worldapi-dev.kes.kano.me when it's usable.
#define _API_URL "https://worldapi-dev.kano.me"


class KanoWorldAPI {
 public:
    static const char* URL;
    static const char* ME_ENDPOINT;
    static const char* AUTH_ENDPOINT;
};


const char* KanoWorldAPI::URL = _API_URL;
const char* KanoWorldAPI::ME_ENDPOINT = _API_URL "/users/me";
const char* KanoWorldAPI::AUTH_ENDPOINT =
    _API_URL "/accounts/auth";


std::shared_ptr<JSON_Value> load_response(const std::string& filename) {
    const std::string data_dir = std::string(CMAKE_PROJ_BASE_DIR) +
        "/test/fixtures/data/api_response/";
    return std::shared_ptr<JSON_Value>(
        json_parse_file((data_dir + filename).c_str()),
        json_value_free);
}


#endif  // TEST_FIXTURES_KW_API_H_
