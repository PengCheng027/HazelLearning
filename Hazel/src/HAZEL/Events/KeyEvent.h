#pragma once

#include"HAZEL/Core/KeyCodes.h"
#include"HAZEL/Events/Event.h"

namespace Hazel {

	class KeyEvent :public Event {
	public:
		KeyCode GetKeyCode() const { return mKeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(const KeyCode keyCode)
			:mKeyCode(keyCode) {

		}

		KeyCode mKeyCode;
	};

	class KeyPressedEvent :public KeyEvent {
	public:
		KeyPressedEvent(const KeyCode keyCode, bool isRepeate = false)
			:KeyEvent(keyCode), mIsRepeate(isRepeate) {

		}

		bool IsRepeate() const { return mIsRepeate; }

		std::string	ToString() const {
			
			std::stringstream ss;
			ss << "KeyPressedEvent: " << mKeyCode << "(repeate = " << mIsRepeate << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressd)

	private:
		bool mIsRepeate;
	};

	class KeyReleasedEvent :public KeyEvent {
	public:
		KeyReleasedEvent(const KeyCode keyCode)
			:KeyEvent(keyCode) {

		}

		std::string ToString() const override {

			std::stringstream ss;
			ss << "KeyReleasedEvent: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent :public KeyEvent {
	public:
		KeyTypedEvent(const KeyCode keyCode)
			:KeyEvent(keyCode) {

		}

		std::string ToString() const override {

			std::stringstream ss;
			ss << "KeyTypedEvent" << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}