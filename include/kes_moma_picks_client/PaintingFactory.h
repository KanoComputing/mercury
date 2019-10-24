/**
 * \file PaintingFactory.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_PAINTINGFACTORY_H_
#define INCLUDE_KES_MOMA_PICKS_CLIENT_PAINTINGFACTORY_H_


#include <memory>
#include <string>

#include "kes_moma_picks_client/IPainting.h"
#include "kes_moma_picks_client/IPaintingFactory.h"

#include "mercury/http/http_client_interface.h"


namespace KESMPC {

class PaintingFactory : public IPaintingFactory {
 public:  // IPaintingFactory Methods.
    std::shared_ptr<IPainting> create() const override;
    std::shared_ptr<IPainting> create(
        const std::string& id,
        const std::string& cover,
        const std::string& title,
        const std::string& username,
        const std::string& dateCreated,
        const std::string& openUrl,
        const std::string& fallbackUrl,
        const std::string& coverPath = "",
        const std::shared_ptr<Mercury::HTTP::IHTTPClient>& httpClient =
            nullptr) const override;
};

}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_PAINTINGFACTORY_H_
