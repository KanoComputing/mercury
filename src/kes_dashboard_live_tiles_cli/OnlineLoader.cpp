/**
 * \file OnlineLoader.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <iostream>
#include <list>
#include <memory>
#include <string>

#include <parson.h>

#include "mercury/_http/http_client.h"
#include "mercury/kes_dashboard_live_tiles_cli/Exceptions.h"
#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/OnlineLoader.h"
#include "mercury/kes_dashboard_live_tiles_cli/Tile.h"

using std::cerr;
using std::endl;
using std::list;
using std::make_shared;
using std::shared_ptr;
using std::string;


OnlineLoader::OnlineLoader(const string& cacheDir):
    cacheDir(cacheDir) {
    // Empty constructor.
}


OnlineLoader::~OnlineLoader() {
    // Empty destructor.
}


list<shared_ptr<ITile>> OnlineLoader::getTiles() {
    list<shared_ptr<ITile>> tiles;
    HTTPClient httpClient;
    shared_ptr<JSON_Value> response;
    JSON_Object* responseData;
    JSON_Array* tilesData;
    JSON_Value* tileData;

    // Download feed from the KES.
    response = httpClient.GET(this->KES_URL);
    responseData = json_value_get_object(response.get());

    // Get the array of tile data objects from the response.
    if (!json_object_has_value_of_type(responseData, "shares", JSONArray)) {
        throw BrokenContractsException(
            "Does not contain array of tiles: ", response.get());
    }
    tilesData = json_object_get_array(responseData, "shares");

    // Create Tile objects from the feed data and download additional data.
    for (int i = 0; i < json_array_get_count(tilesData); i++) {
        shared_ptr<ITile> tile = make_shared<Tile>();
        tileData = json_array_get_value(tilesData, i);

        // Initialise a tile object with data from the feed.
        if (!tile.get()->initialise(tileData)) {
            throw BrokenContractsException("For item with data: ", tileData);
        }
        // Download any files associated with the tile.
        if (!tile.get()->download(this->cacheDir)) {
            cerr << "Failed to download: Item with data: "
                 << string(json_serialize_to_string_pretty(tileData))
                 << endl;
            continue;
        }
        tiles.push_back(tile);
    }
    return tiles;
}


int OnlineLoader::getQueryCooldown() {
    return this->QUERY_COOLDOWN;
}
