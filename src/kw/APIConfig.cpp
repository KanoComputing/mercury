/**
 * \file APIConfig.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Configuration file for web services
 *
 */


#include "mercury/kw/APIConfig.h"

#include <string>
#include <utility>
#include <vector>

#include "mercury/config.h"


using Mercury::KanoWorld::APIConfig;
using std::move;
using std::string;
using std::vector;


APIConfig::APIConfig(vector<string> config_files) :
        API_URL_KEY("API_URL"),
        // FIXME: Find a cross-platform mechanism for this
        SYSTEM_PATH("/etc/mercury-api.yaml") {
#if CMAKE_BUILD_TYPE == Debug
    config_files.push_back(
        string(CMAKE_PROJ_BASE_DIR) + "conf/kw_dev.yaml");
#endif  // DEBUG

    config_files.push_back(SYSTEM_PATH);

    for (const auto& path : config_files) {
        YAML::Node config;
        try {
            config = YAML::LoadFile(path);
        } catch (...) {
            continue;
        }

        if (config.Type() == YAML::NodeType::Map) {
            this->configs.push_back(move(config));
        }
    }
}


bool APIConfig::has(const std::string& key) {
    for (const auto& config : this->configs) {
        if (config[key]) {
            return true;
        }
    }

    return false;
}


string APIConfig::get_api_url() const {
    string url = this->get_value<string>(this->API_URL_KEY);

    if (!url.empty()) {
        return url;
    }

    return "https://worldapi.kano.me";
}
