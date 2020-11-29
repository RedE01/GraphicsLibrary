#pragma once
#include "Event.h"

namespace rgl {

    class WindowCloseEvent : public Event {
    public:
        virtual int GetCategoryFlags() const { return EventCategory::EventCategoryApplication; }
        virtual EventType GetEventType() const { return EventType::WindowClose; }
        virtual const char* GetName() const { return "WindowCloseEvent"; }
    };

}