/**
 * \file ITileFactory.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ITILEFACTORY_H__
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ITILEFACTORY_H__


#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/ITile.h"
#include "mercury/http/http_client_interface.h"


namespace KESDLTC {

class ITileFactory {
 public:  // Constructors & destructors.
    virtual ~ITileFactory() {}

 public:  // Methods.
    virtual std::shared_ptr<ITile> create() const = 0;
    virtual std::shared_ptr<ITile> create(
        const std::string& id,
        const std::string& cover,
        const std::string& title,
        const std::string& description,
        const std::string& username,
        const std::string& app,
        const std::string& openUrl,
        const std::string& fallbackUrl,
        const std::string& coverPath = "",
        const std::shared_ptr<Mercury::HTTP::IHTTPClient>& httpClient =
            nullptr) const = 0;
};

}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ITILEFACTORY_H__
