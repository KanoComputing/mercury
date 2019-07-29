/**
 * \file TileManager.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_TILEMANAGER_H_
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_TILEMANAGER_H_


#include <list>
#include <memory>
#include <string>

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/ITileManager.h"

using std::list;
using std::string;
using std::shared_ptr;


class TileManager : public ITileManager {
 public:  // Constructors & destructors.
    TileManager();
    ~TileManager();

 public:  // ITileManager Methods.
    list<shared_ptr<ITile>> getTiles(bool cache = true) const override;

 private:  // Members.
    string cacheDir;

 private:  // Constants.
    const string CACHE_DIR = ".kes-dlt-cli";
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_TILEMANAGER_H_
