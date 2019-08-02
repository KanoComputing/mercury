/**
 * \file ITileFactory.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ITILEFACTORY_H__
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ITILEFACTORY_H__


#include <memory>
#include <string>

#include "kes_dashboard_live_tiles_client/ITile.h"

using std::shared_ptr;
using std::string;


class ITileFactory {
 public:  // Constructors & destructors.
    virtual ~ITileFactory() {}

 public:  // Methods.
    virtual shared_ptr<ITile> create() const = 0;
    virtual shared_ptr<ITile> create(
        const string& id, const string& cover,
        const string& title, const string& description,
        const string& username, const string& app,
        const string& openUrl, const string& fallbackUrl,
        const string& coverPath = "") const = 0;
};

#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ITILEFACTORY_H__
