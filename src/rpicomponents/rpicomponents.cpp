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
	cout << "Pin is hardware PWM capable? " << Pin::PinIsHardwarePWMCapable(GPIO11) << endl;
	cin.get();
	return 0;
}
