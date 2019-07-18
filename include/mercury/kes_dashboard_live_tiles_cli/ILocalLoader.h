/**
 * \file ILocalLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ILOCALLOADER_H_
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ILOCALLOADER_H_


#include <list>
#include <memory>

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/ITileLoader.h"

using std::list;
using std::shared_ptr;


class ILocalLoader : public ITileLoader {

 public:  // Constructors & destructors.
    virtual ~ILocalLoader() {}

 public:  // Methods.
    virtual void update(const list<shared_ptr<ITile>>& tiles) = 0;
    virtual double getLastUpdated() const = 0;
    virtual bool isCacheEmpty() const = 0;
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_ILOCALLOADER_H_
