#include "../../../headers/crawler/worker/Worker.h"

#include "../../../headers/core.h"
#include "../../../headers/HTML/HTML.h"

#include <string>

using namespace OSSE;

Worker::Worker(Manager *manager) {
    manager_ = manager;
}



void Worker::run(Manager::QueueObject *object) {
    std::string res = OSSE::GET(object->URI);
    HTML::Document document(res);

    for(std::string link : document.links()) {
        if(URI::validURI(link, manager_->config())) {
            manager_->push(URI::parse(link, manager_->config()));
        }else if(object->Robots->isAllowed(link)) {
            manager_->push(new Manager::QueueObject(
                URI::parse(object->URI.asPath(link), nullptr),
                object->Robots
            ));
        }
    }



    // Analyzes document for tags

    // Adds document to SQL Database
}
