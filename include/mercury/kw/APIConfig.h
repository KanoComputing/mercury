/**
 * \file APIConfig.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief Configuration file for web services
 *
 */

#ifndef INCLUDE_MERCURY_KW_APICONFIG_H_
#define INCLUDE_MERCURY_KW_APICONFIG_H_


#include <yaml-cpp/yaml.h>

#include <memory>
#include <string>
#include <vector>


namespace Mercury {
namespace KanoWorld {


/**
 * \class APIConfig
 * \brief Provides configurations for the API configurations
 */
class APIConfig {
 public:
    /**
     * \brief Constructor
     *
     * \param config_files    (Optional) Config files to override defaults
     */
    explicit APIConfig(std::vector<std::string> config_files = {});

    /**
     * \brief Get the API URL
     *
     * \returns the configured API URL or the default if one isn't found
     */
    std::string get_api_url() const;

    /**
     * \brief Determines whether a given key exists
     *
     * \warning This doesn't guarantee that the value is of the required type
     *          or that it is not empty
     *
     * \param key    They value's key
     *
     * \returns whether the key exists
     */
    bool has(const std::string& key);

    /**
     * \brief Get a value from the configuration
     *
     * \param key    They value's key
     *
     * \returns the key's value
     */
    template<typename T>
    T get_value(const std::string& key) const {
        for (const auto& config : this->configs) {
            if (config[key]) {
                return config[key].as<T>();
            }
        }

        return T();
    }

 private:
    const std::string API_URL_KEY;
    const std::string SYSTEM_PATH;
    std::vector<YAML::Node> configs;
};


};  // namespace KanoWorld
};  // namespace Mercury


#endif  // INCLUDE_MERCURY_KW_APICONFIG_H_
