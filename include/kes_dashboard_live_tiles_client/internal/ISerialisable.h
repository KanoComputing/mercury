/**
 * \file ISerialisable.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ISERIALISABLE_H_
#define INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ISERIALISABLE_H_


#include <parson.h>


namespace KESDLTC {
namespace internal {

class ISerialisable {
 public:  // Constructors & destructors.
    virtual ~ISerialisable() {}

 public:  // Methods.
    virtual bool initialise(JSON_Value* serialisedData) = 0;
    virtual JSON_Value* serialise() const = 0;
};

}  // namespace internal
}  // namespace KESDLTC


#endif  // INCLUDE_KES_DASHBOARD_LIVE_TILES_CLIENT_ISERIALISABLE_H_
