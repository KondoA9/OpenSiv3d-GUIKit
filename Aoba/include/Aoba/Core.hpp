﻿#pragma once

#include <Siv3D.hpp>
#include <atomic>

namespace s3d::aoba {
    class UIComponent;
    class Page;
    enum class ColorMode;

    class Core final {
    private:
        std::thread::id m_mainThreadId;

        std::unique_ptr<class PageManager> m_pageManager;
        std::unique_ptr<class TaskRunner> m_taskRunner;

        std::atomic<bool> m_terminationPrevented = false;

        Array<std::function<void()>> m_nextFrameFunctions;

    public:
        Core(const Core&) = delete;

        Core(Core&&) = delete;

        Core& operator=(const Core&) = delete;

        Core& operator=(Core&&) = delete;

        static Core& Instance();

        static bool IsMainThread() noexcept;

        static bool IsAsyncTaskAlive() noexcept;

        static bool IsTerminationPrevented() noexcept;

        static bool IsTimeoutAlive(size_t id) noexcept;

        static bool Start();

        static void Terminate();

        static void SwitchPage(StringView identifier);

        // If you call this, you should call ContinueTermination() to terminate app
        static void PreventTermination() noexcept;

        static void ContinueTermination() noexcept;

        /// <summary>
        /// Request to run a task asynchrony, and if need, a completion process will runs on main thread.
        /// </summary>
        /// <param name="task">The process that runs asynchrony. Do not set a process that changes user
        /// interfaces.</param> <param name="completion">The process that runs on main thread after func()
        /// ended.</param>
        static void PostAsyncTask(const std::function<void()>& task,
                                  const std::function<void()>& completion = std::function<void()>());

        /// <summary>
        /// Request to run a process on main thread. In many cases, func is the process that changes user interfaces.
        /// </summary>
        /// <param name="task">The process that runs on main thread.</param>
        static void PostSyncTask(const std::function<void()>& task);

        /// <summary>
        /// Set an event with timeout. Do not set a process that changes user interfaces.
        /// </summary>
        /// <param name="func">A function that runs when timed out.</param>
        /// <param name="ms">The time to time out.</param>
        /// <param name="threading">If true, the function runs asynchronously.</param>
        /// <returns>The ID of the Timeout. ID is 1, 2, 3, ...</returns>
        static size_t SetTimeout(const std::function<void()>& func, uint64 ms, bool threading);

        static bool StopTimeout(size_t id) noexcept;

        static bool RestartTimeout(size_t id) noexcept;

        // Execute func in the next frame.
        static void NextFrame(const std::function<void()>& func);

        template <class T>
        static T& GetPage(StringView identifier) noexcept {
            return static_cast<T&>(Instance().getPage(identifier));
        }

        template <class T>
        static void AppendPage(StringView identifier) {
            Instance().appendPage(std::unique_ptr<T>(new T(identifier)));
        }

    private:
        Core();

        static void AddLicense();

        Page& getPage(StringView identifier) const noexcept;

        void appendPage(std::unique_ptr<Page>&& page);

        void run();

        void update();

        void callNextFrameFunctions();
    };
}
