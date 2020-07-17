#include "dht11.hpp"

namespace rpicomponents
{
	void Dht11::Initialize()
	{
		auto mode = pin_->OutputMode();
		if (mode != pin::IN_OUT_MODE)
			throw new std::invalid_argument("pin for dht11 must be in in_out_mode");
		AddPin(pin_->GetPin());
	}

	bool Dht11::CheckSum(const std::vector<uint8_t> &bits) const
	{
		auto sum = bits[0] + bits[1] + bits[2] + bits[3];
		if (sum == bits[4] && sum > 0)
			return true;
		return false;
	}

	std::vector<uint8_t> Dht11::ReadSensor()
	{
		std::vector<uint8_t> bits(5, 0);
		uint8_t counter = 0, j = 0;

		std::lock_guard<std::mutex> guard(mtx_);
		pin_->Output(LOW);

		utils::Waiter::SleepMillis(wake_delay_);
		pin_->Output(HIGH);
		utils::Waiter::SleepMillis(40 * time_delay_);

		auto laststate = HIGH;
		for (auto i = 0; i < max_timings_; i++)
		{
			counter = 0;
			while (pin_->ReadPinValue() == laststate)
			{
				counter++;
				utils::Waiter::SleepMillis(time_delay_);
				if (counter == 255)
				{
					return bits;
				}
			}
			laststate = pin_->ReadPinValue();

			if ((i >= 4) && (i % 2 == 0))
			{
				bits[j / 8] <<= 1;
				if (counter > 16)
					bits[j / 8] |= 1;
				j++;
			}
		}
		return bits;
	}

	float Dht11::CalculateTemperature(const std::vector<uint8_t> &bits) const
	{
		return bits[2] + bits[3] * 0.1;
	}

	float Dht11::CalculateHumidty(const std::vector<uint8_t> &bits) const
	{
		return bits[0] + bits[1] * 0.1;
	}
	
	std::vector<uint8_t> Dht11::GetValidBits()
	{
		auto bits = ReadSensor(); {
		while (!CheckSum(bits))
			bits = ReadSensor();
		}
	}

	Dht11::Dht11(std::shared_ptr<pin::Pin> pin) : Component(COMPONENT_DHT11), pin_{pin}
	{
		Initialize();
	}


	Dht11::Dht11(const Dht11 &dht11) : Component(dht11.ToString()), pin_{dht11.GetPin()}
	{
		Initialize();
	}

	float Dht11::GetTemperature()
	{
		auto bits = GetValidBits();
		auto temperature = CalculateTemperature(bits);
		return temperature;
	}

	float Dht11::GetHumidity()
	{
		auto bits = GetValidBits();
		auto humidity = CalculateHumidty(bits);
		return humidity;
	}

	DHT_VALUES Dht11::GetDhtValues()
	{
		DHT_VALUES vals;
		GetDhtValues(vals);
		return vals;
	}
	
	void Dht11::GetDhtValues(DHT_VALUES& out) 
	{
		auto bits = GetValidBits();
		out.humidity = CalculateHumidty(bits);
		out.temperature = CalculateTemperature(bits);
	}
	
	void Dht11::GetValuesJSON(nlohmann::json& out) 
	{
		auto bits = GetValidBits();
		float val = CalculateHumidty(bits);
		out.at("temperature").get_to(val);
		val = CalculateTemperature(bits);
        out.at("humidity").get_to(val);
	}

	const std::shared_ptr<pin::Pin> &Dht11::GetPin() const
	{
		return pin_;
	}

	nlohmann::json Dht11::GetValuesJSON()
	{
		nlohmann::json j;
		GetValuesJSON(j);
		return j;
	}
} // namespace rpicomponents