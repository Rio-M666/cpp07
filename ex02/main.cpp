#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <string>
#include "Array.hpp"

#define MAX_VAL 750

static void check(bool condition, const char *message)
{
    if (!condition)
        throw std::runtime_error(message);
    std::cout << "[PASS] " << message << std::endl;
}

static void testConstruction(void)
{
    std::cout << "=== Construction ===" << std::endl;
    Array<int> empty;
    Array<int> zero(0);
    Array<int> numbers(3);

    check(empty.size() == 0 && zero.size() == 0, "Empty arrays have size 0");
    check(numbers.size() == 3, "Size matches the requested element count");
    check(numbers[0] == 0 && numbers[1] == 0 && numbers[2] == 0,
          "Int elements are initialized to 0");

    bool caught = false;
    try
    {
        empty[0] = 1;
    }
    catch (const std::exception &)
    {
        caught = true;
    }
    check(caught, "Access to an empty array throws std::exception");
}

static void testConstAccess(void)
{
    std::cout << "=== Const access ===" << std::endl;
    Array<int> numbers(2);
    numbers[0] = 10;
    numbers[1] = 20;
    const Array<int> &view = numbers;

    check(view.size() == 2 && view[0] == 10 && view[1] == 20,
          "Const arrays allow reading elements and size");
    bool caught = false;
    try
    {
        (void)view[view.size()];
    }
    catch (const std::exception &)
    {
        caught = true;
    }
    check(caught, "Const access at size() throws std::exception");
}

static void testCopy(void)
{
    std::cout << "=== Copy construction ===" << std::endl;
    Array<int> original(2);
    original[0] = 10;
    original[1] = 20;
    Array<int> copy(original);

    check(copy.size() == 2 && copy[0] == 10 && copy[1] == 20,
          "Copy construction preserves size and values");
    copy[0] = 99;
    check(original[0] == 10, "Changing the copy leaves the original unchanged");
    original[1] = 42;
    check(copy[1] == 20, "Changing the original leaves the copy unchanged");

    Array<int> empty;
    Array<int> emptyCopy(empty);
    check(emptyCopy.size() == 0, "An empty array can be copied");
}

static void testAssignment(void)
{
    std::cout << "=== Assignment ===" << std::endl;
    Array<int> original(2);
    original[0] = 10;
    original[1] = 20;
    Array<int> smaller(1);
    Array<int> larger(4);

    check(&(smaller = original) == &smaller, "Assignment returns the destination");
    check(smaller.size() == 2 && smaller[0] == 10 && smaller[1] == 20,
          "Assignment to a smaller array copies size and values");
    larger = original;
    check(larger.size() == 2 && larger[0] == 10 && larger[1] == 20,
          "Assignment to a larger array copies size and values");
    smaller[0] = 99;
    check(original[0] == 10, "Changing the destination leaves the source unchanged");
    original[1] = 42;
    check(smaller[1] == 20, "Changing the source leaves the destination unchanged");

    Array<int> &alias = smaller;
    smaller = alias;
    check(smaller.size() == 2 && smaller[0] == 99 && smaller[1] == 20,
          "Self-assignment preserves size and values");

    Array<int> empty;
    larger = empty;
    check(larger.size() == 0, "An empty source clears the destination");
    empty = original;
    check(empty.size() == 2 && empty[0] == 10 && empty[1] == 42,
          "An empty destination can receive elements");
}

static void testStrings(void)
{
    std::cout << "=== String elements ===" << std::endl;
    Array<std::string> words(2);
    check(words[0].empty() && words[1].empty(), "String elements are initialized empty");
    words[0] = "hello";
    words[1] = "world";

    Array<std::string> copy(words);
    Array<std::string> assigned(1);
    assigned = words;
    check(copy.size() == 2 && copy[0] == "hello" && copy[1] == "world"
              && assigned.size() == 2 && assigned[0] == "hello" && assigned[1] == "world",
          "String arrays support copy construction and assignment");
    copy[0] = "copy";
    assigned[1] = "assigned";
    check(words[0] == "hello" && words[1] == "world",
          "Changing string copies leaves the original unchanged");
    words[0] = "original";
    check(copy[0] == "copy" && assigned[0] == "hello",
          "Changing the original leaves string copies unchanged");
}

int main(int, char **)
{
    Array<int> numbers(MAX_VAL);
    int *mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    // SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete[] mirror; //

    try
    {
        testConstruction();
        testConstAccess();
        testCopy();
        testAssignment();
        testStrings();
    }
    catch (const std::exception &e)
    {
        std::cerr << "[FAIL] " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
