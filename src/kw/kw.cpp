/**
 * \file kw.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 *  Kano World class methods implemntation
 */

#include <string>
using std::string;

#include "mercury/kw/kw.h"

#include "curl/curl.h"

/**
 * \warning Not implemented
 */
bool KanoWorld::renew_token(string token)
{
    CURL *curl;
    char curl_errbuf[CURL_ERROR_SIZE];
    int err;

    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, "http://google.com");
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_errbuf);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &docbuf);

    err = curl_easy_perform(curl);

    return true;
}

/**
 * \warning Not implemented
 */
bool KanoWorld::is_user_logged_in(string username)
{
    return true;
}

bool KanoWorld::who_am_i(void)
{
  return true;
}
