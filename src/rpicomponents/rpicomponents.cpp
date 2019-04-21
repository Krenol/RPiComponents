// RPiComponents.cpp : Defines the entry point for the application.
//

#include "rpicomponents.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::component;
using namespace rpicomponents::pin;
int main()
{
	cout << "GPIO11 number: " << GPIO11 << endl;
	cout << "Pin is hardware PWM capable? " << PinChecker::PinIsHardwarePWMCapable(GPIO11) << endl;
	auto pin = DigitalPin(GPIO11);
	cout << pin.IsOn() << endl;
	cin.get();
	return 0;
}
