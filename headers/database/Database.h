#ifndef OSSE_DATABASE
#define OSSE_DATABASE

#include "../URI/URI.h"
#include "../types/Types.h"

#include <mutex>
#include <set>
#include <string>
#include <vector>

namespace OSSE {
    /**
     * Database objects
     *
     * The objects stored in the database.
     */
    struct database_object {
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
     * Basic Database Manager Structure
     *
     * A structure representing the functions
     * a `manager` is expected to call when
     * managing the data in a database.
     */
    struct abstract_database {
        protected:
            /**
             * Database Mutex for thread safety function calls
             */
            std::mutex mutex_;



        public:
            /**
             * Adds object to database
             *
             * @param obj Object to add
             */
            virtual void add(database_object* obj);

            /**
             * Removes object from database
             *
             * Uses URI to find and remove the object
             * from the database.
             *
             * @param URI URI of the object to remove
             */
            virtual void remove(std::string URI);

            /**
             * Removes object from database
             *
             * Uses URI to find and remove the object
             * from the database.
             *
             * @param URI URI of the object to remove
             */
            virtual void remove(OSSE::URI URI);



            /**
             * Finds list of `documents` that matches the
             * provided `tags`
             *
             * @param tags Tags to search for when looking for documents
             * @return List of Documents matching the `tags`
             */
            virtual OSSE::database_result find(OSSE::string_set tags);



            virtual ~abstract_database();
    };



    /**
     * Simple but slow database implementation
     *
     * Recommended to replace this with custom
     * database implementation. This database
     * serves as a simple example implementation.
     *
     * `USE THIS DATABASE ON YOUR OWN EXPENSE` as
     * this database is really slow and runs local.
     */
    struct simple_database : abstract_database {
        private:
            /**
             * Database
             */
            std::vector<database_object*> db_;



        public:
            void add(database_object *obj) override;

            OSSE::database_result find(OSSE::string_set tags) override;

            ~simple_database() override;
    };
}

#endif // OSSE_DATABASE
