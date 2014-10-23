#pragma once

namespace ConSup {

    enum class syscall_op_t : uintptr_t {
        push,
        push2,
        drop,
        dup,
        ret
    }

    // flags values: retOf, literal

    // pioIn8 csid:9092 pgrp:A poff:0, pioOut8 csid:9093 pgrp:B poff:0 value:ref(9092)

    // push2(B) push(0) push2(A) push(0) pioIn8 dup ret(9092) pioOut8
    class syscall_engine_c {
        private:
        uintptr_t* stackBase;
        uintptr_t* sp;

        uintptr_t* ip;

        uintptr_t* rp;

        public:
        void executeNext() {
            syscall_op_t opcode = (syscall_op_t)(*ip++);
            switch (opcode) {
                case push:
                    *sp++ = *ip++;
                    break;
                case push2:
                    *sp++ = *ip++;
                    *sp++ = *ip++;
                    break;
                case drop:
                    sp--;
                    break;
                case dup:
                    *sp++ = *(sp - 1);
                    break;
                case ret:
                    *rp++ = syscall_op_t::ret;
                    *rp++ = *ip++;
                    *rp++ = *--sp;
                    break;
            }
        }
    }
}