#include "../headers/crawler/Manager.h"
#include "../headers/crawler/worker/Worker.h"



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


    OSSE::Worker worker(&manager);


    OSSE::Robots* robots = OSSE::Robots::load(&URI, nullptr);
    OSSE::Manager::QueueObject obj(URI, robots);
    worker.run(&obj);


    return 0;
}
