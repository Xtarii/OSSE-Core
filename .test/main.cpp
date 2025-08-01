#include "../headers/crawler/Manager.h"
// #include "../headers/crawler/worker/Worker.h"
// #include "../headers/algorithm/Algorithm.h"
#include <iostream>
// #include <set>
#include <string>



int main() {
    // std::string agent = "*";

    std::string url = "https://google.com/";
    OSSE::URI URI = OSSE::URI::parse(url, nullptr);

    // OSSE::Robots robots = OSSE::Robots::load(&URI, nullptr);

    // std::string page = OSSE::GET(URI);
    // OSSE::HTML::Document document(page);


    // std::set<std::string> tags =
    //     OSSE::Algorithm::analyzeDocument(&document, config);



    CONFIG_LIST config = OSSE::Config::loadConfigList("./.config/tags.list");

    OSSE::Manager manager(config, nullptr);
    manager.push(URI);

    manager.createWorkers(5);
    manager.run();


    std::cout << "Q to quit search" << std::endl;
    while(true) {
        std::string x;
        std::cin >> x;
        if(x.compare("q") == 0) break;
    }


    // OSSE::Worker worker(&manager);


    // OSSE::Robots* robots = OSSE::Robots::load(&URI, nullptr);
    // OSSE::Manager::QueueObject obj(URI, robots);
    // worker.run(&obj);


    // std::set<std::string> tags = OSSE::Algorithm::analyzeText(
    //     "google", config
    // );
    // std::set<OSSE::Database::object*> pages = manager.database()->get(tags);
    // for(OSSE::Database::object* page : pages) {
    //     std::cout << "Found: " << page->title << ", at " << page->URI.fullURI() << std::endl;
    // }


    return 0;
}
