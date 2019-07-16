#include "q74hc595.hpp"

rpicomponents::Q74Hc595::Q74Hc595(const pin::Pin* ds, const pin::Pin* stcp, const pin::Pin* shcp) : Component("q74hc595"), ds_{ds}, stcp_{stcp}, shcp_{shcp}
{

}