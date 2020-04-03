#include "pinchecker.hpp"

bool rpicomponents::pin::PinChecker::IsValidPinValue(int pin) {
    if (pin < PIN_MIN_VALUE || pin > PIN_MAX_VALUE) return false;
    return true;
}

bool rpicomponents::pin::PinChecker::PinIsHardwarePWMCapable(int pin) {
    //PWM channel 0
    if (pin == PWM_CHANNEL0_PIN1 || pin == PWM_CHANNEL0_PIN2) {
        return true;
    }
    //PWM channel 1
    if (pin == PWM_CHANNEL1_PIN1 || pin == PWM_CHANNEL1_PIN2) {
        return true;
    }
    return false;
}
