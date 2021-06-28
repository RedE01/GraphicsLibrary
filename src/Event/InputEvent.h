#pragma once
#include "Event.h"
#include "../Etc/Vector.h"

namespace rgl {

    class KeyPressedEvent : public Event {
    public:
        KeyPressedEvent(const int& key) : key(key) {}
        virtual int GetCategoryFlags() const { return EventCategory::EventCategoryInput | EventCategoryKeyboard; }
        virtual EventType GetEventType() const { return EventType::KeyPressed; }
        virtual const char* GetName() const { return "KeyPressedEvent"; }

    public:
        int key;
    };

    class KeyReleasedEvent : public Event {
    public:
        KeyReleasedEvent(const int& key) : key(key) {}
        virtual int GetCategoryFlags() const { return EventCategory::EventCategoryInput | EventCategoryKeyboard; }
        virtual EventType GetEventType() const { return EventType::KeyReleased; }
        virtual const char* GetName() const { return "KeyReleasedEvent"; }

    public:
        int key;
    };

    class KeyTypedEvent : public Event {
    public:
        KeyTypedEvent(const int& key) : key(key) {}
        virtual int GetCategoryFlags() const { return EventCategory::EventCategoryInput | EventCategoryKeyboard; }
        virtual EventType GetEventType() const { return EventType::KeyTyped; }
        virtual const char* GetName() const { return "KeyTypedEvent"; }

    public:
        int key;
    };

    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(Vector2i windowCoords, Vector2i rootWindowCoords) : windowCoords(windowCoords), rootWindowCoords(rootWindowCoords) {}
        virtual int GetCategoryFlags() const { return EventCategory::EventCategoryInput | EventCategoryMouse; }
        virtual EventType GetEventType() const { return EventType::MouseMoved; }
        virtual const char* GetName() const { return "MouseMovedEvent"; }

    public:
        Vector2i windowCoords, rootWindowCoords;
    };

    class MouseButtonPressedEvent : public Event {
    public:
        MouseButtonPressedEvent(const int& button, Vector2i windowCoords, Vector2i rootWindowCoords) : button(button), windowCoords(windowCoords), rootWindowCoords(rootWindowCoords) {}
        virtual int GetCategoryFlags() const { return EventCategory::EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton; }
        virtual EventType GetEventType() const { return EventType::MouseButtonPressed; }
        virtual const char* GetName() const { return "MouseButtonPressedEvent"; }

    public:
        int button;
        Vector2i windowCoords, rootWindowCoords;
    };

    class MouseButtonReleasedEvent : public Event {
    public:
        MouseButtonReleasedEvent (const int& button, Vector2i windowCoords, Vector2i rootWindowCoords) : button(button), windowCoords(windowCoords), rootWindowCoords(rootWindowCoords) {}
        virtual int GetCategoryFlags() const { return EventCategory::EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton; }
        virtual EventType GetEventType() const { return EventType::MouseButtonReleased; }
        virtual const char* GetName() const { return "MouseButtonReleasedEvent "; }

    public:
        int button;
        Vector2i windowCoords, rootWindowCoords;
    };
}