/**
 * \file TileCache.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_TILECACHE_H_
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_TILECACHE_H_


#include <list>
#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/internal/ITileCache.h"
#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileFactory.h"


namespace KESDLTC {
namespace internal {

class TileCache : public ITileCache {
 public:  // Constructors & destructors.
    explicit TileCache(
        const std::string& cacheDir,
        const std::shared_ptr<ITileFactory>& tileFactory = nullptr);

 public:  // ITileLoader Methods.
    std::list<std::shared_ptr<ITile>> getTiles() override;

 public:  // ITileCache Methods.
    void update(const std::list<std::shared_ptr<ITile>>& tiles) override;
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
    std::shared_ptr<ITileFactory> tileFactory;

 private:  // Constants.
    const std::string CACHE_FILE = "cache.json";
};

}  // namespace internal
}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_TILECACHE_H_
