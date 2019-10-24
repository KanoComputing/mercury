/**
 * \file IPaintingFactory.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_IPAINTINGFACTORY_H__
#define INCLUDE_KES_MOMA_PICKS_CLIENT_IPAINTINGFACTORY_H__


#include <memory>
#include <string>

#include "kes_moma_picks_client/IPainting.h"

#include "mercury/http/http_client_interface.h"


namespace KESMPC {

class IPaintingFactory {
 public:  // Constructors & destructors.
    virtual ~IPaintingFactory() {}

 public:  // Methods.
    virtual std::shared_ptr<IPainting> create() const = 0;
    virtual std::shared_ptr<IPainting> create(
        const std::string& id,
        const std::string& cover,
        const std::string& title,
        const std::string& username,
        const std::string& dateCreated,
        const std::string& openUrl,
        const std::string& fallbackUrl,
        const std::string& coverPath = "",
        const std::shared_ptr<Mercury::HTTP::IHTTPClient>& httpClient =
            nullptr) const = 0;
};

}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_IPAINTINGFACTORY_H__
