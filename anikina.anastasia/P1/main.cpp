#include <iostream>

namespace anikina
{
  int run()
  {
    int x = 0;
    int max = 0;
    int count = 0;
    bool has_numbers = false;

    try
    {
      while (true)
      {
        if (!(std::cin >> x))
        {
          throw 1;
        }

        if (x == 0)
        {
          break;
        }

        if (!has_numbers)
        {
          max = x;
          count = 1;
          has_numbers = true;
        }
        else if (x > max)
        {
          max = x;
          count = 1;
        }
        else if (x == max)
        {
          count++;
        }
      }

      if (!has_numbers)
      {
        throw 2;
      }
    }
    catch (int error)
    {
      if (error == 1)
      {
        std::cerr << "Input error\n";
        return 1;
      }

      if (error == 2)
      {
        std::cerr << "Cannot calculate count max\n";
        return 2;
      }
    }

    std::cout << count << '\n';
    return 0;
  }
}

int main()
{
  return anikina::run();
}
