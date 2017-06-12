# `-lowlevel` - Library for bare-metal C++ programming

Think of this as my own, extremely non-standard library for osdeving and other bare metal 
type stuff.

Much of this is not home grown. It includes much inspiration and code from

  * [Ogonek](https://github.com/libogonek/ogonek) For the unicode character database
  * [Ponder](https://billyquith.github.io/ponder) Inspired the reflection system
  * [keean's Parser-Combinators](https://github.com/keean/Parser-Combinators) Parsing
  * [SilentByte sb-memory-allocator](https://github.com/SilentByte/sb-memory-allocator) Heaps, with additional inspiration from other implemntations of the composable allocator concept
  * [libc++abi](https://libcxxabi.llvm.org/) For bits of the Itanium C++ ABI

And probably various other things which I've seen but haven't knowingly cribbed from.