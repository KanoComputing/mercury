/**
 * \file Painting.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_PAINTING_H_
#define INCLUDE_KES_MOMA_PICKS_CLIENT_PAINTING_H_


#include <parson.h>

#include <memory>
#include <string>

#include "kes_moma_picks_client/IPainting.h"

#include "mercury/http/http_client_interface.h"
#include "mercury/utils/IFilesystem.h"


namespace KESMPC {

class Painting : public IPainting {
 public:  // Constructors & destructors.
    explicit Painting(
        const std::shared_ptr<Mercury::HTTP::IHTTPClient>& httpClient = nullptr,  // NOLINT
        const std::shared_ptr<Mercury::Utils::IFilesystem>& fs = nullptr);

    Painting(
        const std::string& id,
        const std::string& cover,
        const std::string& title,
        const std::string& username,
        const std::string& dateCreated,
        const std::string& openUrl,
        const std::string& fallbackUrl,
        const std::string& coverPath = "",
        const std::shared_ptr<Mercury::HTTP::IHTTPClient>& httpClient = nullptr,  // NOLINT
        const std::shared_ptr<Mercury::Utils::IFilesystem>& fs = nullptr);

 public:  // ISerialisable Methods.
    bool initialise(JSON_Value* serialisedData) override;
    JSON_Value* serialise() const override;

 public:  // IDownloadable Methods.
    bool download(const std::string& baseDir) override;

 public:  // IPainting Methods.
    std::string getId() const override;
    std::string getCover() const override;
    std::string getTitle() const override;
    std::string getUsername() const override;
    std::string getDateCreated() const override;
    std::string getOpenUrl() const override;
    std::string getFallbackUrl() const override;
    std::string getCoverPath() const override;

 private:  // Members.
    std::string id;
    std::string cover;
    std::string coverPath;
    std::string title;
    std::string username;
    std::string dateCreated;
    std::string openUrl;
    std::string fallbackUrl;
    std::shared_ptr<Mercury::HTTP::IHTTPClient> httpClient;
    std::shared_ptr<Mercury::Utils::IFilesystem> filesystem;
};

}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_PAINTING_H_
