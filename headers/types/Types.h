#ifndef OSSE_TYPES
#define OSSE_TYPES

#include <set>
#include <string>
#include <vector>

namespace OSSE {
    struct database_object;



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
