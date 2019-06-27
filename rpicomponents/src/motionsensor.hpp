#include "component.hpp"

#ifndef RPICOMPONENTS_MOTIONSENSOR_H
#define RPICOMPONENTS_MOTIONSENSOR_H


namespace rpicomponents {
	class Motionsensor : Component {
	private:
		const pin::Pin* pin_;

		/*
		 * generic motion sensor initializer to avoid code duplication
		*/
		void Initialize() const;

	public:

		/*
		 * Constructor for the motion sensor
		 * @param pin constant pointer to the input pin of the motion sensor
		*/
		Motionsensor(const pin::Pin* pin);

		/*
		 * Constructor for the motion sensor
		 * @param pin GPIO pin of the motion sensor pin (must be a input pin if already in use)
		*/
		Motionsensor(int8_t pin);

		/*
		 * Method to check if the motion sensor has detected a motion or not
		 * NON BLOCKING
		 * @returns true if a motion has been detected else false
		*/
		bool MotionDetected() const;

	};
}

#endif
