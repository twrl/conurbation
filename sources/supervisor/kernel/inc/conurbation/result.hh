#pragma once

#include "conurbation/status.hh"

namespace Conurbation {

  template <typename T>
  class result_t {
  public:

    result_t(T some) : status_(status_t::success), retval_(some) {}
    result_t(status_t err) : status_(err), retval_() {}

    inline operator bool_t() {
      return this->status_ == status_t::success;
    }

    auto some() -> T { return this->retval_; }
    auto none() -> status_t { return this->status_; }

  private:
    status_t status_;
    T retval_;

  };

}
