#pragma once

#pragma once

#include"HAZEL/Core/MouseCodes.h"
#include"HAZEL/Events/Event.h"

namespace Hazel {

	class MouseMovedEvent :public Event {
	public:
		MouseMovedEvent(const float x, const float y)
			:mMouseX(x), mMouseY(y) {

		}

		float GetX() const { return mMouseX; }
		float GetY() const { return mMouseY; }

		std::string ToString() const override {

			std::stringstream ss;
			ss << "MouseMovedEvent: " << mMouseX << "," << mMouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float mMouseX, mMouseY;
	};

	class MouseScrolledEvent :public Event {
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			:mXOffset(xOffset), mYOffset(yOffset) {

		}

		float GetXOffset() const { return mXOffset; }
		float GetYOffset() const { return mYOffset; }

		std::string ToString() const override {

			std::stringstream ss;
			ss << "MouseScrolledEvent: " << mXOffset << "," << mYOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float mXOffset, mYOffset;
	};

	class MouseButtonEvent :public Event {
	public:
		MouseCode GetMouseButton() const { return mButton; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

	protected:
		MouseButtonEvent(const MouseCode button)
			:mButton(button){

		}

		MouseCode mButton;
	};

	class MouseButtonPressedEvent :public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(const MouseCode button)
			:MouseButtonEvent(button) {

		}

		std::string ToString() const override {
			
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << mButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent :public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(const MouseCode button)
			:MouseButtonEvent(button) {

		}

		std::string ToString() const override{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << mButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}


