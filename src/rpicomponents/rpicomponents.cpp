﻿// RPiComponents.cpp : Defines the entry point for the application.
//

#include "rpicomponents.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::component;
using namespace rpicomponents::pin;

int main() {
	auto p = new DigitalPin(GPIO2);

	cin.get();
	return 0;
}