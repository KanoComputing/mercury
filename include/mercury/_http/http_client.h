/**
 * \file http_client.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     HTTP request client
 *
 */


#ifndef MERCURY__HTTP_HTTP_CLIENT_H_
#define MERCURY__HTTP_HTTP_CLIENT_H_


#include <parson.h>

#include <map>
#include <memory>
#include <string>

#include "mercury/_http/http_client_interface.h"


/**
 * \class HTTPClient
 * \brief Simple implementation of IHTTPClient
 */
class HTTPClient : public IHTTPClient {
 public:
    HTTPClient();
    std::shared_ptr<JSON_Value> POST(
        const std::string& url,
        const std::string& body,
        const std::map<std::string, std::string>& headers =
            std::map<std::string, std::string>()) override;
    std::shared_ptr<JSON_Value> POST(
        const std::string& url,
        const std::shared_ptr<JSON_Value> body,
        const std::map<std::string, std::string>& headers =
            std::map<std::string, std::string>()) override;
    std::shared_ptr<JSON_Value> GET(
        const std::string& url,
        const std::map<std::string, std::string>& headers =
            std::map<std::string, std::string>()) override;

 protected:
    /**
     * \brief Builds and sends a request to a server
     *
     * \param method    The HTTP method to use (One of HTTPRequest::HTTP_GET,
     *                  HTTPRequest::HTTP_POST)
     * \param url       The URL to POST
     * \param headers   (Optional) Headers to pass to add to the request
     * \param body      (Optional) The body of the request
     *
     * \throws SessionInitError          Unable to initialise the session
     * \throws HTTPRequestFailedError    Server response wasn't OK (!= 200)
     */
    std::shared_ptr<JSON_Value> send_request(
        const std::string& method,
        const std::string& url,
        const std::map<std::string, std::string>& headers =
            std::map<std::string, std::string>(),
        const std::string& body = "");
};


#endif  // MERCURY__HTTP_HTTP_CLIENT_H_
