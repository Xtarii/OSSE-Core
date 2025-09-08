#ifndef OSSE_HTML
#define OSSE_HTML

#include "../types/Types.h"
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <string>

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
            OSSE::string_map meta_;
            /**
             * Document Links
             */
            OSSE::string_list links_;



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
            OSSE::string_map meta() const;

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
            OSSE::string_list links() const;

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
