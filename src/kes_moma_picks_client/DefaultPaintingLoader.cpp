/**
 * \file DefaultPaintingLoader.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <parson.h>

#include <list>
#include <memory>

#include "kes_moma_picks_client/internal/DefaultPaintingLoader.h"
#include "kes_moma_picks_client/IPainting.h"
#include "kes_moma_picks_client/IPaintingFactory.h"

using std::list;
using std::shared_ptr;

using KESMPC::internal::DefaultPaintingLoader;
using KESMPC::IPainting;
using KESMPC::IPaintingFactory;


DefaultPaintingLoader::DefaultPaintingLoader(
    const shared_ptr<IPaintingFactory> paintingFactory):
    paintingFactory(paintingFactory) {
    // Empty constructor.
}


DefaultPaintingLoader::~DefaultPaintingLoader() {
    // Empty destructor.
}


list<shared_ptr<IPainting>> DefaultPaintingLoader::getPaintings() {
    list<shared_ptr<IPainting>> paintings;

    paintings.push_back(this->paintingFactory->create(
        "5cd5835432dd0f15550e5086",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5cd5835432dd0f15550e5086.png",  // NOLINT
        "Sparkle Rainbow",
        "holographicleah",
        "09 July 2019",
        "https://world.kano.me/creation/sparkle-rainbow",
        "https://world.kano.me/creation/sparkle-rainbow",
        "/usr/share/kes-dashboad-live-tiles-cli/images/5cd5835432dd0f15550e5086.png"));  // NOLINT

    paintings.push_back(this->paintingFactory->create(
        "5c9ce4fc62a4bf0ff1700b77",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5c9ce4fc62a4bf0ff1700b77.gif",  // NOLINT
        "Paints.",
        "mikegreer",
        "09 July 2019",
        "https://world.kano.me/creation/paints_5",
        "https://world.kano.me/creation/paints_5",
        "/usr/share/kes-dashboad-live-tiles-cli/images/5c9ce4fc62a4bf0ff1700b77.gif"));  // NOLINT

    paintings.push_back(this->paintingFactory->create(
        "5c507ffdd8f37a1015b52eac",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5c507ffdd8f37a1015b52eac.png",  // NOLINT
        "Neon Space Raiders",
        "TyrantLizardRex",
        "09 July 2019",
        "https://world.kano.me/creation/neon-space-raiders",
        "https://world.kano.me/creation/neon-space-raiders",
        "/usr/share/kes-dashboad-live-tiles-cli/images/5c507ffdd8f37a1015b52eac.png"));  // NOLINT

    paintings.push_back(this->paintingFactory->create(
        "5d0103cdebe30b0fe7096c1f",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5d0103cdebe30b0fe7096c1f.png",  // NOLINT
        "Fractal Tree",
        "hicks",
        "09 July 2019",
        "https://world.kano.me/creation/fractal-tree_47",
        "https://world.kano.me/creation/fractal-tree_47",
        "/usr/share/kes-dashboad-live-tiles-cli/images/5d0103cdebe30b0fe7096c1f.png"));  // NOLINT

    return paintings;
}
