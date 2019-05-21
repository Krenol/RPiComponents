#include "waiter.hpp"

using namespace std;
using namespace rpicomponents::utils;

void Waiter::Sleep(chrono::duration<float> time)
{
	this_thread::sleep_for(time);
}

void Waiter::SleepNanos(std::chrono::nanoseconds nanos)
{
	thread p(Sleep, nanos);
	p.join();
}

void Waiter::SleepNanos(float nanos)
{
	thread p(Sleep, chrono::nanoseconds(nanos));
	p.join();
}

void Waiter::SleepMillis(std::chrono::milliseconds millis)
{
	thread p(Sleep, millis);
	p.join();
}

void Waiter::SleepMillis(float millis)
{
	thread p(Sleep, chrono::nanoseconds(millis));
	p.join();
}

void Waiter::SleepSecs(std::chrono::seconds secs)
{
	thread p(Sleep, secs);
	p.join();
}

void Waiter::SleepSecs(float secs)
{
	thread p(Sleep, chrono::nanoseconds(secs));
	p.join();
}
