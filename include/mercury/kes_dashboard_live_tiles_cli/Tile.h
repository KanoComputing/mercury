/**
 * \file Tile.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef __KES_DASHBOARD_LIVE_TILES_CLI_TILE_H__
#define __KES_DASHBOARD_LIVE_TILES_CLI_TILE_H__


#include <parson.h>

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"


class Tile : public ITile {

    // Constructors & destructors.
    public:
        Tile();
        ~Tile();

    // ISerialisable Methods.
    public:
        bool initialise(std::shared_ptr<JSON_Value> serialisedData) override;
        std::shared_ptr<JSON_Value> serialise() override;

    // IDownloadable Methods.
    public:
        bool download() override;

    // ITile Methods.
    public:
        std::string getCover() override;
        std::string getTitle() override;
        std::string getDescription() override;
        std::string getUsername() override;
        std::string getApp() override;
        std::string getOpenUrl() override;
        std::string getFallbackUrl() override;
        std::string getCoverPath() override;

    // Members.
    private:
        std::string cover;
        std::string coverPath;
        std::string title;
        std::string description;
        std::string username;
        std::string app;
        std::string openUrl;
        std::string fallbackUrl;
};

#endif  // __KES_DASHBOARD_LIVE_TILES_CLI_TILE_H__
