/*
 *  cpp_client.cpp
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
    printf ("hello cpp_client\n");
}
