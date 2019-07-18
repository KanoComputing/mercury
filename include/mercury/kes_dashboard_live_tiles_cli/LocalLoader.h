/**
 * \file LocalLoader.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_LOCALLOADER_H__
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_LOCALLOADER_H__


#include <list>
#include <memory>
#include <string>

#include "mercury/kes_dashboard_live_tiles_cli/ITile.h"
#include "mercury/kes_dashboard_live_tiles_cli/ITileLoader.h"

using std::list;
using std::shared_ptr;
using std::string;


class LocalLoader : public ITileLoader {

 public:  // Constructors & destructors.
    explicit LocalLoader(const string& cacheDir);
    ~LocalLoader();

 public:
    // ITileLoader Methods. TODO: ILocalLoader Methods.
    list<shared_ptr<ITile>> getTiles() override;

 public:  // TODO: ILocalLoader Methods.
    void update(const list<shared_ptr<ITile>>& tiles);
    double getLastUpdated() const;
    bool isCacheEmpty() const;

 private:  // Helper methods.
    void load();
    void setCacheData();
    list<shared_ptr<ITile>> getCachedTiles() const;
    list<shared_ptr<ITile>> getDefaultTiles() const;

 private:  // Members.
    string cacheDir;
    string cachePath;
    shared_ptr<JSON_Value> cacheDataRoot;
    JSON_Object* cacheData;

 private:
    // Constants.
    const string CACHE_FILE = "cache.json";
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_LOCALLOADER_H__
