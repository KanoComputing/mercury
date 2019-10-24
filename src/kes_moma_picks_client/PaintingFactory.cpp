/**
 * \file PaintingFactory.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <memory>
#include <string>

#include "kes_moma_picks_client/IPainting.h"
#include "kes_moma_picks_client/Painting.h"
#include "kes_moma_picks_client/PaintingFactory.h"

#include "mercury/http/http_client_interface.h"

using std::make_shared;
using std::shared_ptr;
using std::string;

using KESMPC::IPainting;
using KESMPC::Painting;
using KESMPC::PaintingFactory;

using Mercury::HTTP::IHTTPClient;


shared_ptr<IPainting> PaintingFactory::create() const {
    return make_shared<Painting>();
}


shared_ptr<IPainting> PaintingFactory::create(
        const string& id,
        const string& cover,
        const string& title,
        const string& username,
        const string& dateCreated,
        const string& openUrl,
        const string& fallbackUrl,
        const string& coverPath,
        const shared_ptr<IHTTPClient>& httpClient) const {
    return make_shared<Painting>(
        id,
        cover,
        title,
        username,
        dateCreated,
        openUrl,
        fallbackUrl,
        coverPath,
        httpClient);
}
