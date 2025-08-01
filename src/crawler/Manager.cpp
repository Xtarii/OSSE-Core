#include "../../headers/crawler/Manager.h"
#include "../../headers/crawler/worker/Worker.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace OSSE;

Manager::Manager(CONFIG_LIST tags, std::string config)
    : Manager(tags, new Config(Config::load(config))) {}

Manager::Manager(CONFIG_LIST tags, Config *config) {
    config_ = config;
    tags_ = tags;

    database_ = new Database();
}



Manager::~Manager() {
    std::cout << "\nRemoves manager..." << std::endl;
    std::chrono::time_point start = std::chrono::steady_clock::now();


    delete config_;
    while(!queue_.empty()) delete queue_.pop();
    while(!workers_.empty()) {
        OSSE::Worker* worker = workers_.back();
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
    push(new QueueObject(URI, robots));
}

void Manager::push(Manager::QueueObject *object) {
    queue_.push(object);
}



void Manager::createWorkers(int amount) {
    while(!workers_.empty()) {
        OSSE::Worker* worker = workers_.back();
        workers_.pop_back();
        delete worker;
    }

    for(int x = 0; x < amount; x++)
        workers_.push_back(new OSSE::Worker(this));
}

void Manager::run() {
    std::vector<std::thread> threads;
    for(OSSE::Worker* worker : workers_) if(!queue_.empty()) {
        threads.emplace_back([this, worker](){
            QueueObject* obj = this->queue_.pop();
            worker->run(obj);
            delete obj;
        });
    }

    for(std::thread &thread : threads) if(thread.joinable()) {
        thread.join();
    }
}





Config* Manager::config() const {
    return config_;
}

Database* Manager::database() {
    return database_;
}

CONFIG_LIST& Manager::tags() {
    return tags_;
}
