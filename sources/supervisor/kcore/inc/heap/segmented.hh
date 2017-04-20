#pragma once

namespace Conurbation::Heap {

  template <int NumBins, int (*getClassSize)(const size_t), size_t (*getClassMaxSize)(const int), class Little, class Big>
  class segmented_heap_t : Little {

  public:

  }

}
