#include "DeliveryState.h"
#include <iostream>

DeliveryState::~DeliveryState() {}

void DeliveryState::pickUp(Delivery* context) {
    std::cout << "Invalid transition: cannot pick up from state " << getName() << "\n";
}
void DeliveryState::departForTransit(Delivery* context) {
    std::cout << "Invalid transition: cannot depart for transit from state " << getName() << "\n";
}
void DeliveryState::markDelivered(Delivery* context) {
    std::cout << "Invalid transition: cannot mark delivered from state " << getName() << "\n";
}