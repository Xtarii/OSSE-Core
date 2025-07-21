#include "../../headers/URI/URI.h"

#include <regex>

OSSE::URI::URI(
    std::string protocol,
    std::string host,
    std::string port,
    std::string path,
    std::string query,
    std::string fragment
) {
    protocol_ = protocol;
    host_ = host; port_ = port;
    path_ = path; query_ = query;
    fragment_ = fragment;
}



OSSE::URI OSSE::URI::parse(std::string &uri, OSSE::Config *config) {
    std::regex regex = OSSE::Config::getRegex(config, URI_PARSE);
    std::smatch match;

    if(std::regex_match(uri, match, regex)) {
        std::string protocol = match[1].matched ? match[1].str() : "";
        std::string host     = match[2].matched ? match[2].str() : "";
        std::string port     = match[3].matched ? match[3].str() : "";
        std::string path     = match[4].matched ? match[4].str() : "/";
        std::string query    = match[5].matched ? match[5].str() : "";
        std::string fragment = match[6].matched ? match[6].str() : "";

        if(host.empty()) return {};
        return {
            protocol,
            host, port,
            path,
            query, fragment
        };
    }
    return {};
}



bool OSSE::URI::validURI(std::string &uri, OSSE::Config *config) {
    std::regex regex = OSSE::Config::getRegex(config, URI_PARSE);
    std::smatch match;

    if(std::regex_match(uri, match, regex)) {
        return match[2].matched;
    }

    return false;
}
