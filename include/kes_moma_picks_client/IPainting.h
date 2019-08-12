/**
 * \file IPainting.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_IPAINTING_H_
#define INCLUDE_KES_MOMA_PICKS_CLIENT_IPAINTING_H_


#include <string>

#include "kes_moma_picks_client/internal/IDownloadable.h"
#include "kes_moma_picks_client/internal/ISerialisable.h"


namespace KESMPC {

class IPainting:
    public KESMPC::internal::ISerialisable,
    public KESMPC::internal::IDownloadable {
 public:  // Constructors & destructors.
    virtual ~IPainting() {}

 public:  // KES Contractual Methods.
    virtual std::string getId() const = 0;
    virtual std::string getUsername() const = 0;
    virtual std::string getTitle() const = 0;
    virtual std::string getDateCreated() const = 0;
    virtual std::string getCover() const = 0;
    virtual std::string getOpenUrl() const = 0;
    virtual std::string getFallbackUrl() const = 0;

 public:  // Methods.
    virtual std::string getCoverPath() const = 0;
};

}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_IPAINTING_H_
