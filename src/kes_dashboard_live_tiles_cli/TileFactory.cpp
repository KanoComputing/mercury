/**
 * \file TileFactory.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <memory>
#include <string>

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/Tile.h"
#include "mercury/kes_dashboard_live_tiles_cli/TileFactory.h"

using std::make_shared;
using std::shared_ptr;
using std::string;


TileFactory::TileFactory() {
    // Emptry constructor.
}


TileFactory::~TileFactory() {
    // Empty destructor.
}


shared_ptr<ITile> TileFactory::create() const {
    return make_shared<Tile>();
}


shared_ptr<ITile> TileFactory::create(
        const string& id, const string& cover,
        const string& title, const string& description,
        const string& username, const string& app,
        const string& openUrl, const string& fallbackUrl,
        const string& coverPath) const {
    return make_shared<Tile>(
        id, cover, title, description, username, app, openUrl, fallbackUrl,
        coverPath);
}
