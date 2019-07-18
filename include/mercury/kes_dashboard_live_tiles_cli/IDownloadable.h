/**
 * \file IDownloadable.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_IDOWNLOADABLE_H_
#define INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_IDOWNLOADABLE_H_


#include <string>

using std::string;


class IDownloadable {

 public:  // Constructors & destructors.
    virtual ~IDownloadable() {}

 public:  // Methods.
    virtual bool download(const string& baseDir) = 0;
};

#endif  // INCLUDE_MERCURY_KES_DASHBOARD_LIVE_TILES_CLI_IDOWNLOADABLE_H_
