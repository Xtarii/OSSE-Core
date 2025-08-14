#include "../../headers/crawler/Manager.h"

#include "../../headers/crawler/worker/simple/SimpleWorker.h"

#include "../../headers/crawler/worker/Worker.h"
#include "../../headers/error/Error.h"

#include <chrono>
#include <iostream>

using namespace OSSE;

Manager::Manager(CONFIG_LIST tags, std::string config)
    : Manager(tags, new Config(Config::load(config))) {}

Manager::Manager(CONFIG_LIST tags, Config *config) {
    config_ = config;
    tags_ = tags;

    database_ = nullptr;
}



Manager::~Manager() {
    std::cout << "\nRemoves manager..." << std::endl;
    std::chrono::time_point start = std::chrono::steady_clock::now();

    std::cout << "\t- Awaits active workers to finnish" << std::endl;
    while(!isDone()) {
        std::cout << "\r\t\t: " << getActive() << " workers left";
    }
    std::cout << std::endl;

    delete config_;
    while(!queue_.empty()) queue_.pop();
    while(!workers_.empty()) {
        OSSE::abstract_worker* worker = workers_.back();
        workers_.pop_back();
        delete worker;
    }
    delete database_;


    std::chrono::time_point end = std::chrono::steady_clock::now();
    double delta = std::chrono::duration_cast<std::chrono::milliseconds>(
        end - start).count();
    std::cout << "Deleted manager in " << delta << "ms\n" << std::endl;
}





void Manager::push(URI URI) {
    Robots* robots = Robots::load(&URI, config_);
    push(new uri_object(URI, robots));
}

void Manager::push(uri_object *object) {
    std::shared_ptr<uri_object> ptr = std::shared_ptr<uri_object>(object);
    queue_.push(ptr);
}



void Manager::createWorkers(int amount) {
    while(!workers_.empty()) {
        OSSE::abstract_worker* worker = workers_.back();
        workers_.pop_back();
        delete worker;
    }

    for(int x = 0; x < amount; x++)
        workers_.push_back(new OSSE::Simple::worker(this));
}

void Manager::run() {
    if(database_ == nullptr) throw exception("MANAGER_RUN() No Database");

    for(OSSE::abstract_worker* worker : workers_) {
        if(!queue_.empty()) worker->run(queue_.pop());
    }
}





Config* Manager::config() const {
    return config_;
}

abstract_database* Manager::database() {
    return database_;
}

CONFIG_LIST& Manager::tags() {
    return tags_;
}



void Manager::subscribe() {
    std::unique_lock<std::mutex> lock(mutex_);
    active_++;
}
void Manager::unsubscribe() {
    std::unique_lock<std::mutex> lock(mutex_);
    active_--;
}

int Manager::getActive() {
    std::unique_lock<std::mutex> lock(mutex_);
    return active_;
}

bool Manager::isDone() {
    return active_ <= 0;
}
