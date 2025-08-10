#include "../../headers/algorithm/Algorithm.h"
#include "../../headers/core.h"

using namespace OSSE;

string_set Algorithm::analyzeText(std::string text, string_list &config) {
    string_set result;

    for(std::string tag : config) {
        std::string a = OSSE::toLower(text);
        std::string b = OSSE::toLower(tag);
        if(a.find(b) != std::string::npos) result.insert(tag);
    }

    return result;
}



string_set Algorithm::analyzeDocument(HTML::Document *document, string_list &config) {
    string_set result;
    string_set current;

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
