#pragma once

namespace Conurbation {
    namespace HAL {

        class diagnostic_i {
            public:
            virtual void Write(char* string) = 0;

            diagnostic_i operator<<(char* string) {
                Write(string);
                return this;
            }
        }
    }
}