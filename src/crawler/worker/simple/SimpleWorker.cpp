#include "../../../../headers/crawler/worker/simple/SimpleWorker.h"

#include "../../../../headers/core.h"
#include "../../../../headers/HTML/HTML.h"
#include "../../../../headers/crawler/Manager.h"
#include "../../../../headers/algorithm/Algorithm.h"

using namespace OSSE;
using namespace OSSE::Simple;

worker::worker(Manager *manager) : OSSE::abstract_worker(manager) {
}



void worker::run(std::shared_ptr<uri_object> obj) {
    std::string res = OSSE::GET(obj->URI);
    HTML::Document document(res);

    for(std::string link : document.links()) {
        if(URI::validURI(link, manager_->config())) {
            manager_->push(URI::parse(link, manager_->config()));
        }else if(obj->Robots->isAllowed(link)) {
            manager_->push(new uri_object(
                URI::parse(obj->URI.asPath(link), nullptr),
                obj->Robots
            ));
        }
    }



    // Analyzes document for tags
    std::set<std::string> tags = Algorithm::analyzeDocument(
        &document,
        manager_->tags()
    );

    // Adds document to SQL Database
    database_object db_obj{
        obj->URI,
        document.title(),
        document.meta()["description"],
        tags
    };
    manager_->database()->add(new database_object(db_obj));
}
