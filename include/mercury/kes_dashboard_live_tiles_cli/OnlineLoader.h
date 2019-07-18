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
#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/ITileLoader.h"

using std::list;
using std::shared_ptr;
using std::string;


constexpr int ONE_HOUR_MS = 1000 * 60 * 60;  // in milliseconds


class OnlineLoader : public ITileLoader {

 public:  // Constructors & destructors.
    explicit OnlineLoader(const string& cacheDir);
    ~OnlineLoader();

 public:  // ITileLoader Methods.
    /**
     * \throws  BrokenContractsException
     * \throws  DownloadError
     */
    list<shared_ptr<ITile>> getTiles() override;

 public:  // TODO: IOnlineLoader Methods.
    int getQueryCooldown();

 private:  // Members.
    string cacheDir;

 private:  // Constants.
    // NOTE: Slash at the end is important.
    const string KES_URL = "https://ws.os.kes.kessandbox.co.uk/";
    const int QUERY_COOLDOWN = ONE_HOUR_MS;
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ONLINELOADER_H_
