#include "component.hpp"

#ifndef RPICOMPONENTS_MOTOR_H
#define RPICOMPONENTS_MOTOR_H

namespace rpicomponents {
    constexpr const char* COMPONENT_MOTOR = "motor";

	class Motor : public Component {
	protected:
		virtual ~Motor() = 0; //virtual protected destructor to make class abstract

	public:
        /*
         Constructor for this component

         @param comp_name The component name
        */
        Motor(const std::string& comp_name);

		/*
		Method to stop the motor
		*/
		virtual void Stop() const = 0;

	};
}

#endif // RPICOMPONENTS_MOTOR_H
