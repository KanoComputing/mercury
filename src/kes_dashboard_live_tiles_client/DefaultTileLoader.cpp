/**
 * \file DefaultTileLoader.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <parson.h>

#include <list>
#include <memory>

#include "kes_dashboard_live_tiles_client/internal/DefaultTileLoader.h"
#include "kes_dashboard_live_tiles_client/ITile.h"
#include "kes_dashboard_live_tiles_client/ITileFactory.h"

using std::list;
using std::shared_ptr;

using KESDLTC::internal::DefaultTileLoader;
using KESDLTC::ITile;
using KESDLTC::ITileFactory;


DefaultTileLoader::DefaultTileLoader(
    const shared_ptr<ITileFactory> tileFactory):
    tileFactory(tileFactory) {
    // Empty constructor.
}


DefaultTileLoader::~DefaultTileLoader() {
    // Empty destructor.
}


list<shared_ptr<ITile>> DefaultTileLoader::getTiles() {
    list<shared_ptr<ITile>> tiles;

    tiles.push_back(this->tileFactory->create(
        "5cd5835432dd0f15550e5086",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5cd5835432dd0f15550e5086.png",  // NOLINT
        "Sparkle Rainbow",
        "",
        "holographicleah",
        "kano-draw",
        "https://world.kano.me/creation/sparkle-rainbow",
        "https://world.kano.me/creation/sparkle-rainbow",
        "/usr/share/kes-dashboad-live-tiles-cli/images/5cd5835432dd0f15550e5086.png"));  // NOLINT

    tiles.push_back(this->tileFactory->create(
        "5c9ce4fc62a4bf0ff1700b77",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5c9ce4fc62a4bf0ff1700b77.gif",  // NOLINT
        "Paints.",
        "",
        "mikegreer",
        "make-apps",
        "https://world.kano.me/creation/paints_5",
        "https://world.kano.me/creation/paints_5",
        "/usr/share/kes-dashboad-live-tiles-cli/images/5c9ce4fc62a4bf0ff1700b77.gif"));  // NOLINT

    tiles.push_back(this->tileFactory->create(
        "5c507ffdd8f37a1015b52eac",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5c507ffdd8f37a1015b52eac.png",  // NOLINT
        "Neon Space Raiders",
        "Starting with the basic spaceship shape from the Make Art challenge, I cloned, staggered and added colours to make a trio of Neon Space Raiders. To create some depth, I added a dimmed circular repeating pattern underneath. As a final touch, each Space Raider got a set of laser canons that shoots different shapes and colours. Feel to free to remix, please credit \"TyrantLizardRex\" :D",  // NOLINT
        "TyrantLizardRex",
        "kano-draw",
        "https://world.kano.me/creation/neon-space-raiders",
        "https://world.kano.me/creation/neon-space-raiders",
        "/usr/share/kes-dashboad-live-tiles-cli/images/5c507ffdd8f37a1015b52eac.png"));  // NOLINT

    tiles.push_back(this->tileFactory->create(
        "5d0103cdebe30b0fe7096c1f",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5d0103cdebe30b0fe7096c1f.png",  // NOLINT
        "Fractal Tree",
        "Tree made using an L-system",
        "hicks",
        "kano-draw",
        "https://world.kano.me/creation/fractal-tree_47",
        "https://world.kano.me/creation/fractal-tree_47",
        "/usr/share/kes-dashboad-live-tiles-cli/images/5d0103cdebe30b0fe7096c1f.png"));  // NOLINT

    return tiles;
}
