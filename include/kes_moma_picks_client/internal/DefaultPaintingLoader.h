/**
 * \file DefaultPaintingLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_DEFAULTPAINTINGLOADER_H_
#define INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_DEFAULTPAINTINGLOADER_H_


#include <list>
#include <memory>

#include "kes_moma_picks_client/internal/IPaintingLoader.h"
#include "kes_moma_picks_client/IPainting.h"
#include "kes_moma_picks_client/IPaintingFactory.h"


namespace KESMPC {
namespace internal {

class DefaultPaintingLoader : public IPaintingLoader {
 public:  // Constructors & destructors.
    explicit DefaultPaintingLoader(
        const std::shared_ptr<IPaintingFactory>& paintingFactory = nullptr);

 public:  // IPaintingLoader Methods.
    std::list<std::shared_ptr<IPainting>> getPaintings() override;

 private:  // Members.
    std::shared_ptr<IPaintingFactory> paintingFactory;
};

}  // namespace internal
}  // namespace KESMPC


#endif  // INCLUDE_KES_MOMA_PICKS_CLIENT_INTERNAL_DEFAULTPAINTINGLOADER_H_
