#pragma once

#include "conurbation/status.hh"

namespace Conurbation {

  template <typename R>
  class result_t {
  public:

    result_t(T some) : status_(status_t::success), retval_(some) {}
    result_t(status_t err) : status_(err), retval_() {}

  private:
    status_t status_;
    T retval_;

  }

}
