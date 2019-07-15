/**
 * \file ITile.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef __KES_DASHBOARD_LIVE_TILES_CLI_I_TILE_H__
#define __KES_DASHBOARD_LIVE_TILES_CLI_I_TILE_H__


#include <memory>
#include <string>

#include <parson.h>

#include "mercury/kes_dashboard_live_tiles_cli/IDownloadable.h"
#include "mercury/kes_dashboard_live_tiles_cli/ISerialisable.h"


class ITile : public ISerialisable, IDownloadable {

    public:
        virtual ~ITile() {}

    // KES Contractual Methods.
    public:
        virtual std::string getUsername() = 0;
        virtual std::string getTitle() = 0;
        virtual std::string getDescription() = 0;
        virtual std::string getApp() = 0;
        virtual std::string getCover() = 0;
        virtual std::string getOpenUrl() = 0;
        virtual std::string getFallbackUrl() = 0;

    // Methods.
    public:
        virtual std::string getCoverPath() = 0;
};

#endif  // __KES_DASHBOARD_LIVE_TILES_CLI_I_TILE_H__
