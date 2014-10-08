Driver Model
============

## Early-time Drivers

Early-time drivers are primitive drivers embedded within the kernel/HAL. Their
main functions are

  - Carry forward device state from the (pre-)boot environment to the runtime
    environment, where that continuity is necessary. For example, when the 
    framebuffer is configured by the bootloader before control is passed to the
    HAL, ownership of the framebuffer is passed to an Early-time driver and from
    there to the full graphics stack.
  - Provide minimal IO functions to support logging, diagnostics, and recovery
  - Provide minimal functions necessary to enter User mode and load complete
    driver and service stacks.

For the most part, Early-time drivers will only be called from within the kernel
and HAL, so we can afford to be a bit vague about their interfaces. However, 
ETDs **must** implement a standard method for transfering device state to
the appropriate User-mode driver or service.

## User-mode Drivers

User-mode Drivers are more complete and execute as privileged user-mode 
processes. 