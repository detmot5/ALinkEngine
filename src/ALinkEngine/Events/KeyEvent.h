#ifndef ALINKENGINE_EVENTS_KEYEVENT_H_
#define ALINKENGINE_EVENTS_KEYEVENT_H_

#include "Core/KeyCodes.h"
#include "Event.h"

namespace ALink {

class KeyEvent : public Event {
 public:
  KeyCode GetKeyCode() const { return m_KeyCode; }

  EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
 protected:
  explicit KeyEvent(const KeyCode keycode) : m_KeyCode(keycode) {}

  KeyCode m_KeyCode;
};

class KeyPressedEvent : public KeyEvent {
 public:
  KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount)
      : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

  uint16_t GetRepeatCount() const { return m_RepeatCount; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount
       << " repeats)";
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyPressed)
 private:
  uint16_t m_RepeatCount;
};

class KeyReleasedEvent : public KeyEvent {
 public:
  explicit KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << m_KeyCode;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent {
 public:
  explicit KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyTypedEvent: " << m_KeyCode;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyTyped)
};
}  // namespace ALink
#endif  // ALINKENGINE_EVENTS_KEYEVENT_H_
