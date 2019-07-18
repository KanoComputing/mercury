/**
 * \file LocalLoader.cpp
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

#include "mercury/kes_dashboard_live_tiles_cli/Exceptions.h"
#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/LocalLoader.h"
#include "mercury/kes_dashboard_live_tiles_cli/Tile.h"
#include "mercury/utils/Filesystem.h"
#include "mercury/utils/Time.h"

using std::cerr;
using std::endl;
using std::list;
using std::make_shared;
using std::shared_ptr;
using std::string;


LocalLoader::LocalLoader(const string& cacheDir):
    cacheDir(cacheDir),
    cacheDataRoot(nullptr),
    cacheData(nullptr) {

    this->cachePath = this->cacheDir + "/" + this->CACHE_FILE;

    this->load();
}


LocalLoader::~LocalLoader() {
    // Empty destructor.
}


list<shared_ptr<ITile>> LocalLoader::getTiles() {
    list<shared_ptr<ITile>> tiles;

    // Get from cache first.
    if (!this->isCacheEmpty()) {
        try {
            tiles = this->getCachedTiles();
        } catch(const CorruptedCacheException& e) {
            cerr << e.what() << endl;
        }
    }
    // If no tiles were loaded successfully, cache and return the default ones.
    if (tiles.empty()) {
        tiles = this->getDefaultTiles();
        this->update(tiles);
    }
    return tiles;
}


void LocalLoader::update(const list<shared_ptr<ITile>>& tiles) {
    // TODO: clear cache entirely

    // Update cache with given tiles.
    shared_ptr<JSON_Value> root = shared_ptr<JSON_Value>(
        json_value_init_object(), json_value_free);
    JSON_Object* data = json_value_get_object(root.get());

    JSON_Value* tilesDataRoot = json_value_init_array();
    JSON_Array* tilesData = json_value_get_array(tilesDataRoot);

    json_object_set_number(data, "lastUpdated", getTimestamp());
    json_object_set_value(data, "tilesData", tilesDataRoot);
    for (auto &tile : tiles) {
        json_array_append_value(tilesData, tile.get()->serialise());
    }

    create_directories(this->cacheDir);
    if (json_serialize_to_file_pretty(root.get(), this->cachePath.c_str()) != JSONSuccess) {
        cerr << "LocalLoader: update: Could not serialise data to "
             << this->cachePath << endl;
    }

    this->cacheDataRoot = root;
    this->setCacheData();
}


double LocalLoader::getLastUpdated() const {
    if (!this->isCacheEmpty() &&
        json_object_has_value_of_type(this->cacheData, "lastUpdated", JSONNumber)) {

        return json_object_get_number(this->cacheData, "lastUpdated");
    }
    return -1;
}


bool LocalLoader::isCacheEmpty() const {
    return this->cacheData == nullptr;
}


void LocalLoader::load() {
    this->cacheDataRoot = shared_ptr<JSON_Value>(
        json_parse_file(this->cachePath.c_str()), json_value_free);
    this->setCacheData();
}


void LocalLoader::setCacheData() {
    if (this->cacheDataRoot != nullptr && this->cacheDataRoot.get() != nullptr) {
        this->cacheData = json_value_get_object(this->cacheDataRoot.get());
    }
}


list<shared_ptr<ITile>> LocalLoader::getCachedTiles() const {
    list<shared_ptr<ITile>> tiles;
    JSON_Value* tileData;

    if (!json_object_has_value_of_type(this->cacheData, "tilesData", JSONArray)) {
        throw CorruptedCacheException(
            "tilesData array is missing: ", this->cacheDataRoot.get());
    }

    JSON_Array* tilesData = json_object_get_array(this->cacheData, "tilesData");

    for (int i = 0; i < json_array_get_count(tilesData); i++) {
        shared_ptr<ITile> tile = make_shared<Tile>();
        tileData = json_array_get_value(tilesData, i);

        if (!tile.get()->initialise(tileData)) {
            throw CorruptedCacheException("For item with data: ", tileData);
        }
        tiles.push_back(tile);
    }
    return tiles;
}


list<shared_ptr<ITile>> LocalLoader::getDefaultTiles() const {
    list<shared_ptr<ITile>> tiles;

    tiles.push_back(make_shared<Tile>(
        "5cd5835432dd0f15550e5086",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5cd5835432dd0f15550e5086.png",
        "Sparkle Rainbow",
        "",
        "holographicleah",
        "kano-draw",
        "https://world.kano.me/creation/sparkle-rainbow",
        "https://world.kano.me/creation/sparkle-rainbow",
        "/usr/share/kes-dashboad-live-tiles-cli/images/5cd5835432dd0f15550e5086.png"));

    tiles.push_back(make_shared<Tile>(
        "5c9ce4fc62a4bf0ff1700b77",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5c9ce4fc62a4bf0ff1700b77.gif",
        "Paints.",
        "",
        "mikegreer",
        "make-apps",
        "https://world.kano.me/creation/paints_5",
        "https://world.kano.me/creation/paints_5",
        "/usr/share/kes-dashboad-live-tiles-cli/images/5c9ce4fc62a4bf0ff1700b77.gif"));

    tiles.push_back(make_shared<Tile>(
        "5c507ffdd8f37a1015b52eac",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5c507ffdd8f37a1015b52eac.png",
        "Neon Space Raiders",
        "Starting with the basic spaceship shape from the Make Art challenge, I cloned, staggered and added colours to make a trio of Neon Space Raiders. To create some depth, I added a dimmed circular repeating pattern underneath. As a final touch, each Space Raider got a set of laser canons that shoots different shapes and colours. Feel to free to remix, please credit \"TyrantLizardRex\" :D",
        "TyrantLizardRex",
        "kano-draw",
        "https://world.kano.me/creation/neon-space-raiders",
        "https://world.kano.me/creation/neon-space-raiders",
        "/usr/share/kes-dashboad-live-tiles-cli/images/5c507ffdd8f37a1015b52eac.png"));

    tiles.push_back(make_shared<Tile>(
        "5d0103cdebe30b0fe7096c1f",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5d0103cdebe30b0fe7096c1f.png",
        "Fractal Tree",
        "Tree made using an L-system",
        "hicks",
        "kano-draw",
        "https://world.kano.me/creation/fractal-tree_47",
        "https://world.kano.me/creation/fractal-tree_47",
        "/usr/share/kes-dashboad-live-tiles-cli/images/5d0103cdebe30b0fe7096c1f.png"));

    return tiles;
}
