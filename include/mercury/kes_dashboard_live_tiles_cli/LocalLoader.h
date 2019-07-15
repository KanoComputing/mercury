/**
 * \file LocalLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef __KES_DASHBOARD_LIVE_TILES_CLI_LOCAL_LOADER_H__
#define __KES_DASHBOARD_LIVE_TILES_CLI_LOCAL_LOADER_H__


#include <list>
#include <string>

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/ITileLoader.h"
#include "mercury/kes_dashboard_live_tiles_cli/Tile.h"


class LocalLoader : public ITileLoader {

    // Constructors & destructors.
    public:
        LocalLoader();
        ~LocalLoader();

    // TODO: ILocalLoader Methods.
    public:
        double getLastUpdated();
        void update(std::list<ITile> tiles);

    // ITileLoader Methods. TODO: ILocalLoader Methods.
    public:
        std::list<Tile> getTiles() override;
};

#endif  // __KES_DASHBOARD_LIVE_TILES_CLI_LOCAL_LOADER_H__
