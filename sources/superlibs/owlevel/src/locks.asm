[BITS 64]
[SECTION .text]

;thisptr in rdi

[GLOBAL _ZN2ll4Sync10spinlock_t7acquireEv];:function _ZN2ll4Sync10spinlock_t7acquireEv.end - _ZN2ll4Sync10spinlock_t7acquireEv]
_ZN2ll4Sync10spinlock_t7acquireEv:
    .start:
        lock bts dword [rdi],0
        jc .spin_pause
        ret
    .spin_pause:
        pause
        test dword [rdi],1
        jnz .spin_pause
        jmp .start
    .end:


[GLOBAL _ZN2ll4Sync10spinlock_t7releaseEv];:function _ZN2ll4Sync10spinlock_t7releaseEv.end - _ZN2ll4Sync10spinlock_t7releaseEv]
_ZN2ll4Sync10spinlock_t7releaseEv:
        mov dword [rdi],0
        ret
    end:

[GLOBAL _ZN2ll4Sync12ticketlock_t7acquireEv]
_ZN2ll4Sync12ticketlock_t7acquireEv:
        mov rax,1
        lock xadd dword [rdi], eax
    .spin_pause:
        pause
        cmp dword [rdi + 4], eax
        jne .spin_pause
        ret
    .end:

[GLOBAL _ZN2ll4Sync12ticketlock_t7releaseEv]
_ZN2ll4Sync12ticketlock_t7releaseEv:
        lock inc dword [rdi + 4]
        ret
