/**
 * \file IPaintingLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_IPAINTINGLOADER_H_
#define INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_IPAINTINGLOADER_H_


#include <list>
#include <memory>

#include "kes_moma_picks_client/IPainting.h"


namespace KESMPC {
namespace internal {

class IPaintingLoader {
 public:  // Constructors & destructors.
    virtual ~IPaintingLoader() {}

 public:  // Methods.
    virtual std::list<std::shared_ptr<IPainting>> getPaintings() = 0;
};

}  // namespace internal
}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_IPAINTINGLOADER_H_
