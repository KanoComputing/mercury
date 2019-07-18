/**
 * \file mock_http_client.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 */


#ifndef TEST_MOCKS_MOCK_HTTP_CLIENT_H_
#define TEST_MOCKS_MOCK_HTTP_CLIENT_H_


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <mercury/_http/http_client.h>

#include <map>
#include <memory>
#include <string>


/**
 * \class MockHTTPClient
 * \brief Mock implementation of IHTTPClient
 *
 * This class can be used with the Google Mock framework to allow testing for
 * calls and mocking out return values. Details can be found at:
 *
 *     github.com/google/googletest/blob/master/googlemock/docs/ForDummies.md
 *
 * Note that because of the limitations of Google Mock with optional parameters
 * we define the main function methods to just point to internal `*_impl()`
 * equivalents of them. For this reason, all tests should check for these
 * internal implementation functions.
 *
 * For example:
 *
 * ```
 * MockHTTPClient client;
 * EXPECT_CALL(
 *     client,
 *     GET_impl(
 *         "http://www.example.com",
 *         std::map<std::string, std::string>()))
 *     .Times(3)
 *     .WillRepeatedly(testing::Return(nullptr));
 *
 * test_func(client);
 * ```
 *
 * This will check that the function GET_impl() gets called with
 * "http://www.example.com" and an empty map of headers 3 times, each time
 * returning `nullptr`. This could be because `GET()` is called directly with
 * the two parameters or because it is called and uses the optional parameter.
 * Ultimately, this makes no difference from the test's perspective.
 *
 */
class MockHTTPClient : public IHTTPClient {
 public:
    /**
     * \brief Google Mock doesn't permit optional arguments so simply implement
     *        the mocked function signature and offload to the mocked
     *        implementation (POST_impl)
     *
     * \param url       The URL to POST
     * \param body      The body of the request
     * \param headers   (Optional) Headers to pass to add to the request
     */
    virtual std::shared_ptr<JSON_Value> POST(
        const std::string& url,
        const std::string& body,
        const std::map<std::string, std::string>& headers =
            std::map<std::string, std::string>()) {
        return this->POST_impl(url, body, headers);
    }
    /**
     * \brief Google Mock doesn't permit optional arguments so simply implement
     *        the mocked function signature and offload to the mocked
     *        implementation (POST_impl)
     *
     * \param url       The URL to POST
     * \param body      The body of the request
     * \param headers   (Optional) Headers to pass to add to the request
     */
    virtual std::shared_ptr<JSON_Value> POST(
        const std::string& url,
        std::shared_ptr<JSON_Value> body,
        const std::map<std::string, std::string>& headers =
            std::map<std::string, std::string>()) {
        return this->POST_impl(url, body, headers);
    }
    /**
     * \brief Google Mock doesn't permit optional arguments so simply implement
     *        the mocked function signature and offload to the mocked
     *        implementation (GET_impl)
     *
     * \param url       The URL to GET
     * \param headers   (Optional) Headers to pass to add to the request
     */
    virtual std::shared_ptr<JSON_Value> GET(
        const std::string& url,
        const std::map<std::string, std::string>& headers =
            std::map<std::string, std::string>()) {
        return this->GET_impl(url, headers);
    }
    /**
     */
    MOCK_METHOD2(
        DL,
        bool(
            const std::string& url, const std::string& path));

    /**
     * \brief Internal mocked version of the POST to account for optional
     *        parameters to Google Mock's mocked function. This is the function
     *        that you should be checking to determine whether the function was
     *        run.
     *
     * \param url       The URL to POST
     * \param body      The body of the request
     * \param headers   Headers to pass to add to the request
     */
    MOCK_METHOD3(
        POST_impl,
        std::shared_ptr<JSON_Value>(
            const std::string& url,
            const std::string& body,
            const std::map<std::string, std::string>& headers));
    /**
     * \brief Internal mocked version of the POST to account for optional
     *        parameters to Google Mock's mocked function. This is the function
     *        that you should be checking to determine whether the function was
     *        run.
     *
     * \param url       The URL to POST
     * \param body      The body of the request
     * \param headers   Headers to pass to add to the request
     */
    MOCK_METHOD3(
        POST_impl,
        std::shared_ptr<JSON_Value>(
            const std::string& url,
            std::shared_ptr<JSON_Value> body,
            const std::map<std::string, std::string>& headers));
    /**
     * \brief Internal mocked version of the GET to account for optional
     *        parameters to Google Mock's mocked function. This is the function
     *        that you should be checking to determine whether the function was
     *        run.
     *
     * \param url       The URL to GET
     * \param headers   Headers to pass to add to the request
     */
    MOCK_METHOD2(
        GET_impl,
        std::shared_ptr<JSON_Value>(
            const std::string& url,
            const std::map<std::string, std::string>& headers));
};


#endif  // TEST_MOCKS_MOCK_HTTP_CLIENT_H_
