#include <chrono>
#include <thread>

#ifndef RPICOMPONENTS_UTIL_WAITER_H
#define RPICOMPONENTS_UTIL_WAITER_H

namespace rpicomponents {
	namespace utils {

		class Waiter {

		public:
			/**
			* Method that lets a new thread sleep for a certain amount of nanoseconds
			* @param nanos: the amount of nanoseconds for the thread sleep
			*/
			void SleepNanos(std::chrono::nanoseconds nanos) const;

			/**
			* Method that lets a new thread sleep for a certain amount of nanoseconds
			* @param nanos: the amount of nanoseconds for the thread sleep
			*/
			void SleepNanos(long nanos) const;

			/**
			* Method that lets a new thread sleep for a certain amount of milliseconds
			* @param millis: the amount of milliseconds for the thread sleep
			*/
			void SleepMillis(std::chrono::milliseconds millis) const;

			/**
			* Method that lets a new thread sleep for a certain amount of milliseconds
			* @param millis: the amount of milliseconds for the thread sleep
			*/
			void SleepMillis(long millis) const;

			/**
			* Method that lets a new thread sleep for a certain amount of seconds
			* @param secs: the amount of seconds for the thread sleep
			*/
			void SleepSecs(std::chrono::seconds secs) const;

			/**
			* Method that lets a new thread sleep for a certain amount of seconds
			* @param secs: the amount of seconds for the thread sleep
			*/
			void SleepSecs(long secs) const;
		};
	}
}

#endif