/**
 * \file ITile.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILE_H__
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILE_H__


#include <string>

#include "mercury/kes_dashboard_live_tiles_cli/IDownloadable.h"
#include "mercury/kes_dashboard_live_tiles_cli/ISerialisable.h"

using std::string;


class ITile : public ISerialisable, public IDownloadable {

 public:  // Constructors & destructors.
    virtual ~ITile() {}

 public:  // KES Contractual Methods.
    virtual string getId() const = 0;
    virtual string getUsername() const = 0;
    virtual string getTitle() const = 0;
    virtual string getDescription() const = 0;
    virtual string getApp() const = 0;
    virtual string getCover() const = 0;
    virtual string getOpenUrl() const = 0;
    virtual string getFallbackUrl() const = 0;

 public:  // Methods.
    virtual string getCoverPath() const = 0;
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ITILE_H__
