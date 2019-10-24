/**
 * \file TileCache.cpp
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
#include "kes_dashboard_live_tiles_client/internal/TileCache.h"
#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileFactory.h"
#include "kes_dashboard_live_tiles_client/TileFactory.h"
#include "mercury/utils/Filesystem.h"
#include "mercury/utils/Time.h"

using std::cerr;
using std::endl;
using std::list;
using std::make_shared;
using std::shared_ptr;
using std::string;

using KESDLTC::internal::CorruptedCacheException;
using KESDLTC::internal::TileCache;
using KESDLTC::ITile;
using KESDLTC::ITileFactory;
using KESDLTC::TileFactory;


TileCache::TileCache(
    const string& cacheDir,
    const shared_ptr<ITileFactory>& tileFactory):
        cacheDir(cacheDir),
        tileFactory(tileFactory),
        cacheDataRoot(nullptr),
        cacheData(nullptr) {
    //
    this->cachePath = this->cacheDir + "/" + this->CACHE_FILE;
    if (this->tileFactory == nullptr)
        this->tileFactory = make_shared<TileFactory>();

    this->load();
}


void TileCache::load() {
    this->cacheDataRoot = shared_ptr<JSON_Value>(
        json_parse_file(this->cachePath.c_str()), json_value_free);
    this->setCacheData();
}


void TileCache::setCacheData() {
    if (this->cacheDataRoot != nullptr &&
        this->cacheDataRoot.get() != nullptr) {
        //
        this->cacheData = json_value_get_object(this->cacheDataRoot.get());
    } else {
        this->cacheData = nullptr;
    }
}


list<shared_ptr<ITile>> TileCache::getTiles() {
    list<shared_ptr<ITile>> tiles;
    JSON_Value* tileData;
    JSON_Array* tilesData;

    // Return immediately if the cache is empty.
    if (this->isCacheEmpty())
        return tiles;

    if (!json_object_has_value_of_type(
            this->cacheData, "tiles", JSONArray)) {
        throw CorruptedCacheException(
            "tilesData array is missing: ", this->cacheDataRoot.get());
    }
    tilesData = json_object_get_array(this->cacheData, "tiles");

    // Initialise all tiles with data from the cache and return.
    for (int i = 0; i < json_array_get_count(tilesData); i++) {
        shared_ptr<ITile> tile = this->tileFactory->create();
        tileData = json_array_get_value(tilesData, i);

        if (!tile->initialise(tileData)) {
            throw CorruptedCacheException("For item with data: ", tileData);
        }
        tiles.push_back(tile);
    }
    return tiles;
}


void TileCache::update(const list<shared_ptr<ITile>>& tiles) {
    // TODO: clear cache entirely?

    // Serialise all tiles in order to update the cache.
    shared_ptr<JSON_Value> root = shared_ptr<JSON_Value>(
        json_value_init_object(), json_value_free);
    JSON_Object* data = json_value_get_object(root.get());

    JSON_Value* tilesDataRoot = json_value_init_array();
    JSON_Array* tilesData = json_value_get_array(tilesDataRoot);

    json_object_set_number(data, "lastUpdated", getTimestamp());
    json_object_set_value(data, "tiles", tilesDataRoot);
    for (auto &tile : tiles) {
        json_array_append_value(tilesData, tile->serialise());
    }

    // Ensure the directory and write all serialised tiles to the cache.
    create_directories(this->cacheDir);

    if (json_serialize_to_file_pretty(
            root.get(), this->cachePath.c_str()) != JSONSuccess) {
        // TODO: Throw an exception here?
        cerr << "TileCache: update: Could not serialise data to "
             << this->cachePath << endl;
    }

    // Update pointers to the new data.
    this->cacheDataRoot = root;
    this->setCacheData();
}


double TileCache::getLastUpdated() const {
    if (!this->isCacheEmpty() &&
        json_object_has_value_of_type(
            this->cacheData, "lastUpdated", JSONNumber)) {
        return json_object_get_number(this->cacheData, "lastUpdated");
    }
    return -1;
}


bool TileCache::isCacheEmpty() const {
    return this->cacheData == nullptr;
}
