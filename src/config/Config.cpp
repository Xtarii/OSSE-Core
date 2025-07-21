#include "../../headers/config/Config.h"

#include <fstream>
#include <iostream>

OSSE::Config OSSE::Config::load(std::string &path) {
    Config config;
    std::map<std::string, std::string> map;

    std::fstream stream(path.c_str());
    if(!stream.is_open()) {
        std::cerr << "Could not open file " << path << std::endl;
        return config;
    }

    std::regex regex(CONFIG_REGEX, std::regex::icase);
    std::smatch match;
    std::string line;
    while(std::getline(stream, line)) {
        if(std::regex_match(line, match, regex))
            map[match[1].str()] = match[2].str();
    }

    stream.close();
    config.settings = map;
    std::cout << "Loaded config " << path << std::endl;
    return config;
}





std::string OSSE::Config::operator[](std::string setting) {
    return settings[setting];
}
std::string OSSE::Config::operator[](const char* setting) {
    return settings[setting];
}



std::regex OSSE::Config::getRegexSettings(
    std::string setting,
    std::regex_constants::syntax_option_type flag
) {
    std::regex regex(settings[setting], flag);
    return regex;
}

std::regex OSSE::Config::getRegexSettings(std::string setting) {
    return getRegexSettings(setting, std::regex::icase);
}





std::string OSSE::Config::getValue(Config *config, const OSSE_CONFIG_TYPE &settings) {
    if(config == nullptr) return settings.value;

    std::string value = ((Config)*config)[settings.name];
    if(value.empty()) return settings.value;
    return value;
}

std::regex OSSE::Config::getRegex(
    Config *config,
    const OSSE_CONFIG_TYPE &settings,
    std::regex_constants::syntax_option_type flag
) {
    return std::regex(getValue(config, settings), flag);
}
