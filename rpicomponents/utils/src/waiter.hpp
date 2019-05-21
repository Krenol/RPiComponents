#include <ctime>
#include <thread>

#ifndef RPICOMPONENTS_UTIL_WAITER_H
#define RPICOMPONENTS_UTIL_WAITER_H

namespace rpicomponents {
	namespace utils {

		class Waiter {
		private:
			/**
			* Method that lets a new thread sleep for a certain amount of time
			* @param time: the amount of time for the thread sleep
			*/
			void Sleep(chrono::duration<float> time);

		public:
			/**
			* Method that lets a new thread sleep for a certain amount of nanoseconds
			* @param nanos: the amount of nanoseconds for the thread sleep
			*/
			void SleepNanos(std::chrono::nanoseconds nanos);

			/**
			* Method that lets a new thread sleep for a certain amount of nanoseconds
			* @param nanos: the amount of nanoseconds for the thread sleep
			*/
			void SleepNanos(float nanos);

			/**
			* Method that lets a new thread sleep for a certain amount of milliseconds
			* @param millis: the amount of milliseconds for the thread sleep
			*/
			void SleepMillis(std::chrono::milliseconds millis);

			/**
			* Method that lets a new thread sleep for a certain amount of milliseconds
			* @param millis: the amount of milliseconds for the thread sleep
			*/
			void SleepMillis(float millis);

			/**
			* Method that lets a new thread sleep for a certain amount of seconds
			* @param secs: the amount of seconds for the thread sleep
			*/
			void SleepSecs(std::chrono::seconds secs);

			/**
			* Method that lets a new thread sleep for a certain amount of seconds
			* @param secs: the amount of seconds for the thread sleep
			*/
			void SleepSecs(float secs);
		};
	}
}

#endif