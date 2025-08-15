#ifndef OSSE_TYPES
#define OSSE_TYPES

#include "../URI/URI.h"
#include "../robots/Robots.h"

#include <set>
#include <string>
#include <vector>

namespace OSSE {
    struct database_object;

    /// Manager URI Queue object
    struct uri_object {
        /// URI Object
        OSSE::URI URI;
        /// Robots Object
        OSSE::Robots* Robots;

        /**
         * Construct a new URI Queue object
         *
         * @param uri URI object
         * @param robots Robots object
         */
        uri_object(OSSE::URI uri, OSSE::Robots* robots) : URI(uri), Robots(robots) {
            OSSE::Robots::subscribe(this->Robots);
        }

        ~uri_object() {
            OSSE::Robots::unsubscribe(this->Robots);
        }
    };



    /**
     * A list of strings
     */
    typedef std::vector<std::string> string_list;

    /**
     * A set of strings
     */
    typedef std::set<std::string> string_set;

    /**
     * Database Result Object
     *
     * A set of database objects pointers.
     */
    typedef std::set<database_object*> database_result;
}

#endif // OSSE_TYPES
