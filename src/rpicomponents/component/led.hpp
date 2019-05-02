#include "component.hpp"

#ifndef RPICOMPONENTS_COMPONENT_LED_H
#define RPICOMPONENTS_COMPONENT_LED_H

namespace rpicomponents {
	namespace component {
		class Led : public Component {
		private:
			Pin* pin_;
			int on_mode_{ 0 };

		public:
			Led(Pin* pin, bool onIfPinOn = true);
			void TurnOn();
			void TurnOn(int value);
			void TurnOff();
			bool IsOn();
		};
	}
}

#endif