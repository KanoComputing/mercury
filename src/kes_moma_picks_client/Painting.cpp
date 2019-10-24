/**
 * \file Painting.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <parson.h>

#include <errno.h>
#include <sys/stat.h>

#include <iostream>
#include <memory>
#include <string>

#include "kes_moma_picks_client/Painting.h"
#include "mercury/http/http_client.h"
#include "mercury/http/http_client_interface.h"
#include "mercury/utils/Filesystem.h"
#include "mercury/utils/String.h"

using std::cerr;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::string;

using KESMPC::Painting;

using Mercury::HTTP::HTTPClient;
using Mercury::HTTP::IHTTPClient;


Painting::Painting(const shared_ptr<IHTTPClient>& httpClient):
    Painting("", "", "", "", "", "", "", "", httpClient) {
    // Empty constructor.
}


Painting::Painting(
    const string& id, const string& cover, const string& title,
    const string& username, const string& dateCreated,
    const string& openUrl, const string& fallbackUrl,
    const string& coverPath, const shared_ptr<IHTTPClient>& httpClient):
        id(id), cover(cover), title(title), username(username),
        dateCreated(dateCreated), openUrl(openUrl), fallbackUrl(fallbackUrl),
        coverPath(coverPath), httpClient(httpClient) {
    //
    if (this->httpClient == nullptr)
        this->httpClient = make_shared<HTTPClient>();
}


bool Painting::initialise(JSON_Value* serialisedData) {
    JSON_Object* data = json_value_get_object(serialisedData);

    // Mandatory fields.
    if (!json_object_has_value_of_type(data, "id", JSONString) ||
        !json_object_has_value_of_type(data, "cover", JSONString) ||
        !json_object_has_value_of_type(data, "title", JSONString) ||
        !json_object_has_value_of_type(data, "username", JSONString) ||
        !json_object_has_value_of_type(data, "dateCreated", JSONString) ||
        !json_object_has_value_of_type(data, "openUrl", JSONString) ||
        !json_object_has_value_of_type(data, "fallbackUrl", JSONString)) {
        // NOLINT
        return false;
    }

    this->id = json_object_get_string(data, "id");
    this->cover = json_object_get_string(data, "cover");
    this->title = json_object_get_string(data, "title");
    this->username = json_object_get_string(data, "username");
    this->dateCreated = json_object_get_string(data, "dateCreated");
    this->openUrl = json_object_get_string(data, "openUrl");
    this->fallbackUrl = json_object_get_string(data, "fallbackUrl");

    // Optional fields.
    if (json_object_has_value_of_type(data, "coverPath", JSONString)) {
        this->coverPath = json_object_get_string(data, "coverPath");
    }

    return true;
}


JSON_Value* Painting::serialise() const {
    JSON_Value* root = json_value_init_object();
    JSON_Object* data = json_value_get_object(root);

    // Mandatory fields.
    json_object_set_string(data, "id", this->id.c_str());
    json_object_set_string(data, "cover", this->cover.c_str());
    json_object_set_string(data, "title", this->title.c_str());
    json_object_set_string(data, "username", this->username.c_str());
    json_object_set_string(data, "dateCreated", this->dateCreated.c_str());
    json_object_set_string(data, "openUrl", this->openUrl.c_str());
    json_object_set_string(data, "fallbackUrl", this->fallbackUrl.c_str());

    // Optional fields.
    if (!this->coverPath.empty()) {
        json_object_set_string(data, "coverPath", this->coverPath.c_str());
    }

    return root;
}


bool Painting::download(const string& baseDir) {
    string paintingDir = baseDir + '/' + this->id;
    this->coverPath = paintingDir + '/' + split(this->cover, '/').back();

    // Create the directory path for this painting data.
    if (!create_directories(paintingDir)) {
        cerr << "Failed to create directories: path: " << paintingDir << endl;
        return false;
    }

    // Download the cover.
    if (!this->httpClient->DL(this->cover, this->coverPath)) {
        cerr << "Failed to download: URL: " << this->cover
             << " to " << this->coverPath << endl;
        return false;
    }

    return true;
}


string Painting::getId() const {
    return this->id;
}


string Painting::getUsername() const {
    return this->username;
}


string Painting::getTitle() const {
    return this->title;
}


string Painting::getDateCreated() const {
    return this->dateCreated;
}


string Painting::getCover() const {
    return this->cover;
}


string Painting::getOpenUrl() const {
return this->openUrl;
}


string Painting::getFallbackUrl() const {
return this->fallbackUrl;
}


string Painting::getCoverPath() const {
    return this->coverPath;
}
