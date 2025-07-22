#include "../../headers/algorithm/Algorithm.h"
#include "../../headers/core.h"

std::set<std::string> OSSE::Algorithm::analyzeText(std::string text, CONFIG_LIST &config) {
    std::set<std::string> result;

    for(std::string tag : config) {
        std::string a = OSSE::toLower(text);
        std::string b = OSSE::toLower(tag);
        if(a.find(b) != std::string::npos) result.insert(tag);
    }

    return result;
}



std::set<std::string> OSSE::Algorithm::analyzeDocument(OSSE::HTML::Document *document, CONFIG_LIST &config) {
    std::set<std::string> result;
    std::set<std::string> current;

    current = analyzeText(document->title(), config);
    result.insert(current.begin(), current.end());
    current.clear();

    for(auto& [name, meta] : document->meta()) {
        current = analyzeText(meta, config);
        result.insert(current.begin(), current.end());
        current.clear();
    }

    return result;
}
