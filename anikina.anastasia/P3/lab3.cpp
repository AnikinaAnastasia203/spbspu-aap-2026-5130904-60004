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
    if (argc != 4 || (argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0')
    {
      throw Error{1, "Usage: ./lab 1|2 input output"};
    }
    const char num = argv[1][0];

    std::ifstream in(argv[2]);
    int rows = 0;
    int cols = 0;
    int st[10000];
    if (!(in >> rows >> cols) || rows < 0 || cols < 0 ||
        (num == '1' && 1LL * rows * cols > 10000))
    {
      throw Error{2, "Error: invalid matrix"};
    }
    const long long total = 1LL * rows * cols;

    if (num == '2')
    {
      try
      {
        heap = new int[total + 1];
      }
      catch (...)
      {
        throw Error{2, "Error: invalid matrix"};
      }
    }
    int* a = heap ? heap : st;

    bool readOk = true;
    for (long long i = 0; i < total && readOk; ++i)
    {
      readOk = static_cast<bool>(in >> a[i]);
    }
    char trailing;
    if (!readOk || (in >> trailing))
    {
      throw Error{2, "Error: invalid matrix"};
    }

    int cnt = 0;
    for (int i = 1; i + 1 < rows; ++i)
    {
      for (int j = 1; j + 1 < cols; ++j)
      {
        bool isLocalMax = true;
        for (int di = -1; di <= 1; ++di)
        {
          for (int dj = -1; dj <= 1; ++dj)
          {
            if ((di || dj) && a[(i + di) * cols + j + dj] >= a[i * cols + j])
            {
              isLocalMax = false;
            }
          }
        }
        cnt += isLocalMax;
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
