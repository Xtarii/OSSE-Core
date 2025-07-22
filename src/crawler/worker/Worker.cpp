#include "../../../headers/crawler/worker/Worker.h"

#include "../../../headers/core.h"
#include "../../../headers/HTML/HTML.h"

#include <string>

OSSE::Worker::Worker(OSSE::Manager *manager) {
    manager_ = manager;
}



void OSSE::Worker::run(OSSE::Manager::QueueObject *object) {
    std::string res = OSSE::GET(object->URI);
    OSSE::HTML::Document document(res);

    for(std::string link : document.links()) {
        if(OSSE::URI::validURI(link, manager_->config())) {
            manager_->push(OSSE::URI::parse(link, manager_->config()));
        }else {
            manager_->push(new OSSE::Manager::QueueObject(
                OSSE::URI::parse(object->URI.asPath(link), nullptr),
                object->Robots
            ));
        }
    }



    // Analyzes document for tags

    // Adds document to SQL Database
}
