#include "../headers/core.h"
#include "../headers/URI/URI.h"

#include <string>



int main() {
    std::string configFileName = "./.configs/default.osse";
    Config config = OSSE::loadConfig(configFileName);

    std::string agent = "*";
    std::string url = "https://google.com/";

    OSSE::URI URI = OSSE::URI::parse(url);

    std::string robot = OSSE::getRobots(URI);

    // Parse Robots file
    OSSE::readRobots(robot, agent, &config);

    return 0;
}
