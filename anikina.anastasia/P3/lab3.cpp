#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  const std::string n = argc == 4 ? argv[1] : "";
  if (n != "1" && n != "2")
  {
    std::cerr << "Usage: ./lab 1|2 input output\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  int rows = 0;
  int cols = 0;
  const int max_size = 10000;
  int st[max_size];

  if (!(in >> rows >> cols) || rows < 0 || cols < 0 || (n == "1" && 1LL * rows * cols > max_size))
  {
    std::cerr << "Error: invalid matrix\n";
    return 2;
  }

  int *const heap = n == "2" ? new int[1LL * rows * cols + 1] : nullptr;
  int *const a = heap ? heap : st;

  bool read_ok = true;
  for (long long i = 0; i < 1LL * rows * cols && read_ok; ++i)
  {
    read_ok = bool(in >> a[i]);
  }

  char trailing = 0;
  if (!read_ok || (in >> trailing))
  {
    delete[] heap;
    std::cerr << "Error: invalid matrix\n";
    return 2;
  }

  int cnt = 0;
  for (int i = 1; i + 1 < rows; ++i)
  {
    for (int j = 1; j + 1 < cols; ++j)
    {
      bool is_local_max = true;
      for (int di = -1; di <= 1; ++di)
      {
        for (int dj = -1; dj <= 1; ++dj)
        {
          if ((di || dj) && a[(i + di) * cols + j + dj] >= a[i * cols + j])
          {
            is_local_max = false;
          }
        }
      }
      cnt += is_local_max;
    }
  }

  delete[] heap;
  std::ofstream(argv[3]) << cnt << "\n";
  return 0;
}
