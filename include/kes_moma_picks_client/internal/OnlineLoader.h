/**
 * \file OnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_ONLINELOADER_H_
#define INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_ONLINELOADER_H_


#include <list>
#include <memory>
#include <string>

#include "kes_moma_picks_client/internal/IOnlineLoader.h"
#include "kes_moma_picks_client/IPainting.h"
#include "kes_moma_picks_client/IPaintingFactory.h"
#include "kes_moma_picks_client/PaintingFactory.h"

#include "mercury/http/http_client.h"
#include "mercury/http/http_client_interface.h"


namespace KESMPC {
namespace internal {


constexpr double ONE_HOUR_MS = 1000 * 60 * 60;  // in milliseconds


class OnlineLoader : public IOnlineLoader {
 public:  // Constructors & destructors.
    explicit OnlineLoader(
        const std::string& cacheDir,
        const std::shared_ptr<Mercury::HTTP::IHTTPClient> httpClient =
            std::make_shared<Mercury::HTTP::HTTPClient>(),
        const std::shared_ptr<IPaintingFactory> paintingFactory =
            std::make_shared<PaintingFactory>());

    ~OnlineLoader();

 public:  // IPaintingLoader Methods.
    /**
     * \throws  BrokenContractsException
     * \throws  DownloadError
     */
    std::list<std::shared_ptr<IPainting>> getPaintings() override;

 public:  // IOnlineLoader Methods.
    double getQueryCooldown() const override;

 public:  // Constants.
    static constexpr const char* KES_MP_URL = "https://mp.os.kes.kano.me/";
    // static constexpr const char* KES_MP_URL = "https://mp.os.kes.kessandbox.co.uk/";  // NOLINT

 private:  // Members.
    const std::shared_ptr<Mercury::HTTP::IHTTPClient> httpClient;
    const std::shared_ptr<IPaintingFactory> paintingFactory;
    const std::string cacheDir;

 private:  // Constants.
    const double QUERY_COOLDOWN = ONE_HOUR_MS;
};

}  // namespace internal
}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_ONLINELOADER_H_
