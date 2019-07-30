#include "addresschecker.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>


bool rpicomponents::pin::AddressChecker::IsValidPinValue(int8_t pin) {
	if (pin < PIN_MIN_VALUE || pin > PIN_MAX_VALUE) return false;
	return true;
}

bool rpicomponents::pin::AddressChecker::IsI2CAddress(int16_t address) {
	const std::vector<char> i2c_col = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	const std::vector<char> i2c_row = { '0', '1', '2', '3', '4', '5', '6', '7' };
	auto hexAddr = GetHexAddress(address);

	for (int i = 0; i < i2c_row.size(); i++)
	{
		for (int j = 0; j < i2c_col.size(); j++)
		{
			if (i == 0 && j < 3) continue;
				
			if (i == sizeof(i2c_row) - 1 && j > 7) break;
				
			std::string addr;
			addr += i2c_row[i];
			addr += i2c_col[j];

			if (hexAddr.compare(addr) == 0) return true;
		}
	}

	return false;
}

std::string rpicomponents::pin::AddressChecker::GetHexAddress(int16_t address) {
	std::vector<char> hex = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	std::string hexdec_num = "";
	int r = 0;
	while (address > 0)
	{
		r = address % 16;
		hexdec_num = hex[r] + hexdec_num;
		address /= 16;
	}
	return hexdec_num;
}

bool rpicomponents::pin::AddressChecker::PinIsHardwarePWMCapable(int8_t pin) {
	//PWM channel 0
	if (pin == PWM_CHANNEL0_PIN1 || pin == PWM_CHANNEL0_PIN2) { 
		return true;
	}
	//PWM channel 1
	if (pin == PWM_CHANNEL1_PIN1 || pin == PWM_CHANNEL1_PIN2) {
		return true;
	}
	return false;
}
