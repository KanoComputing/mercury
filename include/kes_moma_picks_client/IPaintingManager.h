/**
 * \file IPaintingManager.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_IPAINTINGMANAGER_H_
#define INCLUDE_KES_MOMA_PICKS_CLIENT_IPAINTINGMANAGER_H_


#include <list>
#include <memory>

#include "kes_moma_picks_client/IPainting.h"


namespace KESMPC {

class IPaintingManager {
 public:  // Constructors & destructors.
    virtual ~IPaintingManager() {}

 public:  // Methods.
    virtual std::list<std::shared_ptr<IPainting>> getPaintings(bool cache = true) const = 0;  // NOLINT
};

}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_IPAINTINGMANAGER_H_
