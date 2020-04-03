#include "addresschecker.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

bool rpicomponents::pin::AddressChecker::IsI2CAddress(int address) {
	const std::vector<char> i2c_col = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	const std::vector<char> i2c_row = { '0', '1', '2', '3', '4', '5', '6', '7' };
	auto hexAddr = GetHexAddress(address);
	std::string addr;
	auto rowLgth = std::distance(i2c_row.begin(), i2c_row.end());
	int rowPos, colPos;

	for(auto row = i2c_row.begin(); row != i2c_row.end(); ++row) {
		for(auto col = i2c_col.begin(); col != i2c_col.end(); ++col) {
			addr.clear();
			rowPos = std::distance(i2c_row.begin(), row);
			colPos = std::distance(i2c_col.begin(), col);

			if (rowPos == 0 && colPos < 3) continue;

			if (rowPos == rowLgth - 1 && colPos > 7) break;

            addr += *row;
            addr += *col;

			if (hexAddr.compare(addr) == 0) return true;
		}
	}

	return false;
}

std::string rpicomponents::pin::AddressChecker::GetHexAddress(int address) {
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
