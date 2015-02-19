# TimerFunction
TimerFunction class in C++

After start(), executes a fonction with a `void (void)` signature and sleep fo n milliseconds till TimerFunction object is destroyed or stop() called.

To compile:

clang++ -std=c++11 -Wall -W main.cpp -o exec -pthread
