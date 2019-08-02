/**
 * \file Tile.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_TILE_H_
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_TILE_H_


#include <parson.h>

#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/ITile.h"

#include "mercury/_http/http_client.h"
#include "mercury/_http/http_client_interface.h"

using std::make_shared;
using std::shared_ptr;
using std::string;


class Tile : public ITile {
 public:  // Constructors & destructors.
    explicit Tile(
        const shared_ptr<IHTTPClient> httpClient = make_shared<HTTPClient>());

    Tile(const string& id, const string& cover,
         const string& title, const string& description,
         const string& username, const string& app,
         const string& openUrl, const string& fallbackUrl,
         const string& coverPath = "",
         const shared_ptr<IHTTPClient> httpClient = make_shared<HTTPClient>());

    ~Tile();

 public:  // ISerialisable Methods.
    bool initialise(JSON_Value* serialisedData) override;
    JSON_Value* serialise() const override;

 public:  // IDownloadable Methods.
    bool download(const string& baseDir) override;

 public:  // ITile Methods.
    string getId() const override;
    string getCover() const override;
    string getTitle() const override;
    string getDescription() const override;
    string getUsername() const override;
    string getApp() const override;
    string getOpenUrl() const override;
    string getFallbackUrl() const override;
    string getCoverPath() const override;

 private:  // Members.
    string id;
    string cover;
    string coverPath;
    string title;
    string description;
    string username;
    string app;
    string openUrl;
    string fallbackUrl;
    const shared_ptr<IHTTPClient> httpClient;
};

#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_TILE_H_
