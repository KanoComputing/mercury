/**
 * \file PaintingCache.cpp
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

#include "kes_moma_picks_client/internal/Exceptions.h"
#include "kes_moma_picks_client/internal/PaintingCache.h"
#include "kes_moma_picks_client/IPainting.h"
#include "kes_moma_picks_client/IPaintingFactory.h"
#include "kes_moma_picks_client/PaintingFactory.h"
#include "mercury/utils/Filesystem.h"
#include "mercury/utils/Time.h"

using std::cerr;
using std::endl;
using std::list;
using std::make_shared;
using std::shared_ptr;
using std::string;

using KESMPC::internal::CorruptedCacheException;
using KESMPC::internal::PaintingCache;
using KESMPC::IPainting;
using KESMPC::IPaintingFactory;
using KESMPC::PaintingFactory;


PaintingCache::PaintingCache(
    const string& cacheDir,
    const shared_ptr<IPaintingFactory>& paintingFactory):
        cacheDir(cacheDir),
        paintingFactory(paintingFactory),
        cacheDataRoot(nullptr),
        cacheData(nullptr) {
    //
    this->cachePath = this->cacheDir + "/" + this->CACHE_FILE;
    if (this->paintingFactory == nullptr)
        this->paintingFactory = make_shared<PaintingFactory>();
    this->load();
}


void PaintingCache::load() {
    this->cacheDataRoot = shared_ptr<JSON_Value>(
        json_parse_file(this->cachePath.c_str()), json_value_free);
    this->setCacheData();
}


void PaintingCache::setCacheData() {
    if (this->cacheDataRoot != nullptr &&
        this->cacheDataRoot.get() != nullptr) {
        // NOLINT
        this->cacheData = json_value_get_object(this->cacheDataRoot.get());
    } else {
        this->cacheData = nullptr;
    }
}


list<shared_ptr<IPainting>> PaintingCache::getPaintings() {
    list<shared_ptr<IPainting>> paintings;
    JSON_Value* paintingData;
    JSON_Array* paintingsData;

    // Return immediately if the cache is empty.
    if (this->isCacheEmpty())
        return paintings;

    if (!json_object_has_value_of_type(
            this->cacheData, "paintings", JSONArray)) {
        throw CorruptedCacheException(
            "paintingsData array is missing: ", this->cacheDataRoot.get());
    }
    paintingsData = json_object_get_array(this->cacheData, "paintings");

    // Initialise all paintings with data from the cache and return.
    for (int i = 0; i < json_array_get_count(paintingsData); i++) {
        shared_ptr<IPainting> painting = this->paintingFactory->create();
        paintingData = json_array_get_value(paintingsData, i);

        if (!painting->initialise(paintingData)) {
            throw CorruptedCacheException("For item with data: ", paintingData);  // NOLINT
        }
        paintings.push_back(painting);
    }
    return paintings;
}


void PaintingCache::update(const list<shared_ptr<IPainting>>& paintings) {
    // TODO: clear cache entirely?

    // Serialise all paintings in order to update the cache.
    shared_ptr<JSON_Value> root = shared_ptr<JSON_Value>(
        json_value_init_object(), json_value_free);
    JSON_Object* data = json_value_get_object(root.get());

    JSON_Value* paintingsDataRoot = json_value_init_array();
    JSON_Array* paintingsData = json_value_get_array(paintingsDataRoot);

    json_object_set_number(data, "lastUpdated", getTimestamp());
    json_object_set_value(data, "paintings", paintingsDataRoot);
    for (auto &painting : paintings) {
        json_array_append_value(paintingsData, painting->serialise());
    }

    // Ensure the directory and write all serialised paintings to the cache.
    create_directories(this->cacheDir);

    if (json_serialize_to_file_pretty(
            root.get(), this->cachePath.c_str()) != JSONSuccess) {
        // TODO: Throw an exception here?
        cerr << "PaintingCache: update: Could not serialise data to "
             << this->cachePath << endl;
    }

    // Update pointers to the new data.
    this->cacheDataRoot = root;
    this->setCacheData();
}


double PaintingCache::getLastUpdated() const {
    if (!this->isCacheEmpty() &&
        json_object_has_value_of_type(
            this->cacheData, "lastUpdated", JSONNumber)) {
        return json_object_get_number(this->cacheData, "lastUpdated");
    }
    return -1;
}


bool PaintingCache::isCacheEmpty() const {
    return this->cacheData == nullptr;
}
