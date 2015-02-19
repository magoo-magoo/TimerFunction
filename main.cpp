#include <iostream>

#include "TimerFunction.hpp"

struct A {

int foo(int a, int b) {
    return a + b;
}

void toto(void) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

};

struct B {

    int cpt = 0;

void operator()() {
    std::cout << __PRETTY_FUNCTION__ << "cpt: " << ++cpt << std::endl;
}
};

void choir() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main(int , char const**)
{
    Timer<> timer;
    A a;
    int val= 0;

    // Create a TimerFunction with a lambda
    TimerFunction timerfunc([&val]() {++val; }, 200);

    // Set a TimerFunction with a functor
    timerfunc.setFunction((B()), 500);

    // Set a TimerFunction with a function address
    timerfunc.setFunction(&choir, 50);

    // Set a TimerFunction with std::bind
    timerfunc.setFunction(std::bind(&A::toto, &a), 150);

    // Start the TimerFunction
    timerfunc.start();

    while (true)
    {
        timer.sleep(100);
        if (timerfunc.itCounts() % 50 == 0)
        {
            timerfunc.stop();
            timer.sleep(1000);

            timerfunc.setFunction([&a] () {
                    std::cout << "1 + 2 = " << a.foo(1, 2) << std::endl;}
                    , 200);

            timerfunc.start();
            timer.sleep(5000);
            return 0;
        }
    }

    return 0;
}
