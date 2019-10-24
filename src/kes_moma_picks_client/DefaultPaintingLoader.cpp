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
#include "kes_moma_picks_client/PaintingFactory.h"

using std::list;
using std::make_shared;
using std::shared_ptr;

using KESMPC::internal::DefaultPaintingLoader;
using KESMPC::IPainting;
using KESMPC::IPaintingFactory;
using KESMPC::PaintingFactory;


DefaultPaintingLoader::DefaultPaintingLoader(
    const shared_ptr<IPaintingFactory>& paintingFactory):
        paintingFactory(paintingFactory) {
    //
    if (this->paintingFactory == nullptr)
        this->paintingFactory = make_shared<PaintingFactory>();
}


list<shared_ptr<IPainting>> DefaultPaintingLoader::getPaintings() {
    list<shared_ptr<IPainting>> paintings;

    paintings.push_back(this->paintingFactory->create(
        "5729d34c1ac433ba3e0be584",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5cd5835432dd0f15550e5086.png",  // NOLINT
        "Laughing Emoji Face",
        "Sadness",
        "04 May 2016",
        "https://world.kano.me/creation/laughing-emoji-face",
        "https://world.kano.me/creation/laughing-emoji-face",
        "/usr/share/kesmpc/images/5729d34c1ac433ba3e0be584.png"));

    paintings.push_back(this->paintingFactory->create(
        "5714ae1ad96b1d8f2cfea718",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5c9ce4fc62a4bf0ff1700b77.gif",  // NOLINT
        "Giraffe",
        "annekebeatrix",
        "18 April 2016",
        "https://world.kano.me/creation/giraffe_1",
        "https://world.kano.me/creation/giraffe_1",
        "/usr/share/kesmpc/images/5714ae1ad96b1d8f2cfea718.png"));

    paintings.push_back(this->paintingFactory->create(
        "570e478e8073ac0914b2c97d",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5c507ffdd8f37a1015b52eac.png",  // NOLINT
        "snowy day",
        "aurynlm",
        "13 April 2016",
        "https://world.kano.me/creation/snowy-day",
        "https://world.kano.me/creation/snowy-day",
        "/usr/share/kesmpc/images/570e478e8073ac0914b2c97d.png"));

    paintings.push_back(this->paintingFactory->create(
        "570acd3549bcac0e14d6d231",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5d0103cdebe30b0fe7096c1f.png",  // NOLINT
        "flame through the water",
        "eben",
        "10 April 2016",
        "https://world.kano.me/creation/flame-through-the-water",
        "https://world.kano.me/creation/flame-through-the-water",
        "/usr/share/kesmpc/images/570acd3549bcac0e14d6d231.png"));

    paintings.push_back(this->paintingFactory->create(
        "56976a3ad0dd0ed469e66f69",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5d0103cdebe30b0fe7096c1f.png",  // NOLINT
        "Day-after-Day",
        "alexxboo",
        "14 January 2016",
        "https://world.kano.me/creation/day-after-day",
        "https://world.kano.me/creation/day-after-day",
        "/usr/share/kesmpc/images/56976a3ad0dd0ed469e66f69.png"));

    paintings.push_back(this->paintingFactory->create(
        "5642aeb595257e0a00fb070a",
        "https://s3-eu-west-1.amazonaws.com/world.kano.me/share-items/covers/5d0103cdebe30b0fe7096c1f.png",  // NOLINT
        "Spring",
        "TheMaxim3458",
        "11 November 2015",
        "https://world.kano.me/creation/spring_1",
        "https://world.kano.me/creation/spring_1",
        "/usr/share/kesmpc/images/5642aeb595257e0a00fb070a.png"));

    return paintings;
}
