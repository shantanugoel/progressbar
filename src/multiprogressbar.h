#ifndef MULTI_PROGRESS_BAR_H_
#define MULTI_PROGRESS_BAR_H_

#include <iostream>

#include "progressbar.h"

template <size_t N>

class MultiProgressBar {
 public:
  void SetProgress(size_t bar, float value) {
    assert(bar < N);
    bars_[bar].SetProgress(value);
  }

  void SetBarWidth(size_t bar, size_t width) {
    assert(bar < N);
    bars_[bar].SetBarWidth(width);
  }

  void FillBarProgressWith(size_t bar, const std::string& chars) {
    assert(bar < N);
    bars_[bar].FillBarProgressWith(chars);
  }

  void FillBarRemainderWith(size_t bar, const std::string& chars) {
    assert(bar < N);
    bars_[bar].FillBarRemainderWith(chars);
  }

  void SetStatusText(size_t bar, const std::string& status) {
    assert(bar < N);
    bars_[bar].SetStatusText(status);
  }

  void Update(size_t bar, float value, std::ostream& os = std::cout) {
    assert(bar < N);
    bars_[bar].SetProgress(value);
    // bars_[bar].WriteProgress(os_[bar]);
    if (first_update_) {
      first_update_ = false;
    } else {
      for (size_t i = 0; i < N; ++i) {
        os << "\x1b[A";
      }
    }
    for (size_t i = 0; i < N; ++i) {
      WriteProgress(i, os);
      os << "\n";
    }
  }

  void WriteProgress(size_t bar, std::ostream& os = std::cout) {
    assert(bar < N);
    bars_[bar].WriteProgress(os);
  }

 private:
  ProgressBar bars_[N];
  bool first_update_ = true;
  // std::ostream os_[N];
};

#endif  // MULTI_PROGRESS_BAR_H_