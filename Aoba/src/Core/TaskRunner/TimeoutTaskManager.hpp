﻿#pragma once

#include <functional>
#include <vector>

#include "src/Core/TaskRunner/Timeout.hpp"

namespace s3d::aoba {
    class TimeoutTaskManager final {
    private:
        std::vector<Timeout> m_timeouts;

    public:
        bool isAlive(size_t id) const noexcept;

        bool isRunning(size_t id) const noexcept;

        size_t addTask(const std::function<void()>& task, uint64_t ms, bool threading);

        void update();

        bool stop(size_t id) noexcept;

        bool restart(size_t id) noexcept;
    };
}
