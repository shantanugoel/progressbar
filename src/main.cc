#include <thread>

#include "progressbar.h"

int main() {
  ProgressBar bar;
  bar.SetBarWidth(50);
  bar.FillBarProgressWith("■");
  bar.FillBarRemainderWith(" ");

  for (size_t i = 1; i <= 100; ++i) {
    bar.Update(i);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}