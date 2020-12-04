#pragma once
#include "Event.h"

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

}