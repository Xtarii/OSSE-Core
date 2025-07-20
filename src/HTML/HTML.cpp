#include "../../headers/HTML/HTML.h"

#include <exception>
#include <iostream>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xmlstring.h>

OSSE::HTML::Document::Document(std::string html) {
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



OSSE::HTML::Document::~Document() {
    xmlXPathFreeContext(ctx_);
    xmlFreeDoc(doc_);
    xmlCleanupParser();
}





void OSSE::HTML::Document::load() {
    loadTitle();
    loadMetas();
    loadLinks();
}

void OSSE::HTML::Document::loadTitle() {
    xmlXPathObjectPtr ptr = xmlXPathEvalExpression(BAD_CAST "//title", ctx_);
    if(ptr && ptr->nodesetval->nodeNr > 0) {
        xmlNode *node = ptr->nodesetval->nodeTab[0];
        xmlChar *title = xmlNodeGetContent(node);

        title_ = std::string((const char*)title);
        xmlFree(title);
    }
    xmlXPathFreeObject(ptr);
}

void OSSE::HTML::Document::loadMetas() {
    xmlXPathObjectPtr ptr = xmlXPathEvalExpression(
        BAD_CAST "//meta[@name and @content]", ctx_);
    for(int i = 0; i < ptr->nodesetval->nodeNr; i++) {
        xmlNode *node = ptr->nodesetval->nodeTab[i];
        xmlChar* name = xmlGetProp(node, BAD_CAST "name");
        xmlChar* content = xmlGetProp(node, BAD_CAST "content");

        meta_[(const char*)name] = (const char*)content;

        xmlFree(name);
        xmlFree(content);
    }
    xmlXPathFreeObject(ptr);
}

void OSSE::HTML::Document::loadLinks() {
    xmlXPathObjectPtr ptr = xmlXPathEvalExpression(BAD_CAST "//a[@href]", ctx_);
    for(int i = 0; i < ptr->nodesetval->nodeNr; i++) {
        xmlNode *node = ptr->nodesetval->nodeTab[i];
        xmlChar* href = xmlGetProp(node, BAD_CAST "href");

        links_.push_back((const char*)href);

        xmlFree(href);
    }
    xmlXPathFreeObject(ptr);
}





std::string OSSE::HTML::Document::title() const {
    return title_;
}

std::map<std::string, std::string> OSSE::HTML::Document::meta() const {
    return meta_;
}

std::vector<std::string> OSSE::HTML::Document::links() const {
    return links_;
}





std::string OSSE::HTML::Document::operator[](std::string meta) {
    return meta_[meta];
}
