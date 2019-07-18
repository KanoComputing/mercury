/**
 * \file exceptions.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 */


#ifndef MERCURY__HTTP_EXCEPTIONS_H_
#define MERCURY__HTTP_EXCEPTIONS_H_


#include <exception>
#include <map>
#include <string>


/**
 * \class HTTPClientError
 * \brief Base exception to throw when there is an error with the HTTPClient
 */
class HTTPClientError : public std::exception {
 public:
    explicit HTTPClientError(const std::string msg) : message(msg) {}
    const std::string message;
    const char *what() const noexcept(true) {
        return this->message.c_str();
    }
};


/**
 * \class SessionInitError
 * \brief Exception to throw when there is an error initialising the HTTP
 *        session
 */
class SessionInitError : public HTTPClientError {
 public:
    explicit SessionInitError(const std::string msg) :
        HTTPClientError(
            std::string("Initialising HTTP session failed: ") + msg
        ) {}
};


/**
 * \class HTTPRequestFailedError
 * \brief Exception to throw when there is an error with the HTTP request
 */
class HTTPRequestFailedError : public HTTPClientError {
 public:
    HTTPRequestFailedError(const int err_no, const std::string reason) :
        HTTPClientError(
            std::string("HTTP request failed. Status code: ") +
            std::to_string(err_no) +
            std::string(" (") + reason + std::string(")")),
        error_code(err_no) {}
    const int error_code;
};


/**
 * \class SessionInitError
 * \brief Exception to throw when there is an error initialising the HTTP
 *        session
 */
class DownloadError : public HTTPClientError {
 public:
    DownloadError(const std::string url, const std::string msg) :
        HTTPClientError(
            std::string("Download for URL: ") + url +
            std::string(" failed: ") + msg
        ) {}
};

#endif  // MERCURY__HTTP_EXCEPTIONS_H_
