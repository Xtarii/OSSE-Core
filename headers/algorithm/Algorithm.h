#ifndef OSSE_ALGORITHM
#define OSSE_ALGORITHM

#include "../config/Config.h"
#include "../types/Types.h"
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
    OSSE::string_set analyzeText(std::string text, OSSE::string_list &config);

    /**
     * Analyzes document and extracts tags
     *
     * @param document Document
     * @param config Config with tags
     * @return List of tags that match the document
     */
    OSSE::string_set analyzeDocument(OSSE::HTML::Document *document, OSSE::string_list &config);
}

#endif // OSSE_ALGORITHM
