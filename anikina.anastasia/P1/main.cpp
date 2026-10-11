#include <iostream>

namespace anikina
{
  int countMax()
  {
    int x = 0, max = 0, count = 0;

    if (!(std::cin >> x))
    {
      std::cerr << "Input is not a sequence" << std::endl;
      return 1;
    }

    if (x == 0)
    {
      std::cerr << "Sequence is too short" << std::endl;
      return 2;
    }

    max = x;
    count = 1;

    while (true)
    {
      if (!(std::cin >> x))
      {
        std::cerr << "Input is not a sequence" << std::endl;
        return 1;
      }

      if (x == 0)
      {
        break;
      }

      if (x > max)
      {
        max = x;
        count = 1;
      }
      else if (x == max)
      {
        count++;
      }
    }

    std::cout << count << std::endl;
    return 0;
  }
}

int main()
{
  return anikina::countMax();
}
