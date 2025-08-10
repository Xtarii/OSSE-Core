#include "../../headers/database/Database.h"

#include "../../headers/error/Error.h"
#include <iostream>
#include <mutex>

using namespace OSSE;

void abstract_database::add(database_object *obj) {
    throw exception("DB_ADD(database_object*) not implemented.");
}

void abstract_database::remove(std::string URI) {
    remove(URI::parse(URI, nullptr));
}
void abstract_database::remove(URI URI) {
    throw exception("DB_REMOVE(URI) not implemented.");
}

database_result abstract_database::find(string_set tags) {
    throw exception("DB_FIND(string_list) not implemented.");
}

abstract_database::~abstract_database() {
    std::cout << "\t- DB_DELETE() Cleanup of database manager" << std::endl;
}





//
// /-----------------------------/
// DEFAULT DATABASE IMPLEMENTATION
// /-----------------------------/
//

simple_database::~simple_database() {
    std::cout << "\t- Cleanup of database manager" << std::endl;
    while(!db_.empty()) {
        database_object* obj = db_.back();
        db_.pop_back();
        delete obj;
    }
}

void simple_database::add(database_object* obj) {
    std::unique_lock<std::mutex> lock(mutex_);
    db_.push_back(obj);
}

database_result simple_database::find(string_set tags) {
    std::unique_lock<std::mutex> lock(mutex_);
    database_result result;
    for(database_object* obj : db_) {
        for(std::string tag : tags) {
            if(std::find(
                obj->tags.begin(),
                obj->tags.end(),
                tag
            ) != obj->tags.end()
            ) {
                result.emplace(obj);
            }
        }
    }
    return result;
}
