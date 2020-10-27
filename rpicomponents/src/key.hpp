/*
||
|| @file Key.h
|| @version 1.0
|| @author Mark Stanley
|| @contact mstanley@technologist.com
||
|| @description
|| | Key class provides an abstract definition of a key or button
|| | and was initially designed to be used in conjunction with a
|| | state-machine.
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU Lesser General Public
|| | License as published by the Free Software Foundation; version
|| | 2.1 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | Lesser General Public License for more details.
|| |
|| | You should have received a copy of the GNU Lesser General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
|| #
||
|| Modified by Krenol
*/

#include "component.hpp"

#ifndef RPICOMPONENTS_KEY_H
#define RPICOMPONENTS_KEY_H

#define byte_key unsigned char 
#define OPEN 0
#define CLOSED 1
typedef unsigned int uint;

namespace rpicomponents {
	constexpr const char* COMPONENT_KEY = "key";
	constexpr const char NO_KEY = '\0';
    enum KeyState { IDLE, PRESSED, HOLD, RELEASED };


	class Key : public Component {
	public:
		// members
		char kchar;
		int kcode;
		KeyState kstate;
		bool stateChanged;

		// methods
		Key();
		Key(char userKeyChar);
		void UpdateKey(char userKeyChar, KeyState userState, bool userStatus);

	protected:
		/*
		Constructor for keypad
		@param compname The name of the child's component
		*/
		Key(const std::string& compname);

	private:
		/*
		Method to init key class values
		*/
		void Initialize();
	};
}

#endif
