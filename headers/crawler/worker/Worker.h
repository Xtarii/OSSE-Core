#ifndef OSSE_CRAWL_WORKER
#define OSSE_CRAWL_WORKER

#include "../../types/Types.h"
#include <memory>

namespace OSSE {
    struct Manager;

    /**
     * Abstract Worker Structure
     *
     * Override this structure when
     * making a custom worker for
     * the `OSSE Manager`
     *
     * An abstract crawler used for
     * making crawlers to map the internet.
     *
     * Workers work under a `Manager`
     */
    struct abstract_worker {
        protected:
            /**
             * Manager pointer
             *
             * A pointer to the manager
             * of this worker object.
             */
            OSSE::Manager *manager_;



        public:
            /**
             * Construct a new abstract worker object
             *
             * @param manager Worker Manager
             */
            abstract_worker(OSSE::Manager *manager);



            /**
             * Runs Worker
             *
             * @param object Data object
             */
            virtual void run(std::shared_ptr<OSSE::uri_object> object);
    };
}

#endif // OSSE_CRAWL_WORKER
