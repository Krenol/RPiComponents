#include "pinchecker.hpp"

using namespace std;
using namespace rpicomponents::pin;


bool PinChecker::IsValidPinValue(int pin) {
	if (pin < PIN_MIN_VALUE || pin > PIN_MAX_VALUE) return false;
	return true;
}

bool PinChecker::IsI2CAddress(int address) {
	vector<char> i2c_col = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	vector<char> i2c_row = { '0', '1', '2', '3', '4', '5', '6', '7' };
	string addr;
	auto hexAddr = GetHexAddress(address);

	for (int i = 0; i < i2c_row.size(); i++)
	{
		for (int j = 0; j < i2c_col.size(); j++)
		{
			if (i == 0 && j < 3) continue;
				
			if (i == sizeof(i2c_row) - 1 && j > 7) break;
				
			addr = "";
			addr += to_string(i2c_row[i]);
			addr += to_string(i2c_col[j]);

			if (hexAddr.compare(addr) == 0) return true;
		}
	}

	return false;
}

string PinChecker::GetHexAddress(int address) {
	vector<char> hex = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	string hexdec_num = "";
	int r = 0;
	while (address > 0)
	{
		r = address % 16;
		hexdec_num = hex[r] + hexdec_num;
		address /= 16;
	}
	return hexdec_num;
}

bool PinChecker::PinIsHardwarePWMCapable(int pin) {
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

bool PinChecker::IsValidOutputMode(int outMode) {
	if (outMode != PWM_MODE && outMode != DIGITAL_MODE && outMode != SOFTPWM_MODE && outMode != SOFTTONE_MODE) {
		return false;
	}
	return true;
}
