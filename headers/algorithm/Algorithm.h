#ifndef OSSE_ALGORITHM
#define OSSE_ALGORITHM

#include "../config/Config.h"
#include "../HTML/HTML.h"

#include <set>
#include <string>

/**
 * Text analyzing Algorithm namespace
 */
namespace OSSE::Algorithm {
    /**
     * Analyzes text and extracts tags
     *
     * @param text Text string
     * @param config Config with tags
     * @return List of tags that match the text
     */
    std::set<std::string> analyzeText(std::string text, CONFIG_LIST &config);

    /**
     * Analyzes document and extracts tags
     *
     * @param document Document
     * @param config Config with tags
     * @return List of tags that match the document
     */
    std::set<std::string> analyzeDocument(OSSE::HTML::Document *document, CONFIG_LIST &config);
}

#endif // OSSE_ALGORITHM
