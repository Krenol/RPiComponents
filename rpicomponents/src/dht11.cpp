#include "dht11.hpp"


void rpicomponents::Dht11::Initialize() const
{
    auto mode = pin_->OutputMode();
	if (mode != rpicomponents::pin::IN_OUT_MODE) throw new std::invalid_argument("pin for dht11 must be in in_out_mode");
    AddPin(pin_->GetPin());
}

bool rpicomponents::Dht11::CheckSum(const std::vector<uint8_t> &bits) const
{
	auto sum = bits[0] + bits[1] + bits[2] + bits[3];
	if (sum == bits[4] && sum > 0)
		return true;
	return false;
}

std::vector<uint8_t> rpicomponents::Dht11::ReadSensor() const
{
	std::lock_guard<std::mutex> grd(mtx_);
	std::vector<uint8_t> bits (5,0);
	uint8_t counter = 0, j = 0;

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

float rpicomponents::Dht11::CalculateTemperature(const std::vector<uint8_t> &bits) const
{
	std::lock_guard<std::mutex> grd(mtx_);
	return bits[2] + bits[3] * 0.1;
}

float rpicomponents::Dht11::CalculateHumidty(const std::vector<uint8_t> &bits) const
{
	std::lock_guard<std::mutex> grd(mtx_);
	return bits[0] + bits[1] * 0.1;
}

rpicomponents::Dht11::Dht11(const int8_t& pin) : Component(COMPONENT_DHT11), pin_{ rpicomponents::pin::PinCreator::CreatePin(pin, rpicomponents::pin::DIGITAL_MODE) }
{
	Initialize();
}

rpicomponents::Dht11::Dht11(int8_t&& pin) : Component(COMPONENT_DHT11), pin_{ rpicomponents::pin::PinCreator::CreatePin(pin, rpicomponents::pin::DIGITAL_MODE) }
{
	Initialize();
}

rpicomponents::Dht11::Dht11(const Dht11& dht11) : Component(dht11.ToString()), pin_{ rpicomponents::pin::PinCreator::CreatePin(dht11.GetPin(), rpicomponents::pin::DIGITAL_MODE) }
{
	Initialize();
}

float rpicomponents::Dht11::GetTemperature() const
{
	auto bits = ReadSensor();
	while(!CheckSum(bits)) bits = ReadSensor();
	auto temperature = CalculateTemperature(bits);
	return temperature;
}

float rpicomponents::Dht11::GetHumidity() const
{
	auto bits = ReadSensor();
	while (!CheckSum(bits)) bits = ReadSensor();
	auto humidity = CalculateHumidty(bits);
	return humidity;
}

rpicomponents::DHT_VALUES rpicomponents::Dht11::GetDhtValues() const
{
	auto bits = ReadSensor();
	while (!CheckSum(bits)) bits = ReadSensor();
	DHT_VALUES vals;
	vals.humidity = CalculateHumidty(bits);
	vals.temperature = CalculateTemperature(bits);
	return vals;
}

const int8_t& rpicomponents::Dht11::GetPin() const
{
    return pin_->GetPin();
}
