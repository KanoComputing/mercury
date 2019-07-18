/**
 * \file kw.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 *  Kano World class methods implemntation
 */

#include <iostream>
#include <string>
#include <ctime>

using std::string;

#include "mercury/kw/kw.h"

#include <curl/curl.h>
#include <parson.h>
#include <stdlib.h>

#include <memory>
#include <string>

#include "mercury/_http/http_client_interface.h"

using std::string;

#include <sys/stat.h>
#include <unistd.h>


KanoWorld::KanoWorld(std::shared_ptr<IHTTPClient> client) :
    http_client(client),
    data_filename (string(getenv("HOME")) + "/" + ".mercury_kw.json"),
    token(""),
    expiration_date("") {
}


/**
 * \brief Calls the login endpoint the username and password credentials.
 *
 * This is a login to the Kano World Services API
 *
 * \param username    The first parameter passed to the function
 * \param password    The second parameter passed to the function
 * \param verbose     Be more descriptive on the transaction details
 *
 * \returns True if login was successful, false otherwise.e
 */
bool KanoWorld::login(const string& username, const string& password, bool verbose)
{
    CURL *curl;
    CURLcode res;
    struct curl_slist *chunk = NULL;
    long code=0L;

    if (!username.length() || !password.length()) {
        return false;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {

        // TODO: use json library
        string payload = "{\n\"username\": \"" + username + "\", \n\"password\": \"" + password + "\"\n}";

        // Apply API expected headers
        chunk = curl_slist_append(chunk, "Accept: application/json");
        chunk = curl_slist_append(chunk, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        curl_easy_setopt(curl, CURLOPT_URL, "https://worldapi-dev.kano.me/accounts/auth");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, verbose ? 1L : 0L);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, payload.length());
        curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, payload.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_server_response);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if(res != CURLE_OK) {
            std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    curl_slist_free_all(chunk);
    save_data();

    // True if server responds with HTTP OK
    if (code == HTTP_OKAY) {
        if (verbose) {
            std::cout << ">>> login SERVER RESPONSE: " << server_response.c_str() << std::endl;
            std::cout << ">>> Token: " << get_token().c_str() << std::endl;
            std::cout << ">>> Expiration date: " << get_expiration_date().c_str() << std::endl;
        }
        return true;
    }

    return false;

} // login


/**
 * \brief Logs out the current user
 *
 * The cache file is removed so that the login details are discarded
 *
 * \param verbose     Be more descriptive on the transaction details
 *
 * \returns True if logout was successful
 */
bool KanoWorld::logout(bool verbose)
{
    struct stat cache;
    int rc = stat(data_filename.c_str(), &cache);

    if (rc != -1) {
        int rc = unlink(data_filename.c_str());
    }

    if (verbose) {
        std::cout << "logout - removing cache file success? " << (rc == -1 ? "No" : "Yes") << std::endl;
    }
    return rc != -1;
}


/**
 * \brief Calls the refresh_token endpoint to request a new token
 *
 * On success, the token is saved locally for future reference
 *
 * \param token       The previously stored token
 * \param verbose     Be more descriptive on the transaction details
 *
 * \returns True if a new token was returned from the server.
 */
bool KanoWorld::refresh_token(string token, bool verbose)
{
    CURL *curl;
    CURLcode res;
    struct curl_slist *chunk = NULL;
    long code=0L;

    if (!token.length()) {
        return false;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {

        // Apply API expected headers
        chunk = curl_slist_append(chunk, "Accept: application/json");
        chunk = curl_slist_append(chunk, get_refresh_header(token).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        curl_easy_setopt(curl, CURLOPT_URL, "https://worldapi-dev.kano.me/accounts/auth/refresh");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, verbose ? 1L : 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_server_response);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if(res != CURLE_OK) {
            std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    curl_slist_free_all(chunk);
    save_data();

    if (code == HTTP_OKAY) {
        if (verbose) {
            std::cout << ">>> refresh_token SERVER RESPONSE: " << server_response.c_str() << std::endl;
            std::cout << ">>> Token: " << get_token().c_str() << std::endl;
            std::cout << ">>> Expiration date: " << get_expiration_date().c_str() << std::endl;
        }
        save_data();
        return true;
    }

    return false;

} // refresh_token()


/**
 * \brief Returns the hostname used to contact the Kano World API
 *
 * On success, the token is saved locally for future reference
 *
 * \param config_filename   Json filename that stores the API details
 *
 * \returns A string with the URL to the server
 */
string KanoWorld::get_hostname(string config_filename)
{
    // TODO: read from json configuration file
    return (string(""));
}


/**
 * \brief Returns the HTTP header needed to call the token "refresh" endpoint
 *
 * \param token    The token needed to submit the request
 *
 * \returns A string with the HTTP header
 */
string KanoWorld::get_refresh_header(string token)
{
    return (string("Authorization: Bearer " + token));
}


/**
 *   libcurl callback function, allows to collect the data response from the server,
 *   which in this case is a json object.
 *
 *   See libCurl CURLOPT_WRITEFUNCTION and CURLOPT_WRITEDATA options.
 *   The WRITEDATA option is used to pass the class instance to safe the data for later processing.
 *
 *   server_response is a class string used to transfer the server data into the class.
 *
 *   TODO: This implementation should be migrated to HTTPClient on top of Moco.
 *
 */
size_t KanoWorld::callback_server_response(void *ptr, size_t size, size_t nmemb, void *user_data)
{
    // Save the server's response in a class string
    KanoWorld *pkw = (KanoWorld *) user_data;
    pkw->server_response = string((char *) ptr);

    return size * nmemb;
}


/**
 * \brief Returns wether the user is currently logged in
 *
 * A local token timestamp comparison is performed, to decide wether it has expired
 *
 * \param verbose    Be more descriptive on the actions performed
 *
 * \returns True if the current user is logged in.
 */
bool KanoWorld::is_logged_in(bool verbose)
{
    std::time_t now = std::time(nullptr);

    if (!load_data()) {
        return false;
    }

    std::time_t duration = atol(expiration_date.c_str());

    if (!duration) {
        return false;
    }

    double seconds = difftime(now, duration);

    if (verbose) {
        std::cout << ">>> Am_I_Logged_In() requested - Time: " << now << " - " <<
            ctime((const time_t *) &now) << std::endl;

        std::cout << ">>> Token expires: " << duration << " - " << ctime((const time_t *) &duration) << std::endl;
        std::cout << ">>> Difference in seconds: " << seconds << std::endl;
        std::cout << ">>> Token valid? " << (seconds < 0 ? "Yes" : "No") << std::endl;
    }

    return (seconds < 0);
}


/**
 *   Not implemented yet
 */
string KanoWorld::whoami()
{
    return string("");
}


/**
 * \brief Returns the token from the server response
 *
 * \returns A string with the complete JWT token
 */
string KanoWorld::get_token()
{
    JSON_Value *schema = json_parse_string(server_response.c_str());
    if (schema) {
        token = string(json_object_dotget_string(json_object(schema), "data.token"));
    }

    return token;
}


/**
 * \brief Returns the token expiration date from the server response
 *
 * \returns A string with the Unix timestamp representing the token expiration date
 */
string KanoWorld::get_expiration_date()
{
    JSON_Value *schema = json_parse_string(server_response.c_str());
    if (schema) {

        // For some reason, the Unix time returned by the server is divide by 1000
        // So we convert it back into a Unix time here. See:
        // https://github.com/KanoComputing/kes-world-api/blob/develop/src/controllers/accounts.js#L35
        long conversion = 1000;
        string translate = string(json_object_dotget_string(json_object(schema), "data.duration"));
        expiration_date = string( std::to_string (std::stol(translate.c_str()) * conversion) );
    }

    return expiration_date;
}


/**
 * \brief Loads the cache data for the latest Kano World transaction
 *
 * The cache data contains the token and expiration timestamp
 *
 * \returns true if the data was successfully loaded.
 */
bool KanoWorld::load_data()
{
    JSON_Value *user_data = json_parse_file(data_filename.c_str());
    if (!user_data) {
        return false;
    }

    token = json_object_get_string(json_object(user_data), "token");
    expiration_date = json_object_get_string(json_object(user_data), "duration");

    return true;
}


/**
 * \brief Saves the data returned from the server on a local cache file.
 *
 * The cache data file is then used to peek at the login token and expiration timestamp
 *
 * \returns true if the data was successfully saved.
 */
bool KanoWorld::save_data()
{
    JSON_Value *user_data = json_value_init_object();

    if (!user_data) {
        return false;
    }

    json_object_set_string(json_object(user_data), "token", get_token().c_str());
    json_object_set_string(json_object(user_data), "duration", get_expiration_date().c_str());

    JSON_Status rc = json_serialize_to_file(user_data, data_filename.c_str());
    json_value_free(user_data);

    return rc == JSONSuccess;
}

/**
 * \warning Not implemented
 */
bool KanoWorld::is_account_verified() {
    return true;
}
