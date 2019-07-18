/**
 * \file http_client.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 */

#include "mercury/_http/http_client.h"

#include <parson.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSessionFactory.h>
#include <Poco/Net/HTTPSessionInstantiator.h>
#include <Poco/Net/HTTPSSessionInstantiator.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/SharedPtr.h>
#include <Poco/URI.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include <exception>

using Poco::Net::HTTPSessionFactory;
using Poco::Net::HTTPSessionInstantiator;
using Poco::Net::HTTPSSessionInstantiator;
using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::Context;
using Poco::Net::AcceptCertificateHandler;
using Poco::Net::SSLManager;


HTTPClient::HTTPClient() {
    try {
        HTTPSessionInstantiator::registerInstantiator();
        HTTPSSessionInstantiator::registerInstantiator();

        // Prepare for SSLManager
        Poco::SharedPtr<AcceptCertificateHandler> cert =
            new AcceptCertificateHandler(false);
        const Poco::Net::Context::Ptr context = new Context(
                                                            Context::CLIENT_USE, "", "", "", Context::VERIFY_NONE, 9, false,
                                                            "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
        SSLManager::instance().initializeClient(0, cert, context);
    } catch (std::exception& e) {
    }
}

/*
HTTPClient::HTTPClient() {
    HTTPSessionInstantiator::registerInstantiator();
    HTTPSSessionInstantiator::registerInstantiator();

    // Prepare for SSLManager
    Poco::SharedPtr<AcceptCertificateHandler> cert =
        new AcceptCertificateHandler(false);
    const Poco::Net::Context::Ptr context = new Context(
        Context::CLIENT_USE, "", "", "", Context::VERIFY_NONE, 9, false,
        "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
    SSLManager::instance().initializeClient(0, cert, context);
}
*/

std::shared_ptr<JSON_Value> HTTPClient::send_request(
    const std::string& method,
    const std::string& url,
    const std::map<std::string, std::string>& headers,
    const std::string& body
) {
    const Poco::URI uri(url);
    std::unique_ptr<HTTPClientSession> session;

    try {
        session = std::unique_ptr<HTTPClientSession>(
            HTTPSessionFactory::defaultFactory().createClientSession(uri));
    } catch (const Poco::DataException& e) {
        throw SessionInitError(e.message());
    } catch (const std::exception& e) {
        throw SessionInitError(e.what());
    }

    HTTPRequest request(method, uri.getPath(), HTTPMessage::HTTP_1_1);
    request.setContentType("application/json");
    request.setContentLength(body.length());
    request.add("Accept", "application/json");

    for (auto header : headers) {
        request.set(header.first, header.second);
    }

    std::ostream& os = session->sendRequest(request);

    if (!body.empty()) {
        os << body;
    }

    HTTPResponse response;
    std::istream& rs = session->receiveResponse(response);

    int status_code = response.getStatus();
    if (status_code != HTTPResponse::HTTP_OK) {
        throw HTTPRequestFailedError(status_code, response.getReason());
    }

    std::ostringstream data_stream;
    data_stream << rs.rdbuf();

    return std::shared_ptr<JSON_Value>(
        json_parse_string(data_stream.str().c_str()), json_value_free);
}


std::shared_ptr<JSON_Value> HTTPClient::POST(
    const std::string& url,
    const std::shared_ptr<JSON_Value> body,
    const std::map<std::string, std::string>& headers) {
    std::shared_ptr<char> body_str(
        json_serialize_to_string(body.get()),
        json_free_serialized_string);

    return this->POST(url, body_str.get());
}


std::shared_ptr<JSON_Value> HTTPClient::POST(
    const std::string& url,
    const std::string& body,
    const std::map<std::string, std::string>& headers) {
    return this->send_request(
        HTTPRequest::HTTP_POST,
        url,
        headers,
        body);
}


std::shared_ptr<JSON_Value> HTTPClient::GET(
    const std::string& url,
    const std::map<std::string, std::string>& headers) {
    return this->send_request(
        HTTPRequest::HTTP_GET,
        url,
        headers);
}
