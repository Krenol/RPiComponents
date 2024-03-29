/*
||
|| @file Keypad.cpp
|| @version 3.1
|| @author Mark Stanley, Alexander Brevig
|| @contact mstanley@technologist.com, alexanderbrevig@gmail.com
||
|| @description
|| | This library provides a simple interface for using matrix
|| | keypads. It supports multiple keypresses while maintaining
|| | backwards compatibility with the old single key library.
|| | It also supports user selectable pins and definable keymaps.
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
*/
#include "keypad.hpp"
#include <chrono>

// <<constructor>> Allows custom keymap, pin configuration, and keypad sizes.
rpicomponents::Keypad::Keypad(char* userKeymap, byte_key* row, byte_key* col, byte_key numRows, byte_key numCols) : Key(COMPONENT_KEYPAD) {
	rowPins = row;
	columnPins = col;
	sizeKpd.rows = numRows;
	sizeKpd.columns = numCols;
	/*
	std::vector<int> dataVec;
	dataVec.insert(dataVec.end(), &row[0], &row[numRows]);
	dataVec.insert(dataVec.end(), &col[0], &col[numCols]);
	AddPins(dataVec);
	begin(userKeymap);
	*/

	setDebounceTime(50);
	setHoldTime(500);
	keypadEventListener = 0;

	startTime = 0;
	single_key = false;
}

// Let the user define a keymap - assume the same row/column count as defined in constructor
void rpicomponents::Keypad::begin(char* userKeymap) {
	keymap = userKeymap;
}

long rpicomponents::Keypad::millis() {
	using namespace std::chrono;
	long duration = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	return duration;
}

// Returns a single key only. Retained for backwards compatibility.
char rpicomponents::Keypad::getKey() {
	single_key = true;
	if (getKeys() && key[0].stateChanged && (key[0].kstate == PRESSED)) {
		return key[0].kchar;
	}

	single_key = false;
	return NO_KEY;
}

// Populate the key list.
bool rpicomponents::Keypad::getKeys() {
	bool keyActivity = false;

	// Limit how often the keypad is scanned. This makes the loop() run 10 times as fast.
	if ((millis() - startTime) > debounceTime) {
		scanKeys();
		keyActivity = updateList();
		startTime = millis();
	}
	return keyActivity;
}

// Private : Hardware scan
void rpicomponents::Keypad::scanKeys() {
	// Re-intialize the row pins. Allows sharing these pins with other hardware.
	for (byte_key r = 0; r < sizeKpd.rows; r++) {
		pin_mode(rowPins[r], INPUT_PULLUP);
	}

	// bitMap stores ALL the keys that are being pressed.
	for (byte_key c = 0; c < sizeKpd.columns; c++) {
		pin_mode(columnPins[c], PI_OUTPUT);
		pin_write(columnPins[c], 0);	// Begin column pulse output.
		for (byte_key r = 0; r < sizeKpd.rows; r++) {
			bitWrite(bitMap[r], c, !pin_read(rowPins[r]));  // keypress is active low so invert to high.
		}
		// Set pin to high impedance input. Effectively ends column pulse.
		pin_write(columnPins[c], 1);
		pin_mode(columnPins[c], PI_INPUT);
	}
}

// Manage the list without rearranging the keys. Returns true if any keys on the list changed state.
bool rpicomponents::Keypad::updateList() {
	bool anyActivity = false;

	// Delete any IDLE keys
	for (byte_key i = 0; i < LIST_MAX; i++) {
		if (key[i].kstate == IDLE) {
			key[i].kchar = NO_KEY;
			key[i].kcode = -1;
			key[i].stateChanged = false;
		}
	}

	// Add new keys to empty slots in the key list.
	for (byte_key r = 0; r < sizeKpd.rows; r++) {
		for (byte_key c = 0; c < sizeKpd.columns; c++) {
			bool button = bitRead(bitMap[r], c);
			char keyChar = keymap[r * sizeKpd.columns + c];
			int keyCode = r * sizeKpd.columns + c;
			int idx = findInList(keyCode);
			// Key is already on the list so set its next state.
			if (idx > -1) {
				nextKeyState(idx, button);
			}
			// Key is NOT on the list so add it.
			if ((idx == -1) && button) {
				for (byte_key i = 0; i < LIST_MAX; i++) {
					if (key[i].kchar == NO_KEY) {		// Find an empty slot or don't add key to list.
						key[i].kchar = keyChar;
						key[i].kcode = keyCode;
						key[i].kstate = IDLE;		// Keys NOT on the list have an initial state of IDLE.
						nextKeyState(i, button);
						break;	// Don't fill all the empty slots with the same key.
					}
				}
			}
		}
	}

	// Report if the user changed the state of any key.
	for (byte_key i = 0; i < LIST_MAX; i++) {
		if (key[i].stateChanged) anyActivity = true;
	}
	return anyActivity;
}

