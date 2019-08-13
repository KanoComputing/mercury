/**
 * \file PaintingManager.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <exception>
#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "kes_moma_picks_client/internal/DefaultPaintingLoader.h"
#include "kes_moma_picks_client/internal/IOnlineLoader.h"
#include "kes_moma_picks_client/internal/IPaintingCache.h"
#include "kes_moma_picks_client/internal/IPaintingLoader.h"
#include "kes_moma_picks_client/internal/OnlineLoader.h"
#include "kes_moma_picks_client/internal/PaintingCache.h"
#include "kes_moma_picks_client/IPainting.h"
#include "kes_moma_picks_client/PaintingManager.h"
#include "mercury/utils/Time.h"

using std::cerr;
using std::endl;
using std::exception;
using std::list;
using std::make_shared;
using std::shared_ptr;
using std::string;

using KESMPC::internal::DefaultPaintingLoader;
using KESMPC::internal::IOnlineLoader;
using KESMPC::internal::IPaintingCache;
using KESMPC::internal::IPaintingLoader;
using KESMPC::internal::OnlineLoader;
using KESMPC::internal::PaintingCache;
using KESMPC::IPainting;
using KESMPC::PaintingManager;


PaintingManager::PaintingManager(
    const string& cacheDir,
    const shared_ptr<IOnlineLoader> onlineLoader,
    const shared_ptr<IPaintingCache> paintingCache,
    const shared_ptr<IPaintingLoader> defaultPaintingLoader):
    cacheDir(cacheDir),
    onlineLoader(onlineLoader),
    paintingCache(paintingCache),
    defaultPaintingLoader(defaultPaintingLoader) {
    // NOLINT
    if (this->cacheDir == "")
        this->cacheDir = string(getenv("HOME")) + "/" + this->CACHE_DIRNAME;
    if (this->onlineLoader == nullptr)
        this->onlineLoader = make_shared<OnlineLoader>(this->cacheDir);
    if (this->paintingCache == nullptr)
        this->paintingCache = make_shared<PaintingCache>(this->cacheDir);
    if (this->defaultPaintingLoader == nullptr)
        this->defaultPaintingLoader = make_shared<DefaultPaintingLoader>();
}


PaintingManager::~PaintingManager() {
    // Empty destructor.
}


list<shared_ptr<IPainting>> PaintingManager::getPaintings(bool cache) const {
    list<shared_ptr<IPainting>> paintings;

    // Check that we're not spamming the server.
    if (!cache && !this->isCooldown()) {
        // Download the feed of paintings from the KES.
        try {
            paintings = this->onlineLoader->getPaintings();
        } catch (const exception& e) {
            cerr << "PaintingManager: Caught: " << e.what() << endl;
        } catch (...) {
            cerr << "PaintingManager: Caught unexpected error" << endl;
        }

        // If it was successful, update the cache.
        if (!paintings.empty()) {
            this->paintingCache->update(paintings);
            return paintings;
        }
    }

    // If paintings were not retrieved from the KES directly, grab
    // the cached ones.
    try {
        paintings = this->paintingCache->getPaintings();
    } catch (const exception& e) {
        cerr << "PaintingManager: Caught: " << e.what() << endl;
    } catch (...) {
        cerr << "PaintingManager: Caught unexpected error" << endl;
    }

    // If everything else failed, return some defaults.
    if (paintings.empty()) {
        paintings = this->defaultPaintingLoader->getPaintings();
    }

    return paintings;
}


bool PaintingManager::isCooldown() const {
    return (this->paintingCache->getLastUpdated() +
            this->onlineLoader->getQueryCooldown())
           > getTimestamp();
}