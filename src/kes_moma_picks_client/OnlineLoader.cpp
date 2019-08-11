/**
 * \file OnlineLoader.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <parson.h>

#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "kes_moma_picks_client/internal/Exceptions.h"
#include "kes_moma_picks_client/internal/OnlineLoader.h"
#include "kes_moma_picks_client/IPainting.h"
#include "kes_moma_picks_client/IPaintingFactory.h"
#include "mercury/http/http_client_interface.h"

using std::cerr;
using std::endl;
using std::list;
using std::shared_ptr;
using std::string;

using KESMPC::internal::OnlineLoader;
using KESMPC::IPainting;
using KESMPC::IPaintingFactory;

using Mercury::HTTP::DownloadError;
using Mercury::HTTP::IHTTPClient;


OnlineLoader::OnlineLoader(
    const string& cacheDir,
    const shared_ptr<IHTTPClient> httpClient,
    const shared_ptr<IPaintingFactory> paintingFactory):
    cacheDir(cacheDir),
    httpClient(httpClient),
    paintingFactory(paintingFactory) {
    // Empty constructor.
}


OnlineLoader::~OnlineLoader() {
    // Empty destructor.
}


list<shared_ptr<IPainting>> OnlineLoader::getPaintings() {
    list<shared_ptr<IPainting>> paintings;
    shared_ptr<JSON_Value> response;
    JSON_Object* responseData;
    JSON_Array* paintingsData;
    JSON_Value* paintingData;

    // Download feed from the KES.
    response = this->httpClient->GET(string(OnlineLoader::KES_MP_URL));
    responseData = json_value_get_object(response.get());

    // Get the array of painting data objects from the response.
    if (!json_object_has_value_of_type(responseData, "paintings", JSONArray)) {
        throw BrokenContractsException(
            "Does not contain array of paintings: ", response.get());
    }
    paintingsData = json_object_get_array(responseData, "paintings");

    // Create Tile objects from the feed data and download additional data.
    for (int i = 0; i < json_array_get_count(paintingsData); i++) {
        shared_ptr<IPainting> painting = this->paintingFactory->create();
        paintingData = json_array_get_value(paintingsData, i);

        // Initialise a painting object with data from the feed.
        if (!painting->initialise(paintingData)) {
            throw BrokenContractsException("For item with data: ", paintingData);  // NOLINT
        }
        // Download any files associated with the painting.
        if (!painting->download(this->cacheDir)) {
            shared_ptr<char> dataStr(
                json_serialize_to_string_pretty(paintingData),
                json_free_serialized_string);
            throw DownloadError("",
                " Tile with data: " + string(dataStr.get()) +
                " failed to download its data");
        }
        paintings.push_back(painting);
    }
    return paintings;
}


double OnlineLoader::getQueryCooldown() const {
    return this->QUERY_COOLDOWN;
}
