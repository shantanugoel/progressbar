#include <thread>

#include "multiprogressbar.h"
#include "progressbar.h"

int main() {
  MultiProgressBar<3> mbars;
  mbars.SetBarWidth(1, 50);
  mbars.FillBarProgressWith(2, "■");
  mbars.FillBarRemainderWith(1, " ");

  for (size_t i = 1; i <= 100; ++i) {
    mbars.Update(1, i);
    mbars.Update(2, i / 2);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}