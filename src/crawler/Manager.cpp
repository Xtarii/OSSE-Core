#include "../../headers/crawler/Manager.h"

OSSE::Manager::Manager(CONFIG_LIST tags, std::string config)
    : OSSE::Manager(tags, new OSSE::Config(OSSE::Config::load(config))) {}

OSSE::Manager::Manager(CONFIG_LIST tags, OSSE::Config *config) {
    config_ = config;
    tags_ = tags;
}



OSSE::Manager::~Manager() {
    delete config_;
    while(!queue_.empty()) delete queue_.pop();
}





void OSSE::Manager::push(OSSE::URI URI) {
    OSSE::Robots robots = OSSE::Robots::load(&URI, config_);
    push(new QueueObject(URI, robots));
}

void OSSE::Manager::push(OSSE::Manager::QueueObject *object) {
    queue_.push(object);
}





OSSE::Config* OSSE::Manager::config() const {
    return config_;
}

CONFIG_LIST& OSSE::Manager::tags() {
    return tags_;
}
