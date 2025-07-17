#include "../headers/URI/URI.h"
#include "../headers/robots/Robots.h"

#include <string>



int main() {
    std::string configFileName = "./.configs/default.osse";
    OSSE::Config config = OSSE::Config::load(configFileName);

    std::string agent = "*";
    std::string url = "https://google.com/";

    OSSE::URI URI = OSSE::URI::parse(url);

    OSSE::Robots robots = OSSE::Robots::load(&URI, &config);

    return 0;
}
