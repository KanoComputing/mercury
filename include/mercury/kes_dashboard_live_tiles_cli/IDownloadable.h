/**
 * \file IDownloadable.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef __KES_DASHBOARD_LIVE_TILES_CLI_I_DOWNLOADABLE_H__
#define __KES_DASHBOARD_LIVE_TILES_CLI_I_DOWNLOADABLE_H__


#include <parson.h>


class IDownloadable {

    public:
        virtual ~IDownloadable() {}

    public:
        virtual bool download() = 0;
};

#endif  // __KES_DASHBOARD_LIVE_TILES_CLI_I_DOWNLOADABLE_H__
