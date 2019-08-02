/**
 * \file Tile.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_TILE_H_
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_TILE_H_


#include <parson.h>

#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/ITile.h"

#include "mercury/_http/http_client.h"
#include "mercury/_http/http_client_interface.h"


namespace KESDLTC {

class Tile : public ITile {
 public:  // Constructors & destructors.
    explicit Tile(
        const std::shared_ptr<IHTTPClient> httpClient =
            std::make_shared<HTTPClient>());

    Tile(const std::string& id,
         const std::string& cover,
         const std::string& title,
         const std::string& description,
         const std::string& username,
         const std::string& app,
         const std::string& openUrl,
         const std::string& fallbackUrl,
         const std::string& coverPath = "",
         const std::shared_ptr<IHTTPClient> httpClient =
            std::make_shared<HTTPClient>());

    ~Tile();

 public:  // ISerialisable Methods.
    bool initialise(JSON_Value* serialisedData) override;
    JSON_Value* serialise() const override;

 public:  // IDownloadable Methods.
    bool download(const std::string& baseDir) override;

 public:  // ITile Methods.
    std::string getId() const override;
    std::string getCover() const override;
    std::string getTitle() const override;
    std::string getDescription() const override;
    std::string getUsername() const override;
    std::string getApp() const override;
    std::string getOpenUrl() const override;
    std::string getFallbackUrl() const override;
    std::string getCoverPath() const override;

 private:  // Members.
    std::string id;
    std::string cover;
    std::string coverPath;
    std::string title;
    std::string description;
    std::string username;
    std::string app;
    std::string openUrl;
    std::string fallbackUrl;
    const std::shared_ptr<IHTTPClient> httpClient;
};

}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_TILE_H_
