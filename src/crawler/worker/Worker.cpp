#include "../../../headers/crawler/worker/Worker.h"
#include "../../../headers/error/Error.h"

using namespace OSSE;

abstract_worker::abstract_worker(Manager *manager) {
    manager_ = manager;
}

void abstract_worker::run(std::shared_ptr<uri_object> obj) {
    throw exception("WORKER_RUN(shared_ptr<uri_object>) not implemented.");
}

void abstract_worker::crawl(std::shared_ptr<uri_object> obj) {
    throw exception("WORKER_CRAWL(shared_ptr<uri_object>) not implemented.");
}
