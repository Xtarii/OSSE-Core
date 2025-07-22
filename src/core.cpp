#include "../headers/core.h"

#include "../headers/URI/URI.h"

#include <cctype>
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>



size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total = size * nmemb;
    std::string *response = static_cast<std::string*>(userp);
    response->append(static_cast<char*>(contents), total);
    return total;
}

std::string OSSE::GET(OSSE::URI &uri) {
    CURL *curl;
    CURLcode res;
    std::string response;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(!curl) return "";

    curl_easy_setopt(curl, CURLOPT_URL, uri.fullURI().c_str());

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





std::string OSSE::replace(std::string str, std::string a, std::string b) {
    std::string::size_type &&pos = str.find(a, size_t{});

    while(pos != std::string::npos) {
        str.replace(pos, a.length(), b);
        pos = str.find(a, pos + b.length());
    }

    return str;
}

std::string OSSE::toLower(std::string str) {
    std::transform(
        str.begin(), str.end(),
        str.begin(),
        [](unsigned char c){ return std::tolower(c); }
    );
    return str;
}
