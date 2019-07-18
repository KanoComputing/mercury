/**
 * \file ITileManager.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILEMANAGER_H_
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILEMANAGER_H_


#include <list>
#include <memory>

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"

using std::list;
using std::shared_ptr;


class ITileManager {

 public:  // Constructors & destructors.
    virtual ~ITileManager() {}

 public:  // Methods.
    virtual list<shared_ptr<ITile>> getTiles(bool cache = true) const = 0;
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILEMANAGER_H_
