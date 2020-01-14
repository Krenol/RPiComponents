#include "component.hpp"
#include "pcf8591.hpp"
#include "button.hpp"

#ifndef RPICOMPONENTS_JOYSTICK_H
#define RPICOMPONENTS_JOYSTICK_H

namespace rpicomponents {

	constexpr const char* COMPONENT_JOYSTICK = "joystick";

	struct JoystickAxes {
		JoystickAxes(int x, int y, bool z) : x{ x }, y{ y }, z{ z }
		{

		}

        const int x{ INT32_MAX }, y{ INT32_MAX };
		const bool z{ false };
	};

	class Joystick : public Component
	{
	private:
		const std::shared_ptr<rpicomponents::Pcf8591> pcf_;
		const int pcfXPin_{ -1 }, pcfYPin_{ -1 };
		const std::shared_ptr<rpicomponents::Button> zBtn_;

		/*
		generic motion sensor initializer to avoid code duplication
		*/
        void Initialize();

	public:
		/*
		Constructor for Joystick component

		@param pcf The used pcf of the joystick
		@param pcf_x_pin The pin at the pcf to which the x axis of the joystick is connected
		@param pcf_y_pin The pin at the pcf to which the y axis of the joystick is connected
		@param zBtn the z pin can be represented as a button
		*/
		Joystick(std::shared_ptr<rpicomponents::Pcf8591> pcf, int pcf_x_pin, int pcf_y_pin, std::shared_ptr<rpicomponents::Button> zBtn);

		/*
		Copy constructor
		@param joystick The joystick to be copied
		*/
		Joystick(const Joystick& joystick);

		/*
		Method to read the value of the joystick's x axis

		@returns the read x axis value
		*/
		int ReadXAxis() const;

		/*
		Method to read the value of the joystick's y axis

		@returns the read y axis value
		*/
		int ReadYAxis() const;

		/*
		Method to read the value of the joystick's z axis

		@returns the read z axis value
		*/
		bool ReadZAxis() const;

		/*
		Method to read the values of the joystick's axes

		@returns the read axes in a JoystickAxes struct
		*/
		JoystickAxes ReadAxes() const;

		/*
		Method to get the pcf pin base

		@returns the pcf pin base
		*/
		const std::shared_ptr<Pcf8591>& GetPcf() const;

		/*
		Method to get the gpio z button of the joystick

		@returns the reference to the shared_ptr of the button
		*/
		const std::shared_ptr<Button>& GetZBtn() const;

		/*
		Method to get the pcf x pin
		@returns the pcf y pin of the joystick
		*/
		int GetPcfXPin() const;

		/*
		Method to get the pcf y pin
		@returns the pcf y pin of the joystick
		*/
		int GetPcfYPin() const;
	};
}

#endif
