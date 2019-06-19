#include "waiter.hpp"

using namespace std;
using namespace rpicomponents::utils;

Waiter::Waiter() {}

Waiter::~Waiter() {}

void Waiter::SleepNanos(std::chrono::nanoseconds nanos) 
{
	thread p([&, nanos] {this_thread::sleep_for(nanos); });
	p.join();
}

void Waiter::SleepNanos(long nanos) 
{
	thread p([&, nanos] {this_thread::sleep_for(std::chrono::nanoseconds(nanos)); });
	p.join();
}

void Waiter::SleepMillis(std::chrono::milliseconds millis) 
{
	thread p([&, millis] {this_thread::sleep_for(millis); });
	p.join();
}

void Waiter::SleepMillis(long millis) 
{
	thread p([&, millis] {this_thread::sleep_for(chrono::nanoseconds(millis)); });
	p.join();
}

void Waiter::SleepSecs(std::chrono::seconds secs) 
{
	thread p([&, secs] {this_thread::sleep_for(secs); });
	p.join();
}

void Waiter::SleepSecs(long secs) 
{
	thread p([&, secs] {this_thread::sleep_for(chrono::nanoseconds(secs)); });
	p.join();
}
