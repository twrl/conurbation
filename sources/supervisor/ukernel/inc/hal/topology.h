#pragma once

#include "types.h"

namespace Conurbation {

    struct numa_t {
        uint32_t numaDomainId;
    };

    struct cpu_t {
        uint32_t logicalCoreId;
        uint32_t packageId;
        numa_t* numaDomain;
        uint32_t coresInPackage;
    };

    struct memory_range_t {
        numa_t* numaDomain;
        uintptr_t base;
        size_t size;
    };

    namespace HAL {

        class topology_i {
            public:
            virtual cpu_t* getBootstrapProcessor() = 0;
            virtual memory_range_t* getRangeOfAddress(uintptr_t address) = 0;
            virtual int64_t getNumaDistance(numa_t* domainA, numa_t* domainB) = 0;

            virtual cpu_t* getCpuById(uint32_t logicalCoreId) = 0;
            virtual numa_t* detNumaDomainById(uint32_t numaDomainId) = 0;
        };
    }
}