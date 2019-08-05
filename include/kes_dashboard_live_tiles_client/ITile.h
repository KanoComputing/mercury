/**
 * \file ITile.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ITILE_H__
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ITILE_H__


#include <string>

#include "kes_dashboard_live_tiles_client/internal/IDownloadable.h"
#include "kes_dashboard_live_tiles_client/internal/ISerialisable.h"


namespace KESDLTC {

class ITile : public internal::ISerialisable, public internal::IDownloadable {
 public:  // Constructors & destructors.
    virtual ~ITile() {}

 public:  // KES Contractual Methods.
    virtual std::string getId() const = 0;
    virtual std::string getUsername() const = 0;
    virtual std::string getTitle() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getApp() const = 0;
    virtual std::string getCover() const = 0;
    virtual std::string getOpenUrl() const = 0;
    virtual std::string getFallbackUrl() const = 0;

 public:  // Methods.
    virtual std::string getCoverPath() const = 0;
};

}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ITILE_H__
