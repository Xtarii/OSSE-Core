#include "../../headers/robots/Robots.h"

#include "../../headers/core.h"

#include <mutex>
#include <sstream>
#include <string>

using namespace OSSE;

Robots* Robots::load(URI *URI, Config *config) {
    std::string path = URI->asPath(
        Config::getValue(config, ROBOTS_PATH)
    );
    OSSE::URI uri = OSSE::URI::parse(path, config);

    std::string content = OSSE::GET(uri);

    return parse(content, config);
}



Robots* Robots::parse(std::string &content, Config *config) {
    Robots* robots = new Robots();

    std::istringstream stream(content);
    std::string line;
    RobotsBlock block;

    block = parseBlock(&stream, config);
    if(!block.agents.empty()) {
        robots->agents_.insert(
            robots->agents_.end(),
            block.agents.begin(), block.agents.end()
        );
        robots->map_.insert(block.map.begin(), block.map.end());
    }

    while(std::getline(stream, line)) {
        block = parseBlock(&stream, config);
        if(!block.agents.empty()) {
            robots->agents_.insert(
                robots->agents_.end(),
                block.agents.begin(), block.agents.end()
            );
            robots->map_.insert(block.map.begin(), block.map.end());
        }
    }

    return robots;
}



Robots::RobotsBlock Robots::parseBlock(std::istringstream *stream, Config *config) {
    RobotsBlock block;

    std::regex regex = Config::getRegex(config, ROBOTS_PARSE);
    std::regex end = Config::getRegex(config, ROBOTS_PARSE_BLOCK_END);

    std::smatch match;
    std::string line;

    std::vector<std::string> agents;
    std::map<std::string, bool> map;

    std::string agent = Config::getValue(config, AGENT);
    std::string userAgent = Config::getValue(config, NAME_USER_AGENT);
    std::string disallow = Config::getValue(config, NAME_DISALLOW);
    std::string allow = Config::getValue(config, NAME_ALLOW);

    while(std::getline(*stream, line)) {
        if(std::regex_match(line, match, regex)) {
            std::string key = match[1].str();
            key = OSSE::toLower(key);

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





bool Robots::operator[](std::string key) {
    return map_[key];
}





bool Robots::isAllowed(std::string path) {
    std::regex regex;
    std::smatch match;

    for(auto& [key, value] : map_) {
        std::string str = OSSE::replace(key, "*", "(.*)");
        regex = std::regex(str, std::regex::icase);

        if(std::regex_match(path, match, regex)) {
            return value;
        }
    }
    return false; // Defaults to not allow crawling
}

bool Robots::isAllowed(URI *URI) {
    return isAllowed(URI->fullPath());
}





void Robots::subscribe(Robots *robots) {
    std::unique_lock<std::mutex> lock(robots->mutex_);
    robots->handlers_++;
}

void Robots::unsubscribe(Robots *robots) {
    std::unique_lock<std::mutex> lock(robots->mutex_);
    robots->handlers_--;
    if(robots->handlers_ <= 0) delete robots;
}
