#include "dht11.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

void Dht11::Initialize() const
{
	if (pin_ == nullptr) throw new invalid_argument("pin is a nullptr! some internal error occured..");
	auto mode = pin_->OutputMode();
	if (mode != IN_OUT_MODE) throw new invalid_argument("pin for dht11 must be in in_out_mode");
	AddPin(pin_->GetPin());
}

bool Dht11::CheckSum(const std::vector<uint8_t>* bits) const
{
	return false;
}

std::vector<uint8_t> Dht11::ReadSensor() const
{
	lock_guard<mutex> grd(mtx_);
	std::vector<uint8_t> bits (5,0);
	uint8_t laststate = HIGH;
	uint8_t counter = 0;
	uint8_t j = 0, i;
	int MAXTIMINGS = 85;

	/*pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	wait->waitFor(wakeDelay);

	digitalWrite(pin, HIGH);
	wait->waitFor(40 * delayTime);

	pinMode(pin, INPUT);

	for (i = 0; i < MAXTIMINGS; i++)
	{
		counter = 0;
		while (digitalRead(pin) == laststate)
		{
			counter++;
			wait->waitFor(delayTime);
			if (counter == 255)
			{
				break;
			}
		}

		laststate = digitalRead(pin);

		if (counter == 255)
			break;

		if ((i >= 4) && (i % 2 == 0))
		{
			bits[j / 8] <<= 1;
			if (counter > 16)
				bits[j / 8] |= 1;
			j++;
		}
	} */
	return bits;
}

float Dht11::CalculateTemperature(const std::vector<uint8_t>* bits) const
{
	lock_guard<mutex> grd(mtx_);
	return bits[2] + bits[3] * 0.1;
}

float Dht11::CalculateHumidty(const std::vector<uint8_t>* bits) const
{
	lock_guard<mutex> grd(mtx_);
	return bits[0] + bits[1] * 0.1;
}

Dht11::Dht11(int pin) : Component("dht11"), pin_{ PinFactory::CreatePin(pin, DIGITAL_MODE) }
{
	Initialize();
}

float Dht11::GetTemperature() const
{
	auto bits = ReadSensor();
	auto temperature = CalculateTemperature(*bits);
	return temperature;
}

float Dht11::GetHumidity() const
{
	auto bits = ReadSensor();
	auto humidity = CalculateHumidty(*bits);
	return humidity;
}

DHT_VALUES Dht11::GetDhtValues() const
{
	auto bits = ReadSensor();
	DHT_VALUES vals;
	vals.humidity = CalculateHumidty(*bits);;
	vals.temperature = CalculateTemperature(*bits);
	return vals;
}
