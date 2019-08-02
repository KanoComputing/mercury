/**
 * \file OnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ONLINELOADER_H_
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ONLINELOADER_H_


#include <list>
#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/IOnlineLoader.h"
#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileFactory.h"
#include "kes_dashboard_live_tiles_client/TileFactory.h"

#include "mercury/_http/http_client.h"
#include "mercury/_http/http_client_interface.h"

using std::list;
using std::make_shared;
using std::shared_ptr;
using std::string;


namespace KESDLTC {
namespace internal {


constexpr double ONE_HOUR_MS = 1000 * 60 * 60;  // in milliseconds


class OnlineLoader : public IOnlineLoader {
 public:  // Constructors & destructors.
    OnlineLoader(
        const string& cacheDir,
        const shared_ptr<IHTTPClient> httpClient = make_shared<HTTPClient>(),
        const shared_ptr<ITileFactory> tileFactory = make_shared<TileFactory>());  // NOLINT

    ~OnlineLoader();

 public:  // ITileLoader Methods.
    /**
     * \throws  BrokenContractsException
     * \throws  DownloadError
     */
    list<shared_ptr<ITile>> getTiles() override;

 public:  // IOnlineLoader Methods.
    double getQueryCooldown() const override;

 public:  // Constants.
    // static constexpr const char* KES_DLT_URL = "https://dlt.os.kes.kano.me/";
    static constexpr const char* KES_DLT_URL = "https://dlt.os.kes.kessandbox.co.uk/";  // NOLINT

 private:  // Members.
    const shared_ptr<IHTTPClient> httpClient;
    const shared_ptr<ITileFactory> tileFactory;
    const string cacheDir;

 private:  // Constants.
    const double QUERY_COOLDOWN = ONE_HOUR_MS;
};

}  // namespace internal
}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ONLINELOADER_H_
