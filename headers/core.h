#ifndef OSSE_CORE
#define OSSE_CORE

#include "URI/URI.h"
#include "config/Config.h"
#include <regex>
#include <string>



/**
 * Robots text document name
 */
#define ROBOTS "/robots.txt"



/**
 * OpenSource Search Engine Namespace
 *
 * Namespace containing all functions and variables for
 * the search engines core.
 */
namespace OSSE {



    std::string getRobots(URI&);

    void readRobots(std::string &robots, std::string agent, OSSE::Config *config);



}



#endif
