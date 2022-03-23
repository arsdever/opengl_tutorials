#include <profiler.hpp>

#include "fps_counter.hpp"

namespace gl
{
    fps_counter::~fps_counter()
    {
        _exit = true;
        _thd.join();
    }

    void fps_counter::start()
    {
        auto scoped_profiler_instance = prof::profiler::profile(__func__);
        _thd                          = std::thread { [ & ]() {
            _fps_counter_start        = std::chrono::system_clock::now();
            _fps_counter              = 0;
            while (!_exit)
                {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    double elapsed =
                        std::chrono::duration<double>(std::chrono::system_clock::now() - _fps_counter_start).count();
                    _last_fps_data     = static_cast<double>(_fps_counter) / elapsed;
                    _fps_counter_start = std::chrono::system_clock::now();
                    _fps_counter       = 0;

                    if (_update_cb)
                        _update_cb(_last_fps_data);
                }
        } };
    }

    void fps_counter::on_data_update(std::function<void(double)> cb)
    {
        auto scoped_profiler_instance = prof::profiler::profile(__func__);
        _update_cb                    = cb;
    }

    void fps_counter::frame()
    {
        auto scoped_profiler_instance = prof::profiler::profile(__func__);
        ++_fps_counter;
    }

    double fps_counter::last_data() const
    {
        auto scoped_profiler_instance = prof::profiler::profile(__func__);
        return _last_fps_data;
    }
} // namespace gl