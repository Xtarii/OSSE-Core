#pragma once

#include <string>



/**
 * OSSE Configuration type
 *
 * Used for default configuration values
 */
struct OSSE_CONFIG_TYPE {
    /**
     * Config name
     */
    const std::string name;
    /**
     * Config value
     */
    const std::string value;

    /**
     * Creates `OSSE_CONFIG_TYPE` object
     */
    OSSE_CONFIG_TYPE(std::string name, std::string value) :
        name(name), value(value) {}
};





/// Robots file path
const OSSE_CONFIG_TYPE ROBOTS_PATH {"ROBOTS_PATH", "/robots.txt"};

/// Default URI Parsing regex
const OSSE_CONFIG_TYPE URI_PARSE {
    "URI_PARSE", R"((?:(\w+)://)?([^/:?#]+)(?::(\d+))?([^?#]*)?(\?[^#]*)?(#.*)?)"
};

/// Default Agent
const OSSE_CONFIG_TYPE AGENT {"AGENT", "*"};

/// User agent keyword name
const OSSE_CONFIG_TYPE NAME_USER_AGENT {"NAME_USER_AGENT", "user-agent"};
/// Disallow keyword name
const OSSE_CONFIG_TYPE NAME_DISALLOW {"NAME_DISALLOW", "disallow"};
/// Allow keyword name
const OSSE_CONFIG_TYPE NAME_ALLOW {"NAME_ALLOW", "allow"};


/// Default Robots Parse Regex
const OSSE_CONFIG_TYPE ROBOTS_PARSE {
    "ROBOTS_PARSE", R"(^\s*(Allow|Disallow|User-agent)\s*:\s*(.+)$)"
};
/// Default Robots block end. The indication of an robots block end.
const OSSE_CONFIG_TYPE ROBOTS_PARSE_BLOCK_END {
    "ROBOTS_PARSE_BLOCK_END", R"(\s*)"
};
