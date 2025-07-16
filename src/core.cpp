#include "../headers/core.h"

#include "../headers/URI/URI.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>



size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total = size * nmemb;
    std::string *response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), total);
    return total;
}



std::string OSSE::getRobots(OSSE::URI &uri) {
    CURL *curl;
    CURLcode res;
    std::string response;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(!curl) return "";

    curl_easy_setopt(curl, CURLOPT_URL, uri.asPath(ROBOTS).c_str());

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
        std::cerr << "curl_easy_perform() failed " << curl_easy_strerror(res) << std::endl;

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return response;
}





void OSSE::readRobots(std::string &robots, std::string agent, Config *config) {
    std::istringstream stream(robots);
    std::string line;
    std::smatch match;

    while(std::getline(stream, line)) {
        if(std::regex_match(line, match, config->robots)) {
            std::cout << "Name: "
                << (match[1].matched ? match[1].str() : "[NONE]") << std::endl;
            std::cout << "Value: "
                << (match[2].matched ? match[2].str() : "[NONE]") << std::endl;
        }
    }
}





//
// IS THIS GOOD ???, Well no it is not, the config format is not
// the best and config reading is not the best.
//
// WHAT DOES THAT MEAN ???, Well I will update this later
// for better configuration.
//
Config OSSE::loadConfig(std::string &file) {
    Config config;
    std::fstream stream(file.c_str());
    if(!stream.is_open()) {
        std::cerr << "Could not open file " << file << std::endl;
        return config;
    }

    std::string line;
    std::regex regex(CONFIG_REGEX, std::regex::icase);
    std::smatch match;

    while(std::getline(stream, line)) {
        if(std::regex_match(line, match, regex)) {
            if(match[1].str() == "parse-robots") {
                config.robots = std::regex(match[2].str(), std::regex::icase);
            }
        }
    }

    return config;
}
