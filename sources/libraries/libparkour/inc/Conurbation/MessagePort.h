#include "Conurbation/Event.h"

namespace Conurbation {
    
    class MessagePort {
        
        public:
            Event<void, message_t, opaque_list_t>       onMessage;
            virtual void sendMessage(message_t msg, opaque_t ...transfer);
        
    }
    
    /**
     * The DiagnosticPort wraps the sc_diagnostic syscall to sendMessage, and 
     * generates onMessage style events for kernel signals
     */
    class DiagnosticPort: public MessagePort { }
    
}