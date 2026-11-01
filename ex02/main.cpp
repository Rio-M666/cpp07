#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <string>
#include "Array.hpp"

int main()
{

    Array<int> a(3);
    if (a.size() != 3 || a[0] != 0)
        return 1;

    a[0] = 42;
    if (a[0] != 42)
        return 1;

    Array<int> b(a);
    if (b[0] != 42)
        return 1;
    b[0] = 100;
    if (a[0] != 42)
        return 1;

    Array<int> c;
    c = b;
    if (c[0] != 100)
        return 1;
    c[0] = 200;
    if (b[0] != 100)
        return 1;

    const Array<int> &ref = a;
    if (ref[0] != 42)
        return 1;

    bool caught = false;
    try
    {
        a[3] = 10;
    }
    catch (const std::exception &)
    {
        caught = true;
    }
    if (!caught)
        return 1;

    Array<std::string> words(2);
    words[0] = "hello";
    if (words[0] != "hello")
        return 1;

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
