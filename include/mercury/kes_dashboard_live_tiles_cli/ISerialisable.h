/**
 * \file ISerialisable.h
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 * \brief     TODO
 */


#ifndef __KES_DASHBOARD_LIVE_TILES_CLI_I_SERIALISABLE_H__
#define __KES_DASHBOARD_LIVE_TILES_CLI_I_SERIALISABLE_H__


#include <memory>

#include <parson.h>


class ISerialisable {

    public:
        virtual ~ISerialisable() {}

    public:
        virtual bool initialise(std::shared_ptr<JSON_Value> serialisedData) = 0;
        virtual std::shared_ptr<JSON_Value> serialise() = 0;
};

#endif  // __KES_DASHBOARD_LIVE_TILES_CLI_I_SERIALISABLE_H__
