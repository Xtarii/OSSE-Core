#include "../../headers/database/Database.h"

#include "../../headers/error/Error.h"
#include <iostream>

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
