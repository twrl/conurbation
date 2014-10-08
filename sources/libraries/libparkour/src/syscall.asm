[BITS 64]

[SECTION .text]



; extern "C" status_t _sc_msg_port_post(opaque_t* port, message_t* message, opaque_t* transfer)
[GLOBAL _sc_msg_port_post:function]
_sc_msg_port_post:
        mov r10, rcx
        mov rax, 0x00010000
        syscall
        ret 
        
; extern "C" status_t _sc_msg_port_poll(opaque_t* port, message_t** message, opaque_t** transfer)
[GLOBAL _sc_msg_port_poll:function]
_sc_msg_port_poll:
        mov r10, rcx
        mov rax, 0x000100001
        syscall
        ret 
        


; extern "C" status_t _sc_opaque_create(void* data, size_t size, opaque_t* opaque);
[GLOBAL _sc_opaque_create:function]
_sc_opaque_create:
        mov r10, rcx
        mov rax, 0x00020001
        syscall
        ret 
    

; extern "C" status_t _sc_opaque_resolve(opaque_t* opaque, void** data, size_t* size);
[GLOBAL _sc_opaque_resolve:function]
_sc_opaque_resolve:
        mov r10, rcx
        mov rax, 0x00020002
        syscall
        ret
        
