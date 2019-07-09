#include "waiter.hpp"

using namespace rpicomponents::utils;

Waiter::Waiter() {}

Waiter::~Waiter() {}

void Waiter::SleepNanos(std::chrono::nanoseconds nanos) 
{
	std::thread p([&, nanos] {std::this_thread::sleep_for(nanos); });
	p.join();
}

void Waiter::SleepNanos(long nanos) 
{
	std::thread p([&, nanos] {std::this_thread::sleep_for(std::chrono::nanoseconds(nanos)); });
	p.join();
}

void Waiter::SleepMillis(std::chrono::milliseconds millis) 
{
	std::thread p([&, millis] {std::this_thread::sleep_for(millis); });
	p.join();
}

void Waiter::SleepMillis(long millis) 
{
	std::thread p([&, millis] {std::this_thread::sleep_for(std::chrono::nanoseconds(millis)); });
	p.join();
}

void Waiter::SleepSecs(std::chrono::seconds secs) 
{
	std::thread p([&, secs] {std::this_thread::sleep_for(secs); });
	p.join();
}

void Waiter::SleepSecs(long secs) 
{
	std::thread p([&, secs] {std::this_thread::sleep_for(std::chrono::nanoseconds(secs)); });
	p.join();
}
