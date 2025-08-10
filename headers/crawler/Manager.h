#ifndef OSSE_CRAWL_MANAGER
#define OSSE_CRAWL_MANAGER

#include "../config/Config.h"
#include "../queue/Queue.h"
#include "../URI/URI.h"
#include "../robots/Robots.h"
#include "../database/Database.h"
#include <vector>

namespace OSSE {
    struct Worker;

    /**
     * Manager for managing Crawlers
     */
    struct Manager {
        /// Manager URI Queue object
        struct QueueObject {
            /// URI Object
            OSSE::URI URI;
            /// Robots Object
            OSSE::Robots* Robots;

            /**
             * Construct a new Queue object
             *
             * @param uri URI object
             * @param robots Robots object
             */
            QueueObject(OSSE::URI uri, OSSE::Robots* robots) : URI(uri), Robots(robots) {
                OSSE::Robots::subscribe(this->Robots);
            }

            ~QueueObject() {
                OSSE::Robots::unsubscribe(this->Robots);
            }
        };



        private:
            /**
             * OSSE Configuration
             */
            OSSE::Config *config_;
            /**
             * List of tags
             */
            OSSE::string_list tags_;

            /**
             * URI Queue
             *
             * A queue of the `URI's` to scan
             */
            OSSE::Queue<QueueObject*> queue_;

            /**
             * List of workers that this manager manages
             */
            std::vector<Worker*> workers_;

            /**
             * Database
             */
            OSSE::abstract_database* database_;



        public:
            /**
             * Construct a new Manager object
             *
             * @param tags List of tags used to analyze websites
             * @param config OSSE Configuration file path
             */
            Manager(CONFIG_LIST tags, std::string config);
            /**
             * Construct a new Manager object
             *
             * @param tags List of tags used to analyze websites
             * @param config OSSE Configuration
             */
            Manager(CONFIG_LIST tags, OSSE::Config *config);



            /**
             * Creates workers
             *
             * Each worker will work in a
             * separate thread.
             *
             * This will reset the workers list.
             *
             * @param amount Amount of workers to create
             */
            void createWorkers(int amount);

            /**
             * Runs all workers in the manager
             */
            void run();



            /**
             * Pushes `URI` into `URI Queue`
             *
             * @param URI URI object
             */
            void push(OSSE::URI URI);

            /**
             * Pushes `object` into `URI Queue`
             *
             * @param object Queue object
             */
            void push(QueueObject *object);



            /**
             * Gets Manager Config object
             *
             * @return Config object
             */
            OSSE::Config* config() const;



            /**
             * Set the Database object
             *
             * @param database Database object
             */
            void setDatabase(abstract_database* database) { database_ = database; }

            /**
             * Gets Manager Database Manager
             *
             * @return Database Manager
             */
            OSSE::abstract_database* database();



            /**
             * Gets Manager tags list
             *
             * @return Tags list
             */
            CONFIG_LIST& tags();



            ~Manager();
    };
}

#endif // OSSE_CRAWL_MANAGER
