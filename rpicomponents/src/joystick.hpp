#include "component.hpp"
#include "pcf8591.hpp"
#include "button.hpp"

#ifndef RPICOMPONENTS_JOYSTICK_H
#define RPICOMPONENTS_JOYSTICK_H

namespace rpicomponents {

	constexpr const char* COMPONENT_JOYSTICK = "joystick";

	struct JoystickAxes {
		JoystickAxes(const int& x, const int& y, bool z) : x{ x }, y{ y }, z{ z }
		{

		}

        const int x{ INT32_MAX }, y{ INT32_MAX };
		const bool z{ false };
	};

	class Joystick : public Component
	{
	private:
		const std::unique_ptr<rpicomponents::Pcf8591> pcf_;
		const int pcfXPin_{ -1 }, pcfYPin_{ -1 };
		const std::unique_ptr<rpicomponents::Button> zBtn_;

		/*
		generic motion sensor initializer to avoid code duplication
		*/
		void Initialize() const;

	public:
		/*
		Constructor for Joystick component

		@param pcf_address The address of the joystick pcf
		@param pin_base The pin base of the joystick pcf
		@param pcf_x_pin The pin at the pcf to which the x axis of the joystick is connected
		@param pcf_y_pin The pin at the pcf to which the y axis of the joystick is connected
		@param gpio_z The gpio pin of the z axis of the joystick
		@param z_pud The PUD of the z axis
		*/
		Joystick(const int& pcf_address, const int& pin_base, const int& pcf_x_pin, const int& pcf_y_pin, const int& gpio_z, const int& z_pud = PUD_UP);

		/*
		Constructor for Joystick component

		@param pcf_address The address of the joystick pcf
		@param pin_base The pin base of the joystick pcf
		@param pcf_x_pin The pin at the pcf to which the x axis of the joystick is connected
		@param pcf_y_pin The pin at the pcf to which the y axis of the joystick is connected
		@param gpio_z The gpio pin of the z axis of the joystick
		@param z_pud The PUD of the z axis
		*/
		Joystick(int&& pcf_address, int&& pin_base, int&& pcf_x_pin, int&& pcf_y_pin, int&& gpio_z, int&& z_pud = PUD_UP);

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
		const int& GetPcfBase() const;

		/*
		Method to get the pcf address

		@returns the pcf address
		*/
		const int& GetPcfAddress() const;

		/*
		Method to get the pcf x pin

		@returns the pcf x pin of the joystick
		*/
		const int& GetPcfXPin() const;

		/*
		Method to get the pcf y pin

		@returns the pcf y pin of the joystick
		*/
		const int& GetPcfYPin() const;

		/*
		Method to get the gpio z pin

		@returns the gpio z pin of the joystick
		*/
		const int& GetGpioZPin() const;

		/*
		Method to get the z pud

		@returns the z pud of the joystick
		*/
		const int& GetZPud() const;
	};
}

#endif
