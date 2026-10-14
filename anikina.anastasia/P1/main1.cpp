#include <iostream>

namespace anikina
{
  int run()
  {
    int x;
    int max = 0;
    int count = 0;
    bool hasNumbers = false;

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

        if (!hasNumbers)
        {
          max = x;
          count = 1;
          hasNumbers = true;
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

      if (!hasNumbers)
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
