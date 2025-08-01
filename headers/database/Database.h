#ifndef OSSE_DATABASE
#define OSSE_DATABASE

#include "../URI/URI.h"

#include <mutex>
#include <set>
#include <string>
#include <vector>

namespace OSSE {
    /**
     * Simple Database structure
     */
    struct Database {
        /**
         * Database object
         */
        struct object {
            /**
             * Document URI
             */
            OSSE::URI URI;

            /**
             * Document Title
             */
            std::string title;

            /**
             * Document description
             */
            std::string description;

            /**
             * Document Tags
             */
            std::set<std::string> tags;
        };



        /**
         * Database
         */
        std::vector<object*> database_p;

        /**
         * Mutex object
         */
        std::mutex mutex_p;



        /**
         * Adds object to database
         *
         * @param obj Object to add
         */
        void add(object* obj);
        /**
         * Removes object with URI from database
         *
         * @param URI URI
         */
        void remove(std::string URI);



        /**
         * Gets list of documents that matches the
         * `tags` parameter
         *
         * @param tags List of tags to search for
         * @return The resulting documents
         */
        std::set<object*> get(std::set<std::string> tags);





        ~Database();
    };
}

#endif // OSSE_DATABASE
