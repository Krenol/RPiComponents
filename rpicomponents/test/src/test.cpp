#include "rpicomponents/rpicomponents.hpp"
#include <thread>
#include <cassert>

 


using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

std::mutex mtx;

void On(Led* led, int no){
	std::lock_guard<std::mutex> lck(mtx);

    for(auto i= 0; i <  no; i++) {
        auto on = led->IsOn();
		std::cout << "thread " << no << " led is " << on<< std::endl;
        on ? led->TurnOff() : led->TurnOn();
    }

    return;
}


int main() {
    auto led = new Led(GPIO2, DIGITAL_MODE);
	PCF8574 pcf(0x48);
    PCF8591 pcf1(0x49, 124);
	MPU6050 mpu(0x51);
    //cout << btn->IsPressed()<<endl;
	UltrasonicSensor uss (GPIO0, GPIO1);
    for(int i = 0; i < 10; i++) {
		std::thread p(On, led, i);
		std::thread p1(On, led, i);
        p.join();
        p1.join();
    }

	std::cout << "500 mm are " << uss.UnitConverter(500, UNIT_MM, UNIT_M) << " m\n";
	std::cout << pcf.ToString() << std::endl;
	std::cin.get();
    delete led;
}
