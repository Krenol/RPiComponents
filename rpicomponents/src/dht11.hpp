#include "component.hpp"
#include "utils/utils.hpp"
#include <nlohmann/json.hpp>
#include <mutex>


#ifndef RPICOMPONENTS_DHT11_H
#define RPICOMPONENTS_DHT11_H

namespace rpicomponents {

	struct DHT_VALUES {
		float temperature{ 0 };
		float humidity{ 0 };
	};

	void to_json(nlohmann::json& j, const DHT_VALUES& d) {
		j = nlohmann::json{{"temperature", d.temperature}, {"humidity", d.humidity}};
	}

    void from_json(const nlohmann::json& j, DHT_VALUES& d) {
        j.at("temperature").get_to(d.temperature);
        j.at("humidity").get_to(d.humidity);
    }

    constexpr const char* COMPONENT_DHT11 = "dht11";
	class Dht11 : public Component {
	private:
        const std::shared_ptr<pin::Pin> pin_; //the used pin of the button
		const float wake_delay_{ 18.0f * 1e-3f }, time_delay_{ 1.0f * 1e-6f }; //ms
		const int max_timings_ = 85;
		std::mutex mtx_;

		/*
		Initializer for Constructors; reduce redundancy
		*/
        void Initialize();

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
		std::vector<uint8_t> ReadSensor();

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

		/*
		Method to get valid bits for further calculation

		@returns the retrieved bits from the dht11
		*/
		std::vector<uint8_t> GetValidBits();
	public:

		/*
		Constructor for creating a DHT11
		
		@param pin: GPIO pin number of the DHT11
		*/
		Dht11(std::shared_ptr<pin::Pin> pin);

		/*
		Constructor for creating a DHT11
		
		@param pin: GPIO pin number of the DHT11
		*/
		//Dht11(int&& pin);

		/*
		Copy Constructor 
		
		@param dht11 The DHT11 to be copied
		*/
		Dht11(const Dht11& dht11);

		/*
		Method to get the temperature measured by the dht11
		
		@returns the temperature or INFINITY if an error occurs
		*/
		float GetTemperature();

		/*
		Method to get the humidty measured by the dht11

		@returns the humidity or INFINITY if an error occurs
		*/
		float GetHumidity();

		/*
		Method to get the temperature & humidty measured by the dht11
		
		@returns the humidty and temperature measured by the DHT11 as a struct; if measured values are INFINITY an error occured
		*/
		DHT_VALUES GetDhtValues();

		/*
		Method to get the temperature & humidty measured by the dht11
		
		@param out: Struct to store the humidty and temperature measured by the DHT11 as a struct; if measured values are INFINITY an error occured
		*/
		void GetDhtValues(DHT_VALUES& out);

		/*
		Method to get the temperature & humidty measured by the dht11
		
		@param out: JSON to store the humidty and temperature measured by the DHT11 as a JSON; if measured values are INFINITY an error occured
		*/
		void GetValuesJSON(nlohmann::json& out);

		/*
		Method to get the temperature & humidty measured by the dht11
		
		@returns the humidty and temperature measured by the DHT11 as a JSON; if measured values are INFINITY an error occured
		*/
		nlohmann::json GetValuesJSON();

		/*
		Method to get the used pin
		
		@returns the used pin of the component
		*/
		const std::shared_ptr<pin::Pin>& GetPin() const;
	};
}

#endif
