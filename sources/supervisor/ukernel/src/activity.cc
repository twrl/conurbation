#include "activity.h"

Conurbation::activity_queue_t aq = Conurbation::activity_queue_t();

namespace Conurbation {
    
    void event_handler_t::run() {
        this->eventHandler(this->handlerState);
    }
    
    void activity_queue_t::queue(activity_i* activity) {
        this->_queue[this->_end++] = activity;
    }
    
}