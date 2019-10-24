/**
 * \file http_client_interface.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 */

#ifndef INCLUDE_MERCURY_HTTP_HTTP_CLIENT_INTERFACE_H_
#define INCLUDE_MERCURY_HTTP_HTTP_CLIENT_INTERFACE_H_


#include <parson.h>

#include <map>
#include <memory>
#include <string>

#include "mercury/http/exceptions.h"


namespace Mercury {
namespace HTTP {

/**
 * \interface IHTTPClient
 * \brief Interface for an HTTP client
 */
class IHTTPClient {
 public:
     /**
      * \brief Explicitly define a virtual destructor so that classes that
      *        implement this don't have issues
      */
    virtual ~IHTTPClient() {}
    /**
     * \brief POSTs data to a server
     *
     * \param url       The URL to POST
     * \param body      The body of the request
     * \param headers   (Optional) Headers to pass to add to the request
     *
     * \throws SessionInitError          Unable to initialise the session
     * \throws HTTPRequestFailedError    Server response wasn't OK (!= 200)
     *
     * \returns    The data returned from the server
     */
    virtual std::shared_ptr<JSON_Value> POST(
        const std::string& url,
        const std::string& body,
        const std::map<std::string, std::string>& headers =
            std::map<std::string, std::string>()) = 0;
    /**
     * \brief POSTs data to a server
     *
     * \param url       The URL to POST
     * \param body      The body of the request
     * \param headers   (Optional) Headers to pass to add to the request
     *
     * \throws SessionInitError          Unable to initialise the session
     * \throws HTTPRequestFailedError    Server response wasn't OK (!= 200)
     *
     * \returns    The data returned from the server
     */
    virtual std::shared_ptr<JSON_Value> POST(
        const std::string& url,
        const std::shared_ptr<JSON_Value>& body,
        const std::map<std::string, std::string>& headers =
            std::map<std::string, std::string>()) = 0;
    /**
     * \brief GETs data from a server
     *
     * \param url       The URL to GET
     * \param headers   (Optional) Headers to pass to add to the request
     *
     * \throws SessionInitError          Unable to initialise the session
     * \throws HTTPRequestFailedError    Server response wasn't OK (!= 200)
     *
     * \returns    The data returned from the server
     */
    virtual std::shared_ptr<JSON_Value> GET(
        const std::string& url,
        const std::map<std::string, std::string>& headers =
            std::map<std::string, std::string>()) = 0;
    /**
     */
    virtual bool DL(const std::string& url, const std::string& path) = 0;
};

}  // namespace HTTP
}  // namespace Mercury


#endif  // INCLUDE_MERCURY_HTTP_HTTP_CLIENT_INTERFACE_H_
