#include "../../headers/robots/Robots.h"

#include "../../headers/core.h"

#include <sstream>
#include <string>

OSSE::Robots OSSE::Robots::load(OSSE::URI *URI, OSSE::Config *config) {
    std::string path = URI->asPath(static_cast<OSSE::Config>(*config)[CONFIG_ROBOTS_PATH]);
    OSSE::URI uri = OSSE::URI::parse(path);

    std::string content = OSSE::GET(uri);

    return parse(content, config);
}



OSSE::Robots OSSE::Robots::parse(std::string &content, OSSE::Config *config) {
    Robots robots;

    std::istringstream stream(content);
    std::string line;
    RobotsBlock block;

    block = parseBlock(&stream, config);
    if(!block.agents.empty()) {
        robots.agents_.insert(
            robots.agents_.end(),
            block.agents.begin(), block.agents.end()
        );
        robots.map_.insert(block.map.begin(), block.map.end());
    }

    while(std::getline(stream, line)) {
        block = parseBlock(&stream, config);
        if(!block.agents.empty()) {
            robots.agents_.insert(
                robots.agents_.end(),
                block.agents.begin(), block.agents.end()
            );
            robots.map_.insert(block.map.begin(), block.map.end());
        }
    }

    return robots;
}



OSSE::Robots::RobotsBlock OSSE::Robots::parseBlock(std::istringstream *stream, OSSE::Config *config) {
    RobotsBlock block;

    std::regex regex = config->getRegexSettings("parse-robots");
    std::regex end = config->getRegexSettings("parse-end-of-robots-blocks");

    std::smatch match;
    std::string line;

    std::vector<std::string> agents;
    std::map<std::string, bool> map;

    std::string agent = static_cast<OSSE::Config>(*config)["agent"];
    std::string userAgent = static_cast<OSSE::Config>(*config)["user-agent"];
    std::string disallow = static_cast<OSSE::Config>(*config)["disallow"];
    std::string allow = static_cast<OSSE::Config>(*config)["allow"];

    while(std::getline(*stream, line)) {
        if(std::regex_match(line, match, regex)) {
            std::string key = match[1].str();
            std::transform( // Makes key to lower case, value is not needed
                key.begin(), key.end(), key.begin(),
                [](unsigned char c) { return std::tolower(c); }
            );

            if(key == userAgent) agents.push_back(match[2].str());
            else if(key == disallow) map[match[2].str()] = false;
            else if(key == allow) map[match[2].str()] = true;
        }

        if(std::regex_match(line, match, end)) break;
    }



    if(
        std::find(agents.begin(), agents.end(), agent) != agents.end() ||
        std::find(agents.begin(), agents.end(), "*") != agents.end()
    ) {
        block.agents = agents;
        block.map = map;
    }

    return block;
}





bool OSSE::Robots::operator[](std::string key) {
    return map_[key];
}
