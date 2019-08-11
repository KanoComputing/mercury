/**
 * \file PaintingManager.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_PAINTINGMANAGER_H_
#define INCLUDE_KES_MOMA_PICKS_CLIENT_PAINTINGMANAGER_H_


#include <stdlib.h>

#include <list>
#include <memory>
#include <string>

#include "kes_moma_picks_client/internal/IOnlineLoader.h"
#include "kes_moma_picks_client/internal/IPaintingCache.h"
#include "kes_moma_picks_client/internal/IPaintingLoader.h"
#include "kes_moma_picks_client/IPainting.h"
#include "kes_moma_picks_client/IPaintingManager.h"


namespace KESMPC {

class PaintingManager : public IPaintingManager {
 public:  // Constructors & destructors.
    PaintingManager(
        const std::string& cacheDir = "",
        const std::shared_ptr<internal::IOnlineLoader> onlineLoader = nullptr,
        const std::shared_ptr<internal::IPaintingCache> paintingCache = nullptr,  // NOLINT
        const std::shared_ptr<internal::IPaintingLoader> defaultPaintingLoader = nullptr);  // NOLINT
    ~PaintingManager();

 public:  // IPaintingManager Methods.
    std::list<std::shared_ptr<IPainting>> getPaintings(bool cache = false) const override;  // NOLINT

 private:  // Methods.
    bool isCooldown() const;

 private:  // Members.
    std::string cacheDir;
    std::shared_ptr<internal::IOnlineLoader> onlineLoader;
    std::shared_ptr<internal::IPaintingCache> paintingCache;
    std::shared_ptr<internal::IPaintingLoader> defaultPaintingLoader;

 private:  // Constants.
    const std::string CACHE_DIRNAME = ".kes-mp-cli";
};

}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_PAINTINGMANAGER_H_
