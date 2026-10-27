#include <fstream>
#include <iostream>

struct Error
{
  int code;
  const char* message;
};

int main(int argc, char* argv[])
{
  int* heap = nullptr;
  try
  {
    if (argc != 4)
    {
      throw Error{1, "Usage: ./lab 1|2 input output"};
    }
    const char num = argv[1][0];
    if ((num != '1' && num != '2') || argv[1][1] != '\0')
    {
      throw Error{1, "Usage: ./lab 1|2 input output"};
    }

    const int max_size = 10000;
    std::ifstream in(argv[2]);
    int rows = 0;
    int cols = 0;
    int st[max_size];
    if (!(in >> rows >> cols) || rows < 0 || cols < 0)
    {
      throw Error{2, "Error: invalid matrix"};
    }
    const long long total = 1LL * rows * cols;
    if (num == '1' && total > max_size)
    {
      throw Error{2, "Error: invalid matrix"};
    }

    if (num == '2')
    {
      try
      {
        heap = new int[total];
      }
      catch (...)
      {
        throw Error{2, "Error: invalid matrix"};
      }
    }
    int* a = nullptr;
    if (heap != nullptr)
    {
      a = heap;
    }
    else
    {
      a = st;
    }

    bool read_ok = true;
    for (long long i = 0; i < total && read_ok; ++i)
    {
      if (!(in >> a[i]))
      {
        read_ok = false;
      }
    }
    char trailing = 0;
    if (!read_ok || (in >> trailing))
    {
      throw Error{2, "Error: invalid matrix"};
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
        if (is_local_max)
        {
          ++cnt;
        }
      }
    }
    delete[] heap;
    heap = nullptr;
    std::ofstream(argv[3]) << cnt << "\n";
  }
  catch (const Error& error)
  {
    delete[] heap;
    std::cerr << error.message << "\n";
    return error.code;
  }
}