// Private
// This function is a state machine but is also used for debouncing the keys.
void rpicomponents::Keypad::nextKeyState(byte_key idx, bool button) {
	key[idx].stateChanged = false;
	switch (key[idx].kstate) {
	case IDLE:
		if (button == CLOSED) {
			transitionTo(idx, PRESSED);
			holdTimer = millis();
		}		// Get ready for next HOLD state.
		break;
	case PRESSED:
		if ((millis() - holdTimer) > holdTime)	// Waiting for a key HOLD...
			transitionTo(idx, HOLD);
		else if (button == OPEN)				// or for a key to be RELEASED.
			transitionTo(idx, RELEASED);
		break;
	case HOLD:
		if (button == OPEN) {

			transitionTo(idx, RELEASED);
		}
		break;
	case RELEASED:
		transitionTo(idx, IDLE);
		break;
	}
}

// New in 2.1
bool rpicomponents::Keypad::isPressed(char keyChar) {
	for (byte_key i = 0; i < LIST_MAX; i++) {
		if (key[i].kchar == keyChar) {
			if ((key[i].kstate == PRESSED) && key[i].stateChanged)
				return true;
		}
	}
	return false;	// Not pressed.
}

// Search by character for a key in the list of active keys.
// Returns -1 if not found or the index into the list of active keys.
int rpicomponents::Keypad::findInList(char keyChar) {
	for (byte_key i = 0; i < LIST_MAX; i++) {
		if (key[i].kchar == keyChar) {
			return i;
		}
	}
	return -1;
}

// Search by code for a key in the list of active keys.
// Returns -1 if not found or the index into the list of active keys.
int rpicomponents::Keypad::findInList(int keyCode) {
	for (byte_key i = 0; i < LIST_MAX; i++) {
		if (key[i].kcode == keyCode) {
			return i;
		}
	}
	return -1;
}

// New in 2.0
char rpicomponents::Keypad::waitForKey() {
	char waitKey = NO_KEY;
	while ((waitKey = getKey()) == NO_KEY);	// Block everything while waiting for a keypress.
	return waitKey;
}

// Backwards compatibility function.
rpicomponents::KeyState rpicomponents::Keypad::getState() {
	return key[0].kstate;
}

// The end user can test for any changes in state before deciding
// if any variables, etc. needs to be updated in their code.
bool rpicomponents::Keypad::keyStateChanged() {
	return key[0].stateChanged;
}

// The number of keys on the key list, key[LIST_MAX], equals the number
// of byte_keys in the key list divided by the number of byte_keys in a Key object.
byte_key rpicomponents::Keypad::numKeys() {
	return sizeof(key) / sizeof(Key);
}

// Minimum debounceTime is 1 mS. Any lower *will* slow down the loop().
void rpicomponents::Keypad::setDebounceTime(uint debounce) {
	debounce < 1 ? debounceTime = 1 : debounceTime = debounce;
}

void rpicomponents::Keypad::setHoldTime(uint hold) {
	holdTime = hold;
}

void rpicomponents::Keypad::addEventListener(void (*listener)(char)) {
	keypadEventListener = listener;
}

void rpicomponents::Keypad::transitionTo(byte_key idx, KeyState nextState) {
	key[idx].kstate = nextState;
	key[idx].stateChanged = true;

	// Sketch used the getKey() function.
	// Calls keypadEventListener only when the first key in slot 0 changes state.
	if (single_key) {
		if ((keypadEventListener != NULL) && (idx == 0)) {
			keypadEventListener(key[0].kchar);
		}
	}
	// Sketch used the getKeys() function.
	// Calls keypadEventListener on any key that changes state.
	else {
		if (keypadEventListener != NULL) {
			keypadEventListener(key[idx].kchar);
		}
	}
}

void rpicomponents::pin_mode(byte_key pinNum, byte_key mode) {
	if (mode == INPUT_PULLUP) {
		gpioSetMode(pinNum, PI_INPUT);
		gpioSetPullUpDown(pinNum, PI_PUD_UP);
	}
	else {
		gpioSetMode(pinNum, mode);
	}
}
void rpicomponents::pin_write(byte_key pinNum, bool level) {
	gpioWrite(pinNum, level);
}
int  rpicomponents::pin_read(byte_key pinNum) {
	return gpioRead(pinNum);
}
