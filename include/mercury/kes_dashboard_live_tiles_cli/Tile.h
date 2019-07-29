/**
 * \file Tile.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_TILE_H_
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_TILE_H_


#include <parson.h>

#include <string>

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"

using std::string;


class Tile : public ITile {
 public:  // Constructors & destructors.
    Tile();

    Tile(const string& id, const string& cover,
         const string& title, const string& description,
         const string& username, const string& app,
         const string& openUrl, const string& fallbackUrl,
         const string& coverPath = "");

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
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_TILE_H_
