#pragma once

#include "types.h"
#include "hal/hwevent.h"

namespace Conurbation {
    
    class activity_i {
        public:
            virtual void run() = 0;
        
    };
    
    class event_handler_t: public activity_i {
        private: 
            hwevent_f*      eventHandler;
            void*           handlerState;
        public:
            virtual void run();
    };
    
    class activity_queue_t {
        private:
            const uint64_t  capacity = 128;
            uint64_t        start;
            uint64_t        end;
            activity_i*     queue[capacity];
        public:
            void            queue(activity_i* activity);
    };
    
}