#ifndef TIMER_HPP_
# define TIMER_HPP_

# include <chrono>
# include <thread>

template<class T = std::chrono::milliseconds>
class Timer
{
public:
    Timer() : start_(std::chrono::high_resolution_clock::now())
    {}

    inline void reset()
    {
        start_ = std::chrono::high_resolution_clock::now();
    }

    inline double elapsed() const
    {
        return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - start_).count();
    }

    inline void sleep(int n) const
    {
        std::this_thread::sleep_for(T(n));
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};

#endif /* end of include guard */
