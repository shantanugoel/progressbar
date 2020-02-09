#ifndef PROGRESS_BAR_H_
#define PROGRESS_BAR_H_
#include <atomic>
#include <iostream>
#include <mutex>

class ProgressBar {
 public:
  void SetProgress(float value) {
    std::unique_lock<std::mutex> lock{mutex_};
    progress_ = value;
  }

  void SetBarWidth(size_t width) {
    std::unique_lock<std::mutex> lock{mutex_};
    bar_width_ = width;
  }

  void FillBarProgressWith(const std::string& chars) {
    std::unique_lock<std::mutex> lock{mutex_};
    fill_ = chars;
  }

  void FillBarRemainderWith(const std::string& chars) {
    std::unique_lock<std::mutex> lock{mutex_};
    remainder_ = chars;
  }

  void SetStatusText(const std::string& status) {
    std::unique_lock<std::mutex> lock{mutex_};
    status_text_ = status;
  }

  void Update(float value, std::ostream& os = std::cout) {
    SetProgress(value);
    WriteProgress(os);
  }

  void WriteProgress(std::ostream& os = std::cout) {
    std::unique_lock<std::mutex> lock{mutex_};
    if (progress_ > 100.0f) return;
    os << "\r" << std::flush;
    os << "[";
    const auto completed =
        static_cast<size_t>(progress_ * static_cast<float>(bar_width_) / 100.0);
    for (size_t i = 0; i < bar_width_; ++i) {
      if (i <= completed) {
        os << fill_;
      } else {
        os << remainder_;
      }
    }

    os << "]";
    os << " " << std::min(static_cast<size_t>(progress_), size_t(100)) << "%";
    os << " " << status_text_;
  }

 private:
  std::mutex mutex_;
  float progress_{0.0f};
  size_t bar_width_{60};
  std::string fill_{"#"}, remainder_{" "}, status_text_{""};
};

#endif  // PROGRESS_BAR_H_