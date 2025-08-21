#include "../../../headers/database/simple/SimpleDatabase.h"

#include "../../../headers/colors/colors.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace OSSE;
using namespace OSSE::Simple;

database::~database() {
    std::cout << colors::BLUE << "\t- Cleanup of database manager"
        << colors::DEFAULT << std::endl;
    while(!db_.empty()) {
        database_object* obj = db_.back();
        db_.pop_back();
        delete obj;
    }
}

void database::add(database_object* obj) {
    std::unique_lock<std::mutex> lock(mutex_);

    for(std::string tag : obj->tags) {
        tag_m[tag].push_back(obj);
    }

    db_.push_back(obj);
}

database_result database::find(string_set tags) {
    std::unique_lock<std::mutex> lock(mutex_);
    struct map_o { database_object* obj = nullptr; int count = 0; };
    std::map<std::string, struct map_o> r_map;

    for(std::string tag : tags) {
        for(database_object *obj : tag_m[tag]) {
            r_map[obj->URI.fullURI()].obj = obj;
            r_map[obj->URI.fullURI()].count++;
        }
    }

    std::vector<map_o> r_vec;
    for(auto [key, value] : r_map)
        r_vec.push_back(value);

    std::sort(r_vec.begin(), r_vec.end(), [](map_o a, map_o b) {
        return a.count > b.count;
    });

    database_result res;
    for(map_o obj : r_vec) res.emplace(obj.obj);
    return res;
}
