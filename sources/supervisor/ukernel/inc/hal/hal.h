#include "hal/diagnostic.h"

namespace Conurbation {
    
    namespace HAL {
        
        class HAL_i {
            private:
                static HAL_i* _instance;
                
            protected:
                virtual Conurbation::HAL::diagnostic_i* _getDiagnostics() = 0;
                
            public:
                static void setInstance(HAL_i* instance) {
                    HAL_i::_instance = instance;
                }
                
                static Conurbation::HAL::diagnostic_i* getDiagnostics() {
                    return Conurbation::HAL::HAL_i::_instance->_getDiagnostics();
                }
        }
        
    }
    
}