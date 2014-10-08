#include "activity.h"

activity_queue_t aq = activity_queue_t();

namespace Conurbation {
    
    void event_handler_t::run() {
        this->eventHandler(this->handlerState);
    }
    
    void activity_queue_t::queue(activity_i* activity) {
        this->queue[this->end++] = activity;
    }
    
}