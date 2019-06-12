#include "rpicomponents/rpicomponents.hpp"
#include <thread>
#include <cassert>

 

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::pin;
using namespace rpicomponents::pin::utils;

mutex mtx;

void On(Led* led, int no){
    lock_guard<mutex> lck(mtx);

    for(auto i= 0; i <  no; i++) {
        auto on = led->IsOn();
        cout << "thread " << no << " led is " << on<<endl;
        on ? led->TurnOff() : led->TurnOn();
    }

    return;
}


int main() {
    auto led = new Led(GPIO2, DIGITAL_MODE);
	PCF8574 pcf(0x48);
    PCF8591 pcf1(0x49, 124);
	
    //cout << btn->IsPressed()<<endl;
	UltrasonicSensor uss (GPIO0, GPIO1);
    for(int i = 0; i < 10; i++) {
        thread p(On, led, i);
        thread p1(On, led, i);
        p.join();
        p1.join();
    }
	pcf1.WriteToPcfPin(5);
	cout << "500 mm are " << uss.UnitConverter(500, UNIT_MM, UNIT_M) << " m\n";
	cout << pcf.ToString() << endl;
	cin.get();
    delete led;
}
