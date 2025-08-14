#include "../../../headers/database/simple/SimpleDatabase.h"
#include <iostream>

using namespace OSSE;
using namespace OSSE::Simple;

database::~database() {
    std::cout << "\t- Cleanup of database manager" << std::endl;
    while(!db_.empty()) {
        database_object* obj = db_.back();
        db_.pop_back();
        delete obj;
    }
}

void database::add(database_object* obj) {
    std::unique_lock<std::mutex> lock(mutex_);
    db_.push_back(obj);
}

database_result database::find(string_set tags) {
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
