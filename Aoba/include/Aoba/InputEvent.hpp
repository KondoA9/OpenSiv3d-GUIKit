﻿#pragma once

#include <Siv3D.hpp>

// Create InputEvent
#define AobaCreateEvent(EVENT_NAME)                                                                      \
    struct EVENT_NAME : public s3d::aoba::InputEvent {                                                   \
        explicit EVENT_NAME(s3d::aoba::UIBase* _component, bool callIfComponentInFront = true) :         \
            s3d::aoba::InputEvent(typeid(EVENT_NAME).hash_code(), _component, callIfComponentInFront) {} \
    };

// Create InputEvent in namespace NAMESPACE
#define AobaCreateEventNS(NAMESPACE, EVENT_NAME) \
    namespace NAMESPACE {                        \
        AobaCreateEvent(EVENT_NAME)              \
    }

// Create InputEvent in namespace s3d::aoba::Event::NAMESPACE
#define AobaCreateEventNSEvent(NAMESPACE, EVENT_NAME) AobaCreateEventNS(s3d::aoba::Event::NAMESPACE, EVENT_NAME)

namespace s3d::aoba {
    class UIBase;

    struct InputEvent {
        const size_t id;
        const double wheel;
        const Vec2 pos, previousPos;
        const bool callIfComponentInFront;

        UIBase* component;

        InputEvent() = delete;

        InputEvent(size_t _id, UIBase* _component, bool _callIfComponentInFront) noexcept :
            id(_id),
            wheel(Mouse::Wheel()),
            pos(Cursor::PosF()),
            previousPos(Cursor::PreviousPosF()),
            callIfComponentInFront(_callIfComponentInFront),
            component(_component) {}

        virtual ~InputEvent() = default;

        constexpr InputEvent(const InputEvent& e) noexcept = default;

        constexpr InputEvent(InputEvent&& e) noexcept = default;

        const InputEvent& operator=(const InputEvent& e) noexcept {
            assert(id == e.id);

            component = e.component;

            return *this;
        }

        const InputEvent& operator=(InputEvent&& e) noexcept {
            assert(id == e.id);

            component = std::move(e.component);

            return *this;
        }
    };
}
