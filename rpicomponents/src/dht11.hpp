#include "component.hpp"


#ifndef RPICOMPONENTS_DHT11_H
#define RPICOMPONENTS_DHT11_H

namespace rpicomponents {

	struct DHT_VALUES {
		float temperature{ 0 };
		float humidity{ 0 };
	};
    constexpr const char* COMPONENT_DHT11 = "dht11";
	class Dht11 : public Component {
	private:
        const std::unique_ptr<pin::Pin> pin_; //the used pin of the button
		const float wake_delay_{ 18.0f * 1e-3f }, time_delay_{ 1.0f * 1e-6f }; //ms
		const int max_timings_ = 85;

		/*
		Initializer for Constructors; reduce redundancy
		*/
		void Initialize() const;

		/*
		Method to check if read values are valid

		@param bits: the bits to be checked (must be of size 5)
		@returns true if checksum is valid, else false
		*/
		bool CheckSum(const std::vector<uint8_t> &bits) const;

		/*
		Method to read the sensor values to a vector

		@returns the read values as a vector
		*/
		std::vector<uint8_t> ReadSensor() const;

		/*
		Method to calculate the temperature out of a bit vector

		@returns the temperature as float or INFINITY on error
		*/
		float CalculateTemperature(const std::vector<uint8_t> &bits) const;

		/*
		Method to calculate the humidty out of a bit vector

		@returns the humidty as float or INFINITY on error
		*/
		float CalculateHumidty(const std::vector<uint8_t> &bits) const;
	public:

		/*
		Constructor for creating a DHT11
		
		@param pin: GPIO pin number of the DHT11
		*/
		Dht11(const int &pin);

		/*
		Constructor for creating a DHT11
		
		@param pin: GPIO pin number of the DHT11
		*/
		Dht11(int&& pin);

		/*
		Copy Constructor 
		
		@param dht11 The DHT11 to be copied
		*/
		Dht11(const Dht11& dht11);

		/*
		Method to get the temperature measured by the dht11
		
		@returns the temperature or INFINITY if an error occurs
		*/
		float GetTemperature() const;

		/*
		Method to get the humidty measured by the dht11

		@returns the humidity or INFINITY if an error occurs
		*/
		float GetHumidity() const;

		/*
		Method to get the temperature & humidty measured by the dht11
		
		@returns the humidty and temperature measured by the DHT11 as a struct; if measured values are INFINITY an error occured
		*/
		DHT_VALUES GetDhtValues() const;

		/*
		Method to get the used pin
		
		@returns the used pin of the component
		*/
		const int& GetPin() const;
	};
}

#endif
