#ifndef TIMERFUNCTION_HPP_
# define TIMERFUNCTION_HPP_

# include <chrono>
# include <thread>
# include <functional>
# include <memory>
# include <atomic>
# include <cassert>

# include "Timer.hpp"

class TimerFunction : public Timer<std::chrono::milliseconds>
{
    typedef std::function<void ()> func;

    public:

    TimerFunction():Timer(),
    cpt_(0), timetoSleep_(0), continue_(true),
    started_(false), stopped_(true)
    {}

    TimerFunction(func function, int timetoSleep)
    :TimerFunction()
    {
        setFunction(function, timetoSleep);
    }

    ~TimerFunction()
    {
        if (!stopped_)
        {
            continue_ = false;
            thread_.join();
        }
    }

    void start()
    {
        assert(started_ == false);

        started_ = true;
        continue_ = true;
        cpt_ = 0;
        stopped_ = false;
        reset();
        thread_ = std::thread(&TimerFunction::run, this);
    }

    void setFunction(func function, int timetoSleep)
    {
        assert(timetoSleep > 0);
        assert(function != nullptr);

        timetoSleep_ = timetoSleep;
        func_ = function;
    }

    void stop()
    {
        assert(started_ == true);
        assert(continue_ == true);

        started_ = false;
        continue_ = false;
        //thread_.detach();
        thread_.join();

    }

    long long itCounts() const
    {
        return cpt_;
    }

    bool isRunning() const
    {
        return thread_.joinable();
    }

    bool isStopped() const
    {
        return stopped_;
    }

    private:

    void run()
    {
        while (continue_)
        {
            ++cpt_;
            func_();
            sleep(timetoSleep_);
        }
        stopped_ = true;
    }

    std::function<void()>           func_;
    std::atomic<long long int>      cpt_;
    int                             timetoSleep_;
    std::thread                     thread_;
    std::atomic<bool>               continue_;
    std::atomic<bool>               started_;
    std::atomic<bool>               stopped_;

};

#endif /* end of include guard */
