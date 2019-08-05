/**
 * \file TileManager.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_TILEMANAGER_H_
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_TILEMANAGER_H_


#include <stdlib.h>

#include <list>
#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/internal/IOnlineLoader.h"
#include "kes_dashboard_live_tiles_client/internal/ITileCache.h"
#include "kes_dashboard_live_tiles_client/internal/ITileLoader.h"
#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileManager.h"


namespace KESDLTC {

class TileManager : public ITileManager {
 public:  // Constructors & destructors.
    TileManager(
        const std::string& cacheDir = "",
        const std::shared_ptr<internal::IOnlineLoader> onlineLoader = nullptr,
        const std::shared_ptr<internal::ITileCache> tileCache = nullptr,
        const std::shared_ptr<internal::ITileLoader> defaultTileLoader = nullptr);  // NOLINT
    ~TileManager();

 public:  // ITileManager Methods.
    std::list<std::shared_ptr<ITile>> getTiles(bool cache = false) const override;  // NOLINT

 private:  // Methods.
    bool isCooldown() const;

 private:  // Members.
    std::string cacheDir;
    std::shared_ptr<internal::IOnlineLoader> onlineLoader;
    std::shared_ptr<internal::ITileCache> tileCache;
    std::shared_ptr<internal::ITileLoader> defaultTileLoader;

 private:  // Constants.
    const std::string CACHE_DIRNAME = ".kes-dlt-cli";
};

}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_TILEMANAGER_H_
