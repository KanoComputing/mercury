/**
 * \file IOnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_IONLINELOADER_H_
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_IONLINELOADER_H_


#include "mercury/kes_dashboard_live_tiles_cli/ITileLoader.h"


class IOnlineLoader : public ITileLoader {
 public:  // Constructors & destructors.
    virtual ~IOnlineLoader() {}

 public:  // Methods.
    virtual double getQueryCooldown() const = 0;
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_IONLINELOADER_H_
