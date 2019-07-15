/**
 * \file TileManager.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef __KES_DASHBOARD_LIVE_TILES_CLI_TILE_MANAGER_H__
#define __KES_DASHBOARD_LIVE_TILES_CLI_TILE_MANAGER_H__


#include <list>

#include "mercury/kes_dashboard_live_tiles_cli/ITileManager.h"


class TileManager : public ITileManager {

    // Constructors & destructors.
    public:
        TileManager();
        ~TileManager();

    // ITileManager Methods.
    public:
        std::list<Tile> getTiles(bool cache = true) override;
};

#endif  // __KES_DASHBOARD_LIVE_TILES_CLI_TILE_MANAGER_H__
