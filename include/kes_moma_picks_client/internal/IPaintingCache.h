/**
 * \file IPaintingCache.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_IPAINTINGCACHE_H_
#define INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_IPAINTINGCACHE_H_


#include <list>
#include <memory>

#include "kes_moma_picks_client/internal/IPaintingLoader.h"
#include "kes_moma_picks_client/IPainting.h"


namespace KESMPC {
namespace internal {

class IPaintingCache : public IPaintingLoader {
 public:  // Constructors & destructors.
    virtual ~IPaintingCache() {}

 public:  // Methods.
    virtual void update(const std::list<std::shared_ptr<IPainting>>& paintings) = 0;  // NOLINT
    virtual double getLastUpdated() const = 0;
    virtual bool isCacheEmpty() const = 0;
};

}  // namespace internal
}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_IPAINTINGCACHE_H_
