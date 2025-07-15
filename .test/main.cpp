#include "../headers/core.h"
#include "../headers/URI/URI.h"

#include <iostream>
#include <string>



int main() {
    std::string url = "https://google.com/";
    OSSE::URI URI = OSSE::URI::parse(url);

    std::cout << OSSE::getRobots(URI) << std::endl;

    // Parse Robots file

    return 0;
}
