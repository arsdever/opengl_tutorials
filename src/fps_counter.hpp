#pragma once

#include <functional>
#include <queue>
#include <thread>

namespace gl
{
    class fps_counter
    {
    public:
        void   start();
        void   frame();
        double last_data() const;
        void   on_data_update(std::function<void(double)> cb);

    private:
        std::thread                           _thd;
        unsigned                              _fps_counter;
        double                                _last_fps_data;
        std::chrono::system_clock::time_point _fps_counter_start;
        std::function<void(double)>           _update_cb;
    };
} // namespace gl