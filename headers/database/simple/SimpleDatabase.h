#ifndef OSSE_SIMPLE_DATABASE
#define OSSE_SIMPLE_DATABASE

#include "../Database.h"

namespace OSSE::Simple {
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
    struct database : abstract_database {
        private:
            /**
             * Database
             */
            std::vector<database_object*> db_;

            /**
             * Tag map
             *
             * A map for fast searching in the database.
             */
            std::map<std::string, std::vector<database_object*>> tag_m;



        public:
            void add(database_object *obj) override;

            OSSE::database_result find(OSSE::string_set tags) override;

            ~database() override;
    };
}

#endif // OSSE_SIMPLE_DATABASE
