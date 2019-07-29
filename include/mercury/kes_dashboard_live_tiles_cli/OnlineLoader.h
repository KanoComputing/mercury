/**
 * \file OnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ONLINELOADER_H_
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ONLINELOADER_H_


#include <list>
#include <memory>
#include <string>

#include "mercury/_http/http_client.h"
#include "mercury/_http/http_client_interface.h"
#include "mercury/kes_dashboard_live_tiles_cli/IOnlineLoader.h"
#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/ITileFactory.h"
#include "mercury/kes_dashboard_live_tiles_cli/TileFactory.h"

using std::list;
using std::make_shared;
using std::shared_ptr;
using std::string;


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

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ONLINELOADER_H_
