/**
 * \file TileFactory.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_TILEFACTORY_H_
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_TILEFACTORY_H_


#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileFactory.h"


namespace KESDLTC {

class TileFactory : public ITileFactory {
 public:  // Constructors & destructors.
    TileFactory();
    ~TileFactory();

 public:  // ITileFactory Methods.
    std::shared_ptr<ITile> create() const override;
    std::shared_ptr<ITile> create(
        const std::string& id,
        const std::string& cover,
        const std::string& title,
        const std::string& description,
        const std::string& username,
        const std::string& app,
        const std::string& openUrl,
        const std::string& fallbackUrl,
        const std::string& coverPath = "") const override;
};

}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_TILEFACTORY_H_
