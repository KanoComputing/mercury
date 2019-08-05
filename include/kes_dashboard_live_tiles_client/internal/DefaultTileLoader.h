/**
 * \file DefaultTileLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_DEFAULTTILELOADER_H_
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_DEFAULTTILELOADER_H_

#include <list>
#include <memory>

#include "kes_dashboard_live_tiles_client/internal/ITileLoader.h"
#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileFactory.h"
#include "kes_dashboard_live_tiles_client/TileFactory.h"


namespace KESDLTC {
namespace internal {

class DefaultTileLoader : public ITileLoader {
 public:  // Constructors & destructors.
    DefaultTileLoader(
        const std::shared_ptr<ITileFactory> tileFactory =
            std::make_shared<TileFactory>());
    ~DefaultTileLoader();

 public:  // ITileLoader Methods.
    std::list<std::shared_ptr<ITile>> getTiles() override;

 private:  // Members.
    const std::shared_ptr<ITileFactory> tileFactory;
};

}  // namespace internal
}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_DEFAULTTILELOADER_H_
