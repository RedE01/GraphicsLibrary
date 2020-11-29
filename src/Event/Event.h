#pragma once

namespace rgl {

    #define BIT(x) (1 << x)

    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

    class Event {
    public:
        virtual int GetCategoryFlags() const = 0;
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;

        bool isInCategory(const EventCategory& category) {
            return GetCategoryFlags() & category;
        }
    };

}