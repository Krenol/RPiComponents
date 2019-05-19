#include "../../include/rpicomponents/rpicomponents.hpp"
#include <thread>

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
	cout << "bla\n";
    auto led = new Led(GPIO2, DIGITAL_MODE);
    //cout << btn->IsPressed()<<endl;
	UltrasonicSensor uss (GPIO0, GPIO1);
    for(int i = 0; i < 10; i++) {
        thread p(On, led, i);
        thread p1(On, led, i);
        p.join();
        p1.join();
    }
	
	cout << "500 mm are " << uss.UnitConverter(500, UNIT_MM, UNIT_M) << " m\n";
	cin.get();
    delete led;
}
