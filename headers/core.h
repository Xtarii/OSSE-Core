#ifndef OSSE_CORE
#define OSSE_CORE

#include "URI/URI.h"
#include "config/Config.h"
#include <regex>
#include <sstream>
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


    std::string GET(URI &uri);



    std::string replace(std::string str, std::string a, std::string b);

    std::string toLower(std::string str);


}



#endif
