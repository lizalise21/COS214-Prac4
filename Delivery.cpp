#include "Delivery.h"
#include "ConcreteStates.h"
#include <iostream>

Delivery::Delivery() : currentState(new CreatedState()), location("Depot") {
    history.push_back("Created");
}

Delivery::~Delivery() {
    delete currentState;
}

void Delivery::setState(DeliveryState* state) {
    delete currentState;
    currentState = state;
    history.push_back(currentState->getName());
}

std::string Delivery::getStateName() const {
    return currentState->getName();
}

void Delivery::pickUp() { currentState->pickUp(this); }
void Delivery::departForTransit() { currentState->departForTransit(this); }
void Delivery::markDelivered() { currentState->markDelivered(this); }

void Delivery::updateLocation(const std::string& loc) {
    location = loc;
    std::cout << "Location updated to " << loc << "\n";
}