#include "../../headers/HTML/HTML.h"

#include "../../headers/core.h"
#include "../../headers/types/Types.h"

#include <exception>
#include <iostream>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xmlstring.h>

using namespace OSSE;
using namespace OSSE::HTML;

Document::Document(std::string html) {
    doc_ = htmlReadMemory(
        html.c_str(), html.length(),
        nullptr, nullptr,
        HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR
    );

    if(!doc_) {
        std::cerr << "Could not parse HTML" << std::endl;
        throw std::exception();
    }

    ctx_ = xmlXPathNewContext(doc_);
    load();
}



Document::~Document() {
    xmlXPathFreeContext(ctx_);
    xmlFreeDoc(doc_);
    xmlCleanupParser();
}





void Document::load() {
    loadTitle();
    loadMetas();
    loadLinks();
}

void Document::loadTitle() {
    xmlXPathObjectPtr ptr = xmlXPathEvalExpression(BAD_CAST "//title", ctx_);
    if(ptr && ptr->nodesetval->nodeNr > 0) {
        xmlNode *node = ptr->nodesetval->nodeTab[0];
        xmlChar *title = xmlNodeGetContent(node);

        title_ = std::string((const char*)title);
        xmlFree(title);
    }
    xmlXPathFreeObject(ptr);
}

void Document::loadMetas() {
    xmlXPathObjectPtr ptr = xmlXPathEvalExpression(
        BAD_CAST "//meta[@name and @content]", ctx_);
    for(int i = 0; i < ptr->nodesetval->nodeNr; i++) {
        xmlNode *node = ptr->nodesetval->nodeTab[i];
        xmlChar* name = xmlGetProp(node, BAD_CAST "name");
        xmlChar* content = xmlGetProp(node, BAD_CAST "content");

        meta_[OSSE::toLower((const char*)name)] = (const char*)content;

        xmlFree(name);
        xmlFree(content);
    }
    xmlXPathFreeObject(ptr);
}

void Document::loadLinks() {
    xmlXPathObjectPtr ptr = xmlXPathEvalExpression(BAD_CAST "//a[@href]", ctx_);
    for(int i = 0; i < ptr->nodesetval->nodeNr; i++) {
        xmlNode *node = ptr->nodesetval->nodeTab[i];
        xmlChar* href = xmlGetProp(node, BAD_CAST "href");

        links_.push_back((const char*)href);

        xmlFree(href);
    }
    xmlXPathFreeObject(ptr);
}





std::string Document::title() const {
    return title_;
}

string_map Document::meta() const {
    return meta_;
}

string_list Document::links() const {
    return links_;
}





std::string Document::operator[](std::string meta) {
    return meta_[meta];
}
