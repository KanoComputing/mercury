/**
 * \file OnlineLoader.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <iostream>

#include <parson.h>

#include "mercury/_http/exceptions.h"
#include "mercury/kes_dashboard_live_tiles_cli/OnlineLoader.h"


OnlineLoader::OnlineLoader() {
    // Empty constructor.
}


OnlineLoader::~OnlineLoader() {
    // Empty destructor.
}


std::list<Tile> OnlineLoader::getTiles() {
    std::list<Tile> tiles;
    HTTPClient httpClient;
    std::shared_ptr<JSON_Value> response;

    // Download feed from the KES.
    try {
        response = httpClient.GET(this->KES_URL);
    } catch (HTTPRequestFailedError& error) {
        std::cerr << error.what();
    }

    // Download each tile to a temporary directory.

    return tiles;
}
