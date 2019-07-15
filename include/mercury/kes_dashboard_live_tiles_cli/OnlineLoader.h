/**
 * \file OnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef __KES_DASHBOARD_LIVE_TILES_CLI_ONLINE_LOADER_H__
#define __KES_DASHBOARD_LIVE_TILES_CLI_ONLINE_LOADER_H__


#include <list>
#include <string>

#include "mercury/_http/http_client.h"
#include "mercury/kes_dashboard_live_tiles_cli/ITileLoader.h"


class OnlineLoader : public ITileLoader {

    // Constructors & destructors.
    public:
        OnlineLoader();
        ~OnlineLoader();

    // ITileLoader Methods.
    public:
        std::list<Tile> getTiles() override;

    // Constants.
    private:
        // NOTE: Slash at the end is important.
        const std::string KES_URL = "https://ws.os.kes.kessandbox.co.uk/";
};

#endif  // __KES_DASHBOARD_LIVE_TILES_CLI_ONLINE_LOADER_H__
