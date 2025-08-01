#include "../headers/crawler/Manager.h"
#include "../headers/algorithm/Algorithm.h"
#include <iostream>
#include <string>



int main() {
    std::string url = "https://google.com/";
    OSSE::URI URI = OSSE::URI::parse(url, nullptr);


    CONFIG_LIST config = OSSE::Config::loadConfigList("./.config/tags.list");

    OSSE::Manager manager(config, nullptr);
    manager.push(URI);

    manager.createWorkers(5);
    manager.run();


    std::cout << "\"q\" to quit search" << std::endl;
    while(true) {
        std::string x;
        std::cin >> x;
        if(x.compare("q") == 0) {
            break;
            return 0;
        }

        manager.run();
        std::set<std::string> tags = OSSE::Algorithm::analyzeText(x, config);
        std::set<OSSE::Database::object*> result = manager.database()->get(tags);
        for(OSSE::Database::object* page : result) {
            std::cout << "Found: " << page->title << ", at " << page->URI.fullURI() << std::endl;
        }
        std::cout << std::endl;
    }


    return 0;
}
