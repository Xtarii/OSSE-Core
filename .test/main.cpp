#include "../headers/crawler/Manager.h"
#include "../headers/algorithm/Algorithm.h"
#include "../headers/database/simple/SimpleDatabase.h"
#include "../headers/colors/colors.h"

#include <iostream>
#include <string>



int main() {

    //
    // Staring point ( Will crawl google.com as a starting point )
    //
    std::string url = "https://google.com/";
    OSSE::URI URI = OSSE::URI::parse(url, nullptr);


    //
    // Loads a list of tags located in build
    // Format ( just a list of words ),
    // <-------------------------->
    // google
    // programming
    // wikipedia
    // mail
    // <-------------------------->
    //
    CONFIG_LIST config = OSSE::Config::loadConfigList("./.config/tags.list");


    //
    // Creates a manager ( list of tags   :   Configuration )
    //
    OSSE::Manager manager(config, nullptr);

    manager.setDatabase(new OSSE::Simple::database()); // Needs to set database
    manager.push(URI); // Adds URI -> google.com to manager

    manager.createWorkers(5); // Creates 5 workers
    manager.run(); // Runs Manager -> workers
    //
    // Note, only one worker will be started because only one URL is provided
    //


    std::cout << "\"q\" to quit search" << std::endl;


    while(true) {
        std::string x;
        std::cin >> x;
        if(x.compare("q") == 0) {
            break;
            return 0;
        }

        manager.run();


        //
        // Analyzes input text and returns tags
        // ( text to analyze   :   list of tags )
        //
        OSSE::string_set tags = OSSE::Algorithm::analyzeText(x, config);

        //
        // Searches manager database for matching websites
        // ( a list of tags to search for )
        //
        OSSE::database_result result = manager.database()->find(tags);

        for(OSSE::database_object* page : result) {

            std::cout << OSSE::colors::GREEN << "Found: ";

            //
            // Prints page title and the URL to the page
            //
            std::cout << OSSE::colors::BLUE << page->title;
            std::cout << ", at " << page->URI.fullURI();
            std::cout << OSSE::colors::DEFAULT << std::endl;
        }

        std::cout << std::endl;
    }


    return 0;
}
