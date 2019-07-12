#include <chrono>


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
			static void SleepNanos(std::chrono::nanoseconds nanos);

			/**
			* Method that lets a new thread sleep for a certain amount of nanoseconds
			* @param nanos: the amount of nanoseconds for the thread sleep
			*/
			static void SleepNanos(long nanos);

			/**
			* Method that lets a new thread sleep for a certain amount of milliseconds
			* @param millis: the amount of milliseconds for the thread sleep
			*/
			static void SleepMillis(std::chrono::milliseconds millis);

			/**
			* Method that lets a new thread sleep for a certain amount of milliseconds
			* @param millis: the amount of milliseconds for the thread sleep
			*/
			static void SleepMillis(long millis);

			/**
			* Method that lets a new thread sleep for a certain amount of seconds
			* @param secs: the amount of seconds for the thread sleep
			*/
			static void SleepSecs(std::chrono::seconds secs);

			/**
			* Method that lets a new thread sleep for a certain amount of seconds
			* @param secs: the amount of seconds for the thread sleep
			*/
			static void SleepSecs(long secs);

		private:
			/**
			 * Constructor; static class by private Constructor & Deconstructor
			 */
			Waiter();
			~Waiter();
		};
	}
}

#endif