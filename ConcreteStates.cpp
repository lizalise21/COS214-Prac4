#include "ConcreteStates.h"
#include "Delivery.h"
#include <iostream>

void CreatedState::pickUp(Delivery* context) {
    std::cout << "Shipment picked up.\n";
    context->setState(new PickedUpState());
}
std::string CreatedState::getName() const { return "Created"; }

void PickedUpState::departForTransit(Delivery* context) {
    std::cout << "Shipment now in transit.\n";
    context->setState(new TransitState());
}
std::string PickedUpState::getName() const { return "PickedUp"; }

void TransitState::markDelivered(Delivery* context) {
    std::cout << "Shipment delivered.\n";
    context->setState(new DeliveredState());
}
std::string TransitState::getName() const { return "InTransit"; }

std::string DeliveredState::getName() const { return "Delivered"; }