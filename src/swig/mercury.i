//
// Swig Definition file to generate Python bindings
//

%module mercury

%include <std_string.i>
%include <std_list.i>
%include <std_shared_ptr.i>


// Add necessary symbols to generated header
%{
    #include "../../include/mercury/theme/theme.h"

    #include "../../include/mercury/kw/kw.h"

    #include "../../include/kes_dashboard_live_tiles_client/internal/DefaultTileLoader.h"
    #include "../../include/kes_dashboard_live_tiles_client/internal/Exceptions.h"
    #include "../../include/kes_dashboard_live_tiles_client/internal/IDownloadable.h"
    #include "../../include/kes_dashboard_live_tiles_client/internal/IOnlineLoader.h"
    #include "../../include/kes_dashboard_live_tiles_client/internal/ISerialisable.h"
    #include "../../include/kes_dashboard_live_tiles_client/internal/ITileCache.h"
    #include "../../include/kes_dashboard_live_tiles_client/internal/ITileLoader.h"
    #include "../../include/kes_dashboard_live_tiles_client/internal/OnlineLoader.h"
    #include "../../include/kes_dashboard_live_tiles_client/internal/TileCache.h"
    #include "../../include/kes_dashboard_live_tiles_client/ITile.h"
    #include "../../include/kes_dashboard_live_tiles_client/ITileFactory.h"
    #include "../../include/kes_dashboard_live_tiles_client/ITileManager.h"
    #include "../../include/kes_dashboard_live_tiles_client/Tile.h"
    #include "../../include/kes_dashboard_live_tiles_client/TileFactory.h"
    #include "../../include/kes_dashboard_live_tiles_client/TileManager.h"

    #include "../../include/kes_moma_picks_client/internal/DefaultPaintingLoader.h"
    #include "../../include/kes_moma_picks_client/internal/Exceptions.h"
    #include "../../include/kes_moma_picks_client/internal/IDownloadable.h"
    #include "../../include/kes_moma_picks_client/internal/IOnlineLoader.h"
    #include "../../include/kes_moma_picks_client/internal/IPaintingCache.h"
    #include "../../include/kes_moma_picks_client/internal/IPaintingLoader.h"
    #include "../../include/kes_moma_picks_client/internal/ISerialisable.h"
    #include "../../include/kes_moma_picks_client/internal/OnlineLoader.h"
    #include "../../include/kes_moma_picks_client/internal/PaintingCache.h"
    #include "../../include/kes_moma_picks_client/IPainting.h"
    #include "../../include/kes_moma_picks_client/IPaintingFactory.h"
    #include "../../include/kes_moma_picks_client/IPaintingManager.h"
    #include "../../include/kes_moma_picks_client/Painting.h"
    #include "../../include/kes_moma_picks_client/PaintingFactory.h"
    #include "../../include/kes_moma_picks_client/PaintingManager.h"
%}

// Type Definitions
%shared_ptr(KESDLTC::internal::IDownloadable);
%shared_ptr(KESDLTC::internal::ISerialisable);
%shared_ptr(KESDLTC::ITile);
%shared_ptr(KESDLTC::ITileFactory);
%shared_ptr(KESDLTC::ITileManager);
%shared_ptr(KESDLTC::Tile);
%shared_ptr(KESDLTC::TileFactory);
%shared_ptr(KESDLTC::TileManager);

%shared_ptr(KESMPC::internal::IDownloadable);
%shared_ptr(KESMPC::internal::ISerialisable);
%shared_ptr(KESMPC::IPainting);
%shared_ptr(KESMPC::IPaintingFactory);
%shared_ptr(KESMPC::IPaintingManager);
%shared_ptr(KESMPC::Painting);
%shared_ptr(KESMPC::PaintingFactory);
%shared_ptr(KESMPC::PaintingManager);

%shared_ptr(Mercury::HTTP::IHTTPClient);


// Generate wrappers for the following objects
%include "../../include/mercury/theme/theme.h"

%include "../../include/mercury/kw/kw.h"

// TODO: IDownloadable and ISerialisable also need to be included here for ITile but names clash.
%include "../../include/kes_dashboard_live_tiles_client/ITile.h"
%include "../../include/kes_dashboard_live_tiles_client/ITileFactory.h"
%include "../../include/kes_dashboard_live_tiles_client/ITileManager.h"
%include "../../include/kes_dashboard_live_tiles_client/Tile.h"
%include "../../include/kes_dashboard_live_tiles_client/TileFactory.h"
%include "../../include/kes_dashboard_live_tiles_client/TileManager.h"

// TODO: IDownloadable and ISerialisable also need to be included here for IPainting but names clash.
%include "../../include/kes_moma_picks_client/IPainting.h"
%include "../../include/kes_moma_picks_client/IPaintingFactory.h"
%include "../../include/kes_moma_picks_client/IPaintingManager.h"
%include "../../include/kes_moma_picks_client/Painting.h"
%include "../../include/kes_moma_picks_client/PaintingFactory.h"
%include "../../include/kes_moma_picks_client/PaintingManager.h"


// Template wrap definitions
%template(ITileSharedPtrList) std::list<std::shared_ptr<KESDLTC::ITile>>;

%template(IPaintingSharedPtrList) std::list<std::shared_ptr<KESMPC::IPainting>>;
