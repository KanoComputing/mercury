/**
 * \file Tile.cpp
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

#include "kes_dashboard_live_tiles_client/Tile.h"
#include "mercury/_http/http_client.h"
#include "mercury/utils/Filesystem.h"
#include "mercury/utils/String.h"

using std::cerr;
using std::endl;
using std::string;

using KESDLTC::Tile;


Tile::Tile(const shared_ptr<IHTTPClient> httpClient):
    Tile("", "", "", "", "", "", "", "", "", httpClient) {
    // Empty constructor.
}


Tile::Tile(const string& id, const string& cover,
           const string& title, const string& description,
           const string& username, const string& app,
           const string& openUrl, const string& fallbackUrl,
           const string& coverPath, const shared_ptr<IHTTPClient> httpClient):
    id(id), cover(cover), title(title),
    description(description), username(username), app(app),
    openUrl(openUrl), fallbackUrl(fallbackUrl), coverPath(coverPath),
    httpClient(httpClient) {
    // Empty constructor.
}


Tile::~Tile() {
    // Empty destructor.
}


bool Tile::initialise(JSON_Value* serialisedData) {
    JSON_Object* data = json_value_get_object(serialisedData);

    // Mandatory fields.
    if (!json_object_has_value_of_type(data, "id", JSONString) ||
        !json_object_has_value_of_type(data, "cover", JSONString) ||
        !json_object_has_value_of_type(data, "title", JSONString) ||
        !json_object_has_value_of_type(data, "description", JSONString) ||
        !json_object_has_value_of_type(data, "username", JSONString) ||
        !json_object_has_value_of_type(data, "app", JSONString) ||
        !json_object_has_value_of_type(data, "openUrl", JSONString) ||
        !json_object_has_value_of_type(data, "fallbackUrl", JSONString)) {
        // NOLINT
        return false;
    }

    this->id = json_object_get_string(data, "id");
    this->cover = json_object_get_string(data, "cover");
    this->title = json_object_get_string(data, "title");
    this->description = json_object_get_string(data, "description");
    this->username = json_object_get_string(data, "username");
    this->app = json_object_get_string(data, "app");
    this->openUrl = json_object_get_string(data, "openUrl");
    this->fallbackUrl = json_object_get_string(data, "fallbackUrl");

    // Optional fields.
    if (json_object_has_value_of_type(data, "coverPath", JSONString)) {
        this->coverPath = json_object_get_string(data, "coverPath");
    }

    return true;
}


JSON_Value* Tile::serialise() const {
    JSON_Value* root = json_value_init_object();
    JSON_Object* data = json_value_get_object(root);

    // Mandatory fields.
    json_object_set_string(data, "id", this->id.c_str());
    json_object_set_string(data, "cover", this->cover.c_str());
    json_object_set_string(data, "title", this->title.c_str());
    json_object_set_string(data, "description", this->description.c_str());
    json_object_set_string(data, "username", this->username.c_str());
    json_object_set_string(data, "app", this->app.c_str());
    json_object_set_string(data, "openUrl", this->openUrl.c_str());
    json_object_set_string(data, "fallbackUrl", this->fallbackUrl.c_str());

    // Optional fields.
    if (!this->coverPath.empty()) {
        json_object_set_string(data, "coverPath", this->coverPath.c_str());
    }

    return root;
}


bool Tile::download(const string& baseDir) {
    string tileDir = baseDir + '/' + this->id;
    this->coverPath = tileDir + '/' + split(this->cover, '/').back();

    // Create the directory path for this tile data.
    if (!create_directories(tileDir)) {
        cerr << "Failed to create directories: path: " << tileDir << endl;
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


string Tile::getId() const {
    return this->id;
}


string Tile::getUsername() const {
    return this->username;
}


string Tile::getTitle() const {
    return this->title;
}


string Tile::getDescription() const {
    return this->description;
}


string Tile::getApp() const {
    return this->app;
}


string Tile::getCover() const {
    return this->cover;
}


string Tile::getOpenUrl() const {
return this->openUrl;
}


string Tile::getFallbackUrl() const {
return this->fallbackUrl;
}


string Tile::getCoverPath() const {
    return this->coverPath;
}
