#ifndef RPICOMPONENTS_PINCHECKER_H
#define RPICOMPONENTS_PINCHECKER_H
#pragma once

#include <string>
#include "pindefinitions.hpp"

namespace rpicomponents {
	namespace pin {
		class AddressChecker {
		public:

			/*
            Static method to check whether an address is a valid I2C address or not
            
            @param address The i2c address to be checked
            @return true if hardware is a valid I2C address capable, else false
            */
			static bool IsI2CAddress(int address);

			/*
            Static method to transform an integer & decimal I2C addres into a std::string hex value
            
            @param address The decimal i2c address to be transformed
            @return String with the transformed hex i2c address
            */
			static std::string GetHexAddress(int address);


		private:
			/*
            Private constructor to make class static
            */
			AddressChecker() {}
			AddressChecker(const AddressChecker&) = delete;
			AddressChecker& operator=(const AddressChecker&) = delete;
		};
	}
}


#endif
