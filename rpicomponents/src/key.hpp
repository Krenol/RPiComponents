#include "component.hpp"

#ifndef RPICOMPONENTS_KEY_H
#define RPICOMPONENTS_KEY_H

namespace rpicomponents {
	constexpr const char* COMPONENT_KEY = "key";

    enum KeyState { IDLE, PRESSED, HOLD, RELEASED };

	class Key : public Component {
	private:
		mutable std::atomic_char userChar_;
        mutable std::atomic<rpicomponents::KeyState> keyState_;
		mutable std::atomic_bool stateChanged_;


	public:
		/*
		Default constructor
		*/
		Key();

		/*
		Constructor

		@param userChar: The char of the key
		*/
		Key(const char& userChar);

		/*
		Constructor

		@param userChar: The char of the key
		*/
		Key(char&& userChar);

		/*
		Constructor

		@param key: The key to be copied
		*/
		Key(const Key& key);

		/*
		Method to update the key
		
		@param userChar: The char that was pressed
		@param userState: The state of the key
		@param userStatus: bool to set if key state has changed
		*/
		void UpdateKey(const char& userChar, const KeyState& userState, bool userStatus) const;

		/*
		Method to get the current char of the key

		@returns the current key char
		*/
		char GetChar() const;

		/*
		Method to get the current key state

		@returns the current key state
		*/
		KeyState GetState() const;

		/*
		Method to check if key changed

		@returns true if key changed else false
		*/
		bool IsChanged() const;
	};
}

#endif
