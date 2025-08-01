#include "../../headers/database/Database.h"
#include <iostream>

using namespace OSSE;

Database::~Database() {
    std::cout << "\t- Cleanup of database manager" << std::endl;
    while(!database_p.empty()) {
        object* obj = database_p.back();
        database_p.pop_back();
        delete obj;
    }
}

void Database::add(object* obj) {
    std::unique_lock<std::mutex> lock(mutex_p);
    database_p.push_back(obj);
}

void Database::remove(std::string URI) {
    std::unique_lock<std::mutex> lock(mutex_p);
    std::cout << "\nShould remove Object from list...\n" << std::endl;
}



std::set<Database::object*> Database::get(std::set<std::string> tags) {
    std::unique_lock<std::mutex> lock(mutex_p);
    std::set<object*> list;
    for(object* obj : database_p) {
        for(std::string tag : tags) {
            if(std::find(
                obj->tags.begin(),
                obj->tags.end(),
                tag
            ) != obj->tags.end()
            ) {
                list.emplace(obj);
            }
        }
    }
    return list;
}
