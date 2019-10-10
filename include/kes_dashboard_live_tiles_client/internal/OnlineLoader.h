/**
 * \file OnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_ONLINELOADER_H_
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_ONLINELOADER_H_


#include <list>
#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/internal/IOnlineLoader.h"
#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileFactory.h"
#include "kes_dashboard_live_tiles_client/TileFactory.h"

#include "mercury/http/http_client.h"
#include "mercury/http/http_client_interface.h"


namespace KESDLTC {
namespace internal {


constexpr double ONE_HOUR_MS = 1000 * 60 * 60;  // in milliseconds


class OnlineLoader : public IOnlineLoader {
 public:  // Constructors & destructors.
    explicit OnlineLoader(
        const std::string& cacheDir,
        const std::shared_ptr<Mercury::HTTP::IHTTPClient> httpClient =
            std::make_shared<Mercury::HTTP::HTTPClient>(),
        const std::shared_ptr<ITileFactory> tileFactory =
            std::make_shared<TileFactory>());

    ~OnlineLoader();

 public:  // ITileLoader Methods.
    /**
     * \throws  BrokenContractsException
     * \throws  DownloadError
     */
    std::list<std::shared_ptr<ITile>> getTiles() override;

 public:  // IOnlineLoader Methods.
    double getQueryCooldown() const override;

 public:  // Constants.
    static constexpr const char* KES_DLT_URL = "https://dlt.os.kes.kano.me/";
    // static constexpr const char* KES_DLT_URL = "https://dlt.os.kes.kessandbox.co.uk/";  // NOLINT

 private:  // Members.
    const std::shared_ptr<Mercury::HTTP::IHTTPClient> httpClient;
    const std::shared_ptr<ITileFactory> tileFactory;
    const std::string cacheDir;

 private:  // Constants.
    const double QUERY_COOLDOWN = ONE_HOUR_MS;
};

}  // namespace internal
}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_INTERNAL_ONLINELOADER_H_
