/**
 * \file TileFactory.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_TILEFACTORY_H_
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_TILEFACTORY_H_


#include <memory>

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/ITileFactory.h"

using std::shared_ptr;


class TileFactory : public ITileFactory {

 public:  // Constructors & destructors.
    TileFactory();
    ~TileFactory();

 public:  // ITileFactory Methods.
    shared_ptr<ITile> create() const;
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_TILEFACTORY_H_
