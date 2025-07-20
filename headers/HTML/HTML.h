#ifndef OSSE_HTML
#define OSSE_HTML

#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <map>
#include <string>
#include <vector>

/**
 * OSSE HTML Namespace
 */
namespace OSSE::HTML {
    /**
     * OSSE HTML Document
     */
    struct Document {
        private:
            /**
             * Document Object
             */
            htmlDocPtr doc_;
            /**
             * XML Context
             */
            xmlXPathContextPtr ctx_;

            /**
             * Document Title
             */
            std::string title_;
            /**
             * Document Meta Data
             */
            std::map<std::string, std::string> meta_;
            /**
             * Document Links
             */
            std::vector<std::string> links_;



            /**
             * Parses the document
             */
            void load();

            /**
             * Parses Titles
             */
            void loadTitle();
            /**
             * Parses Metas
             */
            void loadMetas();
            /**
             * Parses Links
             */
            void loadLinks();



        public:
            /**
             * Construct a new Document object
             *
             * @param html Raw HTML string
             */
            Document(std::string html);



            /**
             * Document Meta
             *
             * @return Meta Data
             */
            std::map<std::string, std::string> meta() const;

            /**
             * Document Meta
             *
             * @param meta Meta name
             * @return Meta value
             */
            std::string operator[](std::string meta);

            /**
             * Document Links
             *
             * @return List of links
             */
            std::vector<std::string> links() const;

            /**
             * Document Title
             *
             * @return Title string
             */
            std::string title() const;



            ~Document();
    };
}

#endif // OSSE_HTML
