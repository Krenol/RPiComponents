#include "component.hpp"
#include "pcf8591.hpp"
#include "button.hpp"
#include <nlohmann/json.hpp>

#ifndef RPICOMPONENTS_JOYSTICK_H
#define RPICOMPONENTS_JOYSTICK_H

namespace rpicomponents {

	constexpr const char* COMPONENT_JOYSTICK = "joystick";

	struct JoystickAxes {
        int x{ INT32_MAX }, y{ INT32_MAX };
		bool z{ false };
	};

	void to_json(nlohmann::json& j, const JoystickAxes& d) {
        j = nlohmann::json{{"x", d.x}, {"y", d.y}, {"z", d.z}};
    }

    void from_json(const nlohmann::json& j, JoystickAxes& d) {
        j.at("x").get_to(d.x);
        j.at("y").get_to(d.y);
		j.at("z").get_to(d.z);
    }

	class Joystick : public Component
	{
	private:
		const std::shared_ptr<rpicomponents::Pcf8591> pcf_;
		const int pcfXPin_{ -1 }, pcfYPin_{ -1 };
		rpicomponents::Button zBtn_;

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
		@param zBtn_pin z pin 
		*/
		Joystick(std::shared_ptr<rpicomponents::Pcf8591> pcf, int pcf_x_pin, int pcf_y_pin, std::shared_ptr<pin::Pin> zBtn_pin);

		/*
		Constructor for Joystick component

		@param pcf The used pcf of the joystick
		@param pcf_x_pin The pin at the pcf to which the x axis of the joystick is connected
		@param pcf_y_pin The pin at the pcf to which the y axis of the joystick is connected
		@param zBtn z pin represented as a button
		*/
		Joystick(std::shared_ptr<rpicomponents::Pcf8591> pcf, int pcf_x_pin, int pcf_y_pin, const rpicomponents::Button& zBtn);

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
		Method to read the values of the joystick's axes

		@returns the read axes as JSON
		*/
		nlohmann::json ReadAxesJSON() const;

		/*
		Method to read the values of the joystick's axes

		@param out: Struct containing the read axes in a JoystickAxes struct
		*/
		void ReadAxes(JoystickAxes& out) const;

		/*
		Method to read the values of the joystick's axes

		@param out: JSON containing the read axes as JSON
		*/
		void ReadAxesJSON(nlohmann::json& out) const;

		/*
		Method to get the pcf pin base

		@returns the pcf pin base
		*/
		const std::shared_ptr<Pcf8591>& GetPcf() const;

		/*
		Method to get the gpio z button of the joystick

		@returns the reference to the unique_ptr of the button
		*/
		const Button& GetZBtn() const;

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
