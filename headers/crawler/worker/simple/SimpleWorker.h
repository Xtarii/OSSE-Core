#ifndef OSSE_SIMPLE_WORKER
#define OSSE_SIMPLE_WORKER

#include "../Worker.h"

namespace OSSE::Simple {
    /**
     * Web Worker
     *
     * A Crawler that crawls the internet
     * to map out `pages` and `websites`.
     *
     * Workers work under a `Manager`
     */
    struct worker : OSSE::abstract_worker {
        public:
            /**
             * Construct a new Worker object
             *
             * @param manager Worker Manager
             */
            worker(OSSE::Manager *manager);



            void run(std::shared_ptr<OSSE::uri_object> object) override;

            void crawl(std::shared_ptr<OSSE::uri_object> object) override;
    };
}

#endif // OSSE_SIMPLE_WORKER
