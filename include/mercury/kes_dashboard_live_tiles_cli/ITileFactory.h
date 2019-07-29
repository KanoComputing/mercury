/**
 * \file ITileFactory.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILEFACTORY_H__
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILEFACTORY_H__


#include <memory>

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"

using std::shared_ptr;


class ITileFactory {
 public:  // Constructors & destructors.
    virtual ~ITileFactory() {}

 public:  // Methods.
    virtual shared_ptr<ITile> create() const = 0;
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILEFACTORY_H__
