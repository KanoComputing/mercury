/**
 * \file IOnlineLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_IONLINELOADER_H_
#define INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_IONLINELOADER_H_


#include "kes_moma_picks_client/internal/IPaintingLoader.h"


namespace KESMPC {
namespace internal {

class IOnlineLoader : public IPaintingLoader {
 public:  // Constructors & destructors.
    virtual ~IOnlineLoader() {}

 public:  // Methods.
    virtual double getQueryCooldown() const = 0;
};

}  // namespace internal
}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_IONLINELOADER_H_
