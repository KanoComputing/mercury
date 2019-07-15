/**
 * \file LocalLoader.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <parson.h>

#include "mercury/kes_dashboard_live_tiles_cli/LocalLoader.h"


LocalLoader::LocalLoader() {
    // Empty constructor.
}


LocalLoader::~LocalLoader() {
    // Empty destructor.
}


double LocalLoader::getLastUpdated() {
    return 0;
}


void LocalLoader::update(std::list<ITile> tiles) {

}


std::list<Tile> LocalLoader::getTiles() {
    std::list<Tile> tiles;

    // TODO

    return tiles;
}
