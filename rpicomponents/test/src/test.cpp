#include "../../include/rpicomponents/rpicomponents.hpp"
#include <thread>

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::component;
using namespace rpicomponents::pin;

static mutex mtx;

void On(Led* led, int no){
    //lock_guard<mutex> lck(mtx);

    for(auto i= 0; i <  no; i++) {
        auto on = led->IsOn();
        cout << "thread " << no << " led is " << on<<endl;
        on ? led->TurnOff() : led->TurnOn();
    }

    return;
}


int main() {
	cout << "bla\n";
    auto led = new Led(GPIO2, DIGITAL);
    //cout << btn->IsPressed()<<endl;

    for(int i = 0; i < 10; i++) {
        thread p(On, led, i);
        thread p1(On, led, i);
        p.join();
        p1.join();
    }
    delete led;
}
