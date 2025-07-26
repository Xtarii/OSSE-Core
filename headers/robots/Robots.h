#ifndef OSSE_ROBOTS
#define OSSE_ROBOTS

#include "../URI/URI.h"
#include "../config/Config.h"

#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

namespace OSSE {
    /**
     * Robots Object
     *
     * This represents a URL's robots file
     * holding rules on which path is allowed
     * to enter and not enter as a `crawler`.
     */
    struct Robots {
        private:
            /**
             * Robots Rule Block
             *
             * Used to parse Robots files.
             */
            struct RobotsBlock {
                /**
                 * Agents that this rule applies to
                 */
                std::vector<std::string> agents;
                /**
                 * A map of the paths that are allowed and
                 * not allowed.
                 */
                std::map<std::string, bool> map;
            };



            /**
             * The agents that this Robots rules applies to.
             */
            std::vector<std::string> agents_;

            /**
             * A map from the robots of which pages and
             * paths that are allowed and not allowed to
             * be crawled.
             */
            std::map<std::string, bool> map_;

            /**
             * Mutex for thread safe robots handling
             */
            std::mutex mutex_;
            /**
             * Amount of handlers connected to this robots file
             */
            int handlers_;



            /**
             * Parses Robots file content
             *
             * @param content Content string
             * @param config OSSE Configuration
             * @return Robots object
             */
            static Robots* parse(std::string &content, OSSE::Config *config);

            /**
             * Parse Robots Rule Block
             *
             * @param stream Content stream
             * @param config OSSE Configuration
             * @return Robots Block object
             */
            static RobotsBlock parseBlock(std::istringstream *stream, OSSE::Config *config);



        public:
            /**
             * Loads `Robots.txt` file from a `URI` and
             * parses it.
             *
             * @param URI URI
             * @param config OSSE Configuration
             * @return Robots object
             */
            static Robots* load(OSSE::URI *URI, OSSE::Config *config);

            /**
             * Registers handler to Robots file
             *
             * @param robots Robots file
             */
            static void subscribe(Robots *robots);
            /**
             * Unregisters handler from robots file
             *
             * @param robots Robots file
             */
            static void unsubscribe(Robots *robots);



            /**
             * Gets access value of path
             *
             * @param key Path
             * @return Access value
             */
            bool operator[](std::string key);



            /**
             * Checks if `path` is allowed to be crawled.
             *
             * If the path is found in the robots file
             * then the `return value` will be equal to the
             * value in the robots file.
             *
             * If the path is not included in the robots file
             * then the status will be `false`
             *
             * @param path Path
             * @return Status of allowing crawling
             */
            bool isAllowed(std::string path);

            /**
             * Checks if `URI path` is allowed to crawl.
             *
             * If the path is found in the robots file
             * then the `return value` will be equal to the
             * value in the robots file.
             *
             * If the path is not included in the robots file
             * then the status will be `false`
             *
             * @param URI URI object
             * @return Status of allowing crawling
             */
            bool isAllowed(OSSE::URI *URI);
    };
}

#endif // OSSE_ROBOTS
