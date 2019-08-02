/**
 * \file ITileLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILELOADER_H_
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILELOADER_H_


#include <list>
#include <memory>

#include "kes_dashboard_live_tiles_client/ITile.h"

using std::list;
using std::shared_ptr;


class ITileLoader {
 public:  // Constructors & destructors.
    virtual ~ITileLoader() {}

 public:  // Methods.
    virtual list<shared_ptr<ITile>> getTiles() = 0;
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILELOADER_H_
