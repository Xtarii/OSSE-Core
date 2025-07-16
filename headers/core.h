#ifndef OSSE_CORE
#define OSSE_CORE

#include "URI/URI.h"
#include <regex>
#include <string>



/**
 * Robots text document name
 */
#define ROBOTS "/robots.txt"



#define CONFIG_REGEX R"(^\s*([A-Za-z_][A-Za-z0-9_-]*)\s*:\s*(.+)$)"

struct Config {
    std::regex robots;
};



/**
 * OpenSource Search Engine Namespace
 *
 * Namespace containing all functions and variables for
 * the search engines core.
 */
namespace OSSE {



    std::string getRobots(URI&);

    void readRobots(std::string &robots, std::string agent, Config *config);



    Config loadConfig(std::string &file);



}



#endif
