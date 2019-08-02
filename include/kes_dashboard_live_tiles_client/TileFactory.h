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

using std::shared_ptr;
using std::string;


namespace KESDLTC {

class TileFactory : public ITileFactory {
 public:  // Constructors & destructors.
    TileFactory();
    ~TileFactory();

 public:  // ITileFactory Methods.
    shared_ptr<ITile> create() const override;
    shared_ptr<ITile> create(
        const string& id, const string& cover,
        const string& title, const string& description,
        const string& username, const string& app,
        const string& openUrl, const string& fallbackUrl,
        const string& coverPath = "") const override;
};

}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_TILEFACTORY_H_
