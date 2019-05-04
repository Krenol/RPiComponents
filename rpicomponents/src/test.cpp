#include "../include/rpicomponents/rpicomponents.hpp"

using namespace std;
using namespace rpicomponents;
using namespace rpicomponents::component;
using namespace rpicomponents::pin;

int main() {
	cout << "bla\n";
    auto btn = new Button(GPIO2, PUD_UP);
    cout << btn->IsPressed()<<endl;
	cin.get();
    delete btn;
}
