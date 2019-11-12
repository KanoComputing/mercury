/*
 *  cpp_client.cpp
 *
 * \copyright Copyright (C) 2019 Kano Computing Ltd.
 *            License: http://www.gnu.org/licenses/gpl-2.0.txt GNU GPL v2
 *
 *  Very simple internal test to statically link against
 *  the static version of the mercury library
 *
 */

#include <stdio.h>

#include "mercury/kw/kw.h"

int main(int argc, char *argv[])
{
    Mercury::KanoWorld::KanoWorld kw;
    printf("hello cpp_client\n");
}
