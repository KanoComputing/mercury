/**
 * \file PaintingCache.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_PAINTINGCACHE_H_
#define INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_PAINTINGCACHE_H_


#include <list>
#include <memory>
#include <string>

#include "kes_moma_picks_client/internal/IPaintingCache.h"
#include "kes_moma_picks_client/IPainting.h"
#include "kes_moma_picks_client/IPaintingFactory.h"

#include "mercury/utils/IFilesystem.h"


namespace KESMPC {
namespace internal {

class PaintingCache : public IPaintingCache {
 public:  // Constructors & destructors.
    explicit PaintingCache(
        const std::string& cacheDir,
        const std::shared_ptr<IPaintingFactory>& paintingFactory = nullptr,
        const std::shared_ptr<Mercury::Utils::IFilesystem>& fs = nullptr);

 public:  // IPaintingLoader Methods.
    std::list<std::shared_ptr<IPainting>> getPaintings() override;

 public:  // IPaintingCache Methods.
    void update(const std::list<std::shared_ptr<IPainting>>& paintings) override;  // NOLINT
    double getLastUpdated() const override;
    bool isCacheEmpty() const override;

 private:  // Helper methods.
    void load();
    void setCacheData();

 private:  // Members.
    std::string cacheDir;
    std::string cachePath;
    std::shared_ptr<JSON_Value> cacheDataRoot;
    JSON_Object* cacheData;
    std::shared_ptr<IPaintingFactory> paintingFactory;
    std::shared_ptr<Mercury::Utils::IFilesystem> filesystem;

 private:  // Constants.
    const std::string CACHE_FILE = "cache.json";
};

}  // namespace internal
}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_PAINTINGCACHE_H_
