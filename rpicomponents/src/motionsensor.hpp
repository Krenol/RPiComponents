#include "component.hpp"

#ifndef RPICOMPONENTS_MOTIONSENSOR_H
#define RPICOMPONENTS_MOTIONSENSOR_H


namespace rpicomponents {
constexpr const char* COMPONENT_MOTIONSENSOR = "motionsensor";
	class Motionsensor : Component {
	private:
        const std::unique_ptr<pin::Pin> pin_;

	public:

		/*
		 * Constructor for the motion sensor
		 * @param pin constant pointer to the input pin of the motion sensor
		*/
        Motionsensor(int pin);

		/*
		 * Constructor for the motion sensor
		 * @param pin GPIO pin of the motion sensor pin (must be a input pin if already in use)
		*/
		//Motionsensor(int&& pin);

		/*
		 * Copy constructor for the motion sensor
		 * @param motionsensor Motionsensor to be copied
		*/
		Motionsensor(const Motionsensor& motionsensor);

		/*
		 * Method to check if the motion sensor has detected a motion or not
		 * NON BLOCKING
		 * @returns true if a motion has been detected else false
		*/
		bool MotionDetected() const;

		/*
		* Method to get the used pin
		*
		* @returns the used pin of the component
		*/
		int GetPin() const;

	};
}

#endif
