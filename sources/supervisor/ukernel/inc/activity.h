#pragma once

#include "types.h"
#include "hal/hwevent.h"

namespace Conurbation {

    class activity_i {
        public:
        virtual void run() = 0;
    };

    class event_handler_t : public activity_i {
        private:
        hwevent_f* eventHandler;
        void* handlerState;

        public:
        virtual void run();
    };

#define ACTIVITY_QUEUE_MAXSIZE 128

    class activity_queue_t {
        private:
        uint64_t _start = 0;
        uint64_t _end = 0;
        activity_i* _queue[ACTIVITY_QUEUE_MAXSIZE];

        public:
        void queue(activity_i* activity);
    };
}