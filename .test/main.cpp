#include "../headers/crawler/Manager.h"
#include "../headers/algorithm/Algorithm.h"
#include "../headers/database/simple/SimpleDatabase.h"

#include <iostream>
#include <string>



int main() {
    std::string url = "https://google.com/";
    OSSE::URI URI = OSSE::URI::parse(url, nullptr);


    CONFIG_LIST config = OSSE::Config::loadConfigList("./.config/tags.list");

    OSSE::Manager manager(config, nullptr);
    manager.setDatabase(new OSSE::Simple::database());
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
        OSSE::string_set tags = OSSE::Algorithm::analyzeText(x, config);
        OSSE::database_result result = manager.database()->find(tags);
        for(OSSE::database_object* page : result) {
            std::cout << "Found: " << page->title << ", at " << page->URI.fullURI() << std::endl;
        }
        std::cout << std::endl;
    }


    return 0;
}
