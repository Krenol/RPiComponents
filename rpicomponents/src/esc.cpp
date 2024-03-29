#include "esc.hpp"
#include "utils/utils.hpp"
#include <iostream>
#include <unistd.h>

namespace rpicomponents
{

    void Esc::Initialize()
    {
        if (escData_.esc_min_value > escData_.esc_max_value)
        {
            throw std::invalid_argument("esc_min_value (" + std::to_string(escData_.esc_min_value) + ") > esc_max_value (" + std::to_string(escData_.esc_max_value) + ")");
        }
        if (escData_.esc_min_value < 0)
        {
            throw std::invalid_argument("ESC min value cannot be lower than 0!");
        }
        if (escData_.esc_max_value < 0)
        {
            throw std::invalid_argument("ESC max value cannot be lower than 0!");
        }
    }

    void to_json(nlohmann::json &j, const EscData &d)
    {
        j = nlohmann::json{{"esc_min_value", d.esc_min_value}, {"esc_max_value", d.esc_max_value}};
    }

    void from_json(const nlohmann::json &j, EscData &d)
    {
        j.at("esc_max_value").get_to(d.esc_max_value);
        j.at("esc_min_value").get_to(d.esc_min_value);
    }

    void Esc::Arm()
    {
        std::lock_guard<std::mutex> guard(mtx_);
        if (!is_armed_)
        {
            pin_->OutputOff();
            usleep(ESC_ARM_SLEEP_TIME_MS * 1000);
            pin_->Output(escData_.esc_max_value);
            usleep(ESC_ARM_SLEEP_TIME_MS * 1000);
            pin_->Output(escData_.esc_min_value);
            usleep(ESC_ARM_SLEEP_TIME_MS * 1000);
            is_armed_ = true;
        }
    }

    Esc::Esc(int pin, int esc_min_value, int esc_max_value) : Component(COMPONENT_ESC), escData_{EscData(esc_min_value, esc_max_value)}
    {
        pin_ = pin::PinCreator::CreatePulsePin(pin, 50);
        Initialize();
    }

    Esc::Esc(int pin, const EscData &escData) : Component(COMPONENT_ESC), escData_{EscData(escData)}
    {
        pin_ = pin::PinCreator::CreatePulsePin(pin, 50);
        Initialize();
    }

    Esc::Esc(const Esc &esc) : Esc(esc.GetPin(), esc.GetEscData())
    {
    }

    void Esc::SetOutputSpeed(int speed) const
    {
        if (!is_armed_)
        {
            throw std::logic_error("Arm ESC before setting it's speed");
        }
        pin_->Output(speed < escData_.esc_min_value ? escData_.esc_min_value : (speed > escData_.esc_max_value ? escData_.esc_max_value : speed));
    }

    int Esc::GetEscSpeed() const
    {
        return pin_->ReadPinValue();
    }

    void Esc::TurnOff() const
    {
        if (!is_armed_)
        {
            throw std::logic_error("Arm ESC before setting it's speed");
        }
        pin_->OutputOff();
    }

    const EscData &Esc::GetEscData() const
    {
        return escData_;
    }

    int Esc::GetPulseFreq() const {
        return pin_->GetMaxOutValue();
    }

    int Esc::GetPin() const
    {
        return pin_->GetPin();
    }

    void Esc::Calibrate(bool cin_on)
    {
        int calibrate_secs = 3;
        if(cin_on) {
            pin_->OutputOff();
            std::cout << "Disconnect the ESC from the battery and press enter\n";
            std::cin.get();
        }
        pin_->Output(escData_.esc_max_value);
        if(cin_on) {
            std::cout << "Connect the ESC to the battery now\n";
            std::cout << "Wait for two beeps and a falling tone, then press enter\n";
            std::cin.get();
        } else {
            usleep(calibrate_secs * 1000000);
        }
        pin_->Output(escData_.esc_min_value);
        std::cout << "Keeping ESC at it's min value for " << calibrate_secs << " seconds\n";
        usleep(calibrate_secs * 1000000);
        std::cout << "ESC calibrated successfully!\n";
        std::cout << "ESC is being armed now!\n";
        Arm();
    }
} // namespace rpicomponents