/**
 * \file Tile.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#include <memory>
#include <string>

#include <parson.h>

#include "mercury/kes_dashboard_live_tiles_cli/Tile.h"


Tile::Tile() {
    // Empty constructor.
}


Tile::~Tile() {
    // Empty destructor.
}


bool Tile::initialise(std::shared_ptr<JSON_Value> serialisedData) {
    // TODO

    return false;
}


std::shared_ptr<JSON_Value> Tile::serialise() {
    std::shared_ptr<JSON_Value> data = nullptr;

    // TODO

    return data;
}


bool Tile::download() {
    // TODO

    return false;
}


std::string Tile::getUsername() {
    return this->username;
}


std::string Tile::getTitle() {
    return this->title;
}


std::string Tile::getDescription() {
    return this->description;
}


std::string Tile::getApp() {
    return this->app;
}


std::string Tile::getCover() {
    return this->cover;
}


std::string Tile::getOpenUrl() {
return this->openUrl;
}


std::string Tile::getFallbackUrl() {
return this->fallbackUrl;
}


std::string Tile::getCoverPath() {
    return this->coverPath;
}
