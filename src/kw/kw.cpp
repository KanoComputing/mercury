/**
 * \file kw.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 *  Kano World class methods implemntation
 */


#include "mercury/kw/kw.h"

#include <curl/curl.h>
#include <parson.h>

#include <memory>
#include <string>

#include "mercury/_http/http_client_interface.h"

using std::string;


KanoWorld::KanoWorld(std::shared_ptr<IHTTPClient> client) :
    http_client(client) {
}


/**
 * \warning Not implemented
 */
bool KanoWorld::login(string username, string password, bool verbose)
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

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    curl_slist_free_all(chunk);

    if (verbose) {
        printf (">>> login SERVER RESPONSE: %s\n", server_response.c_str());
    }

    // True if server responds with HTTP OK
    return (code == 200);
}


/**
 * \warning Not implemented
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
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    curl_slist_free_all(chunk);

    if (verbose) {
        printf (">>> refresh_token SERVER RESPONSE: %s\n", server_response.c_str());
    }

    // True if server responds with HTTP OK
    return (code == 200);
}



/**
 *   Returns the host name from the configuration file
 */
string KanoWorld::get_hostname(string config_filename)
{
    // TODO: read from json configuration file
    return (string(""));
}


/**
 *   Returns the header to request a token refresh
 */
string KanoWorld::get_refresh_header(string token)
{
    return (string("Authorization: Bearer " + token));
}


/**
 *   libcurl callback function to collect response from the server
 *
 */
size_t KanoWorld::write_function(void *ptr, size_t size, size_t nmemb, void *user_data)
{
    // Save the server's response in a class string
    KanoWorld *pkw = (KanoWorld *) user_data;
    pkw->server_response = string((char *) ptr);

    return size * nmemb;
}


/**
 *   Not implemented yet
 */
bool KanoWorld::am_i_logged_in(void)
{
    return false;
}


/**
 *   Not implemented yet
 */
string KanoWorld::whoami(void)
{
    return string("");
}


/**
 * \warning Not implemented
 */
bool KanoWorld::is_account_verified() {
    return true;
}
