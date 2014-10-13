


extern "C" void __cxa_pure_virtual() {
    asm volatile ("cli; hlt;");
    // TODO: Panic
}

extern "C" void __cxa_deleted_virtual() {
    asm volatile ("cli; hlt;");
    // TODO: Panic
}