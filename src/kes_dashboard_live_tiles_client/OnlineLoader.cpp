/**
 * \file OnlineLoader.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <parson.h>

#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/internal/Exceptions.h"
#include "kes_dashboard_live_tiles_client/internal/OnlineLoader.h"
#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileFactory.h"
#include "kes_dashboard_live_tiles_client/TileFactory.h"
#include "mercury/http/http_client.h"
#include "mercury/http/http_client_interface.h"

using std::cerr;
using std::endl;
using std::list;
using std::make_shared;
using std::shared_ptr;
using std::string;

using KESDLTC::internal::OnlineLoader;
using KESDLTC::ITile;
using KESDLTC::ITileFactory;
using KESDLTC::TileFactory;

using Mercury::HTTP::DownloadError;
using Mercury::HTTP::IHTTPClient;
using Mercury::HTTP::HTTPClient;


OnlineLoader::OnlineLoader(
    const string& cacheDir,
    const shared_ptr<IHTTPClient>& httpClient,
    const shared_ptr<ITileFactory>& tileFactory):
        cacheDir(cacheDir),
        httpClient(httpClient),
        tileFactory(tileFactory) {
    //
    if (this->httpClient == nullptr)
        this->httpClient = make_shared<HTTPClient>();
    if (this->tileFactory == nullptr)
        this->tileFactory = make_shared<TileFactory>();
}


list<shared_ptr<ITile>> OnlineLoader::getTiles() {
    list<shared_ptr<ITile>> tiles;
    shared_ptr<JSON_Value> response;
    JSON_Object* responseData;
    JSON_Array* tilesData;
    JSON_Value* tileData;

    // Download feed from the KES.
    response = this->httpClient->GET(string(OnlineLoader::KES_DLT_URL));
    responseData = json_value_get_object(response.get());

    // Get the array of tile data objects from the response.
    if (!json_object_has_value_of_type(responseData, "tiles", JSONArray)) {
        throw BrokenContractsException(
            "Does not contain array of tiles: ", response.get());
    }
    tilesData = json_object_get_array(responseData, "tiles");

    // Create Tile objects from the feed data and download additional data.
    for (int i = 0; i < json_array_get_count(tilesData); i++) {
        shared_ptr<ITile> tile = this->tileFactory->create();
        tileData = json_array_get_value(tilesData, i);

        // Initialise a tile object with data from the feed.
        if (!tile->initialise(tileData)) {
            throw BrokenContractsException("For item with data: ", tileData);
        }
        // Download any files associated with the tile.
        if (!tile->download(this->cacheDir)) {
            shared_ptr<char> dataStr(
                json_serialize_to_string_pretty(tileData),
                json_free_serialized_string);
            throw DownloadError("",
                " Tile with data: " + string(dataStr.get()) +
                " failed to download its data");
        }
        tiles.push_back(tile);
    }
    return tiles;
}


double OnlineLoader::getQueryCooldown() const {
    return this->QUERY_COOLDOWN;
}
