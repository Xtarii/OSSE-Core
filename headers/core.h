#ifndef OSSE_CORE
#define OSSE_CORE

#include "URI/URI.h"
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



}



#endif
