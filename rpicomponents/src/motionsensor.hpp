#include "component.hpp"

#ifndef RPICOMPONENTS_MOTIONSENSOR_H
#define RPICOMPONENTS_MOTIONSENSOR_H


namespace rpicomponents {
constexpr const char* COMPONENT_MOTIONSENSOR = "motionsensor";
	class Motionsensor : Component {
	private:
        const std::unique_ptr<pin::Pin> pin_;

		/*
		 * generic motion sensor initializer to avoid code duplication
		*/
		void Initialize() const;

	public:

		/*
		 * Constructor for the motion sensor
		 * @param pin constant pointer to the input pin of the motion sensor
		*/
        Motionsensor(const int8_t& pin);

		/*
		 * Constructor for the motion sensor
		 * @param pin GPIO pin of the motion sensor pin (must be a input pin if already in use)
		*/
		Motionsensor(int8_t&& pin);

        //@TODO COPY CONSTRUCTOR
		/*
		 * Method to check if the motion sensor has detected a motion or not
		 * NON BLOCKING
		 * @returns true if a motion has been detected else false
		*/
		bool MotionDetected() const;

	};
}

#endif
