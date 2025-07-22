#ifndef OSSE_CRAWL_WORKER
#define OSSE_CRAWL_WORKER

#include "../Manager.h"

namespace OSSE {
    /**
     * Web Worker
     *
     * A Crawler that crawls the internet
     * to map out `pages` and `websites`.
     *
     * Workers work under a `Manager`
     */
    struct Worker {
        private:
            /**
             * Worker manager
             *
             * The manager that manages this
             * worker.
             */
            OSSE::Manager *manager_;



        public:
            /**
             * Construct a new Worker object
             *
             * @param manager Worker Manager
             */
            Worker(OSSE::Manager *manager);



            /**
             * Runs Worker
             *
             * @param object Manager queue object
             */
            void run(OSSE::Manager::QueueObject *object);
    };
}

#endif // OSSE_CRAWL_WORKER
